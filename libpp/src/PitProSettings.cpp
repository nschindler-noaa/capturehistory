
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

//using namespace cbr;
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
    setValue(Version, "4.21.0");

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

QString
PitProSettings::getObsFilePath(const QString prefix) {
    QString suffix = getValue(ObsSuffix);
    QString fileName = prefix + "." + suffix;
    return getDataFilePath(fileName);
}

QString
PitProSettings::getTagFilePath(const QString prefix) {
    QString suffix = getValue(TagSuffix);
    QString fileName = prefix + "." + suffix;
    return getDataFilePath(fileName);
}

QString
PitProSettings::getDataFilePath(const QString fileName) {
    QString dir = getValue(DataDir);
    QString filePath = dir + "/" + fileName;
    return filePath;
}

QString
PitProSettings::getOutFilePath(const QString fileName) {
    QString dir = getValue(OutputDir);
    QString filePath = dir + "/" + fileName;
    return filePath;
}

void
PitProSettings::clear() {
    Settings::clear();
}

bool
PitProSettings::verify() {
    QStringList histList = getValues(PitProSettings::HistField);
    if (histList.size() == 0) {
        lastError = "No main fields defined.";
        return false;
    }

    if (isChecked(GroupRuns)) {
        QString prefix = getValue(OutPrefix);
        if (prefix.isEmpty()) {
            lastError = "No output file prefix defined!";
            return true;
        }
    }

    // check directories
    if (access(getValue(DataDir).toStdString().c_str(), 0) == -1) {
        lastError = "Input directory does not exist!";
        return false;
    }

    if (access(getValue(OutputDir).toStdString().c_str(), 0) == -1) {
        lastError = "Output directory does not exist!";
        return false;
    }

    return true;
}

