//
//  merge-sort.cpp
//  merge
//
//  Created by Rumeysa Bulut on 22.09.2017.
//  Copyright © 2017 Rumeysa Bulut. All rights reserved.
//

#include "merge-sort.hpp"
#include <iostream>
#include <climits>
using namespace std;

MergeSort::MergeSort(int array_size)
{
    size = array_size;
    array = new int[size];
    setElements();
}

MergeSort::~MergeSort()
{
    delete[] array;
    //std::cout << "Object is destroyed." << '\n';
}

int MergeSort::getSize()
{
    return size;
}

void MergeSort::printElements()
{
    for (int i = 0; i < size; i++) {
        std::cout << "Element " << i + 1 << ": " << array[i] << '\n';
    }
}

void MergeSort::setElements()
{
    for (int i = 0; i < size; i++) {
        std::cout << "Enter element[" << i + 1 << "]: ";
        std::cin >> array[i];
    }
}

void MergeSort::mergeSort(unsigned int p, unsigned int r)
{
    if (p < r) {
        int q = ( p + r ) / 2;
        //std::cout << "mergesortta: " << '\n';
        //std::cout << "p:" << p << " q:" << q << " r:" << r << '\n';
        mergeSort(p , q);
        mergeSort(q + 1, r);
        merge(p, q, r);
    }
}

void MergeSort::merge(unsigned int p, unsigned int q, unsigned int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    int L[n1+1];
    int R[n2+1];
    int i, j;
    for( i=0; i<n1;i++)
        L[i]=array[p+i];
    
    for( j=0; j<n2; j++)
        R[j]= array[q+j+1];
    
    L[n1]=INT_MAX;
    
    R[n2]=INT_MAX;
    
    i=j=0;
    for(int k=p; k<=r; k++){

        if(L[i] <= R[j]){
            array[k] = L[i];
            i++;
        }
        else{
            array[k] = R[j];
            j++;
        }
        
    }
    cout<<"Sorted array is:";
    for(int k=p; k<=r; k++){
        cout << array[k]<<"\t";
    }
    cout<<endl;
}
