//
//  main.cpp
//  RADIX-SORT
//
//  Created by 伏开宇 on 2017/3/9.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include <string.h>
using namespace std;

void CountingSort(string * a, string * b, int k, int n, int dig){
    int * c = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    for(int i = 0; i < n; i++){
        c[a[i][dig] - 97] ++;
    }
    for(int i = 1; i <= k; i++){
        c[i] = c[i] + c[i-1];
    }
    
    for(int i = n - 1; i >= 0; i--){
        b[c[a[i][dig] - 97]--].assign(a[i]);
    }
    for(int i = 0; i < n; i++){
        a[i].assign(b[i]);
    }
}

//基数排序
void RadixSort(string *a, string *b, int d, int k,int n){
    for(int i = d - 1; i >= 0; i--){
        CountingSort(a, b, k, n, i);
        
    }
}
int main(int argc, const char * argv[]) {
    string a[16] = {"cow", "dog", "sea", "rug", "row", "mob", "box", "tab", "bar", "ear", "tar", "dig",
        "big", "tea", "now", "fox"};
    string b[16];
    RadixSort(a, b, 3, 26, 16);
    
    for(int i = 0; i < 16; i++){
        cout<<b[i]<<" ";
    }
    cout<<endl;
    return 0;
}
