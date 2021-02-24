#ifndef Sites_h
#define Sites_h

//#include <vector>
#include <iostream>

#include <ArrayDefs.h>

#include <QStringList>
#include <QFile>

#include "Site.h"
#include "Code.h"

typedef QList<Site*> SitesList;
typedef QList<Code*> CodesList;

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

    void read(const QString sitesConfigFile); // read from given file
    void setFirstSite(Site* site);
    void clear();

    void addValidType(const QString type);
    void addValidStage(const QString stage);
    void addValidSite(const QString siteCode);
    void setLastSite(const QString code);

    int nsites() { return sites_.size(); }
    int nrelsites() { return relsites_.size(); }
    Site *getSite(const QString code, bool checkValid = false) const; // match siteCode or a detector code
    Site *getRelSite(const QString code) const; // match siteCode or a detector code
    Site* getSite(int id) const;
    Site* getSiteByCode(const QString code) const; // match siteCode

    const SitesList& getSites() const { return sites_; }

    Site* getFirstSite() const { return firstSite_; }
    const Code* getCode(const QString codeName) const;

    const QString getConfigDate() const { return configDate; }

    const QString getPtagisDate() const { return ptagisDate; }
    int getSiteNumber(const QString code) const; // get the site number for the site

    /* valid sites - these are the sites that are valid based on
       the input parameters and the data. */
    const int* getActiveSites() const { return activeSites_; }
    Site* getActiveSite(int i) const;

    int getNumActiveSites() const { return numActiveSites_; }
    int getActiveSiteIndex(int siteId) const;
    int getNumPeriods() const;
    bool isValid(const Site* site) const;
    bool isValidType(const Site* site) const;
    bool isValidStage(const Site* site) const;
    bool isValidSite(const Site* site) const;

    Site* getLastSite() { return lastSite_; }
    const int* getMainSites();
    const int* getLastSites();

    int getNumMainSites() { return numMainSites_; }
    int getNumLastSites() { return numLastSites_; }


    /* outcomes */
    cbr::CbrPit::Outcome getOutcome(const QString codeName, const QString detector, double jd) const;
    int getHistFlag(const QString codeName, const QString detector, double jd) const;
    QStringList getCoils(const QString codeName, const QString detector, double jd) const;
    const Detector* getDetector(const QString codeName, const QString coil, double jd) const;

    friend std::ostream &operator <<(std::ostream &o, const Sites &sites);

private:
    Sites();

    SitesList sites_;
    SitesList relsites_;
    CodesList codes_;

    QStringList validTypes_;
    QStringList validStages_;
    QStringList validSites_;

    int *activeSites_;
    int *mainSites_;
    int *lastSites_;
    int numActiveSites_;
    int numMainSites_;
    int numLastSites_;
    Site* firstSite_;
    Site* lastSite_; // the last site for which survivals can be calculated

    QString configDate;
    QString ptagisDate;

    void updateActiveSites();
    void updateSitesLists();

    void parseConfigFile(std::istream& in);
    void parseConfigFile(QFile *infile);
    void parseDetConfig(Detector& det, const QString line);
};

#endif






