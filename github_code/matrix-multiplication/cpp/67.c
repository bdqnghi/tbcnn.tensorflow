// Copyright 2018 Delft University of Technology
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// OpenMP:
#include <omp.h>

#include "../matmult.hpp"

/* You may not remove these pragmas: */
/*************************************/
#pragma GCC push_options
#pragma GCC optimize ("O1")
/*************************************/

Matrix<float> multiplyMatricesOMP(Matrix<float> a,
                                  Matrix<float> b,
                                  int num_threads) {


  // Test if matrices can be multiplied.
  if (a.columns != b.rows) {
    throw std::domain_error("Matrix dimensions do not allow matrix-multiplication.");
  }

  // Height and width
  auto rows = a.rows;
  auto columns = b.columns;

  // Create the resulting matrix
  auto result = Matrix<float>(rows, columns);

#pragma omp parallel for
  // For each row
  for (size_t r = 0; r < rows; r++) {
    // For each column
    for (size_t c = 0; c < columns; c++) {

      float e = 0.0;
      // Accumulate the product of the elements
      for (size_t i = 0; i < b.rows; i++) {
        e += a(r, i) * b(i, c);
      }

      // Store the result
      result(r, c) = e;
    }
  }

  return result;
}

Matrix<double> multiplyMatricesOMP(Matrix<double> a,
                                   Matrix<double> b,
                                   int num_threads) {

  // Test if matrices can be multiplied.
  if (a.columns != b.rows) {
    throw std::domain_error("Matrix dimensions do not allow matrix-multiplication.");
  }

  // Height and width
  auto rows = a.rows;
  auto columns = b.columns;

  // Create the resulting matrix
  auto result = Matrix<double>(rows, columns);

#pragma omp parallel for
  // For each row
  for (size_t r = 0; r < rows; r++) {
    // For each column
    for (size_t c = 0; c < columns; c++) {

      double e = 0.0;
      // Accumulate the product of the elements
      for (size_t i = 0; i < b.rows; i++) {
        e += a(r, i) * b(i, c);
      }

      // Store the result
      result(r, c) = e;
    }
  }

  return result;

}
#pragma GCC pop_options
