#include<iostream>
#include<vector>
#include<stdio.h>
#include<queue>
#include<deque>
#include<map>
#include<utility>
#include<algorithm>
#include<stack>
#include<stdio.h>
#include<bits/stdc++.h>
#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define tr(c,it) for(typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define pb push_back
#define inf 1000000000
using namespace std;
typedef vector< pair<int,int> > vpii;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef unsigned long long int ll;
int cut_rodrec(int p[],int n)
{
    if(n<=0)
    {
        return 0;
    }
    int q=INT_MIN;
    for(int i=0;i<n;i++)
    {
        q=max(q,p[i]+cut_rodrec(p,n-i-1));
       // cout<<q;
    }
     return q;
}
int rod_cutdp(int p[],int n)
{
    int val[n+1];
    val[0]=0;
    int s[n+1];
    s[0]=0;
    for(int i=1;i<=n;i++)
    {
        int q=INT_MIN;
        for(int j=0;j<i;j++)
        {
            if(q < p[j]+val[i-j-1]){
                q=p[j]+val[i-j-1];
                s[i]=j+1;
            }
        }
        val[i]=q;
    }
    int tmp=n;
    while(tmp>0)// to show how the rod is cut
    {
        cout<<s[tmp]<<" ";
        tmp=tmp-s[tmp];
    }
    cout<<endl;
    return val[n];
}
int main()
{
    int p[10]={1,5,8,9,10,17,17,20,24,30};
    cout<<cut_rodrec(p,9)<<endl;
    cout<<rod_cutdp(p,9);
    return 0;
}
