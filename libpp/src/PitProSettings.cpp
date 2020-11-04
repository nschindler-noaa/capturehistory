
/*
 * PitProSettings.cpp
 *
 */

#include <string>
#include <fstream>
#include <sstream>

#include <ArrayDefs.h>
#include <DateConverter.h>
#include <Sites.h>
#include <StringManip.h>

#include "PitProSettings.h"
#include "portability.h"

using std::string;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::vector;
using std::map;

using namespace cbr;
static PitProSettings instance;

PitProSettings& PitProSettings::getInstance() {
    return instance;
}

/*
 * Initalize the settings. Set up the key names by mapping
 * text parameter names to parameter numbers. Set default
 * values.
 */
PitProSettings::PitProSettings() : Settings() {
    setKeyNames();
    setConstants();
    setDefaults(true);
}

/*
 *
 */
PitProSettings::~PitProSettings() {
}

/*
 *  These are the names that are used when saving the 
 *  settings to file.
 */
void PitProSettings::setKeyNames() {
    // key names for program constants

    addKeyName("tagSuffix", TagSuffix);
    addKeyName("obsSuffix", ObsSuffix);
    addKeyName("recapSuffix", RecapSuffix);
    addKeyName("mrtSuffix", MrtSuffix);
    addKeyName("ttSuffix", TtSuffix);
    addKeyName("ddSuffix", DdSuffix);
    addKeyName("surphSuffix", SurphSuffix);
    addKeyName("seqSuffix", SeqSuffix);
    addKeyName("errorSuffix", ErrorSuffix);
    addKeyName("configSuffix", ConfigSuffix);
    addKeyName("recapToIgnore", RecapToIgnore);
    addKeyName("filterByFileType", FilterByFileType);

    // set up key names
    addKeyName("adultField", AdultField);
    addKeyName("adultModeSwitch", AdultModeSwitch);
    addKeyName("altRelDate", AltRelDate);
    addKeyName("altSitesConfig", AltSitesConfig);
    addKeyName("anyRouteSwitch", AnyRouteSwitch);
    addKeyName("censorJuvUpstreamSwitch", CensorJuvUpstreamSwitch);
    addKeyName("combineJacks", CombineJacks);
    addKeyName("dataDir", DataDir);
    addKeyName("ddFileSwitch", DdFileSwitch);
    addKeyName("dsplit", Dsplit);
    addKeyName("errorsCheck", ErrorsCheck);
    addKeyName("errorsFileSwitch", ErrorsFileSwitch);
    addKeyName("groupPrefix", GroupPrefix);
    addKeyName("groupRuns", GroupRuns);
    addKeyName("histDetail", HistDetail);
    addKeyName("histField", HistField);
    addKeyName("julianDates", JulianDates);
    addKeyName("juvenileCutoffDate", JuvenileCutoffDate);
    addKeyName("juvenileCutoffSwitch", JuvenileCutoffSwitch);
    addKeyName("lastField", LastField);
    addKeyName("lastOutcomeSwitch", LastOutcomeSwitch);
    addKeyName("lastRouteSwitch", LastRouteSwitch);
    addKeyName("lengthCovSwitch", ICovSwitch);
    addKeyName("migrationYear", MigrationYear);
    addKeyName("migrationYearSwitch", MigrationYearSwitch);
    addKeyName("mortCheck", MortCheck);
    addKeyName("newRcFile", NewRcFile);
    addKeyName("nullCovariateSwitch", NullCovariateSwitch);
    addKeyName("numMainSites", NumMainSites);
    addKeyName("outPrefix", OutPrefix);
    addKeyName("outputDir", OutputDir);
    addKeyName("pitCodeRelKey", PitCodeRelKey);
    addKeyName("rcFileName", RcFileName);
    addKeyName("rearType", RearType);
    addKeyName("relDate", RelDate);
    addKeyName("releaseDataCheck", ReleaseDataCheck);
    addKeyName("relFile", RelFile);
    addKeyName("removeJacks", RemoveJacks);
    addKeyName("removeResidualizers", RemoveResidualizers);
    addKeyName("removalTrumpsSwitch", RemovalTrumpsSwitch);
    addKeyName("resCutoffDate", ResCutoffDate);
    addKeyName("resCutoffSwitch", ResCutoffSwitch);
    addKeyName("ignoreReRecap", IgnoreReRecaps);
    addKeyName("run", Run);
    addKeyName("runsTable", RunsTable);
    addKeyName("sampTransSwitch", SampTransSwitch);
    addKeyName("sequenceFileSwitch", SequenceFileSwitch);
    addKeyName("showConfig", ShowConfig);
    addKeyName("showLambda", ShowLambda);
    addKeyName("singleCoilSwitch", SingleCoilSwitch);
    addKeyName("siteRel", SiteRel);
    addKeyName("species", Species);
    addKeyName("split", Split);
    addKeyName("splitLevel", SplitLevel);
    addKeyName("surphFileSwitch", SurphFileSwitch);
    addKeyName("tagCheck", TagCheck);
    addKeyName("tagGroupRelKey", TagGroupRelKey);
    addKeyName("transSite", TransSite);
    addKeyName("truncUpJuvSwitch", TruncUpJuvSwitch);
    addKeyName("outputFormat", OutputFormat);
    addKeyName("ttFileSwitch", TtFileSwitch);
    addKeyName("usage", Usage);
    addKeyName("useSteelheadYear", UseSteelheadYear);
    addKeyName("unknownSwitch", UnknownSwitch);
    addKeyName("version", Version);
    addKeyName("warnings", Warnings);
    addKeyName("zeroCovariateSwitch", ZeroCovariateSwitch);
}

