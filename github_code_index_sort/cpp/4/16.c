//
//  heap.cpp
//  code_exercise
//
//  Created by Hei Yanbin on 14-5-11.
//  Copyright (c) 2014年 Hei Yanbin. All rights reserved.
//
#include <iostream>
#include "lib.h"
using namespace std;
void minHeapFixup(int a[], int i)
{
    if(!a||i<1) return;
    while((i-1)/2>=0 && a[i]<a[(i-1)/2])
    {
        swap(a[i],a[(i-1)/2]);
        i=(i-1)/2;
    }
}

void insert(int a[], int n, int value)
{
    if(!a||n<0) return;
    if(n<1)
        a[0] = value;
    a[n] = value;
    while((n-1)/2>=0 && a[n]<a[(n-1)/2])
    {
        swap(a[n],a[(n-1)/2]);
        n=(n-1)/2;
    }
}

void minHeapFixDown(int a[], int i, int n)
{
    while(2*i+1<n)
    {
        int j= 2*i+1;
        if(j+1< n && a[j+1]<a[j])
            j=j+1;
        if(a[i]<=a[j]) break;
         swap(a[i],a[j]);
        i=j;
    }
}
void remove(int a[], int n)
{
    if(!a||n<2) return;
    a[0]=a[n-1];
   minHeapFixDown(a, 0, n-1);
}

void heapfy(int a[], int n)
{
    if(!a||n<2) return;
    for(int i= n/2-1;i>=0;i--)
        minHeapFixDown(a, i, n);
}
void heapfy2(int a[], int n)
{
    if(!a||n<2) return;
    for(int i=1;i<n;i++)
    {
        minHeapFixup(a, i);
    }
}

void heapSort(int a[], int n)
{
    if(!a||n<2) return;
    heapfy(a, n);
    for(int i=n-1;i>0;i--)
    {
        swap(a[i],a[0]);
        minHeapFixDown(a, 0, i);
    }
}

void testHeapSort()
{
    int a[] ={6,1,3,4,2,5};
    heapSort(a,6);
    printArray(a,6);
}