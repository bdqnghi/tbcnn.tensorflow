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

int main()
{
    int i,j,n,key;
    int A[500];
    n=5;
    for(j=0;j<n;j++)
    scanf("%d",&A[j]);
    for(j=1;j<n;j++)
    {
        key=A[j];
        i=j-1;
        while(i>=0&&A[i]>key)
        {
            A[i+1]=A[i];
            i=i-1;
        }
        A[i+1]=key;
    }
    for(j=0;j<n;j++)
    printf("%d ",A[j]);

    return 0;
}
