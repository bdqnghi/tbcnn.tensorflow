#include<iostream>
using namespace std;
int searchindex(int a[],int n,int key)
{
    int s=0,e=n-1;/// s for first index and e for last index of array
    int mid;
    while(s<=e)
    {
        mid=(s+e)/2;
        if(a[mid]==key)
    {
        return mid;
    }
     else if (a[mid]>key)
     {
        e=mid-1;
     }
     else
     {
         s=mid+1;
     }
    }

    return 1;
}
int main()
{
    int a[]={1,3,5,6,9,10};
    int n = sizeof(a)/sizeof(int); ///no of elements in the array
    int key;
    cin>>key;
    int index= searchindex(a,n,key);
    if(index==1)
    {
        cout<<key<<"is not present"<<endl;
    }
    else
    {
        cout<<key<<"is present at index"<<index<<endl;
    }

 return 0;
}
