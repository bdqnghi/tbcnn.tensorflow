//
//  main.cpp
//  MatrixChainMultiplication
//
//  Created by archit on 6/2/17.
//  Copyright © 2017 archit. All rights reserved.
//

#include <iostream>
#define NIL -1
using namespace std;


int MatrixChainMultiplication(int p[], int i, int j);
int calculate(int p[], int i, int j, int** lookup);


int main(int argc, const char * argv[]) {
    int p[] = {10, 5, 1, 5, 10, 1}   ;
    
    int n = sizeof(p) / sizeof(int);
    int min = MatrixChainMultiplication(p, 1, n-1);
    cout << "Cost: " << min << endl;
    return 0;
}


int MatrixChainMultiplication(int p[], int i, int j) {
    
    int d = j+1;
    int** lookup = new int*[d];
    for(int k = 0; k < j+1; k++) {
        lookup[k] = new int[d];
        for(int f = 0; f <d; f++) {
            lookup[k][f] = NIL;
        }
        
    }
    
    
    return calculate(p, i, j, lookup);
}

int calculate(int p[], int i, int j, int** lookup) {
    
    if (lookup[i][j] == NIL) {
        
        
        if(i == j)
            lookup[i][j] = 0;
        
        else {
            
            int count;
            int min = INT_MAX;
            
            
            for(int k = i; k < j; k++) {
                
                count = calculate(p, i, k, lookup) + calculate(p, k+1, j, lookup) + p[i-1 ] * p[j] * p[k];
                if(count < min) {
                    min = count;
                }
                
            }
            
            lookup[i][j] =  min;
            
        }
        
    }
    
    return lookup[i][j];
}

