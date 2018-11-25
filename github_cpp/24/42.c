#include <iostream>
using namespace std;
int g=0;
int binarySearch (int* A, int first, int last, int key) {
if (last < first)
return -1;
else {
int mid = (last + first) / 2;
int x;
if (A[mid] == key)
return mid;
else if (A[mid] > key)
x = binarySearch(A, first, mid - 1, key);
else
x = binarySearch(A, mid + 1, last, key);
return x;
}
}
int main () {
int n,key;
cout<<"\n Enter size of array: ";
cin>>n;
int a[n];
for(int i=0;i<n;i++){
a[i]=i;
cout<<a[i]<<" ";
};
cout<<"\n Enter key: ";
cin>>key;
int index = binarySearch(a, 0, n, key);
cout<<"\n Position :"<<index<<endl;
return 0;
}



