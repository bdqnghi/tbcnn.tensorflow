#include <iostream>
using namespace std;

int getMax(int arr[], int n)
{
    int mx = arr[0];

    for(int i = 1; i < n; i++) {
        if(mx < arr[i]) {
            mx = arr[i];
        }
    }

    return mx;
}

void countsort(int arr[], int n, int exp)
{
    int i, sorted[n], cnt[10] = {0};

    for(i = 0; i < n; i++) {
        cnt[ (arr[i]/exp)%10 ]++;
    }

    for(i = 1; i < 10; i++) {
        cnt[i] += cnt[i-1];
    }

    for(i = n-1; i >= 0; i--) {
        sorted[ cnt[(arr[i]/exp)%10]-1 ] = arr[i];
        cnt[(arr[i]/exp)%10]--;
    }

    for(i = 0; i < n; i++) {
        arr[i] = sorted[i];
    }
}

void radix(int arr[], int n)
{
    int mx = getMax(arr, n);

    for(int exp = 1; mx/exp > 0; exp *= 10) {
        countsort(arr, n, exp);
    }
}

void print(int arr[], int n)
{
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}

int main()
{
    int arr[] = {7, 2, 5, 4, 6, 12, 4, 5, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    radix(arr, n);
    print(arr, n);

    return 0;
}
