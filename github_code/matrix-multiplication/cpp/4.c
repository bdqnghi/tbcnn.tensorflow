// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Peter Sumners
// pls945
// Slip days used: <0>
// Spring 2018

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // For malloc, others.
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {

    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
    for (int32_t i = 0; i < a_rows; i++) { // Loop through a_rows
        for (int32_t j = 0; j < b_cols; j++) { // Loop through b_cols.

            c[i * b_cols + j] = 0; // Init. result vals. to 0.
            for (int32_t k = 0; k < a_cols; k++) { // Loop through elems (a_cols), and sum.
                c[i * b_cols + j] += a[i * a_cols + k] * b[k * b_cols + j];
            }
        }
    }
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {

    // a cols == b rows: no need for b rows.

    // Create matrix whose pointer will be returned.
    // Result has a_rows rows and b_cols cols.
    double** result = (double**) malloc(a_rows * sizeof (double*));

    for (int32_t i = 0; i < a_rows; i++) { // Loop through a rows
        // Make new result matrix row.
        result[i] = (double*) malloc(b_cols * sizeof(double));

        for (int32_t j = 0; j < b_cols; j++) { // Loop through b cols.

            result[i][j] = 0; // Init. matrix vals. to 0.
            for (int32_t k = 0; k < a_cols; k++) { // Loop through elems (a_cols), and sum.
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // Sum is elem in row of new matrix.


    return result;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {

    // Just flip rows and columns.
    double** result = (double**) malloc(a_cols * sizeof(double*));
    for (int32_t i = 0; i < a_cols; i++) { // Result rows
        result[i] = (double*) malloc (a_rows * sizeof(double));
        for (int32_t j = 0; j < a_rows; j++) {// Result cols
            result[i][j] = a[j][i];
        }
    }

    return result;
}
