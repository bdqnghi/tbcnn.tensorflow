//
//  main.cpp
//  BUCKET-SORT
//
//  Created by 伏开宇 on 2017/3/9.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//桶排序
void InsertSort(int * a, int n){
    for(int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 and a[j] > key){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}


class listTode{
public:
    void insert(int a){
        
    }
};
void BucketSort(int * a, int n){
    listTode *b = new listTode[n];
    for(int i = 0; i < n; i++){
        b[n * a[i]].insert(a[i]);
    }
    for(int i = 0; i < n; i++){
        //InsertSort(b);
    }
    int j = 0;
    for(int i = 0; i < n; i++){
        //学习链表后在完成
    }
}
//桶排序改 8.4-4练习
void BucketSort1(int * a, int n){
    listTode *b = new listTode[n];
    for(int i = 0; i < n; i++){
        b[n * a[i]].insert(a[i]);
    }
    for(int i = 0; i < n; i++){
        //InsertSort(b);
    }
    int j = 0;
    for(int i = 0; i < n; i++){
        //学习链表后在完成
    }
}



int main(int argc, const char * argv[]) {
    
    return 0;
}
