/*Code for insertion sort*/
// Use <utility> for swap function

#include <iostream>
using namespace std;

void swap (int &a, int  &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void insert_sort(int arr1[ ])
{
    int i,j;
    for (i = 1; i < 10; ++i)
    {
        j = i;
        while(j>0 && arr1[j] < arr1[j-1])
        {
            swap(arr1[j], arr1[j-1]);
            j = j-1;
        }
    }
}

int main() 
{
    int arr[10] = { 4, 2, 7, 1, 9, 3, 8, 6, 5, 0};
    for (int i = 0 ;i < 10 ; ++i)
        cout << arr[i] << " ";
    cout << endl;
    insert_sort(arr);
    for (int i = 0 ;i < 10 ; ++i)
        cout << arr[i] << " ";
}