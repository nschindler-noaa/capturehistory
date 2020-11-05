/*
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unistd.h>
#include <QStringList>

#include <charutil.h>
#include <Sites.h>
#include <CbrPit.h>
#include <ObsSequence.h>
#include <StringManip.h>

#include "Dsplit.h"
#include "PitProSettings.h"
#include "PPTag.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::ends;
using std::stringstream;
using std::list;
using namespace cbr;

#ifdef W //WIN32
#define sprintf sprintf_s
#define unlink _unlink
#endif

const int Dsplit::nfilelim = 16;

Dsplit::Dsplit (PPOutputMaker& out) : out(out), targetSite(0), cutoffDate(PP_NULL_CUTOFF_DATE) {
    PitProSettings& settings = PitProSettings::getInstance();
    string siteName = settings.getValue(PitProSettings::Dsplit);
    Sites* sites = Sites::getInstance();
    targetSite = sites->getSite( siteName.c_str() );
    if (!targetSite)
        out.write("Unknown observation site '" + siteName + "'.", PPOutputMaker::Error);

    // get cutoff date
    if (settings.isChecked (PitProSettings::JuvenileCutoffSwitch)) {
        string cutoff =  settings.getValue( PitProSettings::JuvenileCutoffDate );
        if ( !cutoff.empty()) {
            DateConverter dc( cutoff.c_str() );
            ObsSequence::setJuvenileCutoffDate( dc.getTime() );
        }
    }
    else if (  settings.isChecked( PitProSettings::MigrationYearSwitch ) ) {
        string my = settings.getValue( PitProSettings::MigrationYear );
        if ( my.size() == 4 )
            ObsSequence::setMigrationYear( fromString<int>( my ) );
    }

    cutoffDate = ObsSequence::getCutoffDate();

    // set paths
    outDir = settings.getValue(PitProSettings::OutputDir);
    dataDir = settings.getValue(PitProSettings::DataDir);
    singleCoilSwitch = (settings.getIntValue(PitProSettings::SingleCoilSwitch) == 1);
}

Dsplit::~Dsplit() {
    targetSite = 0;
    cutoffDate = PP_NULL_CUTOFF_DATE;
    outDir = "";
    dataDir = "";
    codel.clear();
}


void Dsplit::split(const RunConfigVector& runConfigVector  ) {
    runItem = runConfigVector.at(0);

    out.write("Splitting \"" + runItem.obs + "\" file...");
    splitObs();

    out.write("Splitting \"" + runItem.tag + "\" file...");
    splitTag();

   if ( codel.size() == 0 ) 
       out.write("No files found.", PPOutputMaker::Error);
   else {
       // Read and parse obs data
       out.write( "Parsing...");
       parseData();

       out.write("Cleaning temporary files...");
       cleanupData();
   }
}

void Dsplit::splitObs() {
    string obsfile = dataDir + "/" + runItem.obs;
    std::ifstream in (obsfile.c_str ());
    if (!in)
        out.write ("Error. Unable to open file \"" + obsfile + "\".");
    else 
    {
        string line;
        int row = 0;
        StringVector fnl;
        OFileList ofilel;
        string code;

        while ( getline( in, line ) ) {
            ++row;
            stringstream instream( line );
            PPObs obs;
            instream >> obs;

            if ( !obs.isOk() ) 
                out.write( "Observation file error on line " + row, PPOutputMaker::Warning );
            else {
                code = Dsplit::getSplitCode( obs.getPitCode() );
                if (find( codel.begin(), codel.end(), code) == codel.end()) {
                    codel.push_back(code);
                }

                string outfile =  obsfile + "." + code;
                ofstream& ofs = getOFStream(ofilel, fnl, outfile);
                ofs << obs << endl;
            }
        }
        in.close();
    }
}


void Dsplit::splitTag()
{
    string tagfile = dataDir + "/" + runItem.tag;
    std::ifstream in (tagfile.c_str ());
    if (!in)
        out.write ("Error. Unable to open file \"" + tagfile + "\".");
    else 
    {
        PPObs obs;
        string line;
        int row = 0;
        StringVector fnl;
        OFileList ofilel;
        string code;

        while ( getline( in, line ) ) {
            ++row;
            stringstream instream( line );
            PPTag tag;
            instream >> tag;

            if ( !tag.isOk() ) 
                out.write( "Tag file error on line " + row, PPOutputMaker::Warning );
            else {
                code = Dsplit::getSplitCode( tag.getPitCode() );
                if (find( codel.begin(), codel.end(), code) == codel.end()) {
                    codel.push_back(code);
                }

                string outfile = tagfile + "." + code;
                ofstream& ofs = getOFStream(ofilel, fnl, outfile);
                ofs << tag << endl;
            }
        }
        in.close();
    }
}



void Dsplit::parseData() {
    OFileList obs_ofilel;
    OFileList tag_ofilel;
    StringVector ofnl;
    StringVector tfnl;

    for ( StringVector::const_iterator it = codel.begin(); it != codel.end(); it++ ) {
        string code = *it;

        ObsList obsl;
        PCodeList pcl;      

        // parse the obs file (by pitcode key) and write the
        // new obs files (by obsdate at target site)
        string obsfile = dataDir + "/" + runItem.obs + "." + code;
        parseObs(obsl, pcl, obsfile);
        writeObs(obs_ofilel, ofnl, pcl, obsl);

        // read the tag file (by pitcode key) and write the
        // new tag files (by obsdate at target site)
        string tagfile = dataDir + "/" + runItem.tag + "." + code;
        writeTag(tag_ofilel, tfnl, pcl, tagfile);
    }
}


void Dsplit::parseObs(ObsList& obsl, PCodeList& pcl, const string& obsfile)
{
    std::ifstream in (obsfile.c_str ());
    if (!in) {
        out.write("Error. Unable to open file \"" + obsfile + "\".", PPOutputMaker::Error);
    }
    else {
        out.write("Parsing \"" + obsfile + "\"...");
        Sites* sites = Sites::getInstance();

        string line;
        while ( getline( in, line ) ) {
            stringstream instream( line );
            PPObs obs;
            instream >> obs;

            if ( obs.isOk() ) {
                Site* currentSite = sites->getSite( obs.getObsSite().c_str() );
                if ( !currentSite ) 
                    continue;

                /* current site equal to target site */
                if ( currentSite == targetSite )  {
                    double obsTime = obs.getTime();
                    if (cutoffDate == PP_NULL_CUTOFF_DATE || obsTime < cutoffDate) {
                        const string& pitCode = obs.getPitCode();
                        const string& obsSite = obs.getObsSite();
                        const string& coil = obs.getCoil();
                        
                        CbrPit::Outcome oc = sites->getOutcome( obsSite.c_str(), coil.c_str(), obsTime );

                        PCodeList::iterator it = find(pcl.begin(), pcl.end(), pitCode.c_str() );
                        if ( it == pcl.end()) {
                            PCode pc( obs.getPitCode(), targetSite );
                            if (singleCoilSwitch) {
                                pc.addRecord(oc, obsTime);
                            }
//                            pc.addRecord( oc, obsTime );
                            pcl.push_back(pc);
                        }
                        else {
                            PCode& pc = *it;
                            pc.addRecord( oc, obsTime );
                        }
                    }
                }
                /* current site downstream of target site */
                else if ( currentSite->isDownstream( targetSite ) ) {
                    obsl.push_back(obs);
                }
            }
        }

        in.close();

    }

    for (PCodeList::iterator it = pcl.begin(); it != pcl.end(); ++it) {
        (*it).compress();
    }
}


