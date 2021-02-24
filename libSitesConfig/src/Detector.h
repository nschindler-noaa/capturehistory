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
    Detector() : outcome(cbr::CbrPit::Invalid) {}
    //Detector( const Detector& det );
    ~Detector() {}
    void setStage (cbr::CbrPit::Stage stage);
    void setStage (char stage);
    void setDetectorName (const QString detectorString);
    void addCoil (const QString& coil);
    void setOutcome (cbr::CbrPit::Outcome outcome);
    void setOutcome (char oc);
    void setOrder (int ord) { order = ord; }

    const QString getDetectorName() const { return detector; }
    const QStringList& getCoils() const { return coils; }
    cbr::CbrPit::Outcome getOutcome() const { return outcome; }
    int getOrder() const { return order; }
    cbr::CbrPit::Stage getStage() const { return stage; }

    bool isMatch (const QString& s) const;
    bool isCoilMatch (const QString& s) const;

    QString output() const;

    friend std::ostream& operator<<(std::ostream& os, const Detector& det);

private:
    QString detector;
    QStringList coils;
    cbr::IntVector icoils;
    cbr::CbrPit::Outcome outcome;
    cbr::CbrPit::Stage stage;
    int order;
    bool hex2dec (const char* hexNum, int& num) const;
    bool validCoil (const QString& scoil) const;
    bool validICoil (const int icoil) const;

};

#endif
