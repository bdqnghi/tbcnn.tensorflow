#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <list>
#include <stack>
#include <map>
#include <set>
using namespace std;

#define DEBUG
#define REP(i,a) for(i=0;i<a;i++)
#define FOR(i,a,b) for(i=a;i<b;i++)
#define VE vector<int>
#define SZ size()
#define PB push_back
#define max_ 9000000
void MERGE(int A[],int p,int q,int r)
{
    int n1,n2,i,k,j;
    n1=q-p+1;
    n2=r-q;
    int L[n1+1],R[n2+1];
    for(i=0; i<n1; i++)
        L[i]=A[p+i];
    for(i=0; i<n2; i++)
        R[i]=A[q+i+1];
    L[n1]=max_;
    R[n2]=max_;
    i=0,j=0;
    for(k=p; k<=r; k++)
    {
        if(L[i]<=R[j])
            A[k]=L[i],i++;
        else
            A[k]=R[j],j++;
    }
}
void MERGE_SORT(int A[],int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        MERGE_SORT(A,p,q);
        MERGE_SORT(A,q+1,r);
        MERGE(A,p,q,r);
    }
}
int main()
{
    int i,j,n,key;
    int A[500];
    n=5;
    for(j=0; j<n; j++)
        scanf("%d",&A[j]);
    MERGE_SORT(A,0,n-1);
    for(j=0; j<n; j++)
        printf("%d ",A[j]);
    return 0;
}
