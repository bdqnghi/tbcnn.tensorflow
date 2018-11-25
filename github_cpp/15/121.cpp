


#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>


template <typename T, std::size_t NR, std::size_t NC>
class Matrix {
public:

	
	Matrix();		
	Matrix(T val);	
	Matrix(const Matrix & matrix);	

	
	~Matrix();	

	

	
	T operator()(int i, int j);				
	Matrix & operator+=(const Matrix & matrix);		
	Matrix & operator-=(const Matrix & matrix);		
	Matrix & operator*=(const T scalar);			
	Matrix & operator+=(const T scalar);			
	Matrix & operator-=(const T scalar);			
	Matrix & operator/=(const T scalar);			
	Matrix & operator=(const Matrix & matrix);		

	
	const T operator()(int i, int j)			const;		
	Matrix operator+(const Matrix & matrix)			const;		
	Matrix operator-(const Matrix & matrix)			const;		
	Matrix operator*(const Matrix<T, NC, NR> & matrix)	const;		
	Matrix operator*(const T scalar)			const;		
	Matrix operator+(const T scalar)			const;		
	Matrix operator-(const T scalar)			const;		
	Matrix operator/(const T scalar)			const;		

	

	
	const void print() const;		

	

	Matrix &	makeIdentity();					
	Matrix		transpose();					
	Matrix &	randomize(T start_range, T end_range);		
	T		trace()				const;		

private:
	
	T * * m_matrix;
};


#ifndef MATRIX_CPP
#include "Matrix.cpp"
#endif 

#endif 
