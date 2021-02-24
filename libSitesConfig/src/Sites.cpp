/*
 * Sites.cpp
 */

#include <functional>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
//#include <list>
//#include <vector>

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
activeSites_(nullptr), mainSites_(nullptr), lastSites_(nullptr),
numActiveSites_(0), numMainSites_(0), numLastSites_(0),
firstSite_(nullptr), lastSite_(nullptr), configDate(QString("??")) {
}

Sites::~Sites() {
    clear();
}

void Sites::clear() {
    for (SitesList::iterator it = sites_.begin(); it != sites_.end(); ++it)
        delete *it;
    delete[] activeSites_;

    sites_.clear();
    codes_.clear();

    activeSites_ = nullptr;
    mainSites_ = nullptr;
    lastSites_ = nullptr;
    numActiveSites_ = 0;
    numMainSites_ = 0;
    numLastSites_ = 0;
    firstSite_ = nullptr;
    lastSite_ = nullptr;
    configDate = "??";

    delete activeSites_;
}

void Sites::read(const QString sitesConfigFile) {
    // open the sites configuration file
    QFile *infile = new QFile(sitesConfigFile);
    try {
        infile->open(QIODevice::ReadOnly);
//        std::ifstream in(sitesConfigFile.toStdString().c_str());

        // parse the config file
        //parseConfigFile(in);
        parseConfigFile(infile);
    } catch (...) {

    }
}

/*
 * Check the site against the validTypes_ list. If no validTypes_ are
 * defined then all sites are valid.
 */
bool Sites::isValidType(const Site* site) const {
    bool result = true;
    if (site) {
        const QString type = site->getType();
        if (validTypes_.size() == 0)
            result = true;

        else if (type.isEmpty())
            result = false;

        else if (!validTypes_.contains("all", Qt::CaseInsensitive) &&
                !validTypes_.contains(type, Qt::CaseInsensitive))
           result = false;
    //    if (std::find(validTypes_.begin(), validTypes_.end(), "all") == validTypes_.end() &&
    //            std::find(validTypes_.begin(), validTypes_.end(), type) == validTypes_.end())
    //        return 0;
    }
    return result;
}

/*
 * Check the stage against the validStages_ list. If no validStages_ are
 * defined then all sites are valid.
 */
bool Sites::isValidStage(const Site* site) const {
    // set default to not valid
    bool result = false;
    // return true if no valid stages are defined
    if (validStages_.size() == 0) {
        result = true;
    }
    // return true if 'all' is one of the valid stages
    else if (validStages_.contains("all", Qt::CaseInsensitive)) {//std::find(validStages_.begin(), validStages_.end(), "all") != validStages_.end())
        result = true;
    }
    // otherwise return true if any of the validstages matches a stage for the site
    else if (site != nullptr) {
        for (int i = 0; i < validStages_.count(); i++) {
            if (site->stageMatch(validStages_.at(i)))
                result = true;
        }
    }
    return result;
}

/*
 * Check the site code against the validSites_ list. If no validSites_ are
 * defined then all sites are valid.
 */
bool Sites::isValidSite(const Site* site) const {
    bool result = true;
    if (validSites_.size() > 0) {
        const QString siteCode = site->getSiteCode();
        if (siteCode.isEmpty())
            result = false;

        else if (std::find(validSites_.begin(), validSites_.end(), "all") == validSites_.end() &&
                std::find(validSites_.begin(), validSites_.end(), siteCode) == validSites_.end())
            result = false;
    }
    return result;
}

/*
 * If no stage is defined, all stages are valid. Likewise for
 * type: if no type is defined, all types are valid
 */
bool Sites::isValid(const Site* site) const {
    bool result = false;
    if (isValidType(site) && isValidStage(site) && isValidSite(site))
        result = true;

    return result;
}

void Sites::addValidType(const QString type) {
    validTypes_.push_back(type);
}

void Sites::addValidStage(const QString stage) {
    validStages_.push_back(stage);
}

void Sites::addValidSite(const QString siteCode) {
    validSites_.push_back(siteCode);
}

/*
 * Set mainSites_ and lastSites_ based on activeSites_
 */
void Sites::updateSitesLists() {
    mainSites_ = activeSites_;
    numMainSites_ = numActiveSites_;
    lastSites_ = nullptr;
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
            lastSites_ = nullptr;
        else
            lastSites_ = activeSites_ + i + 1;
    }
}

void Sites::setLastSite(const QString code) {
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
    int num = 0;
    if (numMainSites_ == numActiveSites_)
        num = numMainSites_;
    else
        num = numMainSites_ + 1;
    return num;
}

