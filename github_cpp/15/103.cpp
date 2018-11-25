#include <bits/stdc++.h>
using namespace std;

inline int matrixMultiplication(char dimention[], int i, int j) {

    int k, minimum = INT_MAX, count = 0;
    if (i == j)
        return 0;
    for (k = i; k <= j; k++) {
        count = matrixMultiplication(dimention, i, k) + matrixMultiplication(dimention, k+1, j) +
                dimention[i-1]*dimention[k]*dimention[j];
        if (count < minimum)
            minimum = count;
    }
    return count;
}

int main() {

    char array[1000], n;
    for (int i = 0; i < 5; i++) {
        cin >> array[i];
    }
    cout << matrixMultiplication(array, 5, 10);
}