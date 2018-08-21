#pragma once
#include <vector>
#include <iostream>
#include <cassert>

namespace cbr
{
	template <class T>
	class Array5D
	{
	public:
		Array5D(int dim1, int dim2, int dim3, int dim4, int dim5);
		Array5D(int dim1, int dim2, int dim3, int dim4, int dim5, const T& initVal);
		~Array5D() {}
		const T& operator()(int i, int j, int k, int m, int n) const;
		const T& at(int i, int j, int k, int m, int n) const;
		T& operator()(int i, int j, int k, int m, int n);
		int dim1() const { return dim1_; }
		int dim2() const { return dim2_; }
		int dim3() const { return dim3_; }
		int dim4() const { return dim4_; }
		int dim5() const { return dim5_; }
	private:
		const int dim1_;
		const int dim2_;
		const int dim3_;
		const int dim4_;
		const int dim5_;
		std::vector<T> vec_;
	};

	template <class T>
	Array5D<T>::Array5D(int dim1, int dim2, int dim3, int dim4, int dim5) :
	dim1_(dim1), dim2_(dim2), dim3_(dim3), dim4_(dim4), dim5_(dim5),
		vec_(dim1*dim2*dim3*dim4*dim5)
	{}

	template <class T>
	Array5D<T>::Array5D(int dim1, int dim2, int dim3, int dim4, int dim5, const T& initVal) :
	dim1_(dim1), dim2_(dim2),dim3_(dim3), dim4_(dim4), dim5_(dim5), vec_(dim1*dim2*dim3*dim4*dim5,initVal)
	{}

	template <class T>
	const T& Array5D<T>::operator()(int i, int j, int k, int m, int n) const
	{
#ifdef _DEBUG
		assert (i >= 0 && i < dim1_);
		assert (j >= 0 && j < dim2_);
		assert (k >= 0 && k < dim3_);
		assert(m >= 0 && m < dim4_);
		assert(n >= 0 && n < dim5_);
#endif
		return vec_[i*dim2_*dim3_*dim4_*dim5_ + j*dim3_*dim4_*dim5_ + k*dim4_*dim5_ + m*dim5_ + n];
	}

	template <class T>
	const T& Array5D<T>::at(int i, int j, int k, int m, int n) const
	{
#ifdef _DEBUG
		assert (i >= 0 && i < dim1_);
		assert (j >= 0 && j < dim2_);
		assert (k >= 0 && k < dim3_);
		assert(m >= 0 && m < dim4_);
		assert(n >= 0 && n < dim5_);
#endif
		return vec_[i*dim2_*dim3_*dim4_*dim5_ + j*dim3_*dim4_*dim5_ + k*dim4_*dim5_ + m*dim5_ + n];
	}

	template <class T>
	T& Array5D<T>::operator()(int i, int j, int k, int m, int n)
	{
		return vec_[i*dim2_*dim3_*dim4_*dim5_ + j*dim3_*dim4_*dim5_ + k*dim4_*dim5_ + m*dim5_ + n];
	}
};
