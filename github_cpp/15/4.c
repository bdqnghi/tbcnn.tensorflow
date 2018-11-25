






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

    
    for (int32_t i = 0; i < a_rows; i++) { 
        for (int32_t j = 0; j < b_cols; j++) { 

            c[i * b_cols + j] = 0; 
            for (int32_t k = 0; k < a_cols; k++) { 
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

    

    
    
    double** result = (double**) malloc(a_rows * sizeof (double*));

    for (int32_t i = 0; i < a_rows; i++) { 
        
        result[i] = (double*) malloc(b_cols * sizeof(double));

        for (int32_t j = 0; j < b_cols; j++) { 

            result[i][j] = 0; 
            for (int32_t k = 0; k < a_cols; k++) { 
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    


    return result;
}


double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {

    
    double** result = (double**) malloc(a_cols * sizeof(double*));
    for (int32_t i = 0; i < a_cols; i++) { 
        result[i] = (double*) malloc (a_rows * sizeof(double));
        for (int32_t j = 0; j < a_rows; j++) {
            result[i][j] = a[j][i];
        }
    }

    return result;
}