void PitProSettings::setConstants() {
    // internal config
    addParamDef(TagSuffix, "tag", true);
    addParamDef(ObsSuffix, "obs", true);
    addParamDef(RecapSuffix, "rcp", true);
    addParamDef(MrtSuffix, "mrt", true);
    addParamDef(TtSuffix, "tt", true);
    addParamDef(DdSuffix, "dd", true);
    addParamDef(SurphSuffix, "ch", true);
    addParamDef(SeqSuffix, "seq", true);
    addParamDef(ErrorSuffix, "err", true);
    addParamDef(ConfigSuffix, "cfg", true);

    addChecked(JulianDates, true, true);
    addChecked(ErrorsCheck, true, true);
    addChecked(UnknownSwitch, false, true);

    addParamDef(RecapToIgnore, "RICEIS", true);
    addParamDef(RecapToIgnore, "CRESIS", true);
    addParamDef(RecapToIgnore, "3MILIS", true);
    addParamDef(RecapToIgnore, "ESANIS", true);
    addParamDef(RecapToIgnore, "BADGEI", true);
    addParamDef(RecapToIgnore, "FOUNDI", true);
    addParamDef(RecapToIgnore, "LMEMIS", true);
    addParamDef(RecapToIgnore, "LMILIS", true);
    addParamDef(RecapToIgnore, "IS18", true);
    addParamDef(RecapToIgnore, "RICHIS", true);
}

void PitProSettings::setDefaults(bool clearDefinitions) {
    if (clearDefinitions)
        clear();
    // version
    setValue(Version, "4.20.3");

    // do not overwrite any existing defaults
    setDefaultMode(true);

    // run tab
    setValue(OutPrefix, "composite");
    setChecked(FilterByFileType, true);

    // files tab
    setValue(DataDir, "data");
    setValue(OutputDir, "output");
    setChecked(SurphFileSwitch, true);
    setChecked(ErrorsFileSwitch, true);
    setChecked(DdFileSwitch, true);
    setChecked(TtFileSwitch, false);
    setChecked(SequenceFileSwitch, false);
    setValue(OutputFormat, "SURPH2");
    setValue(HistDetail, "Std");

    // sites tab
    if (!isSet(HistField)) {
        setDefaultMode(false);
        addParamDef(HistField, "mc");
        addParamDef(HistField, "jd");
        addParamDef(HistField, "bv");
        addParamDef(HistField, "tw");
        setDefaultMode(true);
    }
    setValue(NumMainSites, "2");
    setChecked(SiteRel, false);

    // tag screening tab
    setValue(Species, "All");
    setValue(Run, "All");
    setValue(RearType, "All");

    // adult tab
    setChecked(AdultModeSwitch, false);
    setChecked(LastRouteSwitch, true);
    setChecked(AnyRouteSwitch, false);
    setChecked(RemoveJacks, true);
    setChecked(CombineJacks, false);
    setChecked(JuvenileCutoffSwitch, false);
    setChecked(MigrationYearSwitch, true);
    setChecked(RemoveResidualizers, true);
    setChecked(ResCutoffSwitch, false);
    setChecked(UseSteelheadYear, false);

    // trans tab
    if (!isSet(TransSite)) {
        setDefaultMode(false);
        addParamDef(TransSite, "gr");
        addParamDef(TransSite, "go");
        addParamDef(TransSite, "lm");
        addParamDef(TransSite, "mc");
        setDefaultMode(true);
    }

    // advanced tab
    setChecked(RemovalTrumpsSwitch, true);
    setChecked(LastOutcomeSwitch, false);
    setChecked(IgnoreReRecaps, true);
    setChecked(TagCheck, true);
    setChecked(SingleCoilSwitch, true);
    setChecked(Warnings, false);
    setChecked(SampTransSwitch, false);

    // batch only settings
    setChecked(Usage, false);
    setChecked(AltRelDate, false);
    setValue(RcFileName, "settings.xml");
    setValue(GroupPrefix, "");

    // other
    setChecked(ShowLambda, false);


    if (isError()) {
        // todo
    }

    setDefaultMode(false);

	// fix for misspelled key
	addKeyName("useSteelheadYer", UseSteelheadYer);
	if (isChecked(UseSteelheadYer))
		setChecked(UseSteelheadYear, true);
	clearDefs(UseSteelheadYer);

}

