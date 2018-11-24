#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define MAXN 50005
#define mp make_pair
#define oo 1<<20
using namespace std;
int T,i,j,n,m,s,a,b,c,D[MAXN],u[MAXN],Dmi[MAXN];
vector<pair<int, int> > C[MAXN];
void read(),dijkstra();
int main()
{
    freopen("distante.in","r",stdin);
    freopen("distante.out","w",stdout);
    scanf("%d",&T);
    for(;T;T--)
        read(),dijkstra();
    return 0;
}
void read()
{
    scanf("%d%d%d",&n,&m,&s);
    for(i=1;i<=n;i++)scanf("%d",&Dmi[i]);
    for(i=1;i<=m;i++)scanf("%d%d%d",&a,&b,&c),C[a].push_back(mp(b,c)),C[b].push_back(mp(a,c));
}
void dijkstra()
{
    int pmin,min;
    vector<pair<int,int> >::iterator it;
    for(i=1;i<=n;i++)D[i]=oo;
    D[s]=0;
    for(i=1;i<=n;i++)
    {
        min=oo;
        for(j=1;j<=n;j++)
            if(D[j]<min && !u[j])
                min=D[i],pmin=j;
        u[pmin]=1;
        for(it=C[pmin].begin();it!=C[pmin].end();it++)
            if(D[it->first]>D[pmin]+it->second)
                D[it->first]=D[pmin]+it->second;
    }
    for(i=1;i<=n;i++)C[i].resize(0);
    for(i=1;i<=n;i++)
        if(D[i]!=Dmi[i])
            {printf("NU\n");return;}
    printf("DA\n");
}
