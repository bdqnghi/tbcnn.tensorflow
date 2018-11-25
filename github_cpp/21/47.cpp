#include<iostream>
using namespace std;
void insertion(int[],int);
int main()
{
    int n;
    cout<<"Enter length : ";
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    insertion(a,n);
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
}
void insertion(int a[],int n)
{   int min,temp,k=0;
    for(int i=0;i<n;i++)
    {   min=a[i];
        k=i;
        for(int j=i;j<n;j++)
        {
            if(a[j]<min)
            {
                min=a[j];
                k=j;
            }
        }
        temp=a[i];
        a[i]=a[k];
        a[k]=temp;
    }
}
