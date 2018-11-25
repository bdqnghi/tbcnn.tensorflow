#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

#define REP(i,a,b) for(int i=int(a);i<=int(b);i++)
#define INF 2000000000
#define maxn 100
int p[maxn];
int r[maxn];

int cut_rod(int n){
	if(n==0) return 0;
	else{
		int result = -INF,cutindex;
		REP(i,1,n){
			int current = p[i]+cut_rod(n-i);
			if(result<current){
				cutindex = i;
				result = current;
			}
		}
		
		return result;
	}
}

int memoized_cut_rod(int n){
	if(r[n]>=0) return r[n];
	else{
		int result = -INF;
		if(n==0) result=0;
		else REP(i,1,n) result = max(result,p[i]+memoized_cut_rod(n-i));
		r[n] = result;
		return result;
	}
}

int bottom_up_cut_rod(int n){
	REP(i,1,n){
		int result = -INF;
		REP(j,1,i) result=max(result,p[j]+r[i-j]);
		r[i]=result;
	}
	return r[n];
}

int s[maxn];
int extend_bottom_up_cut_rod(){
	REP(i,1,n){
		int result = -INF;
		REP(j,1,i){
			int t = p[j]+r[i-j];
			if(result<t){
				result = t;
				s[j]
			}
		}
	}
	return r[n];
}

int main()
{
	memset(p,0,sizeof(p));
	memset(r,0,sizeof(r));
	memset(s,0,sizeof(s));
	freopen("input.txt","r",stdin);
	int price;
	int i=1;
	while(scanf("%d",&price)==1) p[i++]=price;
	
	
	REP(i,1,10) printf("%d ",cut_rod(i));
	printf("\n");
	
	
	REP(i,0,sizeof(r)/sizeof(r[0])-1) r[i]=-INF;
	REP(n,1,10) printf("%d ",memoized_cut_rod(n));
	printf("\n");
	
	
	r[0] = 0;
	REP(n,1,10) printf("%d ",bottom_up_cut_rod(n));
	printf("\n");
	
	
	return 0;
}







