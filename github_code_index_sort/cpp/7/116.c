//
//  ShellSort.cpp
//  Sort
//
//  Created by yxwang on 2017/9/8.
//  Copyright © 2017年 yxwang. All rights reserved.
//

#include "ShellSort.hpp"
using namespace std;

void shellInsertSort(int *p ,size_t length, int dk){
    for(auto i = dk;i < length;i++){
        if(p[i] < p[i-dk]){
            int x = p[i];
            p[i] = p[i-dk];
            
            int j = i-dk;
            while( j-dk >= 0){
                if(x<p[j-dk]){
                    p[j] = p[j-dk];
                    j = j-dk;
                }else{
                    break;
                }
            }
            p[j] = x;
        }
    }
}




void shellSort(int *p , size_t length){
    int dk = (int)length/2;
    while( dk >= 1  ){
        shellInsertSort(p, length, dk);
        dk = dk/2;
    }
}



void shellSortDes(int *p , size_t length){
    
    
}