string
PitProSettings::getObsFilePath(const string& prefix) {
    string suffix = getValue(ObsSuffix);
    string fileName = prefix + "." + suffix;
    return getDataFilePath(fileName);
}

string
PitProSettings::getTagFilePath(const string& prefix) {
    string suffix = getValue(TagSuffix);
    string fileName = prefix + "." + suffix;
    return getDataFilePath(fileName);
}

string
PitProSettings::getDataFilePath(const string& fileName) {
    string dir = getValue(DataDir);
    string filePath = dir + "/" + fileName;
    return filePath;
}

string
PitProSettings::getOutFilePath(const string& fileName) {
    string dir = getValue(OutputDir);
    string filePath = dir + "/" + fileName;
    return filePath;
}

void
PitProSettings::clear() {
    Settings::clear();
}

bool
PitProSettings::verify() {
    StringVector histList = getValues(PitProSettings::HistField);
    if (histList.size() == 0) {
        lastError = "No main fields defined.";
        return false;
    }

    if (isChecked(GroupRuns)) {
        string prefix = getValue(OutPrefix);
        if (prefix.empty()) {
            lastError = "No output file prefix defined!";
            return true;
        }
    }

    // check directories
    if (access(getValue(DataDir).c_str(), 0) == -1) {
        lastError = "Input directory does not exist!";
        return false;
    }

    if (access(getValue(OutputDir).c_str(), 0) == -1) {
        lastError = "Output directory does not exist!";
        return false;
    }

    return true;
}

