#include<iostream>
using namespace std;
void counting(int a[],int n,int e){
    int count[10]={0};
    for(int i=0;i<n;i++){
        count[(a[i]/e)%10]++;
    }
    for(int i=1;i<10;i++)
        count[i]+=count[i-1];
    int b[n];
    for(int i=n-1;i>=0;i--){
        b[count[(a[i]/e)%10]-1] = a[i];
        count[(a[i]/e)%10]--;
    }
    for(int i=0;i<n;i++)
        a[i]=b[i];
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
void radix(int a[],int n){
    int max=0;
    for(int i=0;i<n;i++){
        if(max<a[i])
            max= a[i];
    }

    for(int i=1;max/i>0;i*=10){
        counting(a,n,i);
    }
}

int main(){
    int a[]={170, 45, 75, 90, 802, 24, 2, 66};
    int n=sizeof(a)/sizeof(a[0]);
    radix(a,n);
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
}
