#include "MatrixOperations.h"
#include <memory>
using namespace std;

namespace cbr
{
	Matrix<double> *MatrixOperations::multiply(const Matrix<double> &lhs, const Matrix<double> &rhs) const
	{
		Q_ASSERT(lhs.cols() == rhs.rows());
        auto_ptr<Matrix<double> > retValPtr(new Matrix<double>(lhs.rows(), rhs.cols(), 0.0));
		Matrix<double> &retVal = *retValPtr;
		for (int i=0; i < retVal.rows(); ++i)
			for (int j=0; j < retVal.cols(); ++j)
				for (int m=0; m < lhs.cols(); ++m)
					retVal(i, j) += lhs(i, m) * rhs(m, j);
		return retValPtr.release();
	}
};
