#include "stdafx.h" 
#include <iostream> 
using namespace std; 
 
int main(int argc, char* argv[]) 
{
    const int size_array = 10; 
    int array_[size_array] = {-8, -7, -6, -6, -4, 2, 6, 7, 8, 15 }; 
    cout << "array[" << size_array << "] = { ";
    for (int counter = 0; counter < size_array; counter++) 
    {
     cout << array_[counter] << " "; 
    }
    cout << " }"; 
    int average_index = 0, 
        first_index   = 0, 
        last_index    = size_array -1, 
        search_value  = 15; 
    if (last_index == -1) cout << "\narray is empty" << endl; 
 
    while (first_index < last_index)
    {
        average_index = first_index + (last_index - first_index) / 2; 
        search_value <= array_[average_index] ? last_index = average_index : first_index = average_index + 1;    
    }
    if ( array_[last_index] == search_value) 
        cout << "\nvalue is found" << "\nindex = " << last_index << endl;
    else
        cout << "\nvalue is not found" << endl;
    return 0; 
}