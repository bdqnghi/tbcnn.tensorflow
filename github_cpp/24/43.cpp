//https://uva.onlinejudge.org/external/117/11733.pdf
#include <list>

#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <queue>
#include <cmath>
#include <deque>
#include <limits>
#include <string>
#include <cctype>
#include <cstdio>
#include <vector>
#include <bitset>
#include <numeric>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

#define sf scanf
#define pf printf
#define pi 2*acos(0.0)
#define ull unsigned long long
#define all(v) v.begin(),v.end()

#define sii(t) scanf("%d",&t)
#define sll(t) scanf("%lld",&t)
#define sll(t) scanf("%lld",&t)
#define ssll(a,b) scanf("%lld%lld",&a,&b)
#define ssd(a,b) scanf("%lf%lf",&a,&b)
#define sssll(a,b,c) scanf("%lld%lld%lld",&a,&b,&c)
#define ssslf(a,b,c) scanf("%lf%lf%lf",&a,&b,&c)
#define ssssll(a,b,c,d) scanf("%lld%lld%lld%lld",&a,&b,&c,&d)
#define Case(no) printf("Case #%lld: ",++no)
#define nl puts("")
#define pll(a) printf("%lld\n",a)
#define P(a) printf("%d ",a)
#define PLL(a) printf("%lld ",a)


#define ff first
#define pb push_back
#define mp make_pair
#define se second
#define pb push_back
#define ST(v) sort(all(v))
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) (a*(b/gcd(a,b)))
#define max3(a,b,c) max(a,max(b,c))
#define min3(a,b,c) min(a,min(b,c))
#define maxall(v) *max_element(all(v))
#define minall(v) *min_element(all(v))
#define cover(a,d) memset(a,d,sizeof(a))
#define popcount(i) __builtin_popcount(i)                       //count one
#define output freopen("out.txt","w",stdout)
#define input freopen("in.txt","r",stdin)
#define un(v) ST(v), (v).earse(unique(all(v)),v.end())
#define common(a,b) ST(a), ST(b), a.erase(set_intersection(all(a),all(b),a.begin()),a.end())
#define uncommon(a,b) ST(a), ST(b), a.erase(set_symmetric_difference(all(a),all(b),a.begin()),a.end())
#define flop(m,n,q)             for(ll i=m;i<=n;i+=q)
////============ CONSTANT ===============////
#define mx  (100010)
#define inf 10000000000000000
#define eps 1e-9
#define mod 10007
typedef long long ll;
////=====================================////
struct edge
{
    ll u,v,w;
    bool operator<(const edge& p)const
    {
        return w < p.w;
    }
} mew;
vector<edge>node;
ll parent[10010];
ll find(ll r)
{
    return(parent[r]==r)?r:find(parent[r]);
}
ll minimum_spaning_tree(ll a,ll sum)
{
    flop(1,a,1) parent[i]=i;
    ll cnt=a;
    ll sum1=0;
    if(node.size())
    {
        flop(0,node.size()-1,1)
        {
            if(node[i].w>=sum) break;
            ll u=find(node[i].u);
            ll v=find(node[i].v);
            if(u!=v)
            {
                parent[u]=parent[v];
                sum1+=node[i].w;
                if(--cnt==1) break;
            }
        }
    }
    sum*=(cnt);
    sum+=sum1;
    printf("%lld %lld\n",sum,cnt);
}
int main()
{
    //input;
    // output;
    ll a,p,q,s,t=0;
    sll(a);
    while(a--)
    {
        sssll(p,q,s);
        flop(1,q,1)
        {
            ll u,v,w;
            sssll(u,v,w);
            mew.u=u;
            mew.v=v;
            mew.w=w;
            node.pb(mew);
        }
        sort(all(node));
        Case(t);
        minimum_spaning_tree(p,s);
        node.clear();
    }
}
