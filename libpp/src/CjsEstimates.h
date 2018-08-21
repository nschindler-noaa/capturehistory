#ifndef CjsEstimates_H
#define CjsEstimates_H

#include "BArrays.h"
#include "Matrix.h"

class CjsStatistics;
/*!	Calculate the Cormack-Jolly-Seber estimates.
Accessor methods:
- phi(int i) - Survival estimates from site i to site i+1 (i = 1,..., K-1),\n
with phi(K-1) the estimate of the product of survival and detection for the\n
last reach.
- P(int i) - Detection probability estimate for site i (i = 2,...,K-1)
*/
class CjsEstimates
{
public:
	CjsEstimates(const CjsStatistics& statistics);
	~CjsEstimates() {}
	double phi(int period) const { return phi_[period]; }
	double p(int site) const { return p_[site]; }
	int phiIndex(int period) const { return phiIndices_[period]; }
	int pIndex(int site) const { return pIndices_[site]; }
	double reachVariance(int begSite,int endSite) const;
	const cbr::Matrix<double>& covariance() const { return covariance_; }
private:
	cbr::VectorB<double> phi_;
	cbr::VectorB<double> p_;
	cbr::VectorB<int> phiIndices_;
	cbr::VectorB<int> pIndices_;
	cbr::Matrix<double> covariance_;
};
#endif
