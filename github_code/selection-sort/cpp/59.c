#include<iostream>
#include<stdio.h>
using namespace std;

void selection( int a[], int n)
{
     int min,pos;
     for ( int i=0;i<n;i++)
     {
         min=2147483647;
         for ( int j=i;j<n;j++)
         {
             if(min>a[j])
             {
                   min=a[j];
                   pos=j;
             }
         }
         int temp=a[pos];
         a[pos]=a[i];
         a[i]=temp;
     }
}
int main()
{
    int n;
    cin>>n;
    int a[n];
    for ( int i=0;i<n;i++) cin>>a[i];
    selection(a,n);
    cout<<endl;
    for ( int i=0;i<n;i++) cout<<a[i]<<endl;
//    system("pause");
}
