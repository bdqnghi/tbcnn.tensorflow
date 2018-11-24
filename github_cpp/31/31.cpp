#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define n 3
#define INFINITY 500000

using namespace std;

pair<int, int> matrices[n];

int MATRIX_CHAIN_ORDER(){
     int j;
     int m[n][n]; // Minimum scalar multiplications in a chain
     for(int i = 1; i < n; i++){
          m[i][i] = 0;
     }
     for(int l = 2; l < n; l++){ // length of chain

          for(int i = 1; i < n - l + 1; i++){
               j = i + l - 1;
               m[i][j] = INFINITY;
               for(int k = i; k <= j - 1; k++){

                    pair<int, int> matrix;
                    matrix.first = matrices[i].first;
                    matrix.second = matrices[k].second;
                    int scalarMultiplications =  matrices[i].first * matrices[i].second * matrices[k].second +
                              matrix.first * matrix.second * matrices[j].second;
                    int q = m[i][k] + m[k + 1][j] + scalarMultiplications;
                    if(q < m[i][j]){
                         m[i][j] = q;
                    }
               }
          }
     }
     printf("\n%d", m[1][n - 1]);
}

int main(){
     for(int i = 0; i < n; i++){
          matrices[i].first = 1 + rand() % 20;
          matrices[i].second = 1 + rand() % 20;
          printf("%dx%d, ", matrices[i].first, matrices[i].second);
     }
     MATRIX_CHAIN_ORDER();
}
