/*
 * Sites.cpp
 */

#include <functional>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringUtil.h>
#include <StringManip.h>

#include <QStringList>

#include "CbrPit.h"
#include "Sites.h"
#include "Code.h"
#include "Range.h"
#include "Exception.h"
#include "sites_config.h"

using namespace std;
using namespace cbr;

Sites* Sites::getInstance() {
    static Sites instance;
    return &instance;
}

Sites::Sites() :
activeSites_(0), mainSites_(0), lastSites_(0),
numActiveSites_(0), numMainSites_(0), numLastSites_(0),
firstSite_(0), lastSite_(0), configDate("??") {
}

Sites::~Sites() {
    clear();
}

void Sites::clear() {
    for (SitesVector::iterator it = sites_.begin(); it != sites_.end(); ++it)
        delete *it;
    delete[] activeSites_;

    sites_.clear();
    codes_.clear();

    activeSites_ = 0;
    mainSites_ = 0;
    lastSites_ = 0;
    numActiveSites_ = 0;
    numMainSites_ = 0;
    numLastSites_ = 0;
    firstSite_ = 0;
    lastSite_ = 0;
    configDate = "??";

    delete activeSites_;
}

void Sites::read(const string& sitesConfigFile) {
    // open the sites configuration file
    try {
        std::ifstream in(sitesConfigFile.c_str());

        // parse the config file
        parseConfigFile(in);
    } catch (...) {
        
    }
}

/*
 * Check the site against the validTypes_ list. If no validTypes_ are
 * defined then all sites are valid.
 */
int Sites::isValidType(const Site* site) const {
    if (validTypes_.size() == 0)
        return 1;

    const string& type = site->getType();
    if (type.empty())
        return 0;

    if (std::find(validTypes_.begin(), validTypes_.end(), "all") == validTypes_.end() &&
            std::find(validTypes_.begin(), validTypes_.end(), type) == validTypes_.end())
        return 0;

    return 1;
}

/*
 * Check the stage against the validStages_ list. If no validStages_ are
 * defined then all sites are valid.
 */
int Sites::isValidStage(const Site* site) const {
    // return true if no valid stages are defined 
    if (validStages_.size() == 0)
        return 1;

    // return true if 'all' is one of the valid stages
    if (std::find(validStages_.begin(), validStages_.end(), "all") != validStages_.end())
        return 1;

    // otherwise return true if any of the validstages matches a stage for the site
    StringVector::const_iterator it;
    for (it = validStages_.begin(); it != validStages_.end(); ++it) {
        if (site->stageMatch(*it))
            return 1;
    }


    // otherwise it's not valid
    return 0;
}

/*
 * Check the site code against the validSites_ list. If no validSites_ are
 * defined then all sites are valid.
 */
int Sites::isValidSite(const Site* site) const {
    if (validSites_.size() == 0)
        return 1;

    const string& siteCode = site->getSiteCode();
    if (siteCode.empty())
        return 0;

    if (std::find(validSites_.begin(), validSites_.end(), "all") == validSites_.end() &&
            std::find(validSites_.begin(), validSites_.end(), siteCode) == validSites_.end())
        return 0;

    return 1;
}

/*
 * If no stage is defined, all stages are valid. Likewise for
 * type: if no type is defined, all types are valid
 */
int Sites::isValid(const Site* site) const {
    if (isValidType(site) && isValidStage(site) && isValidSite(site))
        return 1;

    return 0;
}

void Sites::addValidType(const string& type) {
    validTypes_.push_back(type);
}

void Sites::addValidStage(const string& stage) {
    validStages_.push_back(stage);
}

void Sites::addValidSite(const string& siteCode) {
    validSites_.push_back(siteCode);
}

/*
 * Set mainSites_ and lastSites_ based on activeSites_
 */
void Sites::updateSitesLists() {
    mainSites_ = activeSites_;
    numMainSites_ = numActiveSites_;
    lastSites_ = 0;
    numLastSites_ = 0;

    if (numActiveSites_ > 1) {

        if (!lastSite_)
            lastSite_ = getActiveSite(numActiveSites_ - 2);

        numMainSites_ = 0;
        // update main sites
        int i;
        for (i = 0; i < numActiveSites_; i++) {
            ++numMainSites_;
            Site* site = getActiveSite(i);
            if (site == lastSite_)
                break;
        }

        // update last sites
        numLastSites_ = numActiveSites_ - numMainSites_;
        if (numLastSites_ == 0)
            lastSites_ = 0;
        else
            lastSites_ = activeSites_ + i + 1;
    }
}

