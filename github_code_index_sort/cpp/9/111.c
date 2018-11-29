/*************************************************************************
	> File Name: selection.cpp
	> Author: sunowsir
	> GitHub: github.com/sunowsir/practice: 
	> Created Time: 2017年12月12日 星期二 15时02分38秒
 ************************************************************************/

#include <bits/stdc++.h>
#include "main.h"
using namespace std;

bool selection(int *data, int n) {
    cout << "选择排序方式" << endl;
    cout << "1. 插入排序" << endl;
    cout << "2. 冒泡排序" << endl;
    cout << "3. 归并排序" << endl;
    cout << "4. 选择排序" << endl;
    cout << "5. 快速排序" << endl;
    cout << "6. 堆排序" << endl;
    cout << "7. 希尔排序" << endl;
    int temp;
    cin >> temp;
    switch(temp) {
        case 1 :{
            insert_sort(data, n);
            return true;
        }
        case 2 :{
            bubble_sort(data, n);
            return true;
        }
        case 3 :{
            cout << "本次归并排序用时：" << merge_sort(data, 0, n - 1) << endl;
            return true;
        }
        case 4 :{
            selection_sort(data, n);
            return true;
        }
        case 5 :{
    cout << "本次快速排序用时：" << quick_sort(data, 0, n - 1) << endl;
            return true;
        }
        case 6 :{
            heap_sort(data, n);
            return true;
        }
        case 7 :{
            shell_sort(data, n);
            return true;
        }
        default :{
            cout << "输入不合法，请重新选择" << endl;
            return false;
        }
    }
}
