#include <bits/stdc++.h>
using namespace std;


void selection_sort(int arr[], int n)
{
    
    for(int i=n-1; i>=0; i--)
    {   
        int max_ele = arr[i];
        int pos = i;
        for(int j=0; j<i; j++)
        {
            max_ele = max(max_ele, arr[j]);
            if(max_ele == arr[j])
                pos = j;
        }
        swap(arr[i], arr[pos]);
    }
}

int main()
{
    int *arr = new int(5);
    for(int i=0; i<5; i++)
        arr[i] = 5-i;
    selection_sort(arr, 5);
    for(int i=0; i<5; i++)
    {
        cout << arr[i] << " ";
    }
}