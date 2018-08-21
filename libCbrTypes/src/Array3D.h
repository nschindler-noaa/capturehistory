#pragma once
#include <vector>
#include <iostream>
#include <cassert>

namespace cbr
{
template <class T>
class Array3D
{
  public:
    Array3D(int dim1, int dim2, int dim3);
    Array3D(int dim1, int dim2, int dim3, const T& initVal);
	~Array3D() {}
    const T& operator()(int i, int j, int k) const;
	const T& at(int i, int j, int k) const;
    T& operator()(int i, int j, int k);
    int dim1() const {return dim1_;}
    int dim2() const {return dim2_;}
    int dim3() const {return dim3_;}
	void writeObject(std::ostream& os) const;
  private:
    const int dim1_;
    const int dim2_;
    const int dim3_;
    std::vector<T> vec_;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Array3D<T>& rhs)
{
	rhs.writeObject(os);
	return os;
}

template <class T>
Array3D<T>::Array3D(int dim1, int dim2, int dim3) :
    dim1_(dim1), dim2_(dim2), dim3_(dim3),
    vec_(dim1*dim2*dim3)
{}

template <class T>
Array3D<T>::Array3D(int dim1, int dim2, int dim3,
		       const T& initVal) :
    dim1_(dim1), dim2_(dim2),dim3_(dim3),
    vec_(dim1*dim2*dim3,initVal)
{}

template <class T>
const T& Array3D<T>::operator()(int i, int j, int k) const
{
#ifdef _DEBUG
	assert (i >= 0 && i < dim1_);
	assert (j >= 0 && j < dim2_);
	assert (k >= 0 && k < dim3_);
#endif
    return vec_[i*dim2_*dim3_ + j*dim3_ + k];
}

template <class T>
const T& Array3D<T>::at(int i, int j, int k) const
{
#ifdef _DEBUG
	assert (i >= 0 && i < dim1_);
	assert (j >= 0 && j < dim2_);
	assert (k >= 0 && k < dim3_);
#endif
    return vec_[i*dim2_*dim3_ + j*dim3_ + k];
}

template <class T>
T& Array3D<T>::operator()(int i, int j, int k)
{
    return vec_[i*dim2_*dim3_ + j*dim3_ + k];
}

template <class T>
void Array3D<T>::writeObject(std::ostream& os) const
{
	for (int i=0; i < dim1(); ++i)
	{
		for (int j=0; j < dim2(); ++j)
		{
			for (int k=0; k < dim3()-1; ++k)
				os << operator()(i,j,k) << " ";
			os << operator()(i,j,dim3()-1) << "\n";
		}
		if (i < dim1()-1)
			os << "\n";
	}
}
};