void Dsplit::writeObs(OFileList& ofilel, StringVector& ofnl, PCodeList& pcl, ObsList& obsl) {
    string name = runItem.name;
    string site = targetSite->getShortName();

    PCodeList::iterator pc_it = pcl.end();
    for ( ObsList::iterator obs_it = obsl.begin(); obs_it != obsl.end(); obs_it++ ) {
        PPObs& obs = *obs_it;

        // if this is a new pitcode, look up it's corresponding PCode object
        if ( pc_it == pcl.end() || (*pc_it).getPitcode().compare( obs.getPitCode() ) != 0 )
            pc_it = find( pcl.begin(), pcl.end(), obs.getPitCode().c_str() );

        if ( pc_it != pcl.end() ) {
            PCode& pc = *pc_it;
            if (pc.isReturned()) {
                const DateConverter date(pc.getTime());
                MBuf fileName;
                sprintf(fileName, "%s/%s.%s.%04d%02d%02d.obs", outDir.c_str(), site.c_str(), name.c_str(),
                    date.year(), date.month(), date.day() );
                getOFStream(ofilel, ofnl, fileName) << obs << endl;
            }
        }
    }
}


//
// writeTag
//
void Dsplit::writeTag(OFileList& ofilel, StringVector& tfnl, PCodeList& pcl, const string& tagfile)
{
    string name = runItem.name;
    string site = targetSite->getShortName();

    std::ifstream in (tagfile.c_str ());
    if (!in) {
        out.write("Error. Unable to open file \"" + tagfile + "\".", PPOutputMaker::Error);
    }
    else {
        out.write("Parsing \"" + tagfile + "\"...");

        string line;
        PCodeList::iterator pc_it = pcl.end();
        while ( getline( in, line ) ) {
            stringstream instream( line );
            PPTag tag;
            instream >> tag;

            if ( tag.isOk() ) {
                if ( pc_it == pcl.end() || (*pc_it).getPitcode().compare( tag.getPitCode() ) != 0 ) 
                    pc_it = find( pcl.begin(), pcl.end(), tag.getPitCode().c_str() );

                if ( pc_it != pcl.end() ) {
                    PCode& pc = *pc_it;
                    if (pc.isReturned()) {
                        const DateConverter date( pc.getTime() );
                        MBuf fileName;
                        sprintf(fileName, "%s/%s.%s.%04d%02d%02d.tag", outDir.c_str(), site.c_str(), name.c_str(),
                            date.year(), date.month(), date.day() );                        getOFStream(ofilel, tfnl, fileName) << tag << endl;
                    }
                }
            }
        }
        in.close();
    }
}


