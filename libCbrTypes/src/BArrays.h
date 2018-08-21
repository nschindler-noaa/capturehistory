#pragma once
/*! \file Define bounded collections.

Allows collections to have a non-zero base, specified by the lower
and upper limits of the collection.
*/

#include <vector>
#include <cassert>
#include "Matrix.h"
#include "Array3D.h"

namespace cbr
{
	namespace BArrays
	{
		typedef std::pair<int,int> bounds;
	};

	template <class T> class VectorB
	{
	public:
		VectorB(BArrays::bounds b);
		VectorB(BArrays::bounds b, const T& initVal);
		VectorB(const VectorB<T>& rhs);
		VectorB(int lower, std::vector<T>* vec);
		~VectorB();
		const T& operator[](int i) const;
		T& operator[](int i);
		int size() const {return vec_->size();}
		const std::vector<T>* raw() const {return vec_;}
	private:
		int lower_;
		int upper_;
		std::vector<T>* vec_;
		bool owner_;
	};

	template <class T> class MatrixB
	{
	public:
		MatrixB(BArrays::bounds bRow, BArrays::bounds bCol);
		MatrixB(BArrays::bounds bRow, BArrays::bounds bCol, const T& initVal);
		MatrixB(int rowL, int colL, Matrix<T>* mat);
		~MatrixB();
		const T& operator()(int i, int j) const;
		T& operator()(int i, int j);
		int rows() const {return mat_->rows();}
		int cols() const {return mat_->cols();}
		const Matrix<T>* raw() const {return mat_;}
	private:
		const int rowL_;
		const int rowU_;
		const int colL_;
		const int colU_;
		Matrix<T>* mat_;
		bool owner_;
	};

	template <class T> class Array3DB
	{
	public:
		Array3DB(BArrays::bounds b1, BArrays::bounds b2, BArrays::bounds b3);
		Array3DB(BArrays::bounds b1, BArrays::bounds b2, BArrays::bounds b3, const T& initVal);
		Array3DB(int dim1L, int dim2L, int dim3L, Array3D<T>* array);
		~Array3DB();
		const T& operator()(int i, int j,int k) const;
		T& operator()(int i, int j,int k);
		int dim1() const {return array_->dim1();}
		int dim2() const {return array_->dim2();}
		int dim3() const {return array_->dim3();}
		const Array3D<T>* raw() const {return array_;}
	private:
		const int dim1L_;
		const int dim1U_;
		const int dim2L_;
		const int dim2U_;
		const int dim3L_;
		const int dim3U_;
		Array3D<T>* array_;
		bool owner_;
	};

	//------------------------------------------------------------------------

	template <class T>
		VectorB<T>::VectorB(BArrays::bounds b) :
	lower_(b.first), upper_(b.second), vec_(new std::vector<T>(b.second-b.first+1)),
		owner_(true)
	{}

	template <class T>
		VectorB<T>::VectorB(BArrays::bounds b, const T& initVal) :
	lower_(b.first), upper_(b.second), vec_(new std::vector<T>(b.second-b.first+1,initVal)),
		owner_(true)
	{}

	template <class T>
		VectorB<T>::VectorB(int lower, std::vector<T>* vec) :
	lower_(lower), upper_(lower+vec->size()), vec_(vec), owner_(false)
	{}

	template <class T>
		VectorB<T>::VectorB(const VectorB<T>& rhs) : lower_(rhs.lower_),upper_(rhs.upper_),
		vec_(new std::vector<T>(*rhs.vec_)), owner_(rhs.owner_)
	{}

	template <class T>
		VectorB<T>::~VectorB()
	{
		if (owner_)
			delete vec_;
	}

	template <class T>
		const T& VectorB<T>::operator[](int i) const
	{
#ifdef _DEBUG
		assert(i <= upper_ && i >= lower_);
#endif
		return (*vec_)[i-lower_];
	}

	template <class T>
		T& VectorB<T>::operator[](int i)
	{
#ifdef _DEBUG
		assert(i <= upper_ && i >= lower_);
#endif
		return (*vec_)[i-lower_];
	}

