#include <iostream>
#include <algorithm>
using namespace std;

// void selectionSort(int a[], int n)
// {
//     for (int i = 0; i < n - 1; i++)
//     {
//         int minIdx = i;
        
//         for (int j = i; j < n; j++)
//         {
//             if (a[j] < a[minIdx])
//                 minIdx = j;
//         }
        
//         swap(a[i], a[minIdx]);
//     }
// }

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = j + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        swap(a[i], a[min]);
    }
}

int main()
{
    int a[] = {10, 6, 7, 12, 2, 45, 8, 90, 55, 120, 32, 1};
    selectionSort(a, 12);
    printArray(a, 12);
    
    return 0;
}