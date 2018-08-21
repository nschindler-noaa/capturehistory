#ifndef TaggingData_H
#define TaggingData_H

#include <string>
#include "CaptureHistoryMap.h"

/** Abstract base class for generic release-recapture data. */
class TaggingData
{
public:
	TaggingData() {}
	virtual ~TaggingData() {}
	virtual const std::string& fileName() const = 0;
	virtual const std::string& dataDescription() const = 0;
	virtual const std::string& populationName(unsigned int pop) const = 0;
	virtual unsigned int numPeriods() const = 0;
	virtual unsigned int numPopulations() const = 0;
	virtual const CaptureHistoryMap& captureHistoryMap(unsigned int pop) const = 0;
};

#endif
