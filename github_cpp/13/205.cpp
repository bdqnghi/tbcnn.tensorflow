//
//  Created by azx on 16/3/5.
//  Copyright © 2016年 azx. All rights reserved.
//
//  输入要排序的数字，终止符结束，用归并排序得出非降序列(与书上实现略有不同)
//  Worst-case: Θ(nlgn)

#include <iostream>
#include <vector>

using namespace std;

int sentinel = INT32_MAX; // 每个数组的最后都插入一个标识，当一组被选完时，保证另一组剩余的全部加上

void mergeSort(vector<int> &T) {
    vector<int> L, R;
    L.assign(T.begin(), T.begin()+T.size()/2); // 数组的左半边赋给L
    R.assign(T.begin()+T.size()/2, T.end()-1);  // 数组的右半边赋给R(将最后的标识去掉)
    
    L.push_back(sentinel);
    R.push_back(sentinel);  // 左右数组最后分别插入标识
    
    if (L.size() != 2) { mergeSort(L); }
    if (R.size() != 2) { mergeSort(R); }  // 当除去sentinel后只剩一个数时，停止递归
    
    int m = 0, n = 0;
    for (int i = 0; i < L.size() + R.size() - 2; i++) {
        if (L[m] < R[n]) {  // 将两数组小的先加入总数组中
            T[i] = L[m];
            m++;
        } else {
            T[i] = R[n];
            n++;
        }
    }
}

int main()
{
    int x;
    vector<int> A;
    while (cin >> x) {
        A.push_back(x);
    }
    A.push_back(sentinel);
    mergeSort(A);
    A.pop_back();  // 将刚刚加入为了mergeSort的sentinel标识除去(作为int_max肯定在最后一个)
    for (vector<int>::iterator it = A.begin(); it != A.end(); ++it) {
        cout << *it << " ";
    }
    
    return 0;
}




