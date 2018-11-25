#include<iostream>
#include<vector>
#include <algorithm>    
#include <math.h>       
using namespace std;

int arr[1001];

void bucketsort(int a[],int n)
{
    vector<int > v[n];
    int flag;
    for(int i=0;i<n;i++)
    {
        int countbits=__builtin_popcount (a[i]) ;
        v[countbits].push_back(a[i]);
    }
     for (int i=0; i<n; i++)
       sort(v[i].begin(), v[i].end());
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if(v[i].size()==0)
        {
            continue;
        }
        for (int j = 0; j < v[i].size(); j++)
        {
          cout<<v[i][j]<<" ";
        }
        if(i!=n-1)
            cout<<endl;
    }

}

int main()
{
    int n;

    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    bucketsort(a,n);
    return 0;
}
