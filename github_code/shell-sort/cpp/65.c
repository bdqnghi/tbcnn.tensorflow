//
//  shellSort.cpp
//  stl
//
//  Created by 鲁飞 on 16/5/6.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "sort.h"

// 在插入排序之上进行缩小增量排序
void shellSort(int a[], int n){
    //每次插入的待排元素
    int sortItem;
    
    //increasement每次插入排序的增量，增量最后变为1，称为一个插入排序，但是元素已基本有序了
    for (int increasement = n / 2; increasement >=1; increasement /= 2) {
        //下面跟插入排序一样
        //每次插入排序进行n - increasement趟排序
        for (int i = increasement; i < n; i++) {
            sortItem = a[i];
            
            int j;
            for (j = i - increasement; j >= 0 && a[j] > sortItem; j -= increasement) {
                a[j + increasement] = a[j];
            }
            
            a[j + increasement] = sortItem;
        }
    }
}
