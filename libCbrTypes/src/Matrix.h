#pragma once

#include <QString>
#include <iostream>
#include <string>

namespace cbr {

    template <class T> class Matrix {
    public:
        typedef int size_type;

        Matrix() : rows_(0), cols_(0), vec_(0) {
        }
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, const T& ival);
        Matrix(const Matrix<T>& matrix);
        ~Matrix();

        int rows() const {
            return rows_;
        }

        int cols() const {
            return cols_;
        }

        void resize(int rows, int cols);

        const T& operator()(int i, int j) const {
            return vec_[i * cols_ + j];
        }

        T& operator()(int i, int j) {
            return vec_[i * cols_ + j];
        }

        const T& at(int i, int j) const {
            return vec_[i * cols_ + j];
        }
        int operator==(const Matrix<T>& matrix) const;

        int operator!=(const Matrix<T>& matrix) const {
            return !(*this == matrix);
        }
        int operator==(const T& val) const;

        int operator!=(const T& val) const {
            return !((*this == val));
        }
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T>& operator+=(const T& rhs);
        Matrix<T>& operator/=(const Matrix<T>& rhs);
        Matrix<T>& operator/=(const T& rhs);
        Matrix<T>& operator=(const Matrix<T>& matrix);
        Matrix<T>& operator=(const T& val);

        const T* operator[](int i) const {
            return vec_ + i*cols_;
        }

        T* operator[](int i) {
            return vec_ + i*cols_;
        }

        T* vec() const {
            return vec_;
        }

        void writeObject(std::ostream& os) const;
        void readObject(std::istream& is);

    private:
        int rows_;
        int cols_;
        T *vec_;
    };

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        matrix.writeObject(os);
        return os;
    }

    template <class T>
    std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
        matrix.readObject(is);
        return is;
    }

    template <class T>
    Matrix<T>::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
        if (rows * cols == 0)
            vec_ = 0;
        else
            vec_ = new T[rows * cols];
    }

    template <class T>
    Matrix<T>::Matrix(int rows, int cols, const T& ival) : rows_(rows),
    cols_(cols) {
        if (rows * cols == 0)
            vec_ = 0;
        else {
            vec_ = new T[rows * cols];
            for (int i = 0; i < rows * cols; i++)
                vec_[i] = ival;
        }
    }

    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& matrix) : rows_(matrix.rows()),
    cols_(matrix.cols()) {
        if (rows_ == 0 || cols_ == 0)
            vec_ = 0;
        else {
            vec_ = new T[rows_ * cols_];
            for (int i = 0; i < rows_ * cols_; i++)
                vec_[i] = matrix.vec_[i];
        }
    }

    template <class T>
    Matrix<T>::~Matrix() {
        delete [] vec_;
    }

    template <class T>
    int Matrix<T>::operator==(const Matrix<T>& matrix) const {
        if ((rows_ != matrix.rows()) || cols_ != matrix.cols())
            return 0;

        int isEqual = 1;
        for (int i = 0; i < rows_ * cols_; i++)
            if (vec_[i] != matrix.vec_[i]) {
                isEqual = 0;
                break;
            }
        return isEqual;
    }

    template <class T>
    int Matrix<T>::operator==(const T& val) const {
        int isEqual = 1;
        for (int i = 0; i < rows_ * cols_; i++)
            if (vec_[i] != val) {
                isEqual = 0;
                break;
            }
        return isEqual;
    }

    template <class T> Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
        if ((rows_ != rhs.rows()) || (cols_ != rhs.cols()))
            throw QString("Matrix+ - matrices not of the same dimensions");

        for (int i = 0; i < rows_ * cols_; ++i)
            vec_[i] += rhs.vec_[i];
        return *this;
    }

    template <class T> Matrix<T>& Matrix<T>::operator+=(const T& rhs) {
        for (int i = 0; i < rows_ * cols_; ++i)
            vec_[i] += rhs;
        return *this;
    }

    template <class T> Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& rhs) {
        if ((rows_ != rhs.rows()) || (cols_ != rhs.cols()))
            throw std::string("Matrix::/= matrices not of the same dimensions");

        for (int i = 0; i < rhs.vec_.size(); ++i)
            vec_[i] /= rhs.vec_[i];

        return *this;
    }

    template <class T> Matrix<T>& Matrix<T>::operator/=(const T& rhs) {
        for (int i = 0; i < rows_ * cols_; ++i)
            vec_[i] /= rhs;
        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
        if (this == &matrix)
            return *this;

        delete [] vec_;
        rows_ = matrix.rows();
        cols_ = matrix.cols();
        if (rows_ == 0 || cols_ == 0)
            vec_ = 0;
        else {
            vec_ = new T[rows_ * cols_];
            for (int i = 0; i < rows_ * cols_; i++)
                vec_[i] = matrix.vec_[i];
        }
        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator=(const T& val) {
        for (int i = 0; i < rows_ * cols_; i++)
            vec_[i] = val;
        return *this;
    }

    template <class T>
    void Matrix<T>::writeObject(std::ostream& os) const {
        int i, j;
        for (i = 0; i < rows_ - 1; i++) {
            for (j = 0; j < cols_ - 1; j++)
                os << vec_[i * cols_ + j] << " ";
            os << vec_[i * cols_ + cols_ - 1] << std::endl;
        }
        if (rows_ > 0) {
            for (j = 0; j < cols_ - 1; j++)
                os << vec_[(rows_ - 1) * cols_ + j] << " ";
            os << vec_[(rows_ - 1) * cols_ + cols_ - 1];
        }
    }

    template <class T>
    void Matrix<T>::readObject(std::istream& is) {
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < cols_; j++)
                is >> vec_[i * cols_ + j];
    }

    template <class T> void Matrix<T>::resize(int rows, int cols) {
        delete [] vec_;
        vec_ = 0;
        rows_ = rows;
        cols_ = cols;

        if (rows * cols > 0)
            vec_ = new T[rows * cols];
    }

    template <class T> Matrix<T> operator+(const Matrix<T>& mat1, const Matrix<T>& mat2) {
        if ((mat1.rows() != mat2.rows()) || (mat1.cols() != mat2.cols()))
            throw QString("Dimensions of matrices do not match");
        Matrix<T> retVal(mat1.rows(), mat1.cols());
        for (int i = 0; i < mat1.rows(); ++i)
            for (int j = 0; j < mat1.cols(); ++j)
                retVal(i, j) = mat1(i, j) + mat2(i, j);
        return retVal;
    }
};
