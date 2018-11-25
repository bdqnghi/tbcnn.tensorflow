#include<iostream>
using namespace std;

int main(){

    int n;
    cout<<"Enter N";
    cin>>n;

    int a[100];
    
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    
    for(int i=0;i<n-1;i++){

        int min_i = i;
        
        for(int j=i+1;j<=n-1;j++){
            if(a[j]<a[min_i]){
                min_i = j;
            }
        }
        
        int temp = a[min_i];
        a[min_i] = a[i];
        a[i] = temp;
    }
    
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }





}
