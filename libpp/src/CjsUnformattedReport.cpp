#include <limits>
#include <iomanip>
#include "CjsUnformattedReport.h"
#include "CjsEstimates.h"
#include "TaggingData.h"
using namespace std;

CjsUnformattedReport::CjsUnformattedReport(const TaggingData& data, const CjsEstimates& estimates) : 
numPeriods_(data.numPeriods()), estimates_(estimates)
{}

void CjsUnformattedReport::writeObject(ostream& os) const
{
	os << setprecision(numeric_limits<double>::digits10);
	// Survival estimates
	for (unsigned int i=1; i < numPeriods_-1; ++i)
	{
		int phiIndex = estimates_.phiIndex(i);
		os << estimates_.phi(i) << " " << estimates_.covariance()(phiIndex,phiIndex) << " ";
	}
	int phiIndex = estimates_.phiIndex(numPeriods_-1);
	os << estimates_.phi(numPeriods_-1) << " " <<  estimates_.covariance()(phiIndex,phiIndex) << "\n";

	// Detection
	for (unsigned int i=2; i < numPeriods_; ++i)
	{
		int pIndex = estimates_.pIndex(i);
		os << estimates_.p(i) << " " << estimates_.covariance()(pIndex,pIndex) << " ";
	}
	int pIndex = estimates_.pIndex(numPeriods_);
	os << estimates_.p(numPeriods_) << " " << estimates_.covariance()(pIndex,pIndex) << "\n";

	// Final survival*detection

	int lambdaIndex = estimates_.phiIndex(numPeriods_);
	os << estimates_.phi(numPeriods_) << " " << estimates_.covariance()(lambdaIndex,lambdaIndex);

}

ostream& operator<<(ostream& os, const CjsUnformattedReport& report)
{
	report.writeObject(os);
	return os;
}
