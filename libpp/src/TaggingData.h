#ifndef TaggingData_H
#define TaggingData_H

#include <QString>
#include "CaptureHistoryMap.h"

/** Abstract base class for generic release-recapture data. */
class TaggingData
{
public:
    TaggingData() {}
    virtual ~TaggingData() {}
    virtual const QString fileName() const = 0;
    virtual const QString dataDescription() const = 0;
    virtual const QString populationName(int pop) const = 0;
    virtual int numPeriods() const = 0;
    virtual int numPopulations() const = 0;
    virtual const CaptureHistoryMap& captureHistoryMap(int pop) const = 0;
};

#endif
