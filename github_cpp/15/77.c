#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;


Matrix createZeroMatrix(int n, int m) {
    return vector<vector<int>>(n, vector<int>(m, 0));
}


Matrix readData(int n, int m) {
    auto matrix = createZeroMatrix(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    return matrix;
}


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
