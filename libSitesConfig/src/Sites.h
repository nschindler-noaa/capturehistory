#ifndef Sites_h
#define Sites_h

#include <vector>
#include <iostream>

#include <ArrayDefs.h>

#include "Site.h"
#include "Code.h"

typedef std::vector<Site*> SitesVector;
typedef std::vector<Code*> CodesVector;

class Detector;

/**
 *  Keeps the site configuration information.
 *
 *  This is implemented as a singleton.
 */
class Sites {
public:

    static Sites* getInstance();
    ~Sites();

    void read(const std::string& sitesConfigFile); // read from given file
    void setFirstSite(Site* site);
    void clear();

    void addValidType(const std::string& type);
    void addValidStage(const std::string& stage);
    void addValidSite(const std::string& siteCode);
    void setLastSite(const std::string& code);

    int nsites() {
        return sites_.size();
    }

    int nrelsites() {
        return relsites_.size();
    }
    Site *getSite(const std::string& code, bool checkValid = false) const; // match siteCode or a detector code
    Site *getRelSite(const std::string& code) const; // match siteCode or a detector code
    Site* getSite(int id) const;
    Site* getSiteByCode(const std::string& code) const; // match siteCode

    const SitesVector& getSites() const {
        return sites_;
    }

    Site* getFirstSite() const {
        return firstSite_;
    }
    const Code* getCode(const std::string& codeName) const;

    const std::string& getConfigDate() const {
        return configDate;
    }

    const std::string& getPtagisDate() const {
        return ptagisDate;
    }
    int getSiteNumber(const std::string& code) const; // get the site number for the site

    /* valid sites - these are the sites that are valid based on
       the input parameters and the data. */
    const int* getActiveSites() const {
        return activeSites_;
    }
    Site* getActiveSite(int i) const;

    int getNumActiveSites() const {
        return numActiveSites_;
    }
    int getActiveSiteIndex(int siteId) const;
    int getNumPeriods() const;
    int isValid(const Site* site) const;
    int isValidType(const Site* site) const;
    int isValidStage(const Site* site) const;
    int isValidSite(const Site* site) const;

    Site* getLastSite() {
        return lastSite_;
    }
    const int* getMainSites();
    const int* getLastSites();

    int getNumMainSites() {
        return numMainSites_;
    }

    int getNumLastSites() {
        return numLastSites_;
    }


    /* outcomes */
    cbr::CbrPit::Outcome getOutcome(const std::string& codeName, const std::string& detector, double jd) const;
    int getHistFlag(const std::string& codeName, const std::string& detector, double jd) const;
    cbr::StringVector getCoils(const std::string& codeName, const std::string& detector, double jd) const;
    const Detector* getDetector(const std::string& codeName, const std::string& coil, double jd) const;

    friend std::ostream &operator <<(std::ostream &o, const Sites &sites);

private:
    Sites();

    SitesVector sites_;
    SitesVector relsites_;
    CodesVector codes_;

    cbr::StringVector validTypes_;
    cbr::StringVector validStages_;
    cbr::StringVector validSites_;

    int *activeSites_;
    int *mainSites_;
    int *lastSites_;
    int numActiveSites_;
    int numMainSites_;
    int numLastSites_;
    Site* firstSite_;
    Site* lastSite_; // the last site for which survivals can be calculated

    std::string configDate;
    std::string ptagisDate;

    void updateActiveSites();
    void updateSitesLists();

    void parseConfigFile(std::istream& in);
    void parseDetConfig(Detector& det, const std::string& line);
};

#endif






