#include <iostream>  
#include "string.h"
#include <vector>
using namespace std; 


























































int main() {  
    int array[] = {3, 2, 5, 4, 7, 6}, k;  
    int len = sizeof(array)/sizeof(int);  

    cout << "The orginal arrayare:" << endl;  
    for(k = 0;k < len;k++)  
        cout << array[k] << ",";  
    cout << endl;  

    quickSort(array, 0, len - 1);  

    cout << "The sorted arrayare:" << endl;  
    for(k = 0; k < len; k++)  
        cout << array[k] << ",";  
    cout << endl;  
    

    cout << sizeof(array) << endl;

    char a[] = "abc";
    cout << sizeof(a) << " " << strlen(a)<< endl;
    return 0;  
}
