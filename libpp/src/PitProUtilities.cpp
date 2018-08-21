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
string PitProUtilities::usage()  {
	const Sites* sites = Sites::getInstance();
	const string t = "\t\t";

	PitProSettings& settings = PitProSettings::getInstance();
	PPSystemSettings& systemSettings = PPSystemSettings::getInstance();

	map<std::string,std::string> usage;
	const std::map<int, std::string>& keyNames = settings.getKeyNames();
	for (map<int,string>::const_iterator it = keyNames.begin(); it != keyNames.end(); ++it) 
    {
        const string& key = (*it).second;
        stringstream ss;
        if (!key.compare("adultField")) {
            SitesVector allsites = sites->getSites();
            ss<<t << "The adult fields for the capture history. See \"histField\" below for" << endl;
            ss<<t << "details on passing multiple fields and field ordering. A site can" << endl;
            ss<<t << "be any one of:";
            for (SitesVector::const_iterator it = allsites.begin(); it != allsites.end(); ++it) {
                Site* site = *it;
                if (site->isAdult()) {
                    ss << endl;
                    ss<<t << "\t" << std::setw(4) << site->getSiteCode() << ": ";
                    ss << site->getLongName();
                }
            }
        }
        else if (!key.compare("adultModeSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Causes the program to attemp to determine fish stage (e.g. juvenile vs adult)." << endl;
            ss<<t << "This is done using either migration year (see migrationYear) or a" << endl;
            ss<<t << "juvenile cutoff date (see juvenileCutoffDate). If this is set to" << endl;
            ss<<t << "false, all detections are assumed to be juveniles.";
        }
        else if (!key.compare("altSitesConfig")) {
            ss<<t << "default: " << systemSettings.get(PPSystemSettings::SitesConfigFile).toString().toStdString() << endl;
            ss<<t << "Use the specified sites configuration file instead of the default.";
        }
        else if (!key.compare("anyRouteSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "A method for mapping adult observation sequences that include." << endl;
            ss<<t << "fallback into capture histories. In this method a fish is" << endl;
            ss<<t << "flagged as detected at a site if it is detected at any stage" << endl;
            ss<<t << "of the migration. Contrast this with the \"last route\"" << endl;
            ss<<t << "method (see lastRouteSwitch).";
        }
        else if (!key.compare("dataDir")) {
            ss<<t << "The folder where the program searches for data files.";
        }
        else if (!key.compare("ddFileSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When set to true the detection date output file is generated.";
        }
        else if (!key.compare("dsplit")) {
            ss<<t << "Put the program in dsplit mode.";
        }
        else if (!key.compare("errorsCheck")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When set to true, the program wil check for and remove errors.";
        }
        else if (!key.compare("errorsFileSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When set to true the errors output file is generated.";
        }
        else if (!key.compare("groupPrefix")) {
            ss<<t << "The group prefix defines the data set. For instance, if the" << endl;
            ss<<t << "prefix is \"prefix\", the program will search for \"prefix.tag\"," << endl;
            ss<<t << "\"prefix.obs\", \"prefix.mrt\", and \"prefix.rcp\", which are the" << endl;
            ss<<t << "tag, observation, mortality, and recapture data, respectively." << endl;
            ss<<t << "Normally each group defined here is a seperate run with seperate output," << endl;
            ss<<t << "To combine the groups to generate one capture history file with a " << endl;
            ss<<t << "seperate population for each group, set groupRuns to true.";
        }
        else if (!key.compare("groupRuns")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Combine all groups into one capture history file, with a seperate" << endl;
            ss<<t << "population for each group. Other types of outputs are not" << endl;
            ss<<t << "combined (e.g. errors, detection date, travel times, etc.).";
        }
        else if (!key.compare("histField")) {
            SitesVector allsites = sites->getSites();
            ss<<t << "Defines the sites that make up the juvenile fields in the capture" << endl;
            ss<<t << "history. Multiple fields are defined by passing multiple histField" << endl;
            ss<<t << "flags with the ordering defined by the order the flags are given." << endl;
            ss<<t << "For instance, --histField=gr --histField=go etc. A site can be" << endl;
            ss<<t << "any one of:" << endl;
            for (SitesVector::const_iterator it = allsites.begin(); it != allsites.end(); ++it) {
                Site* site = *it;
                if (site->isJuvenile()) {
                    ss << endl;
                    ss<<t << "\t" << std::setw(4) << site->getSiteCode() << ": ";
                    ss << site->getLongName();
                }
            }
        }
        else if (!key.compare("ignoreReRecap")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Ignore a juvenile recapture at the release site.";
        }
        else if (!key.compare("julianDates")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When true julian dates are output in the detection date file. Otherwise" << endl;
            ss<<t << "the dates are day of year with a fractional time added." << endl;
        }
        else if (!key.compare("juvenileCutoffDate")) {
            ss<<t << "value: date in format yyyymmdd" << endl;
            ss<<t << "When provided the juvenile cutoff date divides the juvenile outmigration" << endl;
            ss<<t << "from the adult outmigration. Dates must be in yyyymmdd format.";
        }
        else if (!key.compare("lengthCovSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When set to true the program will include individual length covariates in" << endl;
            ss<<t << "in the capture history output. This only applies to SURPH1 and SURPH2 format" << endl;
            ss<<t << "output.";
        }
        else if (!key.compare("migrationYear")) {
            ss<<t << "value: year in the form yyyy" << endl;
            ss<<t << "When provided the migration year provides a method for distinguishing" << endl;
            ss<<t << "the juvenile outmigration from the adult migration." << endl;
        }
        else if (!key.compare("newRcFile")) {
            ss<<t << "Use this flag to generate a default rc file.";
        }
        else if (!key.compare("numMainSites")) {
            ss<<t << "value: [1,n] where n = number of defined sites" << endl;
            ss<<t << "This gives the number of sites that will be represented in the" << endl;
            ss<<t << "capture history, exclusive of the last field. All other sites" << endl;
            ss<<t << "will be combined into the last field. The exception is when" << endl;
            ss<<t << "the last field equals the number of defined sites, in which case" << endl;
            ss<<t << "the number of fields in the capture history equals the number of" << endl;
            ss<<t << "main sites. So if the fields are gr, gr, lm, mc, jd, and bv, and" << endl;
            ss<<t << "and the number of main sites is 4, the fields in the capture" << endl;
            ss<<t << "history will correspond to gr, go, lm, mc and jd+bv for a total" << endl;
            ss<<t << "of 5 fields (not including a release field, if present). If" << endl;
            ss<<t << "numMainSites is 6, there will be one field for each site: gr," << endl;
            ss<<t << "go, lm, mc, jd, and bv. Incidentally this is the same result" << endl;
            ss<<t << "as if the numMainSites had been set to 5.";
        }
        else if (!key.compare("outPrefix")) {
            ss<<t << "This is used mainly when grouping runs. This will be the name" << endl;
            ss<<t << "that prefixes the capture history file (e.g. outprefix.ch)." << endl;
        }
        else if (!key.compare("outputDir")) {
            ss<<t << "The directory (folder) where the output files will be written.";
        }
        else if (!key.compare("outputFormat")) {
            ss<<t << "value: SURPH1, SURPH2, or ROSTER" << endl;
            ss<<t << "The type of capture history data file to output.";
        }
        else if (!key.compare("rcFileName")) {
            ss<<t << "The name (or path) of the run time configuration (rc) file. The rc file" << endl;
            ss<<t << "is an xml file that can contain any of these flags. It is a good place" << endl;
            ss<<t << "to set flags that are common to a number of runs, keeping the command" << endl;
            ss<<t << "line from getting to cluttered and complicated. You can use the" << endl;
            ss<<t << "newRcFile flag to generate a default rc file which can be used as a" << endl;
            ss<<t << "template." << endl;
        }
        else if (!key.compare("rearType")) {
            ss<<t << "The rearing type. This will be compared to the tag file data to filter out" << endl;
            ss<<t << "records that do not match. Use \"All\" to keep all rearing types.";
        }
        else if (!key.compare("relDate")) {
            ss<<t << "value: date in format yyyymmdd" << endl;
            ss<<t << "You can specifiy a release date that applies to all fish. This supercedes any" << endl;
            ss<<t << "release data found in the tagging data file.";
        }
        else if (!key.compare("releaseDataCheck")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Require a release date for a given fish when true. The fish is removed as an" << endl;
            ss<<t << "error. When interested in travel times from release it is a good idea to set" << endl;
            ss<<t << "flat to true.";
        }
        else if (!key.compare("removalTrumpsSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "This controls the way multple observations at one site are combined into a" << endl;
            ss<<t << "final disposition. The order or precedence is Sampled, Returned, and" << endl;
            ss<<t << "Transported, in that order. So that if a fish is seen on a detector" << endl;
            ss<<t << "that indicates sampling, this is the final disposition even if the" << endl;
            ss<<t << "fish is subsequently observed on the return to river detector. If" << endl;
            ss<<t << "this flag is set to false, the last detection (chronlogically)" << endl;
            ss<<t << "is used.";
        }
        else if (!key.compare("removeJacks")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "The program will remove minijacks if this is set to true. The only way for the" << endl;
            ss<<t << "program to identify a jack is if a juvenileCutoffDate is set. Any fish" << endl;
            ss<<t << "detected in that year after the cuttoff date are considered to be minijacks." << endl;
            ss<<t << "Normally these fish are included in ocean age class 1 (\"A\").";
        }
        else if (!key.compare("removeResidualizers")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Remove fish detected subsequent to the migration year on known" << endl;
            ss<<t << "juvenile detectors.";
        }
        else if (!key.compare("resCutoffDate")) {
            ss<<t << "value: date in format yyyymmdd" << endl;
            ss<<t << "A cutoff date for residualizing fish ";
        }
        else if (!key.compare("run")) {
            ss<<t << "The run. This will be compared to the tag file data to filter out" << endl;
            ss<<t << "records that do not match. Use \"All\" to keep all runs";
        }
        else if (!key.compare("sampTransSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "If this is true the program will treat all sampled fish as transported." << endl;
        }
        else if (!key.compare("sequenceFileSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "When true the sequence output file is written to the output directory.";
        }
        else if (!key.compare("showConfig")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Display sites cofiguration and quit.";
        }
        else if (!key.compare("singleCoilSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Allow detections at a site on only one coil (site-wide).";
        }
        else if (!key.compare("siteRel")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "For fish released into a bypass system when only fish returned to river are" << endl;
            ss<<t << "considered valid. Settings this to true will cause any fish not returned to" << endl;
            ss<<t << "at the given site to be removed as an error. The release site can be any" << endl;
            ss<<t << "of the sites defined by histField or adultField.";
        }
        else if (!key.compare("species")) {
            ss<<t << "The species. This will be compared to the tag file data to filter out" << endl;
            ss<<t << "records that do not match. Use \"All\" to keep all species";
        }
        else if (!key.compare("surphFileSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Output the capture history file if true.";
        }
        else if (!key.compare("tagCheck")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Remove observed tags not in the tag file.";
        }
        else if (!key.compare("transSite")) {
            ss<<t << "values: gr, go, lm, or mc" << endl;
            ss<<t << "Define transportation sites. It is possible to effectively remove" << endl;
            ss<<t << "transportationa t a site by ommitting the transSite flag for the site." << endl;
            ss<<t << "Only sites listed using transSite will generate \"transported\"" << endl;
            ss<<t << "dispostions. All transportation observations at unlisted sites" << endl;
            ss<<t << "will instead generate \"unknown\" dispostitions and final disposition" << endl;
            ss<<t << "will depend on other observations, if any. To change the default behavior" << endl;
            ss<<t << "explicitly list the desired transportation sites in the run configuration" << endl;
            ss<<t << "file or on the command line.";
        }
        else if (!key.compare("ttFileSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Output the travel time file if true.";
        }
        else if (!key.compare("unknownSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Use 'U' for unknown dispositions.";
        }
        else if (!key.compare("usage")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Display this message.";
        }
        else if (!key.compare("version")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Display program version.";
        }
        else if (!key.compare("warnings")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Print warning messages if true.";
        }
        else if (!key.compare("zeroLengthSwitch")) {
            ss<<t << "value: true or false" << endl;
            ss<<t << "Remove fish with zero length.";
        }

        const string& description = ss.str();
        if (!description.empty()) {
            usage[key] = ss.str();
        }
    }

    stringstream ss;
    for (map<string,string>::const_iterator it = usage.begin(); it != usage.end(); ++it) {  
        string key = (*it).first;
        string description = (*it).second;

        const ParamDef& def = settings.getDef(key, 0);
        ss << "\t--" << key << ":" << endl;

        string defaultValue = "<none>";
        if (!key.compare("adultField") || !key.compare("histField") || !key.compare("transSite")) {
            StringVector values = settings.getValues(key);
            stringstream ss;
            for (StringVector::iterator it = values.begin(); it != values.end(); ++it) {
                if (it != values.begin()) 
                    ss << ", ";
                ss << *it;
            }
            defaultValue = ss.str();
        }  
        else if (!def.getValue().empty()) {
            defaultValue = def.getValue();
            if (defaultValue.compare("0") == 0)
                defaultValue = "false";
            else if (defaultValue.compare("1") == 0)
                defaultValue = "true";  
        }

        ss<<t << "default: " << defaultValue << endl;
        ss << description << endl << endl;
    }

    return ss.str();
}
