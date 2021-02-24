/*
*/

#include <string>
#include <list>
#include <fstream>
#include <QStringList>
#include <QFile>

#include <ArrayDefs.h>
#include <Site.h>
#include "RunConfigVector.h"
#include "PPOutputMaker.h"
#include "PPObs.h"
#include "OFile.h"
#include "PCode.h"


typedef QList<OFile> OFileList;
typedef QList<PPObs> ObsList;
typedef QList<PCode> PCodeList;

typedef QList<QFile *> QFileList;


class Dsplit {
public:
    Dsplit(PPOutputMaker& out_);
    void split(const RunConfigVector& runConfigVector);
    bool isTargetSiteValid() const { return targetSite != nullptr; }

private:
    PPOutputMaker& out;
    RunConfigItem runItem;
    Site* targetSite;
    double cutoffDate;
    QString outDir;
    QString dataDir;

    QStringList codel;

    void splitObs();
    void splitTag();
    void parseData();
    void parseObs(ObsList& obsl, PCodeList& pcl, const QString obsfile);
    void writeObs(OFileList& ofilel, QStringList& ofnl, PCodeList& pcl, ObsList& obsl);
    void writeTag(OFileList& ofilel, QStringList& tfnl, PCodeList& pcl, const QString tagfile);
    void cleanupData();


    static const int nfilelim;
    static std::ofstream& getOFStream(OFileList& ofilel, QStringList& fnl,
        const QString filen);
    static QString getSplitCode(const QString pitcode);
};
