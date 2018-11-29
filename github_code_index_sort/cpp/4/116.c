//
//  main.cpp
//  HEAP-SORT
//
//  Created by GangGongUi on 2016. 7. 30..
//  Copyright © 2016년 GangGongUi. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;
void heapSort(vector<int>& A);
void buildMaxHeap(vector<int>& A);
void maxHeapify(vector<int>& A, int i, int& heapSize);

void heapSort(vector<int>& A)
{
    buildMaxHeap(A);
    
    int heapSize = (int) A.size() - 1;
    
    for(int i = (int) A.size() -1 ; i > 0; i--)
    {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapSize--;
        maxHeapify(A, 0, heapSize);
    }
}

void buildMaxHeap(vector<int>& A)
{
    int heapSize = (int) A.size() - 1;
    for(int i = (int) (A.size() / 2 - 1); i >= 0; i--)
        maxHeapify(A, i, heapSize);
}

void maxHeapify(vector<int>& A, int i, int& heapSize)
{
    int greater = i;
    
    while(i <= heapSize)
    {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        
        if(l <= heapSize && A[i] < A[l]) greater = l;
        else greater = i;
        
        if(r <= heapSize && A[greater] < A[r])
            greater = r;
        
        if(greater != i)
        {
            int temp = A[i];
            A[i] = A[greater];
            A[greater] = temp;
            i = greater;
        }
        else break;
    }
}


int main()
{
    // insert code here...
    int arr[] = { 5, 13, 2, 25, 7, 17, 20, 8, 4 };
    
    vector<int> A;
    
    for(auto v : arr)
        A.push_back(v);
    
    heapSort(A);
    
    for(auto v : A)
        cout << v << " ";
    
    return 0;
}
