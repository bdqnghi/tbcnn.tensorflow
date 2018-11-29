//@author:      yaotong
//@fileName:    SelectionSort.cpp
//@createTime:  2017/5/5  12:00
//@editor:      XCode
//@os:          mac os
//@language:    C++
//@description:
//          在所有的数中找到最大的，然后将它放在第一个位置，
//          以此在剩下的数中找到最小的，放在之后的位置上，这就是选择排序
//
//  Copyright © 2017年 yt. All rights reserved.
//


#include <iostream>
#include "Student.h"
#include "SelectionSort.h"
#include "SortTestHelper.h"
using namespace std;


 //SelectionSort test

// int main(){
//     int a[10] = {10,9,8,7,6,5,4,3,2,1};
//     selectionSort(a, 10);
//     for (int i = 0; i < 10; i++)
//         cout << a[i] << " ";
//     cout << endl;
    
//     float b[4] = {4.4,3.3,2.2,1.1};
//     selectionSort(b, 4);
//     for (int i = 0; i < 4; i++)
//         cout << b[i] << " ";
//     cout << endl;
    
//     string c[4] = {"D", "C", "B", "A"};
//     selectionSort(c, 4);
//     for (int i = 0; i < 4; i++)
//         cout << c[i] << " ";
//     cout << endl;
    
//     Student d[4] = {{"D", 90},{"C", 100},{"B", 95},{"A", 95}};
//     selectionSort(d, 4);
//     for (int i = 0; i < 4; i++)
//         cout << d[i] << " ";
//     cout << endl;
    
//     int n = 10000;
//     int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//     selectionSort(arr, n);
//     SortTestHelper::printArry(arr, n);
    
//     int n = 100000;
//     int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//     SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    
//     delete[] arr;
//     return 0;
// }
