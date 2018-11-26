#include<stdio.h>
#include<iostream>
using namespace std;


int main(){
int size_of_array,a[100],b[100];
cout<<"enter the size of array: ";
cin>>size_of_array;
for(int i=0;i<size_of_array;i++){
    cin>>a[i];
}
b[0]  =a[0];
for(int i=1;i<size_of_array;i++){
        int pos=0;
    for(int j=0;j<i;j++){
        if(a[j] > a[i])
        {pos = j;
            break;}
    }
    int val = a[i];
    for(int j = i-1;j>pos;j--){
        a[i+1]  = a[i];
    }
    a[pos]  = val;
}
for(int i =0;i<size_of_array;i++){
    cout<<a[i]<<" ";
}
return 0;
}
