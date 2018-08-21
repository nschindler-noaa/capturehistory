/**
 *  Range.cpp
*/

#include <string.h>

#include <StringTok.h>
#include <StringUtil.h>
#include <QStringList>

#include "ArrayDefs.h"
#include "DateConverter.h"
#include "Range.h"

using std::vector;
using std::string;
using std::ostream;
using std::endl;
using std::cout;

using namespace cbr;

const double Range::presentJd = 100000000;

// dates are in one of two formats: a format
// that doesn't include the time ( dd-Mmm-yy )
// or ones that do ( dd-Mmm-yy+hh:mm:ss )
Range::Range( const string& d1, const string& d2 ) {
    string date1;
    string date2;
    string time1;
    string time2;

    QStringList d1Toks;
    QStringList d2Toks;
//    StringVector d1Toks;
//    StringVector d2Toks;
    stringTok( d1Toks, QString(d1.c_str()), "+" );
    stringTok( d2Toks, QString(d2.c_str()), "+" );

    if ( d1Toks.size() > 0 && d2Toks.size() > 0 ) {
        date1 = d1Toks[ 0 ].toStdString();
        date2 = d2Toks[ 0 ].toStdString();

        if ( d1Toks.size() == 2 ) 
            time1 = d1Toks[ 1 ].toStdString();
        else
            time1 = "00:00:00";

        DateConverter dc( date1.c_str(), time1.c_str() );
        jd1 = dc.getTime();
    
        string lowerDate2 = date2;
        toLower( lowerDate2 );
        if ( !lowerDate2.compare( "present" ) ) {
            jd2 = presentJd;
        }
        else {
            if ( d2Toks.size() == 2 ) 
                time2 = d2Toks[ 1 ].toStdString();
            else
                time2 = "23:59:50";

            dc.reset( date2.c_str(), time2.c_str() );
            jd2 = dc.getTime();
        }
    }
}

const char *Range::getDetectorString( int i ) const { 
    const Detector& det = detectors[ i ];
    string detString = det.getDetectorName();
    return detString.c_str();
 }

/*
 * Return the outcome for the target detector. The target detector can
 * be either the detector name or the string representing on of the
 * associated coils.
 */
CbrPit::Outcome Range::getOutcome( const string& targetDetector ) const {
    for ( unsigned int i = 0; i < detectors.size(); i++ ) {
        const Detector& detector = detectors[ i ];
        if ( detector.isMatch( targetDetector ) )
            return detector.getOutcome();
    }
    return CbrPit::Invalid;
}

void Range::addDetector( const Detector& det ) { 
  detectors.push_back( det ); 
}

/*
 * Return the coils for the given detector name
 */
StringVector Range::getCoils( const string& targetDetector ) const {
  StringVector coils;
  for ( unsigned int i = 0; i < detectors.size(); i++ ) {
    const Detector& detector = detectors[ i ];
    if ( detector.isMatch( targetDetector ) ) {
      StringVector c = detector.getCoils();
      coils.insert( coils.begin(), c.begin(), c.end() );
    }
  }
  return coils;
}

/*
 * Get the detector for the target. In this case the coil can
 * be either the code for a particular coil or a detector name
 */
const Detector* Range::getDetector( const string& coil ) const {
    for ( unsigned int i = 0; i < detectors.size(); i++ ) {
        const Detector& detector = detectors[ i ];
        if ( detector.isMatch( coil ) ) 
	  return &detector;
    }

    return (Detector*)0;
}

/*
 */
ostream& operator <<( ostream& os, const Range& range ) {
    DateConverter dc1( range.jd1 );
    dc1.setDateFormat( DateConverter::B );
    dc1.setOutputFormat( DateConverter::DateOnly );

    os << "  range: " << dc1 << " ";
    if ( range.jd2 == Range::presentJd ) 
        os << "Present";
    else {
        DateConverter dc2( static_cast<int>(range.jd2) );
        dc2.setDateFormat( DateConverter::B );
        dc2.setOutputFormat( DateConverter::DateOnly );
        os << dc2;
    }
    os << endl;
    os << "  {" << endl;
    for ( unsigned int i = 0; i < range.detectors.size(); i++ ) {
        const Detector& det = range.detectors[ i ];
        os << "    " << det << endl;
    }
    os << "  }" << endl;

    return os;
}
