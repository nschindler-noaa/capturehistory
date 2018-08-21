/*
 * Detector.h
 */

#ifndef Detector_h
#define Detector_h

#include <string>
#include <iostream>

#include <ArrayDefs.h>
#include "CbrPit.h"

class Detector {

public:
    Detector() : outcome( cbr::CbrPit::Invalid ) {}
    //Detector( const Detector& det );
    ~Detector() {}
    void setStage( cbr::CbrPit::Stage stage );
    void setStage( char stage );
    void setDetectorName( const std::string& detectorString );
    void addCoil( const std::string& coil );
    void setOutcome( cbr::CbrPit::Outcome outcome );
    void setOutcome( char oc );
    void setOrder( int ord ) { order = ord; } 

    const std::string& getDetectorName() const { return detector; }
    const cbr::StringVector& getCoils() const { return coils; }
    cbr::CbrPit::Outcome getOutcome() const { return outcome; }
    int getOrder() const { return order; }
    cbr::CbrPit::Stage getStage() const { return stage; }
    
    bool isMatch(const std::string& s) const;
    bool isCoilMatch( const std::string& s ) const;

    friend std::ostream& operator<<(std::ostream& os, const Detector& det);

private:
    std::string detector;
    cbr::StringVector coils;
	cbr::IntVector icoils;
    cbr::CbrPit::Outcome outcome;
    cbr::CbrPit::Stage stage;
    int order;
	bool hex2dec(const char* hexNum, int& num) const;


};

#endif