	template <class T>
		MatrixB<T>::MatrixB(BArrays::bounds bRow, BArrays::bounds bCol) :
	rowL_(bRow.first), rowU_(bRow.second), colL_(bCol.first), colU_(bCol.second),
		mat_(new Matrix<T>(bRow.second-bRow.first+1,bCol.second-bCol.first+1)), owner_(true)
	{}

	template <class T>
		MatrixB<T>::MatrixB(BArrays::bounds bRow, BArrays::bounds bCol, const T& initVal) :
	rowL_(bRow.first), rowU_(bRow.second), colL_(bCol.first), colU_(bCol.second),
		mat_(new Matrix<T>(bRow.second-bRow.first+1,bCol.second-bCol.first+1,initVal)), owner_(true)
	{}

	template <class T>
		MatrixB<T>::MatrixB(int rowL, int colL, Matrix<T>* mat) :
	rowL_(rowL), rowU_(rowL+mat.rows()), colL_(colL), colU_(colL+mat.cols()),
		mat_(mat), owner_(false)
	{}

	template <class T>
		MatrixB<T>::~MatrixB()
	{
		if (owner_)
			delete mat_;
	}

	template <class T>
		const T& MatrixB<T>::operator()(int i, int j) const
	{
#ifdef _DEBUG
		assert (i <= rowU_ && i >= rowL_ && j <= colU_ && j >= colL_);
#endif
		return (*mat_)(i-rowL_,j-colL_);
	}

	template <class T>
		T& MatrixB<T>::operator()(int i, int j)
	{
#ifdef _DEBUG
		assert(i <= rowU_ && i >= rowL_ && j <= colU_ && j >= colL_);
#endif
		return (*mat_)(i-rowL_,j-colL_);
	}

	template <class T>
		Array3DB<T>::Array3DB(BArrays::bounds b1, BArrays::bounds b2, BArrays::bounds b3) :
	dim1L_(b1.first), dim1U_(b1.second), dim2L_(b2.first), dim2U_(b2.second), dim3L_(b3.first),
		dim3U_(b3.second), array_(new Array3D<T>(b1.second-b1.first+1,b2.second-b2.first+1,
		b3.second-b3.first+1)), owner_(true)
	{}

	template <class T>
		Array3DB<T>::Array3DB(BArrays::bounds b1, BArrays::bounds b2, BArrays::bounds b3, const T& initVal) :
	dim1L_(b1.first), dim1U_(b1.second), dim2L_(b2.first), dim2U_(b2.second), dim3L_(b3.first),
		dim3U_(b3.second), array_(new Array3D<T>(b1.second-b1.first+1,
		b2.second-b2.first+1,
		b3.second-b3.first+1,initVal)), owner_(true)
	{}

	template <class T>
		Array3DB<T>::Array3DB(int dim1L, int dim2L,
		int dim3L, Array3D<T>* array) :

	dim1L_(dim1L), dim1U_(dim1L+array.dim1()),
		dim2L_(dim2L), dim2U_(dim2L+array.dim2()),
		dim3L_(dim3L), dim3U_(dim3L+array.dim3()), array_(array),
		owner_(false)
	{}

	template <class T>
		Array3DB<T>::~Array3DB()
	{
		if (owner_)
			delete array_;
	}

	template <class T>
		const T& Array3DB<T>::operator()(int i, int j,
		int k) const
	{
#ifdef _DEBUG
		assert (i <= dim1U_ && i >= dim1L_ && j <= dim2U_ && j >= dim2L_ && k <= dim3U_ && k >= dim3L_);
#endif
		return (*array_)(i-dim1L_,j-dim2L_,k-dim3L_);
	}

	template <class T>
		T& Array3DB<T>::operator()(int i, int j, int k)
	{
#ifdef _DEBUG
		assert(i <= dim1U_ && i >= dim1L_ && j <= dim2U_ && j >= dim2L_ && k <= dim3U_ && k >= dim3L_);
#endif
		return (*array_)(i-dim1L_,j-dim2L_,k-dim3L_);
	}
};
