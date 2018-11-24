#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

/**
 * Creates and returns a nxm matrix filled with zeros.
 *
 * @param n  Number of rows in the matrix
 * @param m  Number of columns in the matrix
 *
 * @return  Matrix of size nxm
**/
Matrix createZeroMatrix(int n, int m) {
    return vector<vector<int>>(n, vector<int>(m, 0));
}

/**
 * Read the input and it as a matrix of size nxm.
 *
 * @param n  Number of rows
 * @param m  Number of columns
 *
 * @return  Matrix of size nxm with the input in it
**/
Matrix readData(int n, int m) {
    auto matrix = createZeroMatrix(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}

/**
 * Mutiply two matrices of size nxm and mxp.
 *
 * @param a  Matrix of size nxm
 * @param b  Matrix of size mxp
 *
 * @return  Matrix of size nxp
**/
Matrix multiply(const Matrix &a, const Matrix &b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();

    Matrix matrix = createZeroMatrix(n, p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                matrix[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return matrix;
}

/**
 * Print the matrix.
 *
 * @param m  Matrix of size nxm
**/
void printMatrix(const Matrix &m) {
    for (auto row : m) {
        cout << "|";
        for (int v : row) {
            cout << v << "|";
        }
        cout << endl;
    }
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    auto a = readData(n, m);
    auto b = readData(m, p);
    printMatrix(multiply(a, b));
    return 0;
}
