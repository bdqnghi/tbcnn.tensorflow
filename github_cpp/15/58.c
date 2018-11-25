#ifndef MATRIX_H
#define MATRIX_H

#include <string>


template <typename T>
class Matrix {
public:
    explicit Matrix(int size = 0) : Matrix(size, size) { }
    explicit Matrix(int rows, int cols);
    Matrix(std::initializer_list<T> &&s);

    
    Matrix(const Matrix &a);         
    Matrix(Matrix &&a);              
    void operator=(const Matrix &a); 
    void operator=(Matrix &&a);      
    ~Matrix() { delete[] m_vec; }    

    T  operator()(int row, int col) const;
    T& operator()(int row, int col);

    constexpr size_t rows() const { return m_rows; }
    constexpr size_t cols() const { return m_cols; }

    void operator+=(const Matrix &a) { *this = *this + a; }
    void operator-=(const Matrix &a) { *this = *this - a; }
    void operator*=(const Matrix &a) { *this = *this * a; }

    void randomize();
    void reset() { std::fill(begin(), end(), T()); }
    Matrix scalar_multi(const Matrix &a) const;
    Matrix transpose() const;

    using iterator = T*;
    constexpr iterator begin(int row = 0) const { return m_vec + m_cols * row; }
    constexpr iterator end(int row) const { return begin(row+1); }
    constexpr iterator end() const { return begin(m_rows); }
private:
    size_t m_rows, m_cols;
    T *m_vec;
};


#include "Matrix.cpp"

#endif 
