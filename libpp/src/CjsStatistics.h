#ifndef CjsStatistics_H
#define CjsStatistics_H

#include "BArrays.h"
#include "CaptureHistoryMap.h"


/*! Compute a minimum sufficient statistic for Cormack-Jolly-Seber estimates.

Requirements:
- a begin() method returning a constant iterator pointing to the first element
- an end() method returning a constant iterator pointing one past the last element
- a value_type typdef for the type of the container elements.
- value_type::first = A point to the capture history
- value_type::second = The counts for that capture history.
- A capture history may appear more than once in the container - the counts are simply added on
to the previous counts.
- The container elements must be pointers to basic capture histories with the following methods:
- bool captured(int site) indicating if captured ("detected") at site i
- bool removed(int site) indicates if removed at site i
- int lastCaptured() const - Site of last capture
- int initialRelease() const - Returns site of initial release
The names were chosen to coincide with "Design and Analysis Methods for Fish Survival
Experiments based on Release-Recapture" (Burnham et al.).

Outputs:
R(int i) - The number released at site i
r(int i) - The number released at site i and recaptured at a subsequent site
m(int i) - The number of previously released that are deteceted at site i
k()		 - The number of sites
*/
class CjsStatistics
{
public:
	CjsStatistics(const CaptureHistoryMap& captureHistories, int numSites);
	virtual ~CjsStatistics() {}
	int R(int i) const {return R_[i];}
	int r(int i) const {return r_[i];}
	int m(int i) const {return m_[i];}
	int k() const {return R_.size()+1;}
private:
	cbr::VectorB<int> R_;
	cbr::VectorB<int> r_;
	cbr::VectorB<int> m_;
};
#endif