void Dsplit::cleanupData() {
    for ( StringVector::const_iterator it = codel.begin(); it != codel.end(); it++ ) {
        const string& code = *it;
        string obsfile = dataDir + "/" + runItem.obs + "." + code;
        string tagfile = dataDir + "/" + runItem.tag + "." + code;

        unlink(obsfile.c_str());
        unlink(tagfile.c_str());
    }
}


string Dsplit::getSplitCode(const string& pitcode) {
    return pitcode.substr(pitcode.size() - 1, 1);
}

//
// getOFStream
//
// Keep a list (of limited length) with open file pointers so
// that it isn't necessary to open the files each time we want to
// read or write something.
//

ofstream& Dsplit::getOFStream(OFileList& ofilel, StringVector& fnl, const string& filen)
{
    OFileList::iterator it1 = find( ofilel.begin(), ofilel.end(), filen);   
    if ( it1 != ofilel.end() ) {
        OFile& ofile = *it1;
        return ofile.getStream();
    }
    else {
        // make a new OFile for this file name
        if (ofilel.size() == static_cast<size_t>(nfilelim) )
            ofilel.pop_back();

        char mode;
        if (find(fnl.begin(), fnl.end(), filen) != fnl.end()) 
            mode = 'a';
        else {
            mode = 'w';
            fnl.insert(fnl.begin(), filen);
        }

        ofilel.insert(ofilel.begin(), OFile(filen));
        OFile& ofile = ofilel.front();
        ofile.open(mode);
        return ofile.getStream();

    }

}

