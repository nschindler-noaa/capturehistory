/*
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <unistd.h>

#include <QStringList>
#include <QStringRef>

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

Dsplit::Dsplit (PPOutputMaker& out_) : out(out_), targetSite(nullptr), cutoffDate(PP_NULL_CUTOFF_DATE) {
    PitProSettings& settings = PitProSettings::getInstance();
    QString siteName = settings.getValue(PitProSettings::Dsplit);
    Sites* sites = Sites::getInstance();
    targetSite = sites->getSite(siteName);
    if (!targetSite)
        out.write("Unknown observation site '" + siteName + "'.", PPOutputMaker::Error);

    // get cutoff date
    if (settings.isChecked(PitProSettings::JuvenileCutoffSwitch)) {
        QString cutoff =  settings.getValue( PitProSettings::JuvenileCutoffDate );
        if (!cutoff.isEmpty()) {
            DateConverter dc(cutoff);
            ObsSequence::setJuvenileCutoffDate(dc.getTime());
        }
    }
    else if (settings.isChecked(PitProSettings::MigrationYearSwitch)) {
        QString my = settings.getValue(PitProSettings::MigrationYear);
        if (my.size() == 4)
            ObsSequence::setMigrationYear(my.toInt());
    }

    cutoffDate = ObsSequence::getCutoffDate();

    // set paths
    outDir = settings.getValue(PitProSettings::OutputDir);
    dataDir = settings.getValue(PitProSettings::DataDir);
}


void Dsplit::split(const RunConfigVector& runConfigVector  ) {
    runItem = runConfigVector.at(0);

    out.write("Splitting \"" + runItem.obs + "\" file...");
    splitObs();

    out.write("Splitting \"" + runItem.tag + "\" file...");
    splitTag();

   if ( codel.size() == 0 )
       out.write(QString("No files found."), PPOutputMaker::Error);
   else {
       // Read and parse obs data
       out.write(QString("Parsing..."));
       parseData();

       out.write(QString("Cleaning temporary files..."));
       cleanupData();
   }
}

void Dsplit::splitObs() {
    QString msg;
    QString obsfile = dataDir + "/" + runItem.obs;
    std::ifstream in (obsfile.toStdString());
    if (!in)
        out.write ("Error. Unable to open file \"" + obsfile + "\".");
    else
    {
//        string ln;
        QString line;
        int row = 0;
        QStringList fnl;
        OFileList ofilel;
        QString code;
        PPObs obs;

        while (!in.eof()) { //getline(in, ln)) { in.eof();
            ++row;
//            line = QString(ln.data());
//            stringstream instream( line );
            if (!obs.read(in)) { //;
//            instream >> obs;

//            if ( !obs.isOk() ) {
                msg = QString(QString("Observation file error on line %1").arg(QString::number(row)));
                out.write(msg, PPOutputMaker::Warning);
//                out.write( "Observation file error on line " + row, PPOutputMaker::Warning );
            }
            else {
                code = Dsplit::getSplitCode(obs.getPitCode());
                if (!codel.contains(code))
                    codel.append(code);
//                if (find( codel.begin(), codel.end(), code) == codel.end()) {
//                    codel.push_back(code);
//                }

                QString outfile =  obsfile + "." + code;
                ofstream& ofs = getOFStream(ofilel, fnl, outfile);
                ofs << obs << endl;
            }
        }
        in.close();
    }
}


void Dsplit::splitTag()
{
    QString msg;
    QString tagfile = dataDir + "/" + runItem.tag;
    std::ifstream in (tagfile.toStdString());
    if (!in)
        out.write ("Error. Unable to open file \"" + tagfile + "\".");
    else
    {
        PPObs obs;
        QString line;
        int row = 0;
        QStringList fnl;
        OFileList ofilel;
        QString code;
        PPTag tag;

        while (!in.eof()) { // getline( in, line ) ) {
            ++row;
//            stringstream instream( line );
//            instream >> tag;
            if (!tag.read(in)) {

//            if ( !tag.isOk() ) {
                msg = QString(QString("Tag file error on line %1").arg(QString::number(row)));
                out.write(msg, PPOutputMaker::Warning);
//                out.write( "Tag file error on line " + row, PPOutputMaker::Warning );
            }
            else {
                code = Dsplit::getSplitCode(tag.getPitCode());
                if (!codel.contains(code))
                    codel.append(code);
//                if (find( codel.begin(), codel.end(), code) == codel.end()) {
//                    codel.push_back(code);
//                }

                QString outfile = tagfile + "." + code;
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
    QStringList ofnl;
    QStringList tfnl;

    for (QStringList::const_iterator it = codel.begin(); it != codel.end(); it++) {
        QString code = *it;

        ObsList obsl;
        PCodeList pcl;

        // parse the obs file (by pitcode key ) and write the
        // new obs files (by obsdate at target site )
        QString obsfile = dataDir + "/" + runItem.obs + "." + code;
        parseObs(obsl, pcl, obsfile);
        writeObs(obs_ofilel, ofnl, pcl, obsl);

        // read the tag file (by pitcode key) and write the
        // new tag files (by obsdate at target site )
        QString tagfile = dataDir + "/" + runItem.tag + "." + code;
        writeTag(tag_ofilel, tfnl, pcl, tagfile);
    }
}


void Dsplit::parseObs(ObsList& obsl, PCodeList& pcl, const QString obsfile)
{
    std::ifstream in (obsfile.toStdString());
    PPObs obs;
    if (!in) {
        out.write("Error. Unable to open file \"" + obsfile + "\".", PPOutputMaker::Error);
    }
    else {
        out.write("Parsing \"" + obsfile + "\"...");
        Sites* sites = Sites::getInstance();

//        string line;
        while (!in.eof()) { //getline(in, line)) {
//            stringstream instream( line );
//            instream >> obs;
            if (obs.read(in)) {

//            if (obs.isOk()) {
                Site* currentSite = sites->getSite(obs.getObsSite());
                if (!currentSite)
                    continue;

                /* current site equal to target site */
                if ( currentSite == targetSite )  {
                    double obsTime = obs.getTime();
                    if (cutoffDate < -.9 || obsTime < cutoffDate) {// == PP_NULL_CUTOFF_DATE || obsTime < cutoffDate) {
                        const QString& pitCode = obs.getPitCode();
                        const QString& obsSite = obs.getObsSite();
                        const QString& coil = obs.getCoil();

                        CbrPit::Outcome oc = sites->getOutcome(obsSite, coil, obsTime);

                        PCodeList::iterator it = find(pcl.begin(), pcl.end(), pitCode.toStdString());
                        if ( it == pcl.end()) {
                            PCode pc( obs.getPitCode(), targetSite );
                            pcl.push_back(pc);
                            pc.addRecord( oc, obsTime );
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


void Dsplit::writeObs(OFileList& ofilel, QStringList& ofnl, PCodeList& pcl, ObsList& obsl) {
    QString name = runItem.name;
    QString site = targetSite->getShortName();
    PPObs obs;

    PCodeList::iterator pc_it = pcl.end();
    for (ObsList::iterator obs_it = obsl.begin(); obs_it != obsl.end(); obs_it++) {
         obs = *obs_it;

        // if this is a new pitcode, look up it's corresponding PCode object
        if (pc_it == pcl.end() || (*pc_it).getPitcode().compare(obs.getPitCode()) != 0)
            pc_it = find(pcl.begin(), pcl.end(), obs.getPitCode().toStdString());

        if (pc_it != pcl.end()) {
            PCode& pc = *pc_it;
            if (pc.isReturned()) {
                const DateConverter date(pc.getTime());
                QString filename(QString("%1/%2.%3.%4%5%6.obs").arg(outDir, site, name).arg(
                                     date.year()).arg(date.month()).arg(date.day()));

//                MBuf fileName;
//                sprintf(fileName, "%s/%s.%s.%04d%02d%02d.obs", outDir.c_str(), site.c_str(), name.c_str(),
//                    date.year(), date.month(), date.day() );
                getOFStream(ofilel, ofnl, filename) << obs << endl;
            }
        }
    }
}


//
// writeTag
//
void Dsplit::writeTag(OFileList& ofilel, QStringList& tfnl, PCodeList& pcl, const QString tagfile)
{
    QString name = runItem.name;
    QString site = targetSite->getShortName();

    std::ifstream in (tagfile.toStdString());
    if (!in) {
        out.write("Error. Unable to open file \"" + tagfile + "\".", PPOutputMaker::Error);
    }
    else {
        out.write("Parsing \"" + tagfile + "\"...");

        PPTag tag;
        string line;
        PCodeList::iterator pc_it = pcl.end();
        while (!in.eof()) { //tag.read(in)) {// getline( in, line ) ) {
//            stringstream instream( line );

//            instream >> tag;

            if (tag.read(in)) { //tag.isOk() ) {
                if ( pc_it == pcl.end() || (*pc_it).getPitcode().compare( tag.getPitCode() ) != 0 )
                    pc_it = find( pcl.begin(), pcl.end(), tag.getPitCode().toStdString() );

                if ( pc_it != pcl.end() ) {
                    PCode& pc = *pc_it;
                    if (pc.isReturned()) {
                        const DateConverter date( pc.getTime() );
                        QString filename(QString("%1/%2.%3.%4%5%6.tag").arg(outDir, site, name).arg(date.year()).arg(date.month()).arg(date.day()));
           //             MBuf fileName;
           //             sprintf(fileName, "%s/%s.%s.%04d%02d%02d.tag", outDir.toStdString(), site.toStdString(), name.toStdString(),
           //                 date.year(), date.month(), date.day() );
                        getOFStream(ofilel, tfnl, filename) << tag << endl;
                    }
                }
            }
        }
        in.close();
    }
}


void Dsplit::cleanupData() {
    for (QStringList::const_iterator it = codel.begin(); it != codel.end(); it++ ) {
        const QString& code = *it;
        QString obsfile = dataDir + "/" + runItem.obs + "." + code;
        QString tagfile = dataDir + "/" + runItem.tag + "." + code;

        unlink(obsfile.toStdString().data());
        unlink(tagfile.toStdString().data());
    }
}


QString Dsplit::getSplitCode(const QString pitcode) {
    QStringRef sref(&pitcode, pitcode.size()-1, 1);
    return sref.toString();
//    return pitcode.substr(pitcode.size() - 1, 1);
}

//
// getOFStream
//
// Keep a list (of limited length) with open file pointers so
// that it isn't necessary to open the files each time we want to
// read or write something.
//

ofstream& Dsplit::getOFStream(OFileList& ofilel, QStringList& fnl, const QString filen)
{
    char mode;
    QFile *qfile = new QFile(filen);
    OFile ofile(filen);
    int index = ofilel.indexOf(ofile);
    if (index < 0) {
        if (ofilel.count() == nfilelim)
            ofilel.takeLast();

        ofilel.prepend(ofile);
    }

    index = fnl.indexOf(filen);
    if (index < 0) {
        fnl.prepend(filen);
        mode = 'w';
    }
    else {
        mode = 'a';
    }
    ofile.open(mode);
    return ofile.getStream();
    /*
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

    }*/
}

