/*
 * PitProUtilities.cpp
 */

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

#include <Sites.h>
#include <ArrayDefs.h>

#include "PitProUtilities.h"
#include "PitProSettings.h"
#include "PPSystemSettings.h"

using namespace std;
using namespace cbr;


QStringList PitProUtilities::getDataGroups( const QString& dataDir,
                                           const QString& obsSuffix,
                                           const QString& tagSuffix )
{
    QDir dir( dataDir);

    // get all files with the obs suffix from the data dir
    dir.setNameFilters(QStringList(QString("*.%1").arg(obsSuffix)));// "*." + obsSuffix );
    QStringList obsFiles = dir.entryList();

    // get all files with the tag suffix from the data dir
    dir.setNameFilters(QStringList(QString("*.%1").arg(tagSuffix)));// "*." + tagSuffix );
    QStringList tagFiles = dir.entryList();

    // get the common prefixes
    QStringList groups;
    for ( QStringList::iterator it = obsFiles.begin(); it != obsFiles.end(); it++ )  {
        QString& obsFile = *it;
        QStringList list = obsFile.split('.', QString::SkipEmptyParts);//QStringList::split( ".", obsFile );
        if ( list.size() >= 2 ) {
            QString prefix = obsFile.section( ".", 0, list.size() - 2 );
            QString tagFile = prefix + "." + tagSuffix;
            if ( tagFiles.contains( tagFile ) )
                groups << prefix;
        }
    }

    Utilities::sortUnique( groups );

    return groups;
}



QStringList PitProUtilities::getResultsGroups( const QString& outDir, const QStringList& suffixes ) {
    QDir dir( outDir );

    QStringList groups;
    for ( QStringList::const_iterator it = suffixes.begin(); it != suffixes.end(); ++it ) {
        QString suffix = *it;
        dir.setNameFilters(QStringList(QString("*.%1").arg(suffix)));// "*." + suffix );
        QStringList entries = dir.entryList();
        for ( QStringList::iterator it1 = entries.begin(); it1 != entries.end(); ++it1 ) {
            QString fileName = *it1;
            fileName.truncate( fileName.length() - suffix.length() - 1 );
            if (!groups.contains(fileName))
                groups += fileName;
        }
    }

    //Utilities::sortUnique( groups );

    groups.sort();
    return groups;
}

