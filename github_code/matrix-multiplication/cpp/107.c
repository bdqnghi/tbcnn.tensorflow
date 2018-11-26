/*
 * CIS 280 C++ Project - Matrix Main
 * File: matrix.cpp
 * Names: Jeremy Florence, Christopher Tang
 * Date: 3/14/17
*/

/*The matrix template class allows you to construct a matrix object with a filler value of any type.
This class allows you to perform matrix arithmetic on the matrices, including matrix-matrix
addition, multiplication, subtraction as well as the scalar matrix addition, multiplication,
subtraction, and division operations.
The << operator is overloaded to display the matrix.
There are accessors for the matrix template to allow you to access specific elements in the matrix,
using the notation m(unsigned int i, unsigned int j) where m is a matrix, this allows you to access
the value at i, j.
The accessors numrows() and numcols() return how many rows and how many columns the matrix is made of.*/

#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
#include <iostream>

using namespace std;

// Filler Constructor
template<typename T>
Matrix<T>::Matrix(unsigned int _row, unsigned int _column, const T& _filler) {
    this->matrix.resize(_row);
    for(int i = 0; i < matrix.size(); i++) {
        matrix[i].resize(_column, _filler);
    }
    this->rows = _row;
    this->columns = _column;

}

// Copy Constructor
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    this->matrix = other.matrix;
    this->rows = other.rows;
    this->columns = other.columns;
}

// Destructor
template<typename T>
Matrix<T>::~Matrix() {
}

// Assignment
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
  if (&other == this)
    return *this;

  this->rows = other.numrows();
  this->columns = other.numcols();

  matrix.resize(rows);
  for (int i=0; i<rows; i++) {
    matrix[i].resize(columns);
  }

  for (int i=0; i<rows; i++) {
    for (int j=0; j<columns; j++) {
      matrix[i][j] = other(i, j);
    }
  }

  return *this;
}

// Sum of two matrices
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
  Matrix result(this->rows, other.numcols(), 0);
  try {
      if((this->rows != other.numrows()) || this->columns != other.numcols()) {
          throw "ERROR: Cannot add matrices that are not the same size";
      }

      for (int i=0; i<rows; i++) {
          for (int j=0; j<columns; j++) {
              result(i,j) = this->matrix[i][j] + other(i,j);
          }
      }

      return;
  } catch(const char* msg) {
    cerr << msg <<endl;
  } 

  return result;
}

// Difference of two matrices
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
  Matrix result(this->rows, other.numcols(), 0);  
  try {    
      if((this->rows != other.numrows()) || this->columns != other.numcols()) {
          throw "ERROR: Cannot subtract matrices that are not the same size";
      }

      for (int i=0; i<rows; i++) {
          for (int j=0; j<columns; j++) {
              result(i,j) = this->matrix[i][j] - other(i,j);
          }
      }
  } catch(const char* msg) {
    cerr << msg <<endl;
  }

  return result;
}

// Multiplies this matrix with another from the left
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
  Matrix result(this->rows, other.numcols(), 0);
  try {
      if((this->columns != other.numrows())) {
          throw "ERROR: Invalid matrix sizes for multiplication";
      }
  
      for(int i = 0; i < this->rows; i++){
          for(int j = 0; j < other.numcols(); j++) {
              for(int k = 0; k<this->columns; k++) {
                  result(i,j) = result(i,j) + matrix[i][k] * other(k,j);
              }
          }
      }
  } catch(const char* msg) {
    cerr << msg <<endl;
  }

    return result;
}



//Matrix Scalar Addition
template<typename T>
Matrix<T> Matrix<T>::operator+(const T& scalar){
  Matrix<T> result(rows, columns, 0);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      result(i, j) = matrix[i][j] + scalar;
    }
  }
  return result;
}

//Matrix Scalar Subtraction
template<typename T>
Matrix<T> Matrix<T>::operator-(const T& scalar){
  Matrix<T> result(rows, columns, 0);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      result(i, j) = matrix[i][j] - scalar;
    }
  }
  return result;
}

//Matrix Scalar Multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar){
  Matrix<T> result(rows, columns, 0);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      result(i, j) = matrix[i][j] * scalar;
    }
  }
  return result;
}

//Matrix Scalar Division
template<typename T>
Matrix<T> Matrix<T>::operator/(const T& scalar){
  Matrix<T> result(rows, columns, 0);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      result(i, j) = matrix[i][j] / scalar;
    }
  }
  return result;
}

//Transpose of this matrix, work in progress
/*template<typename T>
Matrix<T> Matrix<T>::transpose(){
  Matrix<T> result(rows, columns, 0);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      result(i, j) = matrix[j][i];
    }
  }
  return result;
}*/

// Access a specific element
template<typename T>
T& Matrix<T>::operator()(const unsigned int& row, const unsigned int& column) {
    return this->matrix[row][column];
}

// Access a specific element
template<typename T>
const T& Matrix<T>::operator()(const unsigned int& row, const unsigned int& column) const {
    return this->matrix[row][column];
}

// Returns the number of rows
template<typename T>
unsigned int Matrix<T>::numrows() const {
    return this->rows;
}

// Returns the number of columns
template<typename T>
unsigned int Matrix<T>::numcols() const {
    return this->columns;
}

// Prints a Matrix as output
template<typename T>
ostream& operator << (ostream& out, const Matrix<T>& m) {
    for (int r = 0; r < m.numrows(); r++) {
        for(int c = 0; c < m.numcols(); c++) {
            out << m(r,c) << " ";
        }
        out << endl;
    }

    return out;
}

#endif
