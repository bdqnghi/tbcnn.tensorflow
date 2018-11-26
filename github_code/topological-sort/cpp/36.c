#include<bits/stdc++.h>
using namespace std;

typedef long long  ll;
typedef unsigned long long  ull;

ll mod= 1000000007;

//cout<<fixed<<setprecision(6)<<ans<<"\n";

#define frmlty     int test_case;cin>>test_case;while(test_case--)

#define vi        vector<int>
#define vs        vector<string>
#define vll       vector<ll>
#define pii       pair<int,int>

#define msi       map<string,int>
#define msit      map<string,int>::iterator
#define pb        push_back
#define mp        make_pair

#define loop(i,a,b)      for(int i=a;i<b;i++)
#define rloop(i,a,b)     for(int i=b-1;i>=a;i--)

#define gcd(a,b)  __gcd(a,b)
#define maX(a,b)                     ( (a) > (b) ? (a) : (b))
#define miN(a,b)                     ( (a) < (b) ? (a) : (b))

#define le(x) scanf("%d",&x);
#define le2(x,y) scanf("%d%d",&x,&y);
#define lell(x) scanf("%lld",&x);
#define le2ll(x,y) scanf("%lld%lld",&x,&y);

#define F first
#define S second

vi g[100];
int vis[100]= {};
int ht[100]={};

vi ts;

int dfsts(int sv)
{
    vis[sv]=1;
    ht[sv]=1;
    loop(i,0,g[sv].size())
    {
        if(vis[g[sv][i]]==0)
        {

            if(dfsts(g[sv][i]))
            {
                return 1;
            }
        }
        else if(ht[g[sv][i]])//you are making mistake here,you are at a vertex(sv) and you are going to visit its child and it is not its parent
        {
            return 1;//1 means ts not possible
        }
    }
    ts.pb(sv);
    ht[sv]=0;
    return 0;
}


int main()
{
    int n,m;
    int v1,v2;
    le2(n,m);
    loop(i,0,m)
    {
        le2(v1,v2);
        g[v1].pb(v2);
    }
    int flag=0;
    loop(i,0,n)
    {
        if(vis[i]==0&&dfsts(i)==1)
        {   flag=1;
            cout<<"ts not possible\n";
            return 0;
        }

    }
    if(flag==0)
    {   cout<<"ts possible\n";
        loop(i,0,ts.size())
        cout<<ts[ts.size()-1-i]<<" ";
        cout<<"\n";
    }

    return 0;
}

