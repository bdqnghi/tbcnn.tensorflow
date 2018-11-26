// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Ryan Kim
// jk39938
// Slip days used: 0
// Summer 2018

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],                 // M x N
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],                 // N x K
        const uint32_t b_cols,
        double c[]) {
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order

	int i, j, k;            // index variables
	double sum;             // ij entry of matrix C; type is double since c[] is an array of doubles

	for (i = 0; i < a_rows; i++) {                          // runs M times
		for (j = 0; j < b_cols; j++) {                      // runs K times
			sum = 0;                                        // set initial sum to 0
			for (k = 0; k < a_cols; k++) {                  // runs N times
				sum += a[i*a_cols + k] * b[k*b_cols + j];   // A_ik * B_kj
			}
			c[i*b_cols + j] = sum;                          // Cij = sum
		}
	}
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
	int i, j, k;
	double sum;

	double** c = (double**) malloc(a_rows * sizeof(double));    // allocation of array containing pointer to ith row

	if (c == NULL) {
		return NULL;
	}

	for (i = 0; i < a_rows; i++) {
		c[i] = (double*) malloc(b_cols * sizeof(double));       // allocation of array containing pointer to ij entry
	}

	for (i = 0; i < a_rows; i++) {
		for (j = 0; j < b_cols; j++) {
			sum = 0;
			for (k = 0; k < a_cols; k++) {
				sum += a[i][k] * b[k][j];                       // runs similarly as multiplyMatrices
			}                                                   // uses pointer addressing instead
			c[i][j] = sum;
		}
	}

    return c;                                                   // return pointer to array of pointers
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
	int i, j;

	double** c = (double**) malloc(a_cols * sizeof(double));    // array contains a_cols elements after A is transposed

	if (c == NULL) {
		return NULL;
	}

	for (i = 0; i < a_cols; i++) {
		c[i] = (double*) malloc(a_rows * sizeof(double));       // array contains a_rows elements after A is transposed
	}

	for (i = 0; i < a_rows; i++) {
		for (j = 0; j < a_cols; j++) {
			c[j][i] = a[i][j];                                  // transposition
		}
	}

    return c;                                                   // return pointer to array of pointers
}