QStringList PitProSettings::getJuvenileSites() {
    QStringList siteNames;
    QStringList fields = getValues(HistField);
    Sites* sites = Sites::getInstance();
//    for (QStringList::iterator it = fields.begin(); it != fields.end(); ++it) {
    for (int i = 0; i < fields.count(); i++) {
        Site* site = sites->getSite(fields.at(i));//Site* site = sites->getSite(*it);
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

QStringList PitProSettings::getAdultSites() {
    QStringList siteNames;
    QStringList fields = getValues(AdultField);
    Sites* sites = Sites::getInstance();
//    for (QStringList::iterator it = fields.begin(); it != fields.end(); ++it) {
    for (int i = 0; i < fields.count(); i++) {
        Site* site = sites->getSite(fields.at(i));//Site* site = sites->getSite(*it);
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

QStringList PitProSettings::getTransSites() {
    QStringList siteNames;
    QStringList fields = getValues(TransSite);
    Sites* sites = Sites::getInstance();
    for (int i = 0; i < fields.count(); i++) {
        Site* site = sites->getSite(fields.at(i));//sites->getSite(*it);
        if (site)
            siteNames.push_back(site->getSiteCode());
    }
    return siteNames;
}

int PitProSettings::getNumGroups() {
    QStringList prefixes = getValues(PitProSettings::GroupPrefix);
    if (prefixes.size() > 0)
        return prefixes.size();

    QStringList runs = getValues(PitProSettings::RunsTable);
    int ncols = NCOLS;
    return runs.size() / ncols;
}

QString PitProSettings::getPrefix(int run) {
    QStringList runs = getValues(RunsTable);
    int ncols = NCOLS;
    return runs[ run * ncols + RUN ];
}

QString PitProSettings::getMrtFile(int run) {
    QStringList runs = getValues(RunsTable);
    int ncols = NCOLS;
    return runs[ run * ncols + MRT ];
}

QString PitProSettings::getRunData(int run, ColumnOrder col) {
    QString dataFile;

    QStringList prefixes = getValues(PitProSettings::GroupPrefix);
    if (prefixes.size() > 0) {
        QString prefix = getValue(PitProSettings::GroupPrefix, run);
        if (!prefix.isEmpty()) {
            if (col == RUN)
                dataFile = prefix;
            else
                dataFile = prefix + "." + getSuffix(col);
        }
    } else {

        QStringList runs = getValues(RunsTable);

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

QStringList PitProSettings::getFiles(ColumnOrder col, int run) {
    QStringList prefixes;
    if (run != -1)
        prefixes.push_back(getRunData(run, col));
    else {
        for (int i = 0; i < getNumGroups(); ++i) {
            prefixes.push_back(getRunData(i, col));
        }
    }
    return prefixes;
}

QStringList PitProSettings::getObsFiles(int run) {
    return getFiles(OBS, run);
}

QStringList PitProSettings::getTagFiles(int run) {
    return getFiles(TAG, run);
}

QStringList PitProSettings::getMortFiles(int run) {
    return getFiles(MRT, run);
}

bool PitProSettings::ignoreRecap(const QString recap) {
    bool result = false;
    QStringList recapSites = getValues(RecapToIgnore);
    if (recapSites.contains(recap))
        result = true;
    return result;
//    if (find(recapSites.begin(), recapSites.end(), recap) == recapSites.end())
//        return false;
//    return true;
}

QString PitProSettings::writeLegend() {
    QString legend;
    legend.append(writeParam(DataDir, "Data Folder"));
    legend.append(' ');
    legend.append(writeParam(OutputDir, "Output Folder"));
    return legend;
//    stringstream ss;

//    ss << writeParam(DataDir, "Data Folder");
//    ss << writeParam(OutputDir, "Output Folder");
    //ss << writeFileParam(OBS, "Interrogation data");
    //ss << writeFileParam(TAG, "Tag data");
    //ss << writeFileParam(RCP, "Recapture data");
    //ss << writeFileParam(MRT, "Mortatlity data");

//    return ss.str();
}

QString PitProSettings::writeFileParam(ColumnOrder ord, const QString heading) {
    QStringList files = getFiles(ord, -1);
    QString text(QString("# %1:\n").arg(heading));
    if (files.count() > 0) {
        for (int i = 0; i < files.count(); i++)
            text.append(QString("#     %1\n").arg(files.at(i)));
    }
    else {
        text.append(QString("#     NA\n"));
    }
    text.append("#\n");
    return text;

//    stringstream ss;
//    ss << "# " << heading << ":" << endl;

//    if (files.size() == 0)
//        ss << "#	NA" << endl;
//    else {;
//        for (StringVector::iterator it = files.begin(); it != files.end(); ++it) {
//            ss << "#     " << *it << endl;
//        }
//    }
//    ss << "#" << endl;
//    return ss.str();
}

QString PitProSettings::writeParam(int key, const QString heading) {
    QString value = getValue(key);
    QString text(QString("# %1:\n").arg(heading));
    text.append(QString("#     %1\n").arg(value));
    text.append("#\n");
    return text;

//    stringstream ss;
//    ss << "# " << heading << ":" << endl;
//    ss << "#     " << value << endl;
//    ss << "#" << endl;
//    return ss.str();
}

QString PitProSettings::getSuffix(ColumnOrder col) {
    QString text;
    switch (col) {
        case TAG:
            text = getValue(PitProSettings::TagSuffix);
            break;
        case OBS:
            text = getValue(PitProSettings::ObsSuffix);
            break;
        case RCP:
            text = getValue(PitProSettings::RecapSuffix);
            break;
        case MRT:
            text = getValue(PitProSettings::MrtSuffix);
            break;
        default:
            text = QString("");
    }
    return text;
}

SitesMask PitProSettings::getSitesMask() {
    SitesMask mask;

    QStringList juvenileSites = getJuvenileSites();
    QStringList adultSites = getAdultSites();

    for (int i = 0; i < juvenileSites.count(); i++)
        mask.addSite(juvenileSites.at(i));
    for (int i = 0; i < adultSites.count(); i++)
        mask.addSite(adultSites.at(i));
//    for (StringVector::const_iterator it = juvenileSites.begin(); it != juvenileSites.end(); ++it)
//        mask.addSite((*it).c_str());
//    for (StringVector::const_iterator it = adultSites.begin(); it != adultSites.end(); ++it)
//        mask.addSite((*it).c_str());
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

QString PitProSettings::help(int key) {
    QString s;

    switch (key)
    {
    case AdultField :
        s = "An adult capture history field. Each field should be specified using a seperate --adultField key";
        break;
    case AdultModeSwitch :
        break;
    case AltRelDate :
        break;
    case AltSitesConfig :
        s = "Use the given file as the sites configuration file.";
        break;
    case AnyRouteSwitch :
        break;
    case AssumeJuvenile :
        break;
    case CensorJuvUpstreamSwitch :
        break;
    case HistDetail:
        s = "Granularity of output detection codes; either \"Std\" or \"All\"";
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
        break;
    case ErrorsFileSwitch :
        s = "Output error file giving reason for removing fish.";
        break;
    case FilterByFileType :
        break;
    case GroupPrefix :
        break;
    case GroupRuns :
        break;
    case HistField :
        s = "A juvenile catpture history field. Each field should be specified using a seperate --histField key.";
        break;
    case ICovSwitch :
        break;
    case IgnoreReRecaps :
        break;
    case JuvenileCutoffDate :
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
        break;
    case OutPrefix :
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
        break;
    case RearType :
        break;
    case RelDate :
        break;
    case ReleaseDataCheck :
        break;
    case RelFile :
        break;
    case RemoveJacks :
        break;
    case RemoveResidualizers :
        break;
    case RemovalTrumpsSwitch :
        break;
    case ResCutoffDate :
        break;
    case ResCutoffSwitch :
        break;
    case Run :
        break;
    case RunsTable :
        break;
    case SampTransSwitch :
        break;
    case SequenceFileSwitch :
        s = "Output sequence file, showing sequence of processing steps for each fish.";
        break;
    case ShowConfig :
        break;
    case ShowLambda :
        break;
    case SingleCoilSwitch :
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
        break;
    case TagGroupRelKey :
        break;
    case TransSite :
        break;
    case TruncUpJuvSwitch :
        break;
    case TtFileSwitch :
        s = "Output travel time file, giving travel times from release to each site.";
        break;
    case Usage :
        s = "Display this message.";
        break;
    case UseSteelheadYear :
        break;
    case Version :
        break;
    case Warnings :
        s = "Display warning messages.";
        break;
    case ZeroCovariateSwitch :
        break;
    }

    return s;
}

QString PitProSettings::usage() {
    QString ss;
//    stringstream ss;


    ss.append("Note: this list is under construction.\n\n");// << endl << endl;

    for (int i = 0; i < NParams; i++) {
        QString s = help(i);
        if (!s.isEmpty()) {
            ss.append(QString("%1: %2").arg(getKeyName(i), s));

//            ss << ": ";
//            ss << s;

            QStringList values = getValues(i);
            if (values.size() > 0)
                ss.append(" Default: ");
            if (isBinary(i))
            {
                if (values[0].compare("0") == 0)
                    ss.append("false");
                else
                    ss.append("true");

            }
            else {
                for (int i = 0; i < values.count(); i++)
                    ss.append(QString(", %1").arg(values.at(i)));
            }
            ss.append('\n');
        }
        ss.append('\n');
    }
    return ss;

/*            if (values.size() > 0) {
                ss << " Default: ";

                if (isBinary(i)) {
                    if (values[0].compare("0") == 0)
                        ss << "false";
                    else
                        ss << "true";
                } else if (values.size() > 0) {
                    for (QStringList::iterator it = values.begin(); it != values.end(); ++it) {
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

    return ss.str();*/
}
