//
//  BucketSort.cpp
//
//  Created by 罗铮 on 9/26/12.
//  Copyright (c) 2012 罗铮. All rights reserved.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 10;

void bucket_sort(double A[], int n)
{
    vector< vector<double> > B;
    // make B[i] an empty list
    for (int i = 0; i < n; i++)
    {
        vector<double> v;
        B.push_back(v);
    }
    // insert A[i] into list B[n*A[i]]
    for (int i = 0; i < n; i++)
        B[n*A[i]].push_back(A[i]);

    // sorted list B[i] with insertion sort
    for (int i = 0; i < n; i++)
        sort(B[i].begin(), B[i].end());

    // concatenate the list B[0], B[1] ... B[n-1] together in order
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (!B[i].empty())
        {
            for (vector<double> :: iterator it = B[i].begin(); 
                 it < B[i].end(); it++)
            {
                A[k++] = *it;
            }
        }
    }
}


int main(int argc, const char * argv[])
{
    double a[SIZE] = {0.78,0.17,0.39,0.26,0.72,
                      0.94,0.21,0.12,0.23,0.68};
    // sort the array
    bucket_sort(a, SIZE);
    
    // print the result after sort
    for (int i =0; i < SIZE; i++)
        cout << a[i] << " ";

    return 0;
}

