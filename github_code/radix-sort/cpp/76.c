// https://www.hackerearth.com/practice/algorithms/sorting/radix-sort/tutorial/

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
void counting_sort(int a[], int n, int exp) {
    int count[10] = {0};
    int res[n] = {0};

    for(int i=0; i<n; i++) {
        count[int(a[i]/exp)%10]++;
    }

    for(int i=1; i<10; i++)
        count[i] += count[i-1];

    for(int i=n-1; i>=0; i--) {
        res[count[int(a[i]/exp)%10] - 1] = a[i];
        count[int(a[i]/exp)%10]--;
    }

    for(int i=0; i<n; i++) {
        a[i] = res[i];
        cout<<a[i]<<' ';
    }
    cout<<endl;
}

void radix_sort(int arr[], int n, int max) {
    for(int i=1; max/i>0; i*=10)
        counting_sort(arr, n, i);
}

int main() {
    int n, max = -1;
    cin>>n;
    int arr[n];

    for(int i=0; i<n; i++) {
        cin>>arr[i];
        if (arr[i]>max) max=arr[i];
    }
    radix_sort(arr, n, max);
    return 0;
}
