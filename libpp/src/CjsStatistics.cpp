#include "CjsStatistics.h"
#include "CaptureHistoryMap.h"
#include "CaptureHistory.h"
using namespace std;
using namespace cbr;

CjsStatistics::CjsStatistics(const CaptureHistoryMap& captureHistories, int numPeriods) :
R_(BArrays::bounds(1,numPeriods)), r_(BArrays::bounds(1,numPeriods),0),
	m_(BArrays::bounds(2,numPeriods),0)
{
	CaptureHistoryMap::const_iterator captHistIter = captureHistories.begin();
	for (; captHistIter != captureHistories.end(); ++captHistIter)
	{
		const CaptureHistoryMap::value_type& value = *captHistIter;
		for (int i=1; i <= k()-1; ++i)
		{
			if (value.first->captured(i))
			{
				if (value.first->released() < i)
					m_[i] += value.second;
				if (!value.first->removed(i))
				{
					R_[i] += value.second;
					if (value.first->lastCaptured() > i)
						r_[i] += value.second;
				}
			}
		}
	}
}
