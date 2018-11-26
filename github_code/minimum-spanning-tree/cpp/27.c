#include<bits/stdc++.h>
using namespace std;
int pr[1000];
void reset()
{
    int i;
    for(i=0; i<1000; i++)pr[i]=i;
}
int f(int n)
{
    if(n==pr[n])return n;
    else return f(pr[n]);
}
struct s
{
    int u,v,w;
};
bool com(s lhs,s rhs)
{
    return lhs.w<rhs.w;
}
int main()
{
    //freopen("in.txt","r",stdin);
    reset();
    int n,e,i,sum=0,p,q;
    cin>>n>>e;
    s ar[1000];
    for(i=0; i<e; i++)
        cin>>ar[i].u>>ar[i].v>>ar[i].w;
    sort(ar,ar+e,com);
    //cout<<f(n)<<" "<<f(e)<<endl;
    for(i=0;i<e;i++)
    {
        p=f(ar[i].u); q=f(ar[i].v);
        if(p!=q)
        {
            pr[p]=q;
            sum+=ar[i].w;
            //cout<<sum<<endl;
        }
    }
    cout<<sum<<endl;
}

