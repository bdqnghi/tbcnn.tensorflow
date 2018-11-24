#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define pc putchar_unlocked
#define ll long long int
#define V_ll vector<ll>
#define V_int vector<int>
#define	mp make_pair
#define	pb push_back
#define f first
#define s second
#define F front
#define P pop
#define p push
#define Pb pop_back
#define b begin
#define e end
#define M_ll multiset<ll>
#define M_int multiset<int>
#define IT iterator
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mh make_heap
#define ph push_heap
#define Ph pop_heap
#define sh sort_heap
#define ih is_heap
#define p_que priority_queue
#define FOR_Z(i,a) for(int i=0;i<a;++i)
#define FOR_A(i,a,b) for(int i=a;i<b;++i)
#define mod 1000000007
#define s_l(a) scanf("%lld",&a)
#define s_ll(a, b) scanf("%lld %lld",&a, &b)
#define s_lll(a, b, c) scanf("%lld %lld %lld",&a, &b, &c)

#define s_i(a) scanf("%d",&a)
#define s_ii(a, b) scanf("%d %d",&a, &b)
#define s_iii(a, b, c) scanf("%d %d %d",&a, &b, &c)

#define p_l(a) printf("%lld\n",a)
#define p_ll(a, b) printf("%lld %lld\n",a, b)
#define p_lll(a, b, c) printf("%lld %lld %lld\n",a, b, c)

#define p_i(a) printf("%d\n",a)
#define p_ii(a, b) printf("%d %d\n",a, b)
#define p_iii(a, b, c) printf("%d %d %d\n",a, b, c)
inline int max(int a,int b){return a<b?b:a;}
inline int min(int a,int b){return a>b?b:a;}
inline ll max(ll a,ll b){return a<b?b:a;}
inline ll min(ll a,ll b){return a>b?b:a;}
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
const int MOD = 1e9+7;
const int N = 1e6+10;
const ll inf = 1e18;
#define INF 0x3f3f3f3f

#define fast ios::sync_with_stdio(false);cin.tie(0); cout.tie(0)

typedef pair<int, int> iPair;

ll q_sort (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
//qsort(values, 5, sizeof(int), q_sort);

ll power(ll a, ll b)
{
    int f = 1;
    while(b)
    {
        f = b & 1 ? (f * a) % MOD : f;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return f % MOD;
}

ll modpow(ll a, ll b)
{
	ll r = 1;

	while (b) {
		if (b & 1) {
			r = (r * a) % mod;
		}

		a = (a * a) % mod;

		b >>= 1;
	}

	return r;
}

ll modpowinverse(ll a) 
{
	return modpow(a, mod - 2);
}
void fastscan(ll &x)
{
    bool neg=false;
    register int c;
    x =0;
    c=gc();
    if(c=='-')
    {
        neg = true;
        c=gc();
    }
    for(;(c>47 && c<58);c=gc())
    x = (x<<1) + (x<<3) +c -48;
    if(neg)
       x *=-1;
}
void fastscan(int &x)
{
    bool neg=false;
    register int c;
    x =0;
    c=gc();
    if(c=='-')
    {
        neg = true;
        c=gc();
    }
    for(;(c>47 && c<58);c=gc())
    x = (x<<1) + (x<<3) +c -48;
    if(neg)
       x *=-1;
}
//create method to here
class MST
{
	int V;
	list< pair<int, int> > *adj;
public:
	MST(int V);
	void addEdge(int u, int v, int w);
	void primMST();
};

MST::MST(int V)
{
	this->V = V;
	adj = new list< pair<int, int> >[V];
}

void MST::addEdge(int u, int v, int w)
{
	adj[u].pb(mp(v, w));
	adj[v].pb(mp(u, w));
}

void MST::primMST()
{
	p_que< iPair, vector<iPair>, greater<iPair> > pq;
	int src = 0;
	V_int key(V, INF);
	V_int parent(V, -1);
	V_int inMST(V, false);

	pq.p(mp(0, src));
	key[src] = 0;
	while(!pq.empty())
	{
		int u = pq.top().s;
		pq.P();

		inMST[u] = true;

		list< pair<int, int> >::iterator i;
		for(i = adj[u].b(); i != adj[u].e(); i++)
		{
			int v = (*i).f;
			int w = (*i).s;
			if(inMST[v] == false && key[v] > w)
			{
				key[v] = w;
				pq.p(mp(key[v], v));
				parent[v] = u;
			}
		}
	}
	int sum = 0;
	FOR_A(i, 1, V)
	{
		sum += key[i];
		//p_ii(parent[i], i);
	}
	p_i(sum);
}

void solve()
{
	int V = 9;
	//fastscan(V);
	MST g(V);
	g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
 
    g.primMST();
}
int main()
{
    fast;
    ll T = 1;
    //fastscan(T);
    while(T--)
    {
    	solve();
    }
    return 0;
}
//minimum_spanning_tree.cpp