/*
 * PitProSettings.h
 */

#ifndef PitProSettings_h
#define PitProSettings_h

#include <string>
#include <vector>

#include <QStringList>

#include <ArrayDefs.h>
#include <StringUtil.h>

#include "Settings.h"
#include "RunConfigVector.h"
#include "SitesMask.h"

class PitProSettings : public Settings {
public:

    enum Parameter {
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
        LengthCovSwitch,
        MigrationYear,
        MigrationYearSwitch,
        MrtSuffix,
        MortCheck,
        MortFile,
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
        RelSite,
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
        ZeroLengthSwitch,
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
    QStringList getJuvenileSites();
    QStringList getAdultSites();
    QStringList getTransSites();
    QString getPrefix(int run);
    QString getMrtFile(int run);
    QString getRelFile(int run);
    QString getRunData(int run, ColumnOrder col);
    QString getSuffix(ColumnOrder col);
    void getAllRunConfigs(RunConfigVector& runConfigVector);
    void getRunConfig(RunConfigVector& runConfigVector, int run);
    QStringList getFiles(ColumnOrder, int run = -1);
    QStringList getObsFiles(int run = -1);
    QStringList getTagFiles(int run = -1);
    QStringList getMortFiles(int run = -1);
    QStringList getReleaseFiles(int run = -1);
    QString getObsFilePath(const QString prefix);
    QString getTagFilePath(const QString prefix);
    QString getOutFilePath(const QString fileName);
    QString getDataFilePath(const QString fileName);
    bool ignoreRecap(const QString recap);
    QString writeLegend();

    SitesMask getSitesMask();

    void clear();

    QString help(int key);
    QString usage();
    bool isBinary(int key);

    PitProSettings();

private:
    void setKeyNames();
    QString writeParam(int key, const QString heading);
    QString writeFileParam(ColumnOrder ord, const QString heading);
};

#endif // PitProSettings_h
