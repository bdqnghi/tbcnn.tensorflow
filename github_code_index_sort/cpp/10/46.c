//  
//  main.cpp  
//  BucketSort  
//  
//  Created by Alps on 14-7-25.  
//  Copyright (c) 2014年 chen. All rights reserved.  
//  
  
#include <iostream>  
  
using namespace std;  
  
void BucketSort(int *A, int Max, int Size){  
    int B[Max+1];  
    int i,j,count = 0;  
    memset(B, 0, (Max+1)*sizeof(int));  
    for (i = 0; i < Size; i++) {  
        j = A[i];  
        B[j] += 1;  
    }  
    for (i = 0; i <= Max; i++) {  
        if (B[i] > 0) {  
            for (j = 0; j < B[i]; j++) {  
                A[count] = i;  
                count++;  
            }  
        }  
    }  
}  
  
int main(int argc, const char * argv[])  
{  
    int A[]={1, 2, 2, 7, 4, 9, 3, 5};  
    int Max = 9; //这里可以用一个O(n)的函数来实现，假如数组的手动输入的，则在输入的时候就可以获取到。这里直接赋值是为了排出别的因素，看着简单。  
    int Size = sizeof(A)/sizeof(int);  
    BucketSort(A, Max, Size);  
    for (int i = 0; i < Size; i++) {  
        printf("%d ",A[i]);  
    }  
    printf("\n");  
    return 0;  
}  
