#ifndef CaptureHistoryMap_H
#define CaptureHistoryMap_H

#include <map>
#include <string>
#include "CaptureHistory.h"

/** \struct de-reference the CaptureHistory pointers for comparisons. */
struct captureHistoryPtrLess
{
	bool operator()(const CaptureHistory* lhs, const CaptureHistory* rhs) const
	{ return lhs->label() < rhs->label(); }
};
/** \typedef
- Key:		A pointer to a capture history object
- Value:	The corresponding counts
*/
typedef std::map<CaptureHistory*, unsigned int, captureHistoryPtrLess> CaptureHistoryMap;

#endif
