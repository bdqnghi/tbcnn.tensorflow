//
//  RodCutting.cpp
//  TestApps
//
//  Created by Praveen S on 8/8/14.
//  Copyright (c) 2014 Praveen S. All rights reserved.
//

#include "RodCutting.h"
using namespace std;
int solution[100];

//int max(int a, int b) { return (a > b)? a : b;}

int rodCuttingRecursive(vector <int> & price, int n) {
    if (n<=0) {
        return 0.0;
    }
    int max_val = -1;
    for (int i = 0; i < n; i++ ) {
        int tmp = price[i] + rodCuttingRecursive(price, n-i-1);
        if (tmp > max_val) {
            max_val = tmp;
        }
    }
    return max_val;
}


int rodCuttingDynamicProg(vector<int> & price , int n) {
    int dp[n+1];
    dp[0] = 0;
    int max_val ;
    solution[0] = 0;
    cout << endl;

    for (int i = 1; i <= n; i++) {
        max_val = -1;
        for (int j = 0; j < i ; j++) {
            //max_val = max(max_val, price[j] + dp[i-j-1]);
            if (max_val < price[j] + dp[i-j-1]) {
                max_val = price[j] + dp[i-j-1];
                solution[i] = j;
            }
            cout<< " i = " << i << "  j = "<< j <<  " price[" << j << "] = "  << price[j] << " dp[i-j-1] = " << dp[i-j-1] << " max_val = " << max_val << " solution " << solution[i] << endl;


            // If we store the value of j when the  max changes then we can get the solution
            
        }

        dp[i] = max_val;
        cout<< "dp[" << i << "] = " << dp[i] << endl;

    }
    
    return dp[n];
}

void printSolution(int n) {
    int i=0;
    do {
        cout<< solution[n] << " "  << n << endl;
        int a = solution[n];
        n = n-a;
        n =
        i++;
    } while( i <= n);
}


int mainq1() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    cout<<"The Recursive solution is " << rodCuttingRecursive(price, 8)<< endl;
    cout<<"The Dynamic Programming solution is " << rodCuttingDynamicProg(price, 8)<< endl;
    cout<<"The Dynamic Programming solution set is :" << endl;
    printSolution(8);
    return 0;
}
