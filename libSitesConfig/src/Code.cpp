/*
 * Code.cpp
 */

#include <stdlib.h>

#include "Code.h"
#include "CbrPit.h"

using namespace std;
using namespace cbr;

Code::~Code() {
    for ( unsigned int i = 0; i < ranges.size(); i++ )
        delete ranges[ i ];
    ranges.clear();
}

void Code::addRange( Range* range ) {
    ranges.push_back( range );
}

void Code::addException( Exception* ex ) {
    exceptions.push_back( ex );
}


/*
 * This return the outcome for the detector given either as
 * the detector name or as one of the coils associated with
 * the detector.
 */
CbrPit::Outcome Code::getOutcome( const string& detector, double jd ) const {
    if ( allReturned )
        return CbrPit::Returned;

    const Detector* det = getDetector (detector, jd);
    if (det)
      return det->getOutcome();

    return CbrPit::Invalid;
}

StringVector Code::getCoils( const string& detector, double jd ) const
{
  StringVector coils; // this will be empty if we don't find a detector

  const Detector* det = getDetector (detector, jd);
  if (det)
    {
      StringVector c = det->getCoils();
      coils.insert (coils.begin(), c.begin(), c.end());
    }

  return coils;
}

const Range* Code::getRange( double jd ) const 
{
  for ( unsigned int i = 0; i < ranges.size(); i++ ) 
    {
      Range* range = ranges[ i ];
      if ( jd >= range->getJd1() && jd <= range->getJd2() ) 
	return range;
    }
  return 0;
}

const vector<Exception*> Code::getExceptions (double jd) const 
{
  vector<Exception*> matches;
  vector<Exception*>::const_iterator it_ex;
  for (it_ex = exceptions.begin(); it_ex != exceptions.end(); ++it_ex)
    {
      Exception* ex = *it_ex;
      
      if ( jd >= ex->getJd1() && jd <= ex->getJd2() ) 
	matches.push_back (ex);
    }

  return matches;
}


/*
 * Find the detector for the give coil and julian date. The coil can
 * be either a coil code or a detector name. The coil code is compare
 * both as a string, and as a converted integer (from hex)
 */
const Detector* Code::getDetector( const string& coil, double jd ) const 
{
  // get any exceptions for the julian date
  vector<Exception*> exs = getExceptions (jd);


  // check the exceptions first
  vector<Exception*>::const_iterator it_ex;

  // check coils before detectors to 
  // allow different outcomes for
  // different coils for the same detector
  for (it_ex = exs.begin(); it_ex != exs.end(); ++it_ex)
  {
	  Exception* ex = *it_ex;
	  const Detector* det = ex->getDetector();

	  if (det->isCoilMatch (coil))
		  return det;
  }

  // now check for matches on the detector name
  for (it_ex = exs.begin(); it_ex != exs.end(); ++it_ex)
  {
	  Exception* ex = *it_ex;
	  const Detector* det = ex->getDetector();

	  if (det->isMatch (coil))
		  return det;
  }

  // now check the normal ranges
  const Range* range = getRange( jd );
  if ( !range ) 
    return 0;
  
  return range->getDetector (coil);
}

/**
*/
ostream &operator <<( ostream &o, const Code &code ) {
    o << "code: " << code.name << endl;
    o << "{" << endl;
    unsigned int i;
    for ( i = 0; i < code.ranges.size(); i++ ) {
        Range* range = code.ranges[ i ];
        o << *range;
    }

    for ( i = 0; i < code.exceptions.size(); i++ ) {
        Exception* ex = code.exceptions[ i ];
        o << *ex;
    }
    o << "}" << endl;

    return o;
}
