#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<vector>
#include<map>

#define INF 1111111111
#define SIZE 100
#define MOD 1000000007
#define llong long long
#define f1(i,n) for(i=1;i<=n;i++)
#define f0(i,n) for(i=0;i< n;i++)
using namespace std;
/*Recursive
int rodCutting(vector<int> V,int rodLen)
{       if(rodLen==1)return V[1];
        int A=V[rodLen];
        for(int i=1;i<=rodLen-i;i++)
               A = max(A,rodCutting(V,i)+rodCutting(V,rodLen -i));
        return A;
}
*/

//Tabulated
int rodCutting(vector<int> V,int rodLen)
{       vector<int> A(V.size());
        for(int i=1;i<V.size();i++)
        {       A[i] = V[i];
                for(int j=1;j<i;j++)
                        A[i] = max(A[i],A[j]+A[i-j]);
        }       
        return A[V.size()-1];
}

int main(int argc, char *argv[])
{
        int A[]={0,1,2,4,1,3,7};
        int n=sizeof(A)/sizeof(A[0]);
        reverse(A,A+n);
        vector<int> V;
        while(n--)V.push_back(A[n]);
        cout<<rodCutting(V,sizeof(A)/sizeof(A[0])-1 )<<endl;
        
        return 0;
}
