/*  matrix-multiplication.cpp
 *
 *  a program that multiplies two matrices together
 *
 *  Author: cmhughes
 *  Date:   November 18th, 2016
 *
 *  Output: loop through an array
 *
 */
#include <iostream>
#include <cassert>  // to assert that the matrix dimensions agree

// two-dimensional arrays
int matrix_a[2][3] = {
                       {2,4,8},
                       {20,40,80},
                     };

int matrix_b[3][4] = {
                       {2,4,8,16},
                       {20,40,80,160},
                       {21,41,81,161},
                     };

int main() {

    // make sure the matrix dimensions agree
    int number_of_columns_in_a = sizeof(matrix_a[0])/sizeof(matrix_a[0][0]);
    std::cout << "columns_in_a: " << number_of_columns_in_a << "\n";

    int number_of_rows_in_b = sizeof(matrix_b)/sizeof(matrix_b[0]);
    std::cout << "rows_in_b: " << number_of_rows_in_b << "\n";

    // the program will exit if dimensions don't agree
    assert(number_of_columns_in_a == number_of_rows_in_b);

    // otherwise, let's compute the number of rows in matrix_a
    int number_of_rows_in_a = sizeof(matrix_a)/sizeof(matrix_a[0]);
    std::cout << "rows_in_a: " << number_of_rows_in_a << "\n";

    // and the number of columns in matrix_b
    int number_of_columns_in_b = sizeof(matrix_b[0])/sizeof(matrix_b[0][0]);
    std::cout << "columns_in_b: " << number_of_columns_in_b << "\n";

    // the product will be stored in c
    int matrix_c[number_of_rows_in_a][number_of_columns_in_b];

    // initialise the matrix_c to 0
    for (int i=0; i<number_of_rows_in_a; i++ ){
        for (int j=0; j<number_of_columns_in_b; j++ ){
             matrix_c[i][j] = 0;
        }
    }

    // loop back through and perform matrix multiplication
    for (int i=0; i<number_of_rows_in_a; i++ ){
        for (int j=0; j<number_of_columns_in_b; j++ ){
             for(int k=0; k<number_of_columns_in_a; k++){
                matrix_c[i][j] += matrix_a[i][k]*matrix_b[k][j];
             }
             std::cout << matrix_c[i][j] << " | ";
        }
        std::cout<< "\n===========New row!===========\n";
    }

    return (0);
}
