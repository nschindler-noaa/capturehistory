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

Site::Site (int id, const string& siteCode) : id_(id), 
siteCode_(siteCode), shortName_(siteCode), longName_(siteCode),
type_("dam"), releaseSite_(false)
{
}

Site::~Site () 
{
    stages_.clear ();
    codes_.clear ();
}


void Site::setShortName (const string& shortName) 
{
	shortName_ = shortName;
}

void Site::setLongName (const string& longName) 
{
	longName_ = longName;
}

void Site::setType (const string& type) 
{
    type_ = type;
}

void Site::setStage (const string& stage) 
{
  if (stages_.size() > 0)
    stages_.clear();
  
  stages_.push_back( stage );
}

void Site::setHuc (const string& huc) 
{
	huc_ = huc;
}

void Site::setIndicator (const string& indicator) 
{
	indicator_ = indicator;
}

void Site::addStage (const string& stage) 
{
    stages_.push_back (stage);
}


int Site::isTrap() const {
  if ( type_.empty() )
    return 0;
  return ( !type_.compare("trap"));
}

int Site::isAcclimation() const {
  if ( type_.empty() )
    return 0;
  return ( !type_.compare("acclimation"));
}


bool Site::isAdult() const {
    for (StringVector::const_iterator it = stages_.begin(); it != stages_.end(); ++it) {
        if ((*it).compare("adult") == 0) 
            return true;
    }
    return false;
}

bool Site::isJuvenile() const {
    for (StringVector::const_iterator it = stages_.begin(); it != stages_.end(); ++it) {
        if ((*it).compare("juvenile") == 0)
            return true;
    }
    return false;
}

/**
*  Save a copy of riverk and then parse it, summing
*  up the km's. Changes the origional pointers by
*  using strtok
*/
void Site::setRiverKm (const string& riverk) 
{
	riverkDn_.setRiverKm(riverk);
}
void Site::setRiverKm (const string& riverkDn, const string& riverkUp) 
{
	riverkDn_.setRiverKm(riverkDn);
	riverkUp_.setRiverKm(riverkUp);
}

void Site::addCode (const string& code) 
{
    codes_.push_back (code);
}


/**
*  Return 1 if the given site matches one of this sites codes,
*  0 otherwise
*  This function works dual purpose, looking for a match with
*  either the siteCode or with one of the detector codes
*/
bool 
Site::siteMatch (const string& obssite) const
{
	if (!obssite.compare( siteCode_ ))
		return 1;
	else if (!obssite.compare( longName_ ))
		return 1;
	else
		return find(codes_.begin(), codes_.end(), obssite) != codes_.end();
}

/**
*  Return 1 if the given site stage is one of the defined stages
*  for the site, 0 otherwise
*/
bool
Site::stageMatch (const string& stage) const
{
  return find(stages_.begin(), stages_.end(), stage) != stages_.end(); 
}

/**
*  Return 1 if the given site stage is one of the defined stages
*  for the site, 0 otherwise
*/
bool
Site::stageMatch (CbrPit::Stage stage) const
{
	CbrPit& cbrPit = CbrPit::getInstance();
	std::string stageString = cbrPit.stringFromStage (stage);
	return stageMatch (stageString);
}


/* 
 * Return true if this site is between sitea and siteb on the river. Return false
 * if this site equals sitea or siteb, or if this site's riverk equals sitea's or
 * siteb's
 */
bool
Site::isBetween (const Site* sitea, const Site* siteb, RkType rkaType, RkType rkbType) const {
	return isDownstream(sitea, rkaType) && isUpstream(siteb, rkbType);
}

/* 
 * return true if this site is downstream of the given site. If they are the
 * same site (have the same riverk) return false. The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
*/
bool
Site::isDownstream (const Site* site, RkType rkType) const {
	if ( !site )
		return false;
	else if ( isColocated( site, rkType ) )
		return false;

	if (rkType == RK_Up && site->riverkUp_.isValid())
		return riverkDn_.isDownstream(site->riverkUp_);
	else
		return riverkDn_.isDownstream(site->riverkDn_);
}

/* 
 * return true if this site is upstream of the given site. If they are the
 * same site (have the same riverk) return false. The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
*/
bool
Site::isUpstream (const Site* site, RkType rkType) const {
	if ( !site )
		return false;
	else if ( isColocated(site, rkType ) )
		return false;

	if (rkType == RK_Up && site->riverkUp_.isValid())
		return riverkDn_.isUpstream(site->riverkUp_);
	else
		return riverkDn_.isUpstream(site->riverkDn_);
}

/*
 * Return true if this site and the target site have identical riverk.
 * The rkType indicates which
 * riverk to use for the target site, if the target site spans a range of riverks
 * i.e., riverkUp != riverkDn. The member site (this) always uses the RK_Down riverk.
 */
bool
Site::isColocated (const Site* site, RkType rkType) const {
	if (rkType == RK_Up && riverkUp_.isValid())
		return riverkDn_.isColocated(site->riverkUp_);
	else
		return riverkDn_.isColocated(site->riverkDn_);
}


const RiverKm&
Site::getRiverKm(RkType rkType) const {
  if (rkType == RK_Up && riverkUp_.isValid())
    return riverkUp_;
  else
    return riverkDn_;
}

bool
Site::isRiverkRange() const {
    return riverkUp_.isValid() && !riverkDn_.isColocated(riverkUp_);
}

bool
Site::validRiverkm() const {
	return riverkDn_.isValid();
}


/**
*  Ouput the sites configuration in the configuration file
*  format
*/
ostream &operator <<( ostream &o, const Site &site ) {
	if (site.releaseSite_)
		o << "relsite: ";
	else 
		o << "site: ";
	o << site.siteCode_ << endl;

    o << "{" << endl;

    if ( !site.longName_.empty() ) {
        o << "  name: " << site.longName_ << endl;
    }
    if ( !site.shortName_.empty() ) {
        o << "  shortName: " << site.shortName_ << endl;
    }
    if ( site.riverkDn_.isValid() ) {
        o << "  riverk: " << site.riverkDn_;
		if (site.riverkUp_.isValid())
			o << "-" << site.riverkUp_;
		o << endl;
    }
    if ( !site.type_.empty() ) {
        o << "  type: " << site.type_ << endl;
    }
    if ( !site.huc_.empty() ) {
        o << "  huc: " << site.huc_ << endl;
    }
    if ( !site.indicator_.empty() ) {
        o << "  indicator: " << site.indicator_ << endl;
    }
    if ( site.stages_.size() > 0 ) {
        o << "  stage:";
        for ( unsigned int i = 0; i < site.stages_.size(); i++ )
            o << " " << site.stages_[ i ];
        o << endl;
    }

    if ( site.codes_.size() > 0 ) {
        o << "  codes:";
        for ( unsigned int i = 0; i < site.codes_.size(); i++ )
            o << " " << site.codes_[ i ];
        o << endl;
    }

    o << "}" << endl;

    
    return o;
}