// Call before reading any configuration file
QString PitProUtilities::usage()  {
    const Sites* sites = Sites::getInstance();
    const QString tabs("\t\t");
    QString description;
    QString sstr;

    PitProSettings& settings = PitProSettings::getInstance();
    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();

    QMap<QString, QString> usage;
//	map<std::string,std::string> usage;
    const QMap<int, QString>& keyNames = settings.getKeyNames();
    for (QMap<int,QString>::const_iterator it = keyNames.begin(); it != keyNames.end(); ++it)
    {
        const QString key (it.value());
//        const string& key = (*it).second;
//        stringstream ss;
        if (key.compare("adultField") == 0) {
            SitesList allsites = sites->getSites();
            sstr.append(QString("%1The adult fields for the capture history. See \"histField\" below for\n").arg(tabs));
            sstr.append(QString("%1details on passing multiple fields and field ordering. A site can\n").arg(tabs));
            sstr.append(QString("%1be any one of:\n").arg(tabs));
//            ss<<t << "The adult fields for the capture history. See \"histField\" below for" << endl;
//            ss<<t << "details on passing multiple fields and field ordering. A site can" << endl;
//            ss<<t << "be any one of:";
            for (int i = 0; i < allsites.count(); i++) {
//            for (SitesList::const_iterator it = allsites.begin(); it != allsites.end(); ++it) {
                Site *site = allsites.at(i);
//                Site* site = *it;
                if (site->isAdult()) {
                    QString sitecode (site->getSiteCode());
                    sitecode.resize(4);
                    sstr.append('\n');
                    sstr.append(QString("\t%1: %2").arg(sitecode, site->getLongName()));
//                    ss << endl;
//                    ss<<t << "\t" << std::setw(4) << site->getSiteCode() << ": ";
//                    ss << site->getLongName();
                }
            }
        }
        else if (key.compare("adultModeSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Causes the program to attemp to determine fish stage (e.g. juvenile vs adult).\n").arg(tabs));
            sstr.append(QString("%1This is done using either migration year (see migrationYear) or a\n").arg(tabs));
            sstr.append(QString("%1juvenile cutoff date (see juvenileCutoffDate). If this is set to\n").arg(tabs));
            sstr.append(QString("%1false, all detections are assumed to be juveniles.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Causes the program to attemp to determine fish stage (e.g. juvenile vs adult)." << endl;
//            ss<<t << "This is done using either migration year (see migrationYear) or a" << endl;
//            ss<<t << "juvenile cutoff date (see juvenileCutoffDate). If this is set to" << endl;
//            ss<<t << "false, all detections are assumed to be juveniles.";
        }
        else if (key.compare("altSitesConfig") == 0) {
            sstr.append(QString("%1default: %2\n").arg(tabs, systemSettings.get(PPSystemSettings::SitesConfigFile).toString()));
            sstr.append(QString("%1Use the specified sites configuration file instead of the default.").arg(tabs));
//            ss<<t << "default: " << systemSettings.get(PPSystemSettings::SitesConfigFile).toString().toStdString() << endl;
//            ss<<t << "Use the specified sites configuration file instead of the default.";
        }
        else if (key.compare("anyRouteSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1A method for mapping adult observation sequences that include.\n").arg(tabs));
            sstr.append(QString("%1fallback into capture histories. In this method a fish is\n").arg(tabs));
            sstr.append(QString("%1flagged as detected at a site if it is detected at any stage\n").arg(tabs));
            sstr.append(QString("%1of the migration. Contrast this with the \"last route\"\n").arg(tabs));
            sstr.append(QString("%1method (see lastRouteSwitch).").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "A method for mapping adult observation sequences that include." << endl;
//            ss<<t << "fallback into capture histories. In this method a fish is" << endl;
//            ss<<t << "flagged as detected at a site if it is detected at any stage" << endl;
//            ss<<t << "of the migration. Contrast this with the \"last route\"" << endl;
//            ss<<t << "method (see lastRouteSwitch).";
        }
        else if (key.compare("histDetail") == 0) {
            sstr.append(QString("%1value: Std or All.\n").arg(tabs));
            sstr.append(QString("%1Use different codes to differentiate between detection paths.\n").arg(tabs));
            sstr.append(QString("%1  Std - simplified, compatible with previous versions.\n").arg(tabs));
            sstr.append(QString("%1  All - every code separated out (0-6, 9).").arg(tabs));
//            ss<<t << "value: Std or All." << endl;
//            ss<<t << "Use different codes to differentiate between detection paths." << endl;
//            ss<<t << "  Std - simplified, compatible with previous versions." << endl;
//            ss<<t << "  All - every code separated out (0-6, 9)." ;
        }
        else if (key.compare("dataDir") == 0) {
            sstr.append(QString("%1The folder where the program searches for data files.").arg(tabs));
//            ss<<t << "The folder where the program searches for data files.";
        }
        else if (key.compare("ddFileSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When set to true the detection date output file is generated.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "When set to true the detection date output file is generated.";
        }
        else if (key.compare("dsplit") == 0) {
            sstr.append(QString("%1Put the program in dsplit mode.").arg(tabs));
//            ss<<t << "Put the program in dsplit mode.";
        }
        else if (key.compare("errorsCheck") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When set to true, the program wil check for and remove errors.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "When set to true, the program wil check for and remove errors.";
        }
        else if (key.compare("errorsFileSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When set to true the errors output file is generated.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "When set to true the errors output file is generated.";
        }
        else if (key.compare("groupPrefix") == 0) {
            sstr.append(QString("%1The group prefix defines the data set. For instance, if the\n").arg(tabs));
            sstr.append(QString("%1prefix is \"prefix\", the program will search for \"prefix.tag\",\n").arg(tabs));
            sstr.append(QString("%1\"prefix.obs\", \"prefix.mrt\", and \"prefix.rcp\", which are the\n").arg(tabs));
            sstr.append(QString("%1tag, observation, mortality, and recapture data, respectively.\n").arg(tabs));
            sstr.append(QString("%1Normally each group defined here is a seperate run with seperate output,\n").arg(tabs));
            sstr.append(QString("%1To combine the groups to generate one capture history file with a \n").arg(tabs));
            sstr.append(QString("%1seperate population for each group, set groupRuns to true.").arg(tabs));
//            ss<<t << "The group prefix defines the data set. For instance, if the" << endl;
//            ss<<t << "prefix is \"prefix\", the program will search for \"prefix.tag\"," << endl;
//            ss<<t << "\"prefix.obs\", \"prefix.mrt\", and \"prefix.rcp\", which are the" << endl;
//            ss<<t << "tag, observation, mortality, and recapture data, respectively." << endl;
//            ss<<t << "Normally each group defined here is a seperate run with seperate output," << endl;
//            ss<<t << "To combine the groups to generate one capture history file with a " << endl;
//            ss<<t << "seperate population for each group, set groupRuns to true.";
        }
        else if (key.compare("groupRuns") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Combine all groups into one capture history file, with a seperate\n").arg(tabs));
            sstr.append(QString("%1population for each group. Other types of outputs are not\n").arg(tabs));
            sstr.append(QString("%1combined (e.g. errors, detection date, travel times, etc.).").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Combine all groups into one capture history file, with a seperate" << endl;
//            ss<<t << "population for each group. Other types of outputs are not" << endl;
//            ss<<t << "combined (e.g. errors, detection date, travel times, etc.).";
        }
        else if (key.compare("histField") == 0) {
            SitesList allsites = sites->getSites();
            sstr.append(QString("%1Defines the sites that make up the juvenile fields in the capture\n").arg(tabs));
            sstr.append(QString("%1history. Multiple fields are defined by passing multiple histField\n").arg(tabs));
            sstr.append(QString("%1flags with the ordering defined by the order the flags are given.\n").arg(tabs));
            sstr.append(QString("%1For instance, --histField=gr --histField=go etc. A site can be\n").arg(tabs));
            sstr.append(QString("%1any one of:\n").arg(tabs));
//            ss<<t << "Defines the sites that make up the juvenile fields in the capture" << endl;
//            ss<<t << "history. Multiple fields are defined by passing multiple histField" << endl;
//            ss<<t << "flags with the ordering defined by the order the flags are given." << endl;
//            ss<<t << "For instance, --histField=gr --histField=go etc. A site can be" << endl;
//            ss<<t << "any one of:" << endl;
            for (int i = 0; i < allsites.count(); i++) {
                Site *site = allsites.at(i);
                QString sitecode (site->getSiteCode());
                sitecode.resize(4);
                if (site->isJuvenile()) {
                    sstr.append(QString("\n%1\t;2: %3").arg(tabs, sitecode, site->getLongName()));
                }
            }
//            for (SitesList::const_iterator it = allsites.begin(); it != allsites.end(); ++it) {
//                Site* site = *it;
//                if (site->isJuvenile()) {
//                    ss << endl;
//                    sstr.append(QString("%1\n").arg(tabs));
//                    ss<<t << "\t" << std::setw(4) << site->getSiteCode() << ": ";
//                    ss << site->getLongName();
//                }
//            }
        }
        else if (key.compare("ignoreReRecap") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Ignore a juvenile recapture at the release site.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Ignore a juvenile recapture at the release site.";
        }
        else if (key.compare("julianDates") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When true julian dates are output in the detection date file. Otherwise\n").arg(tabs));
            sstr.append(QString("%1the dates are day of year with a fractional time added.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "" << endl;
//            ss<<t << "the dates are day of year with a fractional time added." << endl;
        }
        else if (key.compare("juvenileCutoffDate") == 0) {
            sstr.append(QString("%1value: date in format yyyymmdd\n").arg(tabs));
            sstr.append(QString("%1When provided the juvenile cutoff date divides the juvenile outmigration\n").arg(tabs));
            sstr.append(QString("%1from the adult outmigration. Dates must be in yyyymmdd format.").arg(tabs));
//            ss<<t << "value: date in format yyyymmdd" << endl;
//            ss<<t << "When provided the juvenile cutoff date divides the juvenile outmigration" << endl;
//            ss<<t << "from the adult outmigration. Dates must be in yyyymmdd format.";
        }
        else if (key.compare("lengthCovSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When set to true the program will include individual length covariates in\n").arg(tabs));
            sstr.append(QString("%1in the capture history output. This only applies to SURPH1 and SURPH2 format\n").arg(tabs));
            sstr.append(QString("%1output.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "When set to true the program will include individual length covariates in" << endl;
//            ss<<t << "in the capture history output. This only applies to SURPH1 and SURPH2 format" << endl;
//            ss<<t << "output.";
        }
        else if (key.compare("migrationYear") == 0) {
            sstr.append(QString("%1value: year in the form yyyy\n").arg(tabs));
            sstr.append(QString("%1When provided the migration year provides a method for distinguishing\n").arg(tabs));
            sstr.append(QString("%1the juvenile outmigration from the adult migration.\n").arg(tabs));
//            ss<<t << "value: year in the form yyyy" << endl;
//            ss<<t << "When provided the migration year provides a method for distinguishing" << endl;
//            ss<<t << "the juvenile outmigration from the adult migration." << endl;
        }
        else if (key.compare("newRcFile") == 0) {
            sstr.append(QString("%1Use this flag to generate a default rc file.\n").arg(tabs));
//            ss<<t << "Use this flag to generate a default rc file.";
        }
        else if (key.compare("numMainSites") == 0) {
            sstr.append(QString("%1value: [1,n] where n = number of defined sites\n").arg(tabs));
            sstr.append(QString("%1This gives the number of sites that will be represented in the\n").arg(tabs));
            sstr.append(QString("%1capture history, exclusive of the last field. All other sites\n").arg(tabs));
            sstr.append(QString("%1will be combined into the last field. The exception is when\n").arg(tabs));
            sstr.append(QString("%1the last field equals the number of defined sites, in which case\n").arg(tabs));
            sstr.append(QString("%1the number of fields in the capture history equals the number of\n").arg(tabs));
            sstr.append(QString("%1main sites. So if the fields are gr, gr, lm, mc, jd, and bv, and\n").arg(tabs));
            sstr.append(QString("%1and the number of main sites is 4, the fields in the capture\n").arg(tabs));
            sstr.append(QString("%1history will correspond to gr, go, lm, mc and jd+bv for a total\n").arg(tabs));
            sstr.append(QString("%1of 5 fields (not including a release field, if present). If\n").arg(tabs));
            sstr.append(QString("%1numMainSites is 6, there will be one field for each site: gr,\n").arg(tabs));
            sstr.append(QString("%1go, lm, mc, jd, and bv. Incidentally this is the same result\n").arg(tabs));
            sstr.append(QString("%1as if the numMainSites had been set to 5.").arg(tabs));
//            ss<<t << "value: [1,n] where n = number of defined sites" << endl;
//            ss<<t << "This gives the number of sites that will be represented in the" << endl;
 //           ss<<t << "capture history, exclusive of the last field. All other sites" << endl;
//            ss<<t << "will be combined into the last field. The exception is when" << endl;
//            ss<<t << "the last field equals the number of defined sites, in which case" << endl;
//            ss<<t << "the number of fields in the capture history equals the number of" << endl;
//            ss<<t << "main sites. So if the fields are gr, gr, lm, mc, jd, and bv, and" << endl;
//            ss<<t << "and the number of main sites is 4, the fields in the capture" << endl;
//            ss<<t << "history will correspond to gr, go, lm, mc and jd+bv for a total" << endl;
//            ss<<t << "of 5 fields (not including a release field, if present). If" << endl;
//            ss<<t << "numMainSites is 6, there will be one field for each site: gr," << endl;
//            ss<<t << "go, lm, mc, jd, and bv. Incidentally this is the same result" << endl;
//            ss<<t << "as if the numMainSites had been set to 5.";
        }
        else if (key.compare("outPrefix") == 0) {
            sstr.append(QString("%1This is used mainly when grouping runs. This will be the name\n").arg(tabs));
            sstr.append(QString("%1that prefixes the capture history file (e.g. outprefix.ch).").arg(tabs));
//            ss<<t << "This is used mainly when grouping runs. This will be the name" << endl;
//            ss<<t << "that prefixes the capture history file (e.g. outprefix.ch)." << endl;
        }
        else if (key.compare("outputDir") == 0) {
            sstr.append(QString("%1The directory (folder) where the output files will be written.").arg(tabs));
//            ss<<t << "The directory (folder) where the output files will be written.";
        }
        else if (key.compare("outputFormat") == 0) {
            sstr.append(QString("%1value: SURPH1, SURPH2, or ROSTER\n").arg(tabs));
            sstr.append(QString("%1The type of capture history data file to output.").arg(tabs));
//            ss<<t << "value: SURPH1, SURPH2, or ROSTER" << endl;
//            ss<<t << "The type of capture history data file to output.";
        }
        else if (key.compare("rcFileName") == 0) {
            sstr.append(QString("%1The name (or path) of the run time configuration (rc) file. The rc file\n").arg(tabs));
            sstr.append(QString("%1is an xml file that can contain any of these flags. It is a good place\n").arg(tabs));
            sstr.append(QString("%1to set flags that are common to a number of runs, keeping the command\n").arg(tabs));
            sstr.append(QString("%1line from getting to cluttered and complicated. You can use the\n").arg(tabs));
            sstr.append(QString("%1newRcFile flag to generate a default rc file which can be used as a\n").arg(tabs));
            sstr.append(QString("%1template.").arg(tabs));
//            ss<<t << "The name (or path) of the run time configuration (rc) file. The rc file" << endl;
//            ss<<t << "is an xml file that can contain any of these flags. It is a good place" << endl;
//            ss<<t << "to set flags that are common to a number of runs, keeping the command" << endl;
//            ss<<t << "line from getting to cluttered and complicated. You can use the" << endl;
//            ss<<t << "newRcFile flag to generate a default rc file which can be used as a" << endl;
//            ss<<t << "template." << endl;
        }
        else if (key.compare("rearType") == 0) {
            sstr.append(QString("%1The rearing type. This will be compared to the tag file data to filter out\n").arg(tabs));
            sstr.append(QString("%1records that do not match. Use \"All\" to keep all rearing types.\n").arg(tabs));
//            ss<<t << "The rearing type. This will be compared to the tag file data to filter out" << endl;
//            ss<<t << "records that do not match. Use \"All\" to keep all rearing types.";
        }
        else if (key.compare("relDate") == 0) {
            sstr.append(QString("%1value: date in format yyyymmdd\n").arg(tabs));
            sstr.append(QString("%1You can specifiy a release date that applies to all fish. This supercedes any\n").arg(tabs));
            sstr.append(QString("%1release data found in the tagging data file.").arg(tabs));
//            ss<<t << "value: date in format yyyymmdd" << endl;
//            ss<<t << "You can specifiy a release date that applies to all fish. This supercedes any" << endl;
//            ss<<t << "release data found in the tagging data file.";
        }
        else if (key.compare("releaseDataCheck") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Require a release date for a given fish when true. The fish is removed as an\n").arg(tabs));
            sstr.append(QString("%1error. When interested in travel times from release it is a good idea to set\n").arg(tabs));
            sstr.append(QString("%1flat to true.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Require a release date for a given fish when true. The fish is removed as an" << endl;
//            ss<<t << "error. When interested in travel times from release it is a good idea to set" << endl;
//            ss<<t << "flat to true.";
        }
        else if (key.compare("removalTrumpsSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1This controls the way multple observations at one site are combined into a\n").arg(tabs));
            sstr.append(QString("%1final disposition. The order or precedence is Sampled, Returned, and\n").arg(tabs));
            sstr.append(QString("%1Transported, in that order. So that if a fish is seen on a detector\n").arg(tabs));
            sstr.append(QString("%1that indicates sampling, this is the final disposition even if the\n").arg(tabs));
            sstr.append(QString("%1fish is subsequently observed on the return to river detector. If\n").arg(tabs));
            sstr.append(QString("%1this flag is set to false, the last detection (chronlogically)\n").arg(tabs));
            sstr.append(QString("%1is used.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "This controls the way multple observations at one site are combined into a" << endl;
//            ss<<t << "final disposition. The order or precedence is Sampled, Returned, and" << endl;
//            ss<<t << "Transported, in that order. So that if a fish is seen on a detector" << endl;
//            ss<<t << "that indicates sampling, this is the final disposition even if the" << endl;
//            ss<<t << "fish is subsequently observed on the return to river detector. If" << endl;
//            ss<<t << "this flag is set to false, the last detection (chronlogically)" << endl;
//            ss<<t << "";
        }
        else if (key.compare("removeJacks") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1The program will remove minijacks if this is set to true. The only way for the\n").arg(tabs));
            sstr.append(QString("%1program to identify a jack is if a juvenileCutoffDate is set. Any fish\n").arg(tabs));
            sstr.append(QString("%1detected in that year after the cuttoff date are considered to be minijacks.\n").arg(tabs));
            sstr.append(QString("%1Normally these fish are included in ocean age class 1 (\"A\").").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "The program will remove minijacks if this is set to true. The only way for the" << endl;
//            ss<<t << "program to identify a jack is if a juvenileCutoffDate is set. Any fish" << endl;
//            ss<<t << "detected in that year after the cuttoff date are considered to be minijacks." << endl;
//            ss<<t << "Normally these fish are included in ocean age class 1 (\"A\").";
        }
        else if (key.compare("removeResidualizers") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Remove fish detected subsequent to the migration year on known\n").arg(tabs));
            sstr.append(QString("%1juvenile detectors.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Remove fish detected subsequent to the migration year on known" << endl;
//            ss<<t << "juvenile detectors.";
        }
        else if (key.compare("resCutoffDate") == 0) {
            sstr.append(QString("%1value: date in format yyyymmdd\n").arg(tabs));
            sstr.append(QString("%1A cutoff date for residualizing fish").arg(tabs));
//            ss<<t << "value: date in format yyyymmdd" << endl;
//            ss<<t << "A cutoff date for residualizing fish ";
        }
        else if (key.compare("run") == 0) {
            sstr.append(QString("%1The run. This will be compared to the tag file data to filter out\n").arg(tabs));
            sstr.append(QString("%1records that do not match. Use \"All\" to keep all runs").arg(tabs));
//            ss<<t << "The run. This will be compared to the tag file data to filter out" << endl;
//            ss<<t << "records that do not match. Use \"All\" to keep all runs";
        }
        else if (key.compare("sampTransSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1If this is true the program will treat all sampled fish as transported.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "If this is true the program will treat all sampled fish as transported." << endl;
        }
        else if (key.compare("sequenceFileSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1When true the sequence output file is written to the output directory.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "When true the sequence output file is written to the output directory.";
        }
        else if (key.compare("showConfig") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Display sites cofiguration and quit.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Display sites cofiguration and quit.";
        }
        else if (key.compare("singleCoilSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Allow detections at a site on only one coil (site-wide).").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Allow detections at a site on only one coil (site-wide).";
        }
        else if (key.compare("siteRel") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1For fish released into a bypass system when only fish returned to river are\n").arg(tabs));
            sstr.append(QString("%1considered valid. Settings this to true will cause any fish not returned to\n").arg(tabs));
            sstr.append(QString("%1at the given site to be removed as an error. The release site can be any\n").arg(tabs));
            sstr.append(QString("%1of the sites defined by histField or adultField.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "For fish released into a bypass system when only fish returned to river are" << endl;
//            ss<<t << "considered valid. Settings this to true will cause any fish not returned to" << endl;
//            ss<<t << "at the given site to be removed as an error. The release site can be any" << endl;
//            ss<<t << "of the sites defined by histField or adultField.";
        }
        else if (key.compare("species") == 0) {
            sstr.append(QString("%1The species. This will be compared to the tag file data to filter out\n").arg(tabs));
            sstr.append(QString("%1records that do not match. Use \"All\" to keep all species").arg(tabs));
//            ss<<t << "The species. This will be compared to the tag file data to filter out" << endl;
//            ss<<t << "records that do not match. Use \"All\" to keep all species";
        }
        else if (key.compare("surphFileSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Output the capture history file if true.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Output the capture history file if true.";
        }
        else if (key.compare("tagCheck") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Remove observed tags not in the tag file.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Remove observed tags not in the tag file.";
        }
        else if (key.compare("transSite") == 0) {
            sstr.append(QString("%1values: gr, go, lm, or mc\n").arg(tabs));
            sstr.append(QString("%1Define transportation sites. It is possible to effectively remove\n").arg(tabs));
            sstr.append(QString("%1transportationa t a site by ommitting the transSite flag for the site.\n").arg(tabs));
            sstr.append(QString("%1Only sites listed using transSite will generate \"transported\"\n").arg(tabs));
            sstr.append(QString("%1dispostions. All transportation observations at unlisted sites\n").arg(tabs));
            sstr.append(QString("%1will instead generate \"unknown\" dispostitions and final disposition\n").arg(tabs));
            sstr.append(QString("%1will depend on other observations, if any. To change the default behavior\n").arg(tabs));
            sstr.append(QString("%1explicitly list the desired transportation sites in the run configuration\n").arg(tabs));
            sstr.append(QString("%1file or on the command line.").arg(tabs));
//            ss<<t << "values: gr, go, lm, or mc" << endl;
//            ss<<t << "Define transportation sites. It is possible to effectively remove" << endl;
//            ss<<t << "transportationa t a site by ommitting the transSite flag for the site." << endl;
//            ss<<t << "Only sites listed using transSite will generate \"transported\"" << endl;
//            ss<<t << "dispostions. All transportation observations at unlisted sites" << endl;
//            ss<<t << "will instead generate \"unknown\" dispostitions and final disposition" << endl;
//            ss<<t << "will depend on other observations, if any. To change the default behavior" << endl;
//            ss<<t << "explicitly list the desired transportation sites in the run configuration" << endl;
//            ss<<t << "file or on the command line.";
        }
        else if (key.compare("ttFileSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Output the travel time file if true.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Output the travel time file if true.";
        }
        else if (key.compare("unknownSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Use 'U' for unknown dispositions.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Use 'U' for unknown dispositions.";
        }
        else if (key.compare("usage") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Display this message.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Display this message.";
        }
        else if (key.compare("version") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Display program version.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Display program version.";
        }
        else if (key.compare("warnings") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Print warning messages if true.").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Print warning messages if true.";
        }
        else if (key.compare("zeroLengthSwitch") == 0) {
            sstr.append(QString("%1value: true or false\n").arg(tabs));
            sstr.append(QString("%1Remove fish with zero length.\n").arg(tabs));
//            ss<<t << "value: true or false" << endl;
//            ss<<t << "Remove fish with zero length.";
        }

        if (sstr.isEmpty()) {
            usage[key] = QString("");
        }
        description.append(sstr);
//        const string& description = ss.str();
 //       if (!description.empty()) {
  //          usage[key] = ss.str();
  //      }
    }

    sstr.clear();
//    stringstream ss;
    for (QMap<QString,QString>::const_iterator it = usage.begin(); it != usage.end(); ++it) {
        QString key = it.key();//*it).first;
        QString description = it.value();//*it).second;

        const ParamDef& def = settings.getDef(key, 0);
        sstr.append(QString("\t--%1:\n").arg(key));
//        ss << "\t--" << key << ":" << endl;

        QString defaultValue;
        if (!key.compare("adultField") || !key.compare("histField") || !key.compare("transSite")) {
            QStringList values = settings.getValues(key);
            defaultValue.append(values.at(0));
            for (int i = 1; i < values.count(); i++) {
                defaultValue.append(QString(", %1").arg(values.at(i)));
            }
//            stringstream ss;
//            for (StringVector::iterator it = values.begin(); it != values.end(); ++it) {
//                if (it != values.begin())
//                    ss << ", ";
//                ss << *it;
//            }
//            defaultValue = ss.str();
        }
        else if (!def.getValue().isEmpty()) {
            defaultValue.append(def.getValue());
            if (defaultValue.compare("0") == 0)
                defaultValue = QString("false");
            else if (defaultValue.compare("1") == 0)
                defaultValue = QString("true");
        }
        else {
           defaultValue.append("<none>") ;
        }
        sstr.append(QString("%1default: %2\n").arg(tabs, defaultValue));
        sstr.append(QString("%1\n\n").arg(description));

//        ss<<t << "default: " << defaultValue << endl;
//        ss << description << endl << endl;
    }

    return QString(sstr);//ss.str();
}
