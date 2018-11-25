#include <cstdio>
using namespace std;


void quickSort(int a[], int left, int right)
{
    if(left >= right) return;
    int l = left;
    int r = right;
    int pivot = a[l];

    while(l < r)
    {
        while(l < r && a[r] >= pivot)
        {
            --r;
        }
        a[l] = a[r];
        while(l < r && a[l] <= pivot)
        {
            ++l;
        }
        a[r] = a[l];
    }

    a[l] = pivot;
    quickSort(a, left, l - 1);
    quickSort(a, l + 1, right);
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i]);
    }
    quickSort(arr, 0, n - 1);

    for(int i = 0; i < n; ++ i)
    {
        printf("%d ", arr[i]);
    }
    puts("");

    return 0;
}


