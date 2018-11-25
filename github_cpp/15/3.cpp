

#include "../definitions.hpp"

#define DIM 3

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

void CpMatrix (int A[][DIM], int B[][DIM], int r, int c)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            A[i][j] = B[i][j];
}

void MatrixExponentiation(int M[][DIM], int N, int E)
{
    int I[N][DIM], tmp[N][DIM];

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            I[i][j] = (i==j ? 1:0);

    while (E) {
        if (E & 1) {
            MatrixMultiplication(tmp, M, N, N, I, N, N);
            CpMatrix(I, tmp, N, N);
        }

        MatrixMultiplication(tmp, M, N, N, M, N, N);
        CpMatrix(M, tmp, N, N);

        E >>= 1;
    }

    CpMatrix(M, I, N, N);
}

int main()
{
    int M[DIM][DIM] = {{9, 3, 0}, {15, 8, 0}, {0, 0, 0}};
    int A[DIM][DIM];

    MatrixMultiplication(A, M, 2, 2, M, 2, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << A[i][j] << " ";
        cout << endl;
    } cout << endl;

    MatrixExponentiation(M, 2, 2);
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            cout << M[i][j] << " ";
        cout << endl;
    } cout << endl;

    int N[DIM][DIM] = {{1, 3, 0}, {1, 2, 1}, {1, 2, 1}};

    MatrixMultiplication(A, N, 3, 3, N, 3, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << A[i][j] << " ";
        cout << endl;
    } cout << endl;

    MatrixExponentiation(N, 3, 2);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << N[i][j] << " ";
        cout << endl;
    } cout << endl;


    return 0;
}