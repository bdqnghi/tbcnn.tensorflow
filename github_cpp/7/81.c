#include<iostream>
using namespace std;
void merge_sort(int *numbers, int begin, int end);
int main() {
    int n;
    
    cout<<"Enter the no. of numbers you want to sort:";
    cin>>n;
    cout<<"Enter "<<n<<" numbers to be sorted:"<<endl;
    int *numbers = new int[n];
    for(int i = 0; i < n; ++i) {
        cin>>numbers[i];
    }
    
    
    merge_sort(numbers, 0, n - 1);
    
    
    cout<<"The numbers in sorted order are:"<<endl;
    for(int i = 0; i < n; ++i) {
        cout<<numbers[i]<<endl;
    }
    
    system("pause");
    return 0;	
}
void merge_sort(int *numbers, int begin, int end) {
    
    if(begin == end) {
        return;
    }
    int mid = (begin + end)/2;
    merge_sort(numbers, begin, mid);
    merge_sort(numbers, mid + 1, end);
    
    
    int arr1[mid-begin+2], arr2[end-mid+1];
    for(int i = 0; i < mid - begin+1; ++i) {
        arr1[i] = numbers[begin+i];
    }
    arr1[mid-begin+1] = 2147483647;
    for(int i = 0; i < end - mid; ++i) {
        arr2[i] = numbers[mid+1+i];
    }
    arr2[end-mid] = 2147483647;
    
    
    
    
    
    int ptr1 = 0;
    int ptr2 = 0;
    for(int i = 0; i < end - begin + 1; ++i) {
        if(arr1[ptr1] < arr2[ptr2]) {
            numbers[begin+i] = arr1[ptr1];
            ++ptr1;
        } else {
            numbers[begin+i] = arr2[ptr2];
            ++ptr2;
        }
    }
}
