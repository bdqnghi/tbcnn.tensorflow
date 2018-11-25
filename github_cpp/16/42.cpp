

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;



void shellSort(int* unsorted_array, int array_size){
    int temp = 0;
    int columns = array_size / 2;
    int i = 0;
    int j = 0;
    while(columns > 0){
        for(i = columns; i < array_size; i++){
            temp = unsorted_array[i];
            for(j = i; j >= columns ;j -= columns){
                if(temp < unsorted_array[j - columns]){
                    unsorted_array[j] = unsorted_array[j - columns];
                }
                else{
                    break;
                }
            }
            unsorted_array[j] = temp;
        }
        columns /= 2;
    }
}


int main(){
    
    int* array1;
    int* array2;
    array1 = new int[20];
    array2 = new int[50];
    
    for(int i = 0; i < 20; i++){
        array1[i] = rand() % 50;
    }
    
    for(int i = 0; i < 50; i++){
        array2[i]  = rand() % 50;
    }
    
    cout << "Array before Shellsort: " << endl;
    for(int i = 0; i < 20; i++){
        cout << array1[i] << endl;
    }
    
    cout << "Array after Shellsort: " << endl;
    shellSort(array1, 20);
    for(int i = 0; i < 20; i++){
        cout << array1[i] << endl;
    }
    
    cout << "Array before Shellsort: " << endl;
    for(int i = 0; i < 50; i++){
        cout << array2[i] << endl;
    }
    
    shellSort(array2, 50);
    cout << "Array after Shellsort: " << endl;
    for(int i = 0; i < 50; i++){
        cout << array2[i] << endl;
    }
    
    delete[] array1;
    delete[] array2;
    return 0;
}