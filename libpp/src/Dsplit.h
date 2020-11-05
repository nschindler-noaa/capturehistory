/*
*/

#include <string>
#include <list>
#include <fstream>

#include <ArrayDefs.h>
#include <Site.h>
#include "RunConfigVector.h"
#include "PPOutputMaker.h"
#include "PPObs.h"
#include "OFile.h"
#include "PCode.h"

typedef std::list<OFile> OFileList;
typedef std::list<PPObs> ObsList;
typedef std::list<PCode> PCodeList;


class Dsplit {
public:
    Dsplit (PPOutputMaker& out);
    ~Dsplit ();
    void split (const RunConfigVector& runConfigVector);
    bool isTargetSiteValid() const { return targetSite != 0; }

private:
	PPOutputMaker& out;
    RunConfigItem runItem;
    Site* targetSite;
    double cutoffDate;
    std::string outDir;
    std::string dataDir;
    bool singleCoilSwitch;

    cbr::StringVector codel;

    void splitObs();
    void splitTag();
    void parseData();
    void parseObs(ObsList& obsl, PCodeList& pcl, const std::string& obsfile);
    void writeObs(OFileList& ofilel, cbr::StringVector& ofnl, PCodeList& pcl, ObsList& obsl);
    void writeTag(OFileList& ofilel, cbr::StringVector& tfnl, PCodeList& pcl, const std::string& tagfile);
    void cleanupData();


    static const int nfilelim;
    static std::ofstream& getOFStream(OFileList& ofilel, cbr::StringVector& fnl, 
        const std::string& filen);
    static std::string getSplitCode(const std::string& pitcode);
};
