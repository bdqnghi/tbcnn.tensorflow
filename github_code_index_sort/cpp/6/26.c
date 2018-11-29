//
//  main.cpp
//  Sort_and_BS
//
//  Created by Дарья Яковлева on 23.05.14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

const int N = 1010, M = 300;
int n, m, k;
vector<string> arr;
int pos[N], newpos[N];
int radix[M];

void radixsort() {
    for (int i = 0; i < k; i++) {
        
        for (int j = 0; j < M; j++) 
            radix[j] = 0;
        
        for (int j = 0; j < n; j++)
            radix[arr[j][arr[j].size() - 1 - i]]++;
        int count = 0;
        for (int j = 0; j < M; j++) {
            int tmp = radix[j];
            radix[j] = count;
            count += tmp;
        }
        for (int j = 0; j < n; j++) {
            int sym = arr[pos[j]][arr[pos[j]].size() - 1 - i];
            newpos[radix[sym]] = pos[j];
            radix[sym]++;
        }
        for (int j = 0; j < n; j++) {
            pos[j] = newpos[j];
        }
    }
    
}

int main() {
      freopen("radixsort.in", "r", stdin);
      freopen("radixsort.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        arr.push_back(s);
        pos[i] = i;
    }
    radixsort();
    for (int i = 0; i < n; i++)
        cout << arr[pos[i]] << endl;
    
}

