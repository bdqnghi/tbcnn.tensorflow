#include<iostream>
using namespace std;

int getMax(int *a,int n) {
    int max = a[0];
    for (int i=1;i<n;i++) {
        if (a[i]>max)
            max = a[i];
    }
    return max;
}
void countSort(int *a,int n,int k) {
    int *b = new int[n];
    int c[10] = {0};
    for (int i=0;i<n;i++) {
        ++c[(a[i]/k)%10];
    }
    for (int i=1;i<n;i++) {
        c[i] += c[i-1];
    }
    for (int i=n-1;i>=0;i--) {
        b[--c[(a[i]/k)%10]] = a[i];
    }
    for (int i=0;i<n;i++) {
        a[i] = b[i];
    }
}
void radixSort(int *a,int n) {
    int max = getMax(a,n);
    for (int i=1;(max/i) > 0;i *= 10) {
        countSort(a,n,i);
    }
}
int main() {
    int n;
    cout<<"Enter size of array"<<endl;
    cin>>n;
    int a[n];
    cout<<"Enter elements to be sorted"<<endl;
    for (int i=0;i<n;i++) {
        cin>>a[i];
    }
    cout<<"The sorted array is : "<<endl;
    radixSort(a,n);
    for (int i=0;i<n;i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}