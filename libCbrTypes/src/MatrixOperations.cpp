#include "MatrixOperations.h"
#include <memory>
using namespace std;

namespace cbr
{
    Matrix<double> *MatrixOperations::multiply(const Matrix<double> &lhs, const Matrix<double> &rhs) const
    {
        Q_ASSERT(lhs.cols() == rhs.rows());
        int rows = lhs.rows();
        int cols = rhs.cols();
        Matrix <double> *retMatrix = new Matrix<double>(rows, cols, 0.0);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int m = 0; m < lhs.cols(); m++) {
                    retMatrix->vec()[i * cols + j] += lhs.at(i, m) * rhs.at(m, j);
                }
            }
        }
        return retMatrix;
/*        auto_ptr<Matrix<double> > retValPtr(new Matrix<double>(lhs.rows(), rhs.cols(), 0.0));
        Matrix<double> &retVal = *retValPtr;
        for (int i=0; i < retVal.rows(); ++i)
            for (int j=0; j < retVal.cols(); ++j)
                for (int m=0; m < lhs.cols(); ++m)
                    retVal(i, j) += lhs(i, m) * rhs(m, j);
        return retValPtr.release();*/
    }
};
