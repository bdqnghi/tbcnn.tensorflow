#ifndef MATRIX_H
#define MATRIX_H

#include <string>

/**
 * Class that gives the functionality of matrices from linear algebra.
 * Implements operations like matrix-multiplication, scalar multiplication etc.
 * Overloads several operators such as the *-operator for ease of use.
 *
 * Uses a raw heap allocated array internally. This is not optimal but I did it
 * to learn more about memory management.
 *
 * Stores the matrix-data as a std::vector in the background and gives an api to the
 * matrix via the ()-operator, as a getter and setter.
 *
 * Example:
 *
 *      Matrix<double> A(2,3); // constructs a 2x3 matrix
 *      A(0,0) = 5             // sets element 0,0 equal to 5
 *      double d = A(0,0)      // variable d is now equal to 5
 *      A(0,0) += 1            // Adds 1 to element 0,0
 *
 * @author Axel Lindeberg
 */
template <typename T>
class Matrix {
public:
    explicit Matrix(int size = 0) : Matrix(size, size) { }
    explicit Matrix(int rows, int cols);
    Matrix(std::initializer_list<T> &&s);

    // rule of five
    Matrix(const Matrix &a);         // copy constructor
    Matrix(Matrix &&a);              // move constructor
    void operator=(const Matrix &a); // copy assignment
    void operator=(Matrix &&a);      // move assignment
    ~Matrix() { delete[] m_vec; }    // destructor

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

// solves linker issue with templates in header files
#include "Matrix.cpp"

#endif /* MATRIX_H */
