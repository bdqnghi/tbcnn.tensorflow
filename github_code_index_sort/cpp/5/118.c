/*
 * Author: Vic Lin    File Name: bubbleSort.cpp
 * Created Time: 2017年09月07日 星期四 15时28分24秒
 *
 * Cpp source code - replace this with a description
 * of the code and write the code below this text
 *
 */


#include <iostream>
using namespace std;

const int ArSize = 10;
void bubbleSort(int arr[], const int n);

int main(int argc, char * argv[])
{
    int array[ArSize] = {21,2,12,5,4,33,98,42,1,56};
    int i;
    cout << "Array:\n";
    for (i=0; i<10;++i)
        cout << array[i] <<"\t";
    bubbleSort(array, ArSize);
    cout << "\nAfter bubble sort:\n";
    for (i=0; i<10;++i)
        cout << array[i] <<"\t";
    return 0;
}

void bubbleSort(int arr[], const int n)
{
    int i;
    bool flag;
    int temp;
    for (i = n-1, flag = true; i >= 1 && flag; --i){
        flag = false;
        for (int j = 0; j < i; ++j){
            if (arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
        }
    }
}
