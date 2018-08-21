#pragma once
#include "Matrix.h"

namespace cbr
{
	class MatrixOperations
	{
	public:
		MatrixOperations() {}
		~MatrixOperations() {}
		 Matrix<double> *multiply(const Matrix<double> &lhs, const Matrix<double> &rhs) const;
	};
};
