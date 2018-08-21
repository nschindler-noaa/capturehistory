/*
 * file: CapthistSite.cpp
 * 
 * This is the old site.c. The old way of determing detection history
 * has been updated to use the Sites class of the CbrPit library. This
 * was done to unify the site configuration for this program and the Dat
 * program, as well as to facilitate the automatic updating of 
 * configuration from the original PTAGIS site configuration history.
 * 
 *
 */

#include <pragma.h>

#include <string>

#include <string.h>
#include <stdio.h>

#include <Sites.h>

#include "CapthistSite.h"
#include "chlib.h"
#include "pptime.h"
#include "error.h"
#include "flag.h"

using std::string;

using namespace cbr;

int isSingleHitOk(SiteDet *site);
int findDetector(const char* obssite, const char* coilString, double jd);

SiteDet *SiteCr(int sn)
{
    Sites* sites = Sites::getInstance();
    Site* siteConfig = sites->getSite( sn );

    SiteDet *site = NEW(SiteDet);

    if (site) {
        site->hits=0;
        site->any=0;
        site->coils = bitfield_cr(NDETS);
        SiteInit(site);
        site->config = siteConfig;
        site->isLastField = 0;
    }
    return site;
}



void SiteInit(SiteDet *site)
{
    site->ftt = site->ltt = TTNA;
    site->fjd = site->ljd = JDNA;
    bitfield_cl(site->coils);
}

void SiteDr(SiteDet *site)
{
    if (site) {
        bitfield_dr(site->coils);
        free(site);
    }
}

void SitePrCoil(FILE *fp, SiteDet *site)
{
    char *delim = " ";
    bitfield_pr(fp, site->coils, delim);
}

int SiteHits(SiteDet *site)
{ return site->hits; }


void setValues(SiteDet *h, double tt, double jd)
{
    if (!h->fjd && !h->ljd) {
        h->ftt = h->ltt = tt;
        h->fjd = h->ljd = jd;
    }
    else if (jd < h->fjd) {
        h->ftt = tt;
        h->fjd = jd;
    }
    else if (jd > h->ljd) {
        h->ltt = tt;
        h->ljd = jd;
    }
}

/* Return 1 if site is detected on the given detector,
Return 0 if not */
int detected(SiteDet *site, int detector) {
    if (!site)
        return 0;
    return getbit(site->coils, detector);
}

int SiteAnyDetections(SiteDet *site)
{ return site->any; }

/*
* Set the any flat to 1 if there are any detections at this site. This
* takes into account the settings for whether a single coil it is allowed
* and whether or not the site allows single hits normally or not.
*/
void SiteSetAny(SiteDet *site)
{
    int tooFewHits = FlagSingleCoil() == 1 ? 0 : 1;
    
    if ((isSingleHitOk(site) && site->hits > 0) || site->hits > tooFewHits)
        site->any = 1;
}


void SiteAddObs(SiteDet *site, Obs *obs, double relDate)
{
    double jd;
    double tt=TTNA;
    
    if ( site ) {
        site->hits += ObsNumCoils(obs);
        
        jd = julianTime(ObsDate(obs), ObsTime(obs));
        tt = (relDate != JDNA) ? jd - relDate : TTNR;
        setValues(site, tt, jd);
        
        setbit( site->coils, findDetector(ObsSite(obs), ObsCoilString(obs), jd) );
    }
}

void SitePr(FILE *fp, SiteDet *site, int format)
{
    double fjd;
    double ljd;
    
    switch(format)
    {
    case TT:
        fprintf (fp, " %f %f", site->ftt, site->ltt);
        break;
    case DD:
        fjd = site->fjd;
        ljd = site->ljd;

	if ( FlagJulianDates() == 0 ) {
	  if (fjd > 0)
            fjd = timeOfYear( fjd );
	  if (ljd > 0)
            ljd = timeOfYear( ljd );
	}

        fprintf (fp, " %f %f", fjd, ljd);
        break;
    }
}

int SiteIsLastField(SiteDet *site)
{  return site->isLastField; }

void SiteSetIsLastField(SiteDet *site)
{  site->isLastField = 1; }




/**************************
* Site configuration *
**************************/

int findDetector(const char* obssite, const char* coilString, double jd) {
    Sites* sites = Sites::getInstance();
    if ( !sites )
        return 0;

    CbrPit::Outcome oc = sites->getOutcome( obssite, coilString, jd );
    switch (oc) {
    case CbrPit::Returned:
        return EXIT;
    case CbrPit::Hold:
        return HOLD;
    case CbrPit::Sampled:
        return SAMP;
    case CbrPit::Transported:
        return RACE;
	case CbrPit::Bypass:
		return BYPASS;
    case CbrPit::Unknown:
        return UNKN;
    default:
        return 0;
    }

}


char SiteGetHist(SiteDet *site, double relDate)
{
    char hist = UNDETECTED;
    
    if (detected(site, SAMP) || detected(site, HOLD))
        hist = CENSORED;
    else if (detected(site, RACE))
        hist = TRANSPORTED;
    else if (detected(site, EXIT))
        hist = RETURNED;
    else if (detected(site, UNKN))
        hist = UNKNOWN;
	else if (detected(site, BYPASS))
		hist = RETURNED;
    
    
    /* for an adult site detection, replace a RETURNED flag with
    and indication of what year the adult returned in: first,
    second, etc. Anyfish returning in the 5th year or beyond
    gets the same flag (FIVANDOLDER) */
    if (  SiteAdult( site ) && hist == RETURNED ) {
        int relYear = yearFromJd( (int)relDate );
        int detYear = yearFromJd( (int)(site->ljd) );
        int numYears = (int)( detYear - relYear);
        switch ( numYears ) {
        case 0:
            hist = JACK;
            break;
        case 1:
            hist = ONEYEAR;
            break;
        case 2:
            hist = TWOYEAR;
            break;
        case 3:
            hist = THREEYEAR;
            break;
        case 4:
            hist = FOURYEAR;
            break;
        default:
            hist = FIVEANDOLDER;
        }
        
    }
    
    return hist;   
}

/* 
* For a site with a full array of detectors, we wouldn't expect to
* get a detection on a single coil. When we do, we reject the
* single detection. For less complicated detection systems, this
* may be normal operation so we allow it in those cases.
*/
int isSingleHitOk(SiteDet *site)
{
    const char* siteCode = site->config->getSiteCode();

    if ( !strcmp( siteCode, "gr" ) )    
        return 0;
    else if ( !strcmp( siteCode, "go" ) )
        return 0;
    else if ( !strcmp( siteCode, "lm" ) )
        return 0;
    else if ( !strcmp( siteCode, "mc" ) )
        return 0;
    else if ( !strcmp( siteCode, "jd" ) )
        return 0;
    else if ( !strcmp( siteCode, "bv" ) )
        return 0;
    else
        return 1;
}

int SiteAdult(SiteDet *site)
{ 
	CbrPit& cbrPit = CbrPit::getInstance();
	string stage = cbrPit.stringFromStage( CbrPit::ST_Adult );
    if ( site->config->stageMatch( stage ) )
        return 1;
    return 0;
}


int SiteNumber(const char *siteCode)
{
    Sites* sites = Sites::getInstance();
    if ( !sites )
        return 0;
    Site* site = sites->getSite( siteCode );
    if ( !site )
        return sites->nsites();

    return site->getId();
}

const char *SiteName(int siteId)
{
    Sites* sites = Sites::getInstance();
    if ( !sites )
        return 0;
    Site* site = sites->getSite( siteId );
    if ( !site )
        return 0;

    return site->getSiteCode();
}


