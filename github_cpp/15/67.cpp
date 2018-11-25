














#include <omp.h>

#include "../matmult.hpp"



#pragma GCC push_options
#pragma GCC optimize ("O1")


Matrix<float> multiplyMatricesOMP(Matrix<float> a,
                                  Matrix<float> b,
                                  int num_threads) {


  
  if (a.columns != b.rows) {
    throw std::domain_error("Matrix dimensions do not allow matrix-multiplication.");
  }

  
  auto rows = a.rows;
  auto columns = b.columns;

  
  auto result = Matrix<float>(rows, columns);

#pragma omp parallel for
  
  for (size_t r = 0; r < rows; r++) {
    
    for (size_t c = 0; c < columns; c++) {

      float e = 0.0;
      
      for (size_t i = 0; i < b.rows; i++) {
        e += a(r, i) * b(i, c);
      }

      
      result(r, c) = e;
    }
  }

  return result;
}

Matrix<double> multiplyMatricesOMP(Matrix<double> a,
                                   Matrix<double> b,
                                   int num_threads) {

  
  if (a.columns != b.rows) {
    throw std::domain_error("Matrix dimensions do not allow matrix-multiplication.");
  }

  
  auto rows = a.rows;
  auto columns = b.columns;

  
  auto result = Matrix<double>(rows, columns);

#pragma omp parallel for
  
  for (size_t r = 0; r < rows; r++) {
    
    for (size_t c = 0; c < columns; c++) {

      double e = 0.0;
      
      for (size_t i = 0; i < b.rows; i++) {
        e += a(r, i) * b(i, c);
      }

      
      result(r, c) = e;
    }
  }

  return result;

}
#pragma GCC pop_options
