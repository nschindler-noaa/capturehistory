/*
 * The list of coils that signify the outcome for a particular
 * time frame. This information is read in from the sites.config file.
 *
 */

#ifndef Exception_h
#define Exception_h

#include <string>
#include <iostream>

#include <ArrayDefs.h>

#include "CbrPit.h"
#include "Detector.h"

class Exception 
{
public:
    Exception(const QString &date1, const QString &date2, const Detector& det );

    const char *getDetectorString() const;
    cbr::CbrPit::Outcome getOutcome() const;
    const cbr::StringVector& getCoils() const;
    double getJd1() const { return jd1; }
    double getJd2() const { return jd2; }
    const Detector* getDetector() const { return &det; }
    
    friend std::ostream &operator <<( std::ostream &o, const Exception &ex );

private:
    double jd1;
    double jd2; 
    Detector det;

    static const double presentJd;
};

#endif
