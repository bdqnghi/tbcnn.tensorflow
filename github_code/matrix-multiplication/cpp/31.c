/* @Author: Marcello Marques de Oliveira [CP3 code]
 * Matrix Multiplication (naive)
 */

#include "../definitions.hpp"

#define DIM 2

                          //answer
void MatrixMultiplication(int A[][DIM], int M[][DIM], int rm, int cm,
                          int N[][DIM], int rn, int cn)
{
    if (cm != rn) return; 

    for (int i = 0; i < rm; i++)
        for (int j = 0; j < cn; j++) {
            A[i][j] = 0;
            for (int k = 0; k < cm; k++)
                A[i][j] += M[i][k] * N[k][j];
        }
}

int main()
{
    int N[DIM][DIM] = {{1, 0}, {0, 1}};
    int M[DIM][DIM] = {{9, 3,}, {15, 8}};
    int A[DIM][DIM];

    MatrixMultiplication(A, N, DIM, DIM, M, DIM, DIM);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            cout << A[i][j] << " ";

    return 0;
}