/*
 * PitProSettings.h
 */

#ifndef PitProSettings_h
#define PitProSettings_h

#include <string>
#include <vector>


#include <ArrayDefs.h>
#include <StringUtil.h>

#include "Settings.h"
#include "RunConfigVector.h"
#include "SitesMask.h"

class PitProSettings : public Settings {
public:

    enum Parameters {
        AdultField = 0,
        AdultModeSwitch,
        AltRelDate,
        AltSitesConfig,
        AnyRouteSwitch,
        AssumeJuvenile,
        CensorJuvUpstreamSwitch,
        CoilSuffix,
        CombineJacks,
        ConfigSuffix,
        DataDir,
        DdFileSwitch,
        DdSuffix,
        Dsplit,
        ErrorsCheck,
        ErrorsFileSwitch,
        ErrorSuffix,
        FilterByFileType,
        GroupPrefix,
        GroupRuns,
        HistDetail,
        HistField,
        ICovSwitch,
        IgnoreReRecaps,
        JulianDates,
        JuvenileCutoffDate,
        JuvenileCutoffSwitch,
        LastField,
        LastOutcomeSwitch,
        LastRouteSwitch,
        MigrationYear,
        MigrationYearSwitch,
        MrtSuffix,
        MortCheck,
        NewRcFile,
//        NoHistTruncate,  // using HistDetail = All
        NullCovariateSwitch,
        NumMainSites,
        ObsSuffix,
        OutPrefix,
        OutputDir,
        OutputFormat,
        PitCodeRelKey,
        RcFileName,
        RearType,
        RecapSuffix,
        RecapToIgnore,
        RelDate,
        ReleaseDataCheck,
        RelFile,
        RelSuffix,
        RemoveJacks,
        RemoveResidualizers,
        RemovalTrumpsSwitch,
        ResCutoffDate,
        ResCutoffSwitch,
        Run,
        RunsTable,
        SampTransSwitch,
        SeqSuffix,
        SequenceFileSwitch,
        ShowConfig,
        ShowLambda,
        SingleCoilSwitch,
        SiteRel,
        Species,
        Split,
        SurphFileSwitch,
        SplitLevel,
        SurphSuffix,
        TagCheck,
        TagGroupRelKey,
        TagSuffix,
        TransSite,
        TruncUpJuvSwitch,
        TtFileSwitch,
        TtSuffix,
        UnknownSwitch,
        Usage,
        UseSteelheadYear,
		UseSteelheadYer, // used to fix previous misspelling
        Version,
        Warnings,
        ZeroCovariateSwitch,
        NParams
    };

    enum ColumnOrder {
        RUN = 0, TAG, OBS, RCP, MRT, NCOLS
    };

    static PitProSettings& getInstance();
    virtual ~PitProSettings();

    void setDefaults(bool clearDefs = false);
    void setConstants();
    bool verify();

    int getNumGroups();

    bool isGroupRuns() {
        return isChecked(GroupRuns);
    }

    bool showLambda() {
        return isChecked(ShowLambda);
    }
    cbr::StringVector getJuvenileSites();
    cbr::StringVector getAdultSites();
    cbr::StringVector getTransSites();
    std::string getPrefix(int run);
    std::string getMrtFile(int run);
    std::string getRelFile(int run);
    std::string getRunData(int run, ColumnOrder col);
    std::string getSuffix(ColumnOrder col);
    void getAllRunConfigs(RunConfigVector& runConfigVector);
    void getRunConfig(RunConfigVector& runConfigVector, int run);
    cbr::StringVector getFiles(ColumnOrder, int run = -1);
    cbr::StringVector getObsFiles(int run = -1);
    cbr::StringVector getTagFiles(int run = -1);
    cbr::StringVector getMortFiles(int run = -1);
    cbr::StringVector getReleaseFiles(int run = -1);
    std::string getObsFilePath(const std::string& prefix);
    std::string getTagFilePath(const std::string& prefix);
    std::string getOutFilePath(const std::string& fileName);
    std::string getDataFilePath(const std::string& fileName);
    bool ignoreRecap(const std::string& recap);
    std::string writeLegend();

    SitesMask getSitesMask();

    void clear();

    std::string help(int key);
    std::string usage();
    bool isBinary(int key);

    PitProSettings();

private:
    void setKeyNames();
    std::string writeParam(int key, const std::string& heading);
    std::string writeFileParam(ColumnOrder ord, const std::string& heading);
};

#endif // PitProSettings_h
