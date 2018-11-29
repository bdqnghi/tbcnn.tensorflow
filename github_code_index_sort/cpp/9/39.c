#include <exception>
using namespace std;

#include "SelectionSort.h"


SelectionSort::SelectionSort()
{
}


SelectionSort::~SelectionSort()
{
}

void SelectionSort::SortData(int *data, size_t count)
{
    
    for (int i = 0 ; i<count; i++) {
        int min = i;
        
        
        for (int j=i+1; j< count; j++) {
            if (data[j] < data[min]) {
                min=j;
            }
            
            
        }
        
        if (min != i)
            swap(data[min], data[i]);
    }
}
