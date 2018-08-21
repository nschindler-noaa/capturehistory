/*
 */

#include <QStringList>

#include <iostream>
#include <vector>
#include <algorithm>

#include "ObsSequence.h"
#include "CbrPit.h"
#include <Site.h>

#include "ObsPreProcessor.h"

using namespace std;
using namespace cbr;

void ObsPreProcessor::process( ObsSequence& seq )
{
  const ObsRecordVector& v = seq.getSequence();

  for ( ObsRecordVector::const_iterator it = v.begin(); it != v.end(); ++it ) {
    const ObsRecord& rec = *it; 
    const Site* site = rec.getSitePointer();
    if ( rec.getStage() == CbrPit::ST_Juvenile ) {
      if ( find( juvenileSites.begin(), juvenileSites.end(), site) == juvenileSites.end() )
	juvenileSites.push_back( site );
    }
    else if ( rec.getStage() == CbrPit::ST_Adult ) {
      if ( find( adultSites.begin(), adultSites.end(), site) == adultSites.end() )
	adultSites.push_back( site );
    }
  }
}

struct site_upriver : public binary_function<const Site*, const Site*, bool>
{
  bool operator () ( const Site* s1, const Site* s2 )
  {
    return s2->isDownstream(s1);
  }
};

struct site_downriver : public binary_function<const Site*, const Site*, bool>
{
  bool operator () ( const Site* s1, const Site* s2 )
  {
	return s1->isDownstream(s2);
  }
};

void ObsPreProcessor::post()
{
  sort( juvenileSites.begin(), juvenileSites.end(), site_upriver() );
  sort( adultSites.begin(), adultSites.end(), site_downriver() );
}
