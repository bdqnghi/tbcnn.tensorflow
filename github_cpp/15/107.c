



#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
#include <iostream>

using namespace std;


template<typename T>
Matrix<T>::Matrix(unsigned int _row, unsigned int _column, const T& _filler) {
    this->matrix.resize(_row);
    for(int i = 0; i < matrix.size(); i++) {
        matrix[i].resize(_column, _filler);
    }
    this->rows = _row;
    this->columns = _column;

}


template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    this->matrix = other.matrix;
    this->rows = other.rows;
    this->columns = other.columns;
}


template<typename T>
Matrix<T>::~Matrix() {
}


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





template<typename T>
T& Matrix<T>::operator()(const unsigned int& row, const unsigned int& column) {
    return this->matrix[row][column];
}


template<typename T>
const T& Matrix<T>::operator()(const unsigned int& row, const unsigned int& column) const {
    return this->matrix[row][column];
}


template<typename T>
unsigned int Matrix<T>::numrows() const {
    return this->rows;
}


template<typename T>
unsigned int Matrix<T>::numcols() const {
    return this->columns;
}


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
