/*This is a very simple Selection-Sort algorithm for an array to sort it in ascending order*/

#include <iostream>
#include <algorithm>
 
using namespace std;
 
void selectSort(int arr[], int size)
{
    for(int i = 0; i < size; ++i){
        int min = arr[i];
        int minindex = -1;
        for(int y = i; y < size; ++y){
            if(min > arr[y]){
                min = arr[y];
                minindex = y;
            }
        }
        if(minindex != -1){
        swap(arr[i], arr[minindex]);
        }
    }
}
 
int main()
{
    cout << "Size of array " << endl;
    int s;cin >> s;
    int arraya[s];
    for(int i = 0; i < s; ++i){
        int x;
        cin >> x;
        arraya[i] = x;
    }
    selectSort(arraya, s);
    cout << endl;
    for(int i = 0; i < s; ++i){
        cout << arraya[i] << endl;
    }
}
