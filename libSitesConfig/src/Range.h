/*
 * The list of coils that signify the outcome for a particular
 * time frame. This information is read in from the sites.config file.
 *
 */

#ifndef Range_h
#define Range_h

#include <string>
#include <iostream>

#include <ArrayDefs.h>

#include "CbrPit.h"
#include "Detector.h"

class Range {
private:
    std::vector<Detector> detectors;
    double jd1;
    double jd2; 

    static const double presentJd;
public:
	Range( const std::string& date1, const std::string& date2 );

    void addDetector( const Detector& det );
    const char *getDetectorString( int i ) const;
    cbr::CbrPit::Outcome getOutcome( const std::string& d ) const;
    const Detector* getDetector( const std::string& coil ) const;
    cbr::StringVector getCoils( const std::string& detector ) const;
    double getJd1() const { return jd1; }
    double getJd2() const { return jd2; }
    int numDetectors() const { return detectors.size(); }
    
    friend std::ostream &operator <<( std::ostream &o, const Range &range );

    
    
};

#endif
