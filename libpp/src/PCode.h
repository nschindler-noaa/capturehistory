/**********************************************************************
file:  PCode.h
***********************************************************************/

#ifndef PCode_H
#define PCode_H

#include <QString>
#include <string>

#include <CbrPit.h>
#include <DateConverter.h>
#include <ObsSequence.h>
#include <Site.h>

class PCode
{
public:
    PCode (const QString& pc, const Site* site);
    ~PCode() {}
    double getTime() const;
    void compress();
    void addRecord (cbr::CbrPit::Outcome outcome, double obsdate);
    bool isReturned() const;
    const QString& getPitcode() const;

    friend bool operator==(const PCode& pc, const std::string s);

private:
    const Site* site;
    ObsSequence seq;

};

#endif
