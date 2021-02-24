/*
* Site.cpp
*/

#include <sstream>
#include <algorithm>

#include <string.h>
#include <stdlib.h>

#include "Site.h"
#include "RiverKm.h"

using std::ostream;
using std::string;
using std::endl;
using std::vector;
using std::string;

using namespace cbr;

Site::Site (int id, const QString siteCode) : id_(id),
siteCode_(siteCode), shortName_(siteCode), longName_(siteCode),
type_("dam"), releaseSite_(false)
{
}

Site::~Site ()
{
    stages_.clear ();
    codes_.clear ();
}


void Site::setShortName (const QString shortName)
{
    shortName_ = shortName;
}

void Site::setLongName (const QString longName)
{
    longName_ = longName;
}

void Site::setType (const QString type)
{
    type_ = type;
}

void Site::setStage (const QString stage)
{
  if (stages_.size() > 0)
    stages_.clear();

  stages_.push_back( stage );
}

void Site::setHuc (const QString huc)
{
    huc_ = huc;
}

void Site::setIndicator (const QString indicator)
{
    indicator_ = indicator;
}

void Site::addStage (const QString stage)
{
    stages_.push_back (stage);
}


int Site::isTrap() const {
  if ( type_.isEmpty() )
    return 0;
  return ( !type_.compare("trap"));
}

int Site::isAcclimation() const {
  if ( type_.isEmpty() )
    return 0;
  return ( !type_.compare("acclimation"));
}


bool Site::isAdult() const {
    for (int i = 0; i < stages_.count(); i++) { //StringVector::const_iterator it = stages_.begin(); it != stages_.end(); ++it) {
        if (stages_.at(i).compare("adult", Qt::CaseInsensitive) == 0) //if ((*it).compare("adult") == 0)
            return true;
    }
    return false;
}

bool Site::isJuvenile() const {
    for (int i = 0; i < stages_.count(); i++) {//StringVector::const_iterator it = stages_.begin(); it != stages_.end(); ++it) {
        if (stages_.at(i).compare("juvenile", Qt::CaseInsensitive) == 0)//if ((*it).compare("juvenile") == 0)
            return true;
    }
    return false;
}

/**
*  Save a copy of riverk and then parse it, summing
*  up the km's. Changes the origional pointers by
*  using strtok
*/
void Site::setRiverKm (const QString riverk)
{
    riverkDn_.setRiverKm(riverk);
}
void Site::setRiverKm (const QString riverkDn, const QString riverkUp)
{
    riverkDn_.setRiverKm(riverkDn);
    riverkUp_.setRiverKm(riverkUp);
}

void Site::addCode (const QString code)
{
    codes_.push_back (code);
}


/**
*  Return 1 if the given site matches one of this sites codes,
*  0 otherwise
*  This function works dual purpose, looking for a match with
*  either the siteCode or with one of the detector codes
*/
bool Site::siteMatch (const QString obssite) const
{
    if (!obssite.compare( siteCode_ ))
        return 1;
    else if (!obssite.compare( longName_ ))
        return 1;
    else
        return codes_.contains(obssite, Qt::CaseInsensitive);//find(codes_.begin(), codes_.end(), obssite) != codes_.end();
}

/**
*  Return 1 if the given site stage is one of the defined stages
*  for the site, 0 otherwise
*/
bool Site::stageMatch (const QString stage) const
{
  return stages_.contains(stage, Qt::CaseInsensitive);//find(stages_.begin(), stages_.end(), stage) != stages_.end();
}

/**
*  Return 1 if the given site stage is one of the defined stages
*  for the site, 0 otherwise
*/
bool Site::stageMatch (CbrPit::Stage stage) const
{
    CbrPit& cbrPit = CbrPit::getInstance();
    QString stageString = cbrPit.stringFromStage (stage);
    return stageMatch (stageString);
}


/*
 * Return true if this site is between sitea and siteb on the river. Return false
 * if this site equals sitea or siteb, or if this site's riverk equals sitea's or
 * siteb's
 */
