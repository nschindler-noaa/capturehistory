/*
 * The list of coils that signify the outcome for a particular
 * time frame. This information is read in from the sites.config file.
 *
 */

#ifndef Range_h
#define Range_h

#include <string>
#include <iostream>

#include <QStringList>

#include <ArrayDefs.h>

#include "CbrPit.h"
#include "Detector.h"

class Range {

public:
    Range (const QString& date1, const QString& date2);

    void addDetector (const Detector& det);
    QString getDetectorString(int i) const;
    cbr::CbrPit::Outcome getOutcome (const QString d) const;
    const Detector* getDetector (const QString coil) const;
    QStringList getCoils (const QString detector) const;
    double getJd1() const { return jd1; }
    double getJd2() const { return jd2; }
    int numDetectors() const { return detectors.size(); }

    friend std::ostream &operator <<( std::ostream &o, const Range &range );

private:
    QList<Detector> detectors;
    double jd1;
    double jd2;

    static const double presentJd;

};

#endif
