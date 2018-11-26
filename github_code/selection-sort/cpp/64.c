#include<iostream>
using namespace std;

int main()
{
    int A[6];
    int temp,minimum,i,j,k;
    int n=6;
    cout<<"Enter elements to be sorted\n";
    for(i=0; i<6; i++)
    {
        cin>>A[i];
    }
    for(i=0; i<n-1; i++)
    {
        minimum=i;
        for(j=i+1; j<=n; j++)
        {
            if(A[j]<A[minimum])
            {
                minimum=j;
            }
        }
        if(minimum != i)
        {
            temp=A[i];
            A[i]=A[minimum];
            A[minimum]=temp;
        }
           for(k=0; k<6; k++)
            {
            cout<< A[k]<< " ";
            }
            cout<<endl;

    }

     cout<<"\nThe sorted array is \n";
    for(i=0; i<6; i++)
        cout<<A[i]<< " ";
    return 0;
}
