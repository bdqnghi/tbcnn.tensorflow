/*
*	© Superharmonic Technologies
*	Pavlos Sakoglou
*
*  ===================================================
*
*	Matrix class definition
*
*/

// Multiple include guards
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>

// Compile-time Matrix class
template <typename T, std::size_t NR, std::size_t NC>
class Matrix {
public:

	// Constructors
	Matrix();		
	Matrix(T val);	
	Matrix(const Matrix & matrix);	

	// Destructor
	~Matrix();	

	// Operator overloading

	// Modifying operators
	T operator()(int i, int j);				// Access and modify
	Matrix & operator+=(const Matrix & matrix);		// Matrix Addition
	Matrix & operator-=(const Matrix & matrix);		// Matrix Subtraction
	Matrix & operator*=(const T scalar);			// Scalar Multiplication
	Matrix & operator+=(const T scalar);			// Scalar Addition
	Matrix & operator-=(const T scalar);			// Scalar Subtraction	
	Matrix & operator/=(const T scalar);			// Scalar Division
	Matrix & operator=(const Matrix & matrix);		// Assignment operator

	// Non-modifying operators
	const T operator()(int i, int j)			const;		// Get an element	
	Matrix operator+(const Matrix & matrix)			const;		// Matrix Addition	
	Matrix operator-(const Matrix & matrix)			const;		// Matrix Subtraction
	Matrix operator*(const Matrix<T, NC, NR> & matrix)	const;		// Matrix Multiplication 
	Matrix operator*(const T scalar)			const;		// Scalar Multiplication	
	Matrix operator+(const T scalar)			const;		// Scalar Addition	
	Matrix operator-(const T scalar)			const;		// Scalar Subtraction	
	Matrix operator/(const T scalar)			const;		// Scalar Division

	// Utilities

	// Print matrix
	const void print() const;		

	// Elementary Algorithms

	Matrix &	makeIdentity();					// Identity Matrix
	Matrix		transpose();					// Transpose 
	Matrix &	randomize(T start_range, T end_range);		// Randomize 			
	T		trace()				const;		// Trace of a square matrix

private:
	// 2D dynamic array
	T * * m_matrix;
};


#ifndef MATRIX_CPP
#include "Matrix.cpp"
#endif // !MATRIX_CPP

#endif // !MATRIX_HPP