bool Site::isBetween (const Site* sitea, const Site* siteb, RkType rkaType, RkType rkbType) const {
    bool btween = isDownstream(sitea, rkaType) && isUpstream(siteb, rkbType);
    return btween;
}

/*
 * return true if this site is downstream of the given site. If they are the
 * same site (have the same riverk) return false. The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
*/
bool Site::isDownstream (const Site* site, RkType rkType) const {
    bool dnstrm = false;
/*    if (!site)
        return false;
    else if (isColocated(site, rkType))
        return false;*/
    if (site && !isColocated(site, rkType)) {
        if (rkType == RK_Up && site->riverkUp_.isValid())
            dnstrm = riverkDn_.isDownstream(site->riverkUp_);
        else
            dnstrm = riverkDn_.isDownstream(site->riverkDn_);
    }
    return dnstrm;
}

/*
 * return true if this site is upstream of the given site. If they are the
 * same site (have the same riverk) return false. The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
*/
bool Site::isUpstream (const Site* site, RkType rkType) const {
    bool upstrm = false;
/*    if (!site)
        return false;
    else if (isColocated(site, rkType))
        return false;*/

    if (site && !isColocated(site, rkType)) {
        if (rkType == RK_Up && site->riverkUp_.isValid())
            upstrm = riverkDn_.isUpstream(site->riverkUp_);
        else
            upstrm = riverkDn_.isUpstream(site->riverkDn_);
    }
    return upstrm;
}

/*
 * Return true if this site and the target site have identical riverk.
 * The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
 */
bool Site::isColocated (const Site* site, RkType rkType) const {
    bool coloc = false;
    if (rkType == RK_Up && riverkUp_.isValid())
        coloc = riverkDn_.isColocated(site->riverkUp_);
    else
        coloc = riverkDn_.isColocated(site->riverkDn_);
    return coloc;
}


const RiverKm& Site::getRiverKm(RkType rkType) const {
  if (rkType == RK_Up && riverkUp_.isValid())
    return riverkUp_;
  else
    return riverkDn_;
}

bool Site::isRiverkRange() const {
    bool valid = riverkUp_.isValid() && !riverkDn_.isColocated(riverkUp_);
    return valid;
}

bool Site::validRiverkm() const {
    bool valid = riverkDn_.isValid();
    return valid;
}


/**
*  Ouput the sites configuration in the configuration file
*  format
*/
ostream &operator <<(ostream &o, const Site &site) {
    if (site.releaseSite_)
        o << "relsite: ";
    else
        o << "site: ";
    o << site.siteCode_.toStdString() << endl;

    o << "{" << endl;

    if (!site.longName_.isEmpty()) {
        o << "  name: " << site.longName_.toStdString() << endl;
    }
    if (!site.shortName_.isEmpty()) {
        o << "  shortName: " << site.shortName_.toStdString() << endl;
    }
    if (site.riverkDn_.isValid()) {
        o << "  riverk: " << site.riverkDn_;
        if (site.riverkUp_.isValid())
            o << "-" << site.riverkUp_;
        o << endl;
    }
    if (!site.type_.isEmpty()) {
        o << "  type: " << site.type_.toStdString() << endl;
    }
    if (!site.huc_.isEmpty()) {
        o << "  huc: " << site.huc_.toStdString() << endl;
    }
    if (!site.indicator_.isEmpty()) {
        o << "  indicator: " << site.indicator_.toStdString() << endl;
    }
    if (site.stages_.size() > 0) {
        o << "  stage:";
        for ( int i = 0; i < site.stages_.size(); i++ )
            o << " " << site.stages_[i].toStdString();
        o << endl;
    }

    if (site.codes_.size() > 0) {
        o << "  codes:";
        for ( int i = 0; i < site.codes_.size(); i++ )
            o << " " << site.codes_[i].toStdString();
        o << endl;
    }

    o << "}" << endl;


    return o;
}









