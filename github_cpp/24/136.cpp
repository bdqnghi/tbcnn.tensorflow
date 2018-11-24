#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#ifndef ONLINE_JUDGE
#define gc getchar
#else
#define gc getchar_unlocked
#endif
#define ll long long
#define nl() printf ("\n")
#define si(a) scanf("%d",&a)
#define sl(a) scanf("%lld",&a)
#define pi(x) printf ("%d",x)
#define pl(x) printf ("%lld",x)
#define pc(x) printf ("%c",x)
#define ps(x) printf ("%s",x)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define repu(i,a,n,step) for (i = a; i < n; i += step)
#define repd(i,a,n,step) for (i = a - 1; i >= n; i += step)
using namespace std;
int readi () {
	int n=0,sign=0;
	char c=gc();
	while (c<48) {
		if (c==45) sign=1;
		c=gc();
	}
	while (c>47) {
		n=n*10+c-'0';
		c=gc();
	}
	if (sign) return (-n);
	return n;
}
ll readl () {
	ll n=0;int sign=0;
	char c=gc();
	while (c<48) {
		if (c==45) sign=1;
		c=gc();
	}
	while (c>47) {
		n=n*10+c-'0';
		c=gc();
	}
	if (sign) return (-n);
	return n;
}
double power(double x, int y)
{
    double temp;
    if( y == 0)
       return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
    {
        if(y > 0)
            return x*temp*temp;
        else
            return (temp*temp)/x;
    }
}
int parent[1001],vertices,edges;
vector <pair<pair<int,int>,int> > graph;
bool compare(const pair<pair<int,int>, int > &p1, const pair<pair<int,int>,int> &p2) {
        return (p1.second < p2.second);
}
int findset(int x, int parent[]) {
        if (x != parent[x]) parent[x] = findset(parent[x],parent);
        return parent[x];
}
int kruskal() {
        int tot = 0,parentU,parentV;
        sort(graph.begin(),graph.end(),compare);
        for (int i = 0;i<edges; i++) {
                parentU = findset(graph[i].first.first, parent);
                parentV = findset(graph[i].first.second, parent);
                if (parentU != parentV) {
                        tot += graph[i].second;
                        parent[parentU] = parent[parentV];
                }
        }
        //cout<<tot<<"\n";
        return tot;
}
int main() {
        int t,u,v,w,p;
        t=readi();
        while (t--) {
                p = readi();
                vertices = readi();
                edges = readi();
                for (int i = 1; i <= vertices; i++) parent[i] = i;
                for (int i=0;i<edges; i++) {
                        u = readi(); v = readi(); w = readi();
                        w *= p;
                        graph.pb(mp(mp(u,v),w));
                }
                pi(kruskal());nl();
                graph.clear();
        }
return 0;
}