/**
 *  No error checking done here. Config file needs
 *  to be perfect.
 */
void Sites::parseConfigFile(istream& in) {
    clear();

    Site *site = nullptr;
    Code *code = nullptr;
    Range *range = nullptr;

    std::string line;
    while (std::getline(in, line)) {
        line = line.substr(0, line.find_first_of("#"));

        QStringList toks;
        stringTok(toks, QString(line.c_str()), " \t");

        if (toks.size() == 0)
            continue;

        QString tok = toks.takeFirst();

        // branch based on the first token
        if (!tok.compare("configDate:")) {
            configDate = toks.first();
        }
        else if (!tok.compare("ptagisDate:") && toks.size() > 0) {
            ptagisDate = toks.first();
        }
        else if (!tok.compare("site:") && toks.size() > 0) {
            site = new Site(nsites(), toks.first());
            site->setReleaseSite(false);
            sites_.push_back(site);
        }
        else if (!tok.compare("relsite:") && toks.size() > 0) {
            site = new Site(nrelsites(), toks.first());
            site->setReleaseSite(true);
            relsites_.push_back(site);
        }
        else if (!tok.compare("codes:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addCode(toks.first());
        }
        else if (!tok.compare("code:") && toks.size() > 0) {
            code = new Code(toks.front());
            codes_.push_back(code);
            if (toks.size() > 0 && !toks.front().compare("ALL"))
                code->setAllReturned();
        }
        else if (!tok.compare("name:")) {
            site->setLongName(listToString(toks));
        }
        else if (!tok.compare("shortName:") && toks.size() > 0) {
            site->setShortName(toks.first());
        }
        else if (!tok.compare("riverk:") && toks.size() > 0) {
            QStringList riverks;
            stringTok(riverks, toks.front(), "-");
            QString riverkDn = riverks.at(0);
            QString riverkUp;
            if (riverks.size() > 1)
                riverkUp = riverks.at(1);
            site->setRiverKm(riverkDn, riverkUp);
        }
        else if (!tok.compare("type:") && toks.size() > 0) {
            site->setType(toks.first());
        }
        else if (!tok.compare("huc:") && toks.size() > 0) {
            site->setHuc(toks.first());
        }
        else if (!tok.compare("indicator:") && toks.size() > 0) {
            site->setIndicator(toks.first());
        }
        else if (!tok.compare("stage:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addStage(toks.first());
        }
        else if (!tok.compare("range:") && toks.size() > 1) {
            QString date1 = toks.first();
            toks.pop_front();
            QString date2 = toks.first();
            range = new Range(date1, date2);
            code->addRange(range);
        }
        else if (!tok.compare("exception:")) {
            //  exception: 08-May-97+07:00:00 17-May-97+07:00:00 { R: U : 0 : A-RACEWAY/EXIT : 90 92 94 96 }
            if (toks.size() > 1) {
                QString date1 = toks.first();
                toks.pop_front();
                QString date2 = toks.first();
                toks.pop_front();
                QString detConfig = QString(line.substr(line.find_first_of("{")).c_str());

                Detector det;
                parseDetConfig(det, detConfig);

                Exception* ex = new Exception(QString(date1), QString(date2), det);
                code->addException(ex);
            }
        }
        else if (!tok.compare("H:") || !tok.compare("R:") || !tok.compare("S:") ||
                 !tok.compare("T:") || !tok.compare("B:") || !tok.compare("U:") ||
                 !tok.compare("W:") || !tok.compare("P:") || !tok.compare("A:") ||
                 !tok.compare("D:") || !tok.compare("G:") || !tok.compare("M:") ||
                 !tok.compare("V:")) {
            Detector det;
            parseDetConfig(det, QString(line.c_str()));
            range->addDetector(det);
        }

    }
}

#define MAXLINE 1024

void Sites::parseConfigFile(QFile *infile) {
    clear();

    Site *site = nullptr;
    Code *code = nullptr;
    Range *range = nullptr;

    QString line;
    QStringList toks;
    QString tok;

    while (!infile->atEnd()) {//std::getline(in, line)) {
        line = QString(infile->readLine(MAXLINE)).simplified();
        line = line.section('#', 0, 0);
//        line = line.substr(0, line.find_first_of("#"));

        toks.clear();
        stringTok(toks, line, " \t");

        if (toks.size() == 0)
            continue;

        tok = toks.takeFirst();

        // branch based on the first token
        if (!tok.compare("configDate:")) {
            configDate = toks.takeFirst();
        }
        else if (!tok.compare("ptagisDate:") && toks.size() > 0) {
            ptagisDate = toks.takeFirst();
        }
        else if (!tok.compare("site:") && toks.size() > 0) {
            site = new Site(nsites(), toks.takeFirst());
            site->setReleaseSite(false);
            sites_.push_back(site);
        }
        else if (!tok.compare("relsite:") && toks.size() > 0) {
            site = new Site(nrelsites(), toks.takeFirst());
            site->setReleaseSite(true);
            relsites_.push_back(site);
        }
        else if (!tok.compare("codes:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addCode(toks.takeFirst());
        }
        else if (!tok.compare("code:") && toks.size() > 0) {
            code = new Code(toks.front());
            codes_.push_back(code);
            if (toks.size() > 0 && !toks.front().compare("ALL"))
                code->setAllReturned();
        }
        else if (!tok.compare("name:")) {
            site->setLongName(listToString(toks));
        }
        else if (!tok.compare("shortName:") && toks.size() > 0) {
            site->setShortName(toks.takeFirst());
        }
        else if (!tok.compare("riverk:") && toks.size() > 0) {
            QStringList riverks;
            stringTok(riverks, toks.front(), "-");
            QString riverkDn = riverks.at(0);
            QString riverkUp;
            if (riverks.size() > 1)
                riverkUp = riverks.at(1);
            site->setRiverKm(riverkDn, riverkUp);
        }
        else if (!tok.compare("type:") && toks.size() > 0) {
            site->setType(toks.takeFirst());
        }
        else if (!tok.compare("huc:") && toks.size() > 0) {
            site->setHuc(toks.takeFirst());
        }
        else if (!tok.compare("indicator:") && toks.size() > 0) {
            site->setIndicator(toks.takeFirst());
        }
        else if (!tok.compare("stage:")) {
            for (int i = 0; i < toks.count(); i++)
                site->addStage(toks.takeFirst());
        }
        else if (!tok.compare("range:") && toks.size() > 1) {
            QString date1 = toks.takeFirst();
            QString date2 = toks.takeFirst();
            range = new Range(date1, date2);
            code->addRange(range);
        }
        else if (!tok.compare("exception:")) {
            //  exception: 08-May-97+07:00:00 17-May-97+07:00:00 { R: U : 0 : A-RACEWAY/EXIT : 90 92 94 96 }
            if (toks.size() > 1) {
                QString date1 = toks.first();
                toks.pop_front();
                QString date2 = toks.first();
                toks.pop_front();
                QString detConfig = line.section('{', 1, 1);//QString(line.substr(line.find_first_of("{")).c_str());

                Detector det;
                parseDetConfig(det, detConfig);

                Exception* ex = new Exception(QString(date1), QString(date2), det);
                code->addException(ex);
            }
        }
        else if (!tok.compare("H:") || !tok.compare("R:") || !tok.compare("S:") ||
                 !tok.compare("T:") || !tok.compare("B:") || !tok.compare("U:") ||
                 !tok.compare("W:") || !tok.compare("P:") || !tok.compare("A:") ||
                 !tok.compare("D:") || !tok.compare("G:") || !tok.compare("M:") ||
                 !tok.compare("V:")) {
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
void Sites::parseDetConfig(Detector& det, const QString detConfig) {
    QStringList detToks;
    stringTok(detToks, detConfig, "{:}");

    enum {
        Outcome = 0, Stage, Order, Detector, Coils
    };

    for (int i = 0; i < detToks.size(); ++i) {
        QString detTok(detToks.at(i).simplified());//.toLocal8Bit().data();
        switch (i) {
            case Outcome:
                det.setOutcome(detTok[0].toLatin1());
                break;
            case Stage:
                det.setStage(detTok[0].toLatin1());
                break;
            case Order:
                det.setOrder(detTok[0].toLatin1());
                break;
            case Detector:
                det.setDetectorName(detTok);
                break;
            case Coils:
            {
                QStringList coilToks;
                stringTok(coilToks, detTok, " ");
                for (int i = 0; i < coilToks.count(); i++)
                    det.addCoil(coilToks.at(i));
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
    return sites_[activeSites_[i]];
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
    activeSites_ = new int[nsites() + 1];
    int n = 0;

    for (int i = 0; i < sites_.size(); i++) {
        Site *site = sites_[i];
        if (firstSite_ == site)
            activeSites_[n++] = i;
        else {
            if (isValid(site)) {
                bool currentSiteJuvenile = site->stageMatch("juvenile");
                if (site->validRiverkm()) {
                    if (firstSiteJuvenile) {
                        if (!currentSiteJuvenile || site->isDownstream(firstSite_))
                            activeSites_[n++] = i;
                    } else {
                        if (!currentSiteJuvenile && !site->isDownstream(firstSite_))
                            activeSites_[n++] = i;
                    }
                }
            }
        }
    }

    // bubble sort based on total
    for (int pass = 0; pass < n; pass++) {
        for (int i = 0; i < n - 1; i++) {
            Site *a = sites_[activeSites_[i]];
            Site *b = sites_[activeSites_[i + 1]];
            if (a->isDownstream(b)) {
                int tmp = activeSites_[i + 1];
                activeSites_[i + 1] = activeSites_[i];
                activeSites_[i] = tmp;
            }
        }
    }

    activeSites_[n] = -1;
    numActiveSites_ = n;
}

Site *Sites::getSite(const QString code, bool checkValid) const {
    Site *site = nullptr;
    for (int i = 0; i < sites_.size(); i++) {
        site = sites_[i];
        if (site->siteMatch(code)) {
            if (!checkValid)
                return site;
            else if (isValid(site))
                return site;
        }
    }
    return site;
}

Site *Sites::getRelSite(const QString code) const {
    Site *site = nullptr;
    for (int i = 0; i < relsites_.size(); i++) {
        site = relsites_[i];
        if (site->siteMatch(code)) {
            return site;
        }
    }
    return site;
}

int Sites::getSiteNumber(const QString code) const {
    Site *site = getSite(code);
    if (!site)
        return 0;
    return site->getId();
}

Site *Sites::getSiteByCode(const QString siteCode) const {
    Site *site = nullptr;
    if (!siteCode.isEmpty()) {
        for (int i = 0; i < sites_.size(); i++) {
            site = sites_[i];
            if (!siteCode.compare(site->getSiteCode()))
                break;
        }
    }
    return site;
}

const Code *Sites::getCode(const QString codeName) const {
    Code *code = nullptr;
    if (!codeName.isEmpty()) {
        for (int i = 0; i < codes_.size(); i++) {
            code = codes_[i];
            if (!codeName.compare(code->getName()))
                break;
        }
    }
    return code;
}

int Sites::getActiveSiteIndex(int siteId) const {
    int i, result = -1;
    for (i = 0; i < numActiveSites_; i++) {
        if (siteId == activeSites_[i]) {
            result = i;
            break;
        }
    }
    return result;
}

Site *Sites::getSite(int id) const {
    Site *site = nullptr;
    for (int i = 0; i < sites_.size(); i++) {
        site = sites_[i];
        if (site->getId() == id)
            break;;
    }
    return site;
}

/**
 *  Given a coil, search the coil list for a match. If a
 *  match is found, return the outcome.
 *
 */
CbrPit::Outcome Sites::getOutcome(const QString codeName, const QString detector, double jd) const {
    CbrPit::Outcome oc = CbrPit::Invalid;
    const Code* code = getCode(codeName);
    if (code != nullptr)
        oc = code->getOutcome(detector, jd);
    return oc;
}

/**
 *  Given a detector, search the coilReturned list for a match. If a
 *  match is found, return 1. Otherwise the returned/removed
 *  status is unknown so return a 2.
 *
 */
int Sites::getHistFlag(const QString codeName, const QString detector, double jd) const {
    int result = 2;
    for (int i = 0; i < codes_.size(); i++) {
        Code* code = codes_[i];
        if (codeName.compare(code->getName()) == 0) {
            CbrPit::Outcome outcome = code->getOutcome(detector, jd);
            if (outcome == CbrPit::Returned) {
                result = 1;
                break;
            }
        }
    }

    return result;
}

/**
 *  Given a detector, obs site, and detection date, return the coils
 *  the list of individual coils that make up the detector
 *
 */
QStringList Sites::getCoils(const QString siteCode, const QString detector, double jd) const {
    QStringList coils;
    for (int i = 0; i < codes_.size(); i++) {
        Code* code = codes_[i];
        if (siteCode.compare(code->getName()) == 0) {
            QStringList c = code->getCoils(detector, jd);
            coils.append(c);//insert(coils.begin(), c.begin(), c.end());
        }
    }

    return coils;
}

const Detector* Sites::getDetector(const QString codeName, const QString coil, double jd) const {
    const Detector *det = nullptr;
    const Code* code = getCode(codeName);
    if (code != nullptr)
        det = code->getDetector(coil, jd);

    return det;
}

ostream &operator <<(ostream &o, const Sites &sites) {
    int i;

    o << "#" << endl;
    o << "# Site Configuration" << endl;
    o << "#" << endl << endl;
    o << "configDate: " << sites.getConfigDate().toStdString() << endl;
    o << "ptagisDate: " << sites.getPtagisDate().toStdString() << endl << endl;
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





