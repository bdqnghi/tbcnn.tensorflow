#include<iostream>
#include<list>
#include<string>
#include<cstring>
#include<sstream>
#include<cctype>
#include<string.h>
#include<algorithm>
#include<cmath>
#include<stack>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<iomanip>
#include<queue>

using namespace std;

#define INF (1<<29)
#define cls(a) memset(a,-1,sizeof(a))
#define ALL(a) a.begin(),a.end()
#define CLR(a) memset(a,0,sizeof(a))
#define FILL(a,v) memset(a,v,sizeof(a))
#define PB push_back
#define FOR(i,n) for(int i = 0;i<n;i++)
#define PI acos(-1.0)
#define EPS 1e-9
#define MP(a,b) make_pair(a,b)
#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))
#define READ freopen("input.txt", "r", stdin)
#define WRITE freopen("output.txt", "w", stdout)
#define LL long long
#define MX 1000
#define MOD 1000000007

#define p(x) printf("%d",x)
#define inp(x) scanf("%d",&x)
#define inpd(x) scanf("%lf",&x)
#define inpll(x) scanf("%lld",&x)
#define getcx getchar_unlocked
/*inline void inp( int &n ) 
 {
    n=0;
    int ch=getcx();int sign=1;
    while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}
 
    while(  ch >= '0' && ch <= '9' )
            n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
    n=n*sign;
  }*/


using namespace std;
struct topo_sort{
	int in,fin,str;
}lst[MX];
bool check[MX],inlist[MX];
vector<int> grf[MX];
int ver[MX], per[MX],st[MX],f[MX],v,e,s,d,time,idx;
void initial(int n)
{
	for(int i=1;i<=n;i++)
	ver[i]=INF;
}
void DFS_visit(int n)
{
	idx++;
	cout<<"\nnode = "<<n;
	time++;
	st[n]=time;
	int odr=idx;
	lst[odr].str=time;
	check[n]=1;
	int l=grf[n].size();
	for(int i=0;i<l;i++)
	{
		if(check[grf[n][i]]==0)
		{
			DFS_visit(grf[n][i]);
		}
	}
	time++;
	f[n]=time;
	lst[odr].in=n;
	lst[odr].fin=time;
}

void DFS()
{
	time=idx=0;
	DFS_visit(s);
	for(int i=1;i<=v;i++)
	{
		if(check[i]==0)
		{
			DFS_visit(i);
		}
	}
}
int compare(const topo_sort a,const topo_sort b)
{
	return ((a.fin==b.fin)?(a.in<b.in):(a.fin>b.fin));
}
int main()
{
	cout<<"\nenter vertices : ";
	inp(v);
	cout<<"\nenter number of edages : ";
	inp(e);
	//initial(v);
	cout<<"\nenter directed edages ";
	for(int i=0;i<e;i++)
	{
		inp(s);
		inp(d);
		grf[s].push_back(d);
	}
	cout<<"\nenter source ";
	inp(s);
	DFS();
	for(int i=1;i<=v;i++)
	{
		cout<<"\ni = "<<i<<" st = "<<st[i]<<" ed = "<<f[i];
	}
	cout<<"\n";
	for(int i=1;i<=v;i++)
	{
		cout<<"\ni = "<<lst[i].in <<" st = "<<lst[i].str<<" ed = "<<lst[i].fin;
	}
	sort(lst+1,lst+v+1,compare);
	
	cout<<"\n";
	for(int i=1;i<=v;i++)
	{
		cout<<"\ni = "<<lst[i].in <<" st = "<<lst[i].str<<" ed = "<<lst[i].fin;
	}
	return 0;
}
