#include<iostream>
using namespace std;
int main()
{
    int a[20];
    int mid;
    int beg;
    int last;
    int n;
    int item;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
        cout<<"enter the number you want to search"<<endl;
        cin>>item;
    beg=0;
    last=n-1;
    mid=(beg+last)/2;
    while(a[mid]!=item)
    {
        if(item>a[mid])
        {

            beg=mid+1;
        }
        else if(item<a[mid])
        {

            last=mid-1;
        }
        mid=(beg+last)/2;
    }
    if(a[mid]==item)
    {

        cout<<"element is found at"<<mid;
    }
    else
        cout<<"element is not found";
}
