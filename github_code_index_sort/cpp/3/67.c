//nexus01
#include <bits/stdc++.h>
using namespace std;

typedef long long int lli;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<lli> vll;
typedef vector<double> vd;
typedef vector<pii> vpii;

#define fla(i,a,b) for(int i=a; i<b; i++)
#define flra(i,a,b) for(int i=a; i>b; i--)
#define fl(i,a) for(int i=0; i<(a); ++i)

#define gi(x) scanf("%d",&x)
#define gl(x) scanf("%ld", &x)

#define pn printf("\n")
#define pi(x) printf("%d",x)

#define endl "\n"
#define spc printf(" ")
#define prec(x) cout<<fixed<<setprecision(x)
#define all(x) (x).begin(), (x).end()
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define fr freopen("input.in", "r", stdin)
#define fw freopen("output.txt", "w", stdout)
#define SET(a, v) memset(a, v, sizeof a)
const int inf = numeric_limits<int>::max();
const lli linf = numeric_limits<lli>::max();

const int mod= (int)1e9 + 7;
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
class Graph
{
    int v;//number of vertices
    vi *vec;
    void dfsutil(int v, bool vis[]);
    void topologicalsortutil(int v, bool vis[], stack <int> &s);
    public:
    Graph(int v);//constructor
    void addedge(int a, int b);
    void dfs(int v);
    void topologicalsort();
};
Graph::Graph(int v)
{
    this->v=v;
    vec= new vi[v+1];
}
void Graph::addedge(int a, int b)
{
    vec[a].pb(b);
    //vec[b].pb(a);
}
void Graph::dfsutil(int v, bool vis[])
{
    vis[v]=true;
    cout<<v<<" ";
    for(int i=0;i<vec[v].size();i++)
    {
        if(!vis[vec[v][i]])dfsutil(vec[v][i], vis);
    }
}
void Graph::dfs(int v)
{
    bool vis[v+1]={0};
    dfsutil(v, vis);
}
void Graph::topologicalsortutil(int v, bool vis[], stack <int> &s)
{
    vis[v]=true;
    for(auto i=vec[v].begin();i!=vec[v].end();i++)
    {
        if(!vis[*i])
        {
            topologicalsortutil(*i, vis, s);
        }
    }
    s.push(v);
}
void Graph::topologicalsort()
{
    stack <int> s;
    bool *vis=new bool[v];
    vis[v]={0};
    for(int i=0;i<v;i++)
    {
        if(!vis[i])topologicalsortutil(i, vis, s);
    }
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
}
int main()
{
    int n;
    cin>>n;
    Graph g(n);
    int e, a, b;
    cin>>e;
    fl(i, e)
    {
        cin>>a>>b;
        g.addedge(a, b);
    }
    g.topologicalsort();
    return 0;
}