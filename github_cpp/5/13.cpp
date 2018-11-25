







#include "insertion.hpp"
#include <iostream>
#include <climits>
using namespace std;

InsertionSort::InsertionSort(int array_size)
{
    size = array_size;
    array = new int[size];
    setElements();
}

InsertionSort::~InsertionSort()
{
    delete[] array;
    
}

int InsertionSort::getSize()
{
    return size;
}

void InsertionSort::printElements()
{
    for (int i = 0; i < size; i++) {
        std::cout << "Element " << i + 1 << ": " << array[i] << '\n';
    }
}

void InsertionSort::setElements()
{
    for (int i = 0; i < size; i++) {
        std::cout << "Enter element[" << i + 1 << "]: ";
        std::cin >> array[i];
    }
}

void InsertionSort::InsertSort(unsigned int n)
{
    int key, i;
    for(int j=1; j<n; j++){
        key = array[j];
        i = j-1;
        while(i >= 0 && array[i] > key){
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
