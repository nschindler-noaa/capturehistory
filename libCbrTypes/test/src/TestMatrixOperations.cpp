/*
	Unit test for CJS estimates

	Input:  the minimum sufficient statistics for the Burnham Blue Book example.
	Expected output:  The cjs estimates and corresponding variances and covarianctes from Burnham's Blue Book.
*/

#include "TestMatrixOperations.h"
#include <MatrixOperations.h>
using namespace cbr;

TEST(MatrixOperations, multiply)
{
	MatrixOperations matrixOper;

	Matrix<double> lhs(3, 2);
	lhs(0, 0) = 2.;
	lhs(0, 1) = 3.;
	lhs(1, 0) = 4.;
	lhs(1, 1) = 5.;
	lhs(2, 0) = 6.;
	lhs(2, 1) = 7.;
	Matrix<double> rhs(2, 3);
	rhs(0, 0) = 8.;
	rhs(0, 1) = 9.;
	rhs(0, 2) = 10.;
	rhs(1, 0) = 11.;
	rhs(1, 1) = 12.;
	rhs(1, 2) = 13.;

	Matrix<double> *result = matrixOper.multiply(lhs, rhs);
	EXPECT_EQ(3, result->rows());
	EXPECT_EQ(3, result->cols());
	EXPECT_EQ(49., result->at(0,0));
	EXPECT_EQ(54., result->at(0,1));
	EXPECT_EQ(59., result->at(0,2));
	EXPECT_EQ(87., result->at(1,0));
	EXPECT_EQ(96., result->at(1,1));
	EXPECT_EQ(105., result->at(1,2));
	EXPECT_EQ(125., result->at(2,0));
	EXPECT_EQ(138., result->at(2,1));
	EXPECT_EQ(151., result->at(2,2));

	delete result;
};
