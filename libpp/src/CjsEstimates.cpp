#include "CjsEstimates.h"
#include "CjsStatistics.h"
using namespace std;
using namespace cbr;

CjsEstimates::CjsEstimates(const CjsStatistics& statistics) : phi_(BArrays::bounds(1,statistics.k()-1)),
	p_(BArrays::bounds(2,statistics.k()-1)), phiIndices_(BArrays::bounds(1,statistics.k()-1)),
	pIndices_(BArrays::bounds(2,statistics.k()-1)), covariance_(statistics.k()*2-3,statistics.k()*2-3,0.0)
{
	const int k = statistics.k();
	int index = 0;
	for (int i=1; i <= k-1; ++i)
		phiIndices_[i] = index++;
	for (int i=2; i <= k-1; ++i)
		pIndices_[i] = index++;

	VectorB<double> r(BArrays::bounds(1,k-1));
	VectorB<double> R(BArrays::bounds(1,k-1));
	VectorB<double> m(BArrays::bounds(2,k-1));
	VectorB<double> z(BArrays::bounds(2,k-1));
	VectorB<double> A(BArrays::bounds(1,k));
	VectorB<double> B(BArrays::bounds(2,k));

	for (int i=1; i <= k-1; ++i)
	{
		r[i] = static_cast<double>(statistics.r(i));
		R[i] = static_cast<double>(statistics.R(i));
	}
	for (int i=2; i <= k-1; ++i)
		m[i] = static_cast<double>(statistics.m(i));
	z[2] = statistics.r(1) - statistics.m(2);
	for (int i=3; i <= k-1; ++i)
		z[i] = z[i-1] + r[i-1] - m[i];

	for (int i=1; i <= k-1; ++i)
		A[i] = r[i]/R[i];
	for (int i=2; i <= k-1; ++i)
		B[i] = m[i]/(m[i] + z[i]);
	A[k] = B[k] = 1.0;

	for (int i=1; i <= k-1; ++i)
		phi_[i] = A[i]*(B[i+1] + (1.0 - B[i+1])/A[i+1]);
	for (int i=2; i <= k-1; ++i)
		p_[i] = B[i]/(B[i] + (1.0-B[i])/A[i]);

	for (int i=1; i <= k-2; ++i)
		covariance_(phiIndex(i),phiIndex(i)) = phi(i)*phi(i) *
		((1.0/r[i] - 1.0/R[i]) + (1.0-p_[i+1])*(1.0-p(i+1))*
		(1.0/r[i+1] - 1/R[i+1]) + p(i+1)*(1.0-p(i+1))*
		(1.0-A[i+1])*(1.0-A[i+1])/(A[i+1]*(m[i+1]+z[i+1])));
	covariance_(phiIndex(k-1),phiIndex(k-1)) = phi(k-1)*phi(k-1)*(1.0/r[k-1] - 1.0/R[k-1]);
	for (int i=2; i <= k-1; ++i)
		covariance_(pIndex(i),pIndex(i)) = p(i)*p(i)*(1.0-p(i))*(1.0-p(i))*
		(1.0/r[i] - 1.0/R[i] + 1.0/m[i] + 1.0/z[i]);

	for (int i=1; i <= k-2; ++i)
		covariance_(phiIndex(i),phiIndex(i+1)) = covariance_(phiIndex(i+1),phiIndex(i)) =
		-phi(i)*phi(i+1)*(1.0-p(i+1))*(1.0/r[i+1] - 1.0/R[i+1]);
	for (int i=2; i <= k-1; ++i)
		covariance_(phiIndex(i),pIndex(i)) = covariance_(pIndex(i),phiIndex(i)) =
		phi(i)*p(i)*(1.0-p(i))*(1.0/r[i] - 1/R[i]);
	for (int i=1; i <= k-2; ++i)
		covariance_(phiIndex(i),pIndex(i+1)) = covariance_(pIndex(i+1),phiIndex(i)) = 
		-phi(i)*p(i+1)*(1.0-p(i+1))*(1.0-p(i+1))*
		((1.0/r[i+1] - 1.0/R[i+1]) + (1.0-r[i+1]/R[i+1])*(1.0/z[i+1]));
}

double CjsEstimates::reachVariance(int begSite, int endSite) const
{
	VectorB<double> derivatives(BArrays::bounds(begSite,endSite),1.0);
	VectorB<int> indices(BArrays::bounds(begSite,endSite));
	for (int i=begSite; i <= endSite; ++i)
	{
		indices[i] = phiIndex(i);
		for (int j=begSite; j < i; ++j)
			derivatives[i] *= phi(j);
		for (int j=i+1; j <= endSite; ++j)
			derivatives[i] *= phi(j);
	}
	double returnValue = 0.0;
	for (int i=begSite; i <=endSite; ++i)
		for (int j=begSite; j <= endSite; ++j)
			returnValue += derivatives[i]*derivatives[j]*covariance_(indices[i],indices[j]);
	return returnValue;
}
