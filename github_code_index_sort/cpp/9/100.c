#include<iostream>
using namespace std;

int main(){

    int n;
    cout<<"Enter N";
    cin>>n;

    int a[100];
    ///Input
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    ///Selection Sort
    for(int i=0;i<n-1;i++){

        int min_i = i;
        ///Rem Part
        for(int j=i+1;j<=n-1;j++){
            if(a[j]<a[min_i]){
                min_i = j;
            }
        }
        ///Swap min_i && i th bucket
        int temp = a[min_i];
        a[min_i] = a[i];
        a[i] = temp;
    }
    ///Print the elements
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }





}
