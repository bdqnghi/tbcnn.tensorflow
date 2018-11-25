#include <iostream>

void quicksort(int arr[], int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left+right) / 2];
    
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    
    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
}

int main()
{
    int arr[] = {1,3,5,6,2,4};
    quicksort(arr, 0, sizeof(arr)/sizeof(*arr));
    for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++) {
        std::cout << arr[i];
    }
    
    return 0;
}
