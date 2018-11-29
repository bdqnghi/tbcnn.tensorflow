#include<bits/stdc++.h>

using namespace std;

int main()
{
    int A[100];
    int n;
    cout<<"how many numbers?:";
    cin>>n;
    int i;
    srand(time(NULL));
    for(i=1; i<=n; i++)
    {
        A[i]=rand()%100;
    }
    cout<<"Before sort:";
    for(i=1; i<=n; i++)
    {
        cout<<A[i]<<" ";
    }
    int j,key;
    for(j=2;j<=n;j++)
    {
        key=A[j];
        i=j-1;
        while(i>0 && A[i]>key)
        {
            A[i+1]=A[i];
            i=i-1;
        }
        A[i+1]=key;
            }

    cout<<"\nAfter sort:";
    for(i=1; i<=n; i++)
    {
        cout<<A[i]<<" ";
    }
    return 0;
}