StringVector PitProSettings::getJuvenileSites() {
    StringVector siteNames;
    StringVector fields = getValues(HistField);
    Sites* sites = Sites::getInstance();
    for (StringVector::iterator it = fields.begin(); it != fields.end(); ++it) {
        Site* site = sites->getSite((*it).c_str());
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

StringVector PitProSettings::getAdultSites() {
    StringVector siteNames;
    StringVector fields = getValues(AdultField);
    Sites* sites = Sites::getInstance();
    for (StringVector::iterator it = fields.begin(); it != fields.end(); ++it) {
        Site* site = sites->getSite((*it).c_str());
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

StringVector PitProSettings::getTransSites() {
    StringVector siteNames;
    StringVector fields = getValues(TransSite);
    Sites* sites = Sites::getInstance();
    for (StringVector::iterator it = fields.begin(); it != fields.end(); ++it) {
        Site* site = sites->getSite((*it).c_str());
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

int PitProSettings::getNumGroups() {
    StringVector prefixes = getValues(PitProSettings::GroupPrefix);
    if (prefixes.size() > 0)
        return prefixes.size();

    StringVector runs = getValues(PitProSettings::RunsTable);
    int ncols = NCOLS;
    return runs.size() / ncols;
}

string PitProSettings::getPrefix(int run) {
    StringVector runs = getValues(RunsTable);
    int ncols = NCOLS;
    return runs[ run * ncols + RUN ];
}

string PitProSettings::getMrtFile(int run) {
    StringVector runs = getValues(RunsTable);
    int ncols = NCOLS;
    return runs[ run * ncols + MRT ];
}

string PitProSettings::getRunData(int run, ColumnOrder col) {
    string dataFile;

    StringVector prefixes = getValues(PitProSettings::GroupPrefix);
    if (prefixes.size() > 0) {
        string prefix = getValue(PitProSettings::GroupPrefix, run);
        if (!prefix.empty()) {
            if (col == RUN)
                dataFile = prefix;
            else
                dataFile = prefix + "." + getSuffix(col);
        }
    } else {

        StringVector runs = getValues(RunsTable);

        if (static_cast<int> (runs.size()) > run * NCOLS + col)
            dataFile = runs[ run * NCOLS + col ];
    }
    return dataFile;
}

void PitProSettings::getAllRunConfigs(RunConfigVector& runConfigVector) {
    for (int i = 0; i < getNumGroups(); ++i) {
        getRunConfig(runConfigVector, i);
    }
}

void PitProSettings::getRunConfig(RunConfigVector& runConfigVector, int run) {
    RunConfigItem item;
    item.name = getRunData(run, RUN);
    item.tag = getRunData(run, TAG);
    item.obs = getRunData(run, OBS);
    item.recap = getRunData(run, RCP);
    item.mort = getRunData(run, MRT);
    runConfigVector.push_back(item);
}

StringVector PitProSettings::getFiles(ColumnOrder col, int run) {
    StringVector prefixes;
    if (run != -1)
        prefixes.push_back(getRunData(run, col));
    else {
        for (int i = 0; i < getNumGroups(); ++i) {
            prefixes.push_back(getRunData(i, col));
        }
    }
    return prefixes;
}

StringVector PitProSettings::getObsFiles(int run) {
    return getFiles(OBS, run);
}

StringVector PitProSettings::getTagFiles(int run) {
    return getFiles(TAG, run);
}

StringVector PitProSettings::getMortFiles(int run) {
    return getFiles(MRT, run);
}

bool PitProSettings::ignoreRecap(const string& recap) {
    StringVector recapSites = getValues(RecapToIgnore);
    if (find(recapSites.begin(), recapSites.end(), recap) == recapSites.end())
        return false;
    return true;
}

string PitProSettings::writeLegend() {
    stringstream ss;

    ss << writeParam(DataDir, "Data Folder");
    ss << writeParam(OutputDir, "Output Folder");
    //ss << writeFileParam(OBS, "Interrogation data");
    //ss << writeFileParam(TAG, "Tag data");
    //ss << writeFileParam(RCP, "Recapture data");
    //ss << writeFileParam(MRT, "Mortatlity data");

    return ss.str();
}

string PitProSettings::writeFileParam(ColumnOrder ord, const string& heading) {
    StringVector files = getFiles(ord, -1);

    stringstream ss;
    ss << "# " << heading << ":" << endl;

    if (files.size() == 0)
        ss << "#	NA" << endl;
    else {
        for (StringVector::iterator it = files.begin(); it != files.end(); ++it) {
            ss << "#     " << *it << endl;
        }
    }
    ss << "#" << endl;
    return ss.str();
}

string PitProSettings::writeParam(int key, const string& heading) {
    string value = getValue(key);
    stringstream ss;
    ss << "# " << heading << ":" << endl;
    ss << "#     " << value << endl;
    ss << "#" << endl;
    return ss.str();
}

string PitProSettings::getSuffix(ColumnOrder col) {
    switch (col) {
        case TAG:
            return getValue(PitProSettings::TagSuffix);
            break;
        case OBS:
            return getValue(PitProSettings::ObsSuffix);
            break;
        case RCP:
            return getValue(PitProSettings::RecapSuffix);
            break;
        case MRT:
            return getValue(PitProSettings::MrtSuffix);
            break;
        default:
            return "";
    }
}

SitesMask PitProSettings::getSitesMask() {
    SitesMask mask;

    StringVector juvenileSites = getJuvenileSites();
    StringVector adultSites = getAdultSites();

    for (StringVector::const_iterator it = juvenileSites.begin(); it != juvenileSites.end(); ++it)
        mask.addSite((*it).c_str());
    for (StringVector::const_iterator it = adultSites.begin(); it != adultSites.end(); ++it)
        mask.addSite((*it).c_str());
    mask.setNumJuvenileSites(juvenileSites.size());
    mask.setNumMainSites(getIntValue(NumMainSites));
    mask.setSiteRel(isChecked(SiteRel));
    return mask;
}

bool PitProSettings::isBinary(int key) {
    switch (key) {
        case Usage: case Warnings:
            return true;
        default:
            return false;
    };
}

string PitProSettings::help(int key) {
    string s;

	switch (key) 
	{
	case AdultField :
        s = "An adult capture history field. Each field should be specified using a separate --adultField key";
/*        s = "The adult fields for the capture history. See \"histField\" below for " \
            "details on passing multiple fields and field ordering. A site can " \
            "be any one of:";
        for (SitesVector::const_iterator it = allsites.begin(); it != allsites.end(); ++it) {
            Site* site = *it;
            if (site->isAdult()) {
                s << std::endl;
                s << "\t" << std::setw(4) << site->getSiteCode() << ": ";
                s << site->getLongName();
            }*/
        break;
    case AdultModeSwitch :
        s = "Causes the program to attemp to determine fish stage (e.g. juvenile vs adult). " \
            "This is done using either migration year (see migrationYear) or a " \
            "juvenile cutoff date (see juvenileCutoffDate). If this is set to " \
            "false, all detections are assumed to be juveniles.";
        break;
	case AltRelDate :
		break;
	case AltSitesConfig :
        s = "Use the specified sites configuration file instead of the default.";
		break;
	case AnyRouteSwitch :
        s = "A method for mapping adult observation sequences that include. " \
            "fallback into capture histories. In this method a fish is " \
            "flagged as detected at a site if it is detected at any stage " \
            "of the migration. Contrast this with the \"last route\" " \
            "method (see lastRouteSwitch).";
		break;
	case AssumeJuvenile :
		break;
	case CensorJuvUpstreamSwitch :
		break;
	case CombineJacks :
		break;
	case DataDir :
		s = "The directory where data files are located.";
		break;
	case DdFileSwitch :
		s = "Output detection date file giving Julian Date of observation at each site (first and last).";
		break;
	case Dsplit :
        s = "Put the program in dsplit mode.";
        break;
    case ErrorsCheck:
        s = "When set to true, the program will check for and remove errors.";
        break;
	case ErrorsFileSwitch :
        s = "Generate output error file giving reason for removing fish.";
		break;
	case FilterByFileType :
		break;
	case GroupPrefix :
        s = "The group prefix defines the data set. For instance, if the " \
            "prefix is \"prefix\", the program will search for \"prefix.tag\", " \
            "\"prefix.obs\", \"prefix.mrt\", and \"prefix.rcp\", which are the " \
            "tag, observation, mortality, and recapture data, respectively. " \
            "Normally each group defined here is a separate run with separate output, " \
            "To combine the groups to generate one capture history file with a " \
            "separate population for each group, set groupRuns to true.";
		break;
	case GroupRuns :
        s = "Combine all groups into one capture history file, with a separate " \
            "population for each group. Other types of outputs are not " \
            "combined (e.g. errors, detection date, travel times, etc.).";
		break;
    case HistDetail:
        s = "Use different codes to differentiate between detection paths." \
            "  \"Std\" - simplified, compatible with previous versions." \
            "  \"All\" - almost every code separated out (0-7, 9).";
        break;
    case HistField :
        s = "A juvenile catpture history field. Each field should be specified using a separate --histField key.";
		break;
	case ICovSwitch :
		break;
	case IgnoreReRecaps :
        s = "Ignore a juvenile recapture at the release site.";
        break;
    case JulianDates :
        s = "When true julian dates are output in the detection date file. Otherwise " \
            "the dates are day of year with a fractional time added.";
        break;
	case JuvenileCutoffDate :
        s = "When provided the juvenile cutoff date divides the juvenile outmigration " \
            "from the adult outmigration. Dates must be in yyyymmdd format.";
		break;
	case JuvenileCutoffSwitch :
		break;
	case LastField :
		break;
	case LastOutcomeSwitch :
		break;
	case LastRouteSwitch :
		break;
	case MigrationYear :
        s = "The migration year provides a method for distinguishing" \
            "the juvenile outmigration from the adult migration.";
		break;
	case MigrationYearSwitch :
		break;
	case MortCheck :
		break;
	case NewRcFile :
		s = "Create a blank rc file.";
		break;
	case NullCovariateSwitch :
		break;
	case NumMainSites :
        s = "This gives the number of sites that will be represented in the" \
            "capture history, exclusive of the last field. All other sites" \
            "will be combined into the last field. ";
		break;
	case OutPrefix :
        s = "This is the name that prefixes the capture history file (e.g. outprefix.ch).";
		break;
	case OutputDir :
		s = "The directory where output should be written.";
		break;
	case OutputFormat :
		s = "Output format. One of SURPH1, SURPH2, or ROSTER.";
		break;
	case PitCodeRelKey :
		break;
	case RcFileName :
        s = "The name (or path) of the run time configuration (rc) file.";
		break;
	case RearType :
        s = "The rearing type. Use \"All\" to keep all rearing types.";
		break;
	case RelDate :
        s = "A release date that applies to all fish.";
		break;
	case ReleaseDataCheck :
        s = "Require a release date for a given fish when true. Fish without a date are removed";
		break;
	case RelFile :
		break;
	case RemovalTrumpsSwitch :
        s = "This controls the way multple observations at one site are combined into a " \
            "final disposition. The order or precedence is Sampled, Returned, and " \
            "Transported, in that order. So that if a fish is seen on a detector " \
            "that indicates sampling, this is the final disposition even if the " \
            "fish is subsequently observed on the return to river detector. If " \
            "this flag is set to false, the last detection (chronlogically) " \
            "is used. This is not used if histDetail set to \"All\".";
        break;
    case RemoveJacks :
        s = "The program will remove minijacks if this is set to true. The only way for the " \
             "program to identify a jack is if a juvenileCutoffDate is set. Any fish " \
             "detected in that year after the cuttoff date are considered to be minijacks. " \
             "Normally these fish are included in ocean age class 1 (\"A\").";
        break;
    case RemoveResidualizers :
        s = "Remove fish detected subsequent to the migration year on known juvenile detectors.";
        break;
    case ResCutoffDate :
        s = "A cutoff date for residualizing fish ";
		break;
	case ResCutoffSwitch :
		break;
	case Run :
        s = "The run. This will be compared to the tag file data to filter out " \
            "records that do not match. Use \"All\" to keep all runs";
		break;
	case RunsTable :
		break;
	case SampTransSwitch :
        s = "If this is true the program will treat all sampled fish as transported. "\
            "This is not used if histDetail set to \"All\".";
		break;
	case SequenceFileSwitch :
		s = "Output sequence file, showing sequence of processing steps for each fish.";
		break;
	case ShowConfig :
        s = "Display sites cofiguration and quit.";
		break;
	case ShowLambda :
		break;
	case SingleCoilSwitch :
        s = "Allow detections at a site on only one coil (site-wide).";
		break;
	case SiteRel :
		s = "Causes first captures history field to be treated as the release. Only includes fish detected and " \
			"re-released at this site.";
		break;
	case Species :
		s = "Species for the run, using PTAGIS designations 1-5";
		break;
	case Split :
		break;
	case SurphFileSwitch :
		s = "Write capture history file. Used for all formats, not just SURPH.";
		break;
	case SplitLevel :
		break;
	case TagCheck :
        s = "Remove observed tags not in the tag file.";
		break;
	case TagGroupRelKey :
		break;
	case TransSite :
        s = "Define transportation sites. ";
		break;
	case TruncUpJuvSwitch :
		break;
	case TtFileSwitch :
		s = "Output travel time file, giving travel times from release to each site.";
        break;
    case UnknownSwitch :
        s = "Use 'U' for unknown dispositions.";
        break;
	case Usage :
		s = "Display this message.";
		break;
	case UseSteelheadYear :
		break;
	case Version :
        s = "Display version information.";
		break;
	case Warnings :
		s = "Display warning messages.";
		break;
	case ZeroCovariateSwitch :
		break;
	}

    return s;
}

string PitProSettings::usage() {
    stringstream ss;


    ss << "** Note: this list is under construction. **" << endl << endl;

    for (int i = 0; i < NParams; i++) {
        string s = help(i);
        if (!s.empty()) {
            ss << getKeyName(i);

            ss << ": ";
            ss << s << endl;

            vector<string> values = getValues(i);
            if (values.size() > 0) {
                ss << "\tDefault: ";

                if (isBinary(i)) {
                    if (values[0].compare("0") == 0)
                        ss << "false";
                    else
                        ss << "true";
                } else if (values.size() > 0) {
                    for (vector<string>::iterator it = values.begin(); it != values.end(); ++it) {
                        if (it != values.begin())
                            ss << ", ";
                        ss << *it;
                    }
                }
            }

            ss << endl;

        }
    }

    ss << endl;

    return ss.str();//formatBlock(ss.str(), 0, 1);
}