void Sites::setLastSite(const string& code) {
    lastSite_ = getSiteByCode(code);
    updateSitesLists();
}

const int* Sites::getMainSites() {
    return mainSites_;
}

const int* Sites::getLastSites() {
    return lastSites_;
}

int Sites::getNumPeriods() const {
    if (numMainSites_ == numActiveSites_)
        return numMainSites_;
    else
        return numMainSites_ + 1;
}

/**
 *  No error checking done here. Config file needs
 *  to be perfect.
 */
void Sites::parseConfigFile(istream& in) {
    clear();

    Site *site = 0;
    Code *code = 0;
    Range *range = 0;

    string line;
    while (std::getline(in, line)) {
        line = line.substr(0, line.find_first_of("#"));

        QStringList toks;
//        std::list<string> toks;
        stringTok(toks, line.c_str(), " \t");

        if (toks.size() == 0)
            continue;

        string tok = toks.front().toStdString();
        toks.pop_front();

        // branch based on the first token
        if (!tok.compare("configDate:")) {
            configDate = toks.front().toStdString();
        } else if (!tok.compare("ptagisDate:") && toks.size() > 0) {
            ptagisDate = toks.front().toStdString();
        } else if (!tok.compare("site:") && toks.size() > 0) {
            site = new Site(nsites(), toks.front().toStdString());
            site->setReleaseSite(false);
            sites_.push_back(site);
        } else if (!tok.compare("relsite:") && toks.size() > 0) {
            site = new Site(nrelsites(), toks.front().toStdString());
            site->setReleaseSite(true);
            relsites_.push_back(site);
        } else if (!tok.compare("codes:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addCode(toks.at(i).toStdString());
//            for (list<string>::const_iterator it = toks.begin(); it != toks.end(); ++it)
//                site->addCode(*it);
        } else if (!tok.compare("code:") && toks.size() > 0) {
            code = new Code(toks.front().toStdString());
            codes_.push_back(code);
            if (toks.size() > 0 && !toks.front().toStdString().compare("ALL"))
                code->setAllReturned();
        } else if (!tok.compare("name:")) {
            site->setLongName(listToString(toks));
        } else if (!tok.compare("shortName:") && toks.size() > 0) {
            site->setShortName(toks.front().toStdString());
        } else if (!tok.compare("riverk:") && toks.size() > 0) {
            QStringList riverks;
//            std::vector<string> riverks;
            stringTok(riverks, toks.front(), "-");
            string riverkDn = riverks.at(0).toStdString();
            string riverkUp;
            if (riverks.size() > 1)
                riverkUp = riverks.at(1).toStdString();

            site->setRiverKm(riverkDn, riverkUp);
        } else if (!tok.compare("type:") && toks.size() > 0) {
            site->setType(toks.front().toStdString());
        } else if (!tok.compare("huc:") && toks.size() > 0) {
            site->setHuc(toks.front().toStdString());
        } else if (!tok.compare("indicator:") && toks.size() > 0) {
            site->setIndicator(toks.front().toStdString());
        } else if (!tok.compare("stage:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addStage(toks.at(i).toStdString());
//            for (list<string>::const_iterator it = toks.begin(); it != toks.end(); ++it)
//                site->addStage(*it);
        } else if (!tok.compare("range:") && toks.size() > 1) {
            string date1 = toks.front().toStdString();
            toks.pop_front();
            string date2 = toks.front().toStdString();
            range = new Range(date1, date2);
            code->addRange(range);
        } else if (!tok.compare("exception:")) {
            //  exception: 08-May-97+07:00:00 17-May-97+07:00:00 { R: U : 0 : A-RACEWAY/EXIT : 90 92 94 96 }
            if (toks.size() > 1) {
                string date1 = toks.front().toStdString();
                toks.pop_front();
                string date2 = toks.front().toStdString();
                toks.pop_front();
                string detConfig = line.substr(line.find_first_of("{"));

                Detector det;
                parseDetConfig(det, detConfig);

                Exception* ex = new Exception(QString(date1.c_str()), QString(date2.c_str()), det);
                code->addException(ex);
            }
        } else if (!tok.compare("H:") || !tok.compare("R:") || !tok.compare("S:") ||
                !tok.compare("T:") || !tok.compare("B:") || !tok.compare("U:")) {
            Detector det;
            parseDetConfig(det, line);
            range->addDetector(det);
        }

    }
}

/*
 * Takes string of form:
 *   <outcome> : <stage> : <order> : <detector name> : <coil 1> <coil 2> ... <coil n>
 *
 */
void Sites::parseDetConfig(Detector& det, const string& detConfig) {
    QStringList detToks;
//    vector<string> detToks;
    stringTok(detToks, QString(detConfig.data()), "{:}");

    enum {
        Outcome = 0, Stage, Order, Detector, Coils
    };
    
    for (int i = 0; i < detToks.size(); ++i) {
        string detTok = trim(detToks[i]);
        switch (i) {
            case Outcome:
                det.setOutcome(fromString<char>(detTok));
                break;
            case Stage:
                det.setStage(fromString<char>(detTok));
                break;
            case Order:
                det.setOrder(cbr::fromString<int>(detTok));
                break;
            case Detector:
                det.setDetectorName(detTok);
                break;
            case Coils:
            {
                QStringList coilToks;
//                vector<string> coilToks;
                stringTok(coilToks, QString(detTok.data()), " ");
                for (int i = 0; i < coilToks.count(); i++)
                    det.addCoil(coilToks.at(i).toStdString());
//                for (vector<string>::iterator it = coilToks.begin(); it != coilToks.end(); ++it)
//                    det.addCoil(*it);
            }
        }
    }
}

void Sites::setFirstSite(Site* site) {
    firstSite_ = site;
    updateActiveSites();
    updateSitesLists();
}

Site* Sites::getActiveSite(int i) const {
    return sites_[ activeSites_[ i ] ];
}

/**
 *  Return indices of all site downstream of the given
 *  site. Include the index of the given site. Return in
 *  sorted ( upstream to downstream order ). Terminate
 *  the indices with a -1. Only include the requested
 *  types (ie dam trap acclimation diversion)
 *
 *  Also, if mainFields have been set then only those
 *  sites can be valid
 *
 */
void Sites::updateActiveSites() {
    if (!firstSite_)
        return;

    bool firstSiteJuvenile = firstSite_->stageMatch("juvenile");


    if (activeSites_)
        delete[] activeSites_;
    activeSites_ = new int[ nsites() + 1 ];
    int n = 0;

    for (unsigned int i = 0; i < sites_.size(); i++) {
        Site *site = sites_[ i ];
        if (firstSite_ == site)
            activeSites_[ n++ ] = i;
        else {
            if (isValid(site)) {
                bool currentSiteJuvenile = site->stageMatch("juvenile");
                if (site->validRiverkm()) {
                    if (firstSiteJuvenile) {
                        if (!currentSiteJuvenile || site->isDownstream(firstSite_))
                            activeSites_[ n++ ] = i;
                    } else {
                        if (!currentSiteJuvenile && !site->isDownstream(firstSite_))
                            activeSites_[ n++ ] = i;
                    }
                }
            }
        }
    }

    // bubble sort based on total 
    for (int pass = 0; pass < n; pass++) {
        for (int i = 0; i < n - 1; i++) {
            Site *a = sites_[ activeSites_[ i ] ];
            Site *b = sites_[ activeSites_[ i + 1 ] ];
            if (a->isDownstream(b)) {
                int tmp = activeSites_[ i + 1 ];
                activeSites_[ i + 1 ] = activeSites_[ i ];
                activeSites_[ i ] = tmp;
            }
        }
    }

    activeSites_[ n ] = -1;
    numActiveSites_ = n;
}

Site *Sites::getSite(const string& code, bool checkValid) const {
    Site *site;
    for (unsigned int i = 0; i < sites_.size(); i++) {
        site = sites_[ i ];
        if (site->siteMatch(code)) {
            if (!checkValid)
                return site;
            else if (isValid(site))
                return site;
        }
    }
    return (Site*) 0;
}

Site *Sites::getRelSite(const string& code) const {
    Site *site;
    for (unsigned int i = 0; i < relsites_.size(); i++) {
        site = relsites_[ i ];
        if (site->siteMatch(code)) {
            return site;
        }
    }
    return (Site*) 0;
}

int Sites::getSiteNumber(const string& code) const {
    Site *site = getSite(code);
    if (!site)
        return 0;
    return site->getId();
}

Site *Sites::getSiteByCode(const string& siteCode) const {
    if (siteCode.empty())
        return 0;

    Site *site;
    for (unsigned int i = 0; i < sites_.size(); i++) {
        site = sites_[ i ];
        if (!siteCode.compare(site->getSiteCode()))
            return site;
    }
    return 0;
}

const Code *Sites::getCode(const string& codeName) const {
    if (!codeName.empty()) {
        Code *code = 0;
        for (unsigned int i = 0; i < codes_.size(); i++) {
            code = codes_[ i ];
            if (!codeName.compare(code->getName()))
                return code;
        }
    }
    return 0;
}

int Sites::getActiveSiteIndex(int siteId) const {
    int i;
    for (i = 0; i < numActiveSites_; i++) {
        if (siteId == activeSites_[ i ])
            return i;
    }
    return -1;
}

Site *Sites::getSite(int id) const {
    Site *site;
    for (unsigned int i = 0; i < sites_.size(); i++) {
        site = sites_[ i ];
        if (site->getId() == id)
            return site;
    }
    return (Site*) 0;
}

/**
 *  Given a coil, search the coil list for a match. If a
 *  match is found, return the outcome. 
 *
 */
CbrPit::Outcome Sites::getOutcome(const string& codeName, const string& detector, double jd) const {
    const Code* code = getCode(codeName);
    if (!code)
        return CbrPit::Invalid;
    return code->getOutcome(detector, jd);
}

/**
 *  Given a detector, search the coilReturned list for a match. If a
 *  match is found, return 1. Otherwise the returned/removed
 *  status is unknown so return a 2.
 *
 */
int Sites::getHistFlag(const string& codeName, const string& detector, double jd) const {
    for (unsigned int i = 0; i < codes_.size(); i++) {
        Code* code = codes_[ i ];
        if (codeName.compare(code->getName()) == 0) {
            CbrPit::Outcome outcome = code->getOutcome(detector, jd);
            if (outcome == CbrPit::Returned)
                return 1;
        }
    }

    return 2;
}

/**
 *  Given a detector, obs site, and detection date, return the coils
 *  the list of individual coils that make up the detector
 *
 */
StringVector Sites::getCoils(const string& siteCode, const string& detector, double jd) const {
    StringVector coils;
    for (unsigned int i = 0; i < codes_.size(); i++) {
        Code* code = codes_[ i ];
        if (siteCode.compare(code->getName()) == 0) {
            StringVector c = code->getCoils(detector, jd);
            coils.insert(coils.begin(), c.begin(), c.end());
        }
    }

    return coils;
}

const Detector* Sites::getDetector(const string& codeName, const string& coil, double jd) const {
    const Code* code = getCode(codeName);
    if (!code)
        return (Detector*) 0;

    return code->getDetector(coil, jd);
}

ostream &operator <<(ostream &o, const Sites &sites) {
    unsigned int i;

    o << "#" << endl;
    o << "# Site Configuration" << endl;
    o << "#" << endl << endl;
    o << "configDate: " << sites.getConfigDate() << endl;
    o << "ptagisDate: " << sites.getPtagisDate() << endl << endl;
    o << "#" << endl;
    o << "# Obervation Site Configuration" << endl;
    o << "#" << endl << endl;

    Code *code;
    for (i = 0; i < sites.codes_.size(); i++) {
        code = sites.codes_[ i ];
        o << *code << endl;
    }

    o << "#" << endl;
    o << "# Project Configuration" << endl;
    o << "#" << endl << endl;

    for (i = 0; i < sites.sites_.size(); i++) {
        Site* site = sites.sites_[ i ];
        o << *site << endl;
    }

    o << "#" << endl;
    o << "# Release sites" << endl;
    o << "#" << endl << endl;

    for (i = 0; i < sites.relsites_.size(); i++) {
        Site* relsite = sites.relsites_[ i ];
        o << *relsite << endl;
    }



    return o;
}





