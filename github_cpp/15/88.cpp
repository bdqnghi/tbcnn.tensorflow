






#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],                 
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],                 
        const uint32_t b_cols,
        double c[]) {
    

	int i, j, k;            
	double sum;             

	for (i = 0; i < a_rows; i++) {                          
		for (j = 0; j < b_cols; j++) {                      
			sum = 0;                                        
			for (k = 0; k < a_cols; k++) {                  
				sum += a[i*a_cols + k] * b[k*b_cols + j];   
			}
			c[i*b_cols + j] = sum;                          
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

	double** c = (double**) malloc(a_rows * sizeof(double));    

	if (c == NULL) {
		return NULL;
	}

	for (i = 0; i < a_rows; i++) {
		c[i] = (double*) malloc(b_cols * sizeof(double));       
	}

	for (i = 0; i < a_rows; i++) {
		for (j = 0; j < b_cols; j++) {
			sum = 0;
			for (k = 0; k < a_cols; k++) {
				sum += a[i][k] * b[k][j];                       
			}                                                   
			c[i][j] = sum;
		}
	}

    return c;                                                   
}


double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
	int i, j;

	double** c = (double**) malloc(a_cols * sizeof(double));    

	if (c == NULL) {
		return NULL;
	}

	for (i = 0; i < a_cols; i++) {
		c[i] = (double*) malloc(a_rows * sizeof(double));       
	}

	for (i = 0; i < a_rows; i++) {
		for (j = 0; j < a_cols; j++) {
			c[j][i] = a[i][j];                                  
		}
	}

    return c;                                                   
}
