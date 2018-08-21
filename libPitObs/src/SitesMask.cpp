/*
 */


#include <string>
#include <stdexcept>
#include <sstream>

#include "ArrayDefs.h"
#include "SitesMask.h"
#include "Site.h"
#include "Sites.h"

using std::string;
using std::runtime_error;
using std::stringstream;

using cbr::StringVector;

void SitesMask::init( const StringVector& juvSites, const StringVector& adultSites, int numMainSites )
{ 
  int numTotalSites = juvSites.size() + adultSites.size();
  if ( numMainSites < 1 || numMainSites > numTotalSites )
    numMainSites = numTotalSites;

  setNumJuvenileSites( juvSites.size() );
  setNumMainSites( numMainSites );

  Sites* sites = Sites::getInstance();
  for ( StringVector::const_iterator it = juvSites.begin(); it != juvSites.end(); ++it ) 
    {
      string siteCode = *it;
      Site* site = sites->getSite( siteCode.c_str() );
      if ( site ) 
	addSite( site );
      else
	{
	  stringstream ss;
	  ss << "Un-recognized site in juvenile sites vector: \"" << *it << "\"";
	  throw runtime_error( ss.str() );
	}
    }

  for ( StringVector::const_iterator it = adultSites.begin(); it != adultSites.end(); ++it ) 
    {
      Site* site = sites->getSite( (*it).c_str() );
      if ( site ) 
	addSite( site );
      else
	{
	  stringstream ss;
	  ss << "Un-recognized site in adult sites vector: \"" << *it << "\"";
	  throw runtime_error( ss.str() );
	}
    }

  
}

void SitesMask::addSite (const Site* site)
{
  if (site)
    mask.push_back (site);
}

void SitesMask::addSite (const char* code)
{
  Sites* sites = Sites::getInstance();
  mask.push_back (sites->getSite (code));
}


void SitesMask::autoConfigure(const Site*) // firstSite)
{}

const Site* SitesMask::getSite( size_t i ) const {
  if ( i >= getNumSites() )
    return 0;
  else 
    return mask[ i ];
}


/*
 * todo: this assumes the release site is above
 * the first site in the mask. This will need
 * to be fixed.
 */
size_t SitesMask::numPeriods() const
{
  size_t numPeriods;
  if (numMainSites == -1 || static_cast<unsigned int>(numMainSites) == mask.size())
    numPeriods = mask.size(); // add one for the release site
  else 
    numPeriods = numMainSites + 1;

  return numPeriods;
}
