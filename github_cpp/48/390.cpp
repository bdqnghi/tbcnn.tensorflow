#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;

const ull base=233,P=1E9+7;
const int N=8E5+5;

struct str{
	char o[N];
	int f[N],n;
	ll sum[N];
	ull fr[N][2],pw[N][2],bk[N][2];
	inline ull frw(int l,int r,int t){
		if(t) return (fr[r][1]+P-fr[l-1][1]*pw[r-l+1][1]%P)%P;
		return fr[r][0]-fr[l-1][0]*pw[r-l+1][0];
	}
	inline ull bkw(int l,int r,int t){
		if(t) return (bk[l][1]+P-bk[r+1][1]*pw[r-l+1][1]%P)%P;
		return bk[l][0]-bk[r+1][0]*pw[r-l+1][0];
	}
	inline bool check(int l,int r){
		if(fr[r][0]-bk[l][0]!=(fr[l-1][0]-bk[r+1][0])*pw[r-l+1][0])return false;
		return (fr[r][1]+P-bk[l][1]+(bk[r+1][1]+P-fr[l-1][1])*pw[r-l+1][1])%P==0;
	}
	void read(bool rev){
		scanf("%s",o+1);
		n=strlen(o+1);
		if(rev)for(int i=1;i<=n/2;i++)swap(o[i],o[n-i+1]);
		pw[0][0]=pw[0][1]=1;
		for(int i=1;i<=n;i++){
			fr[i][0]=fr[i-1][0]*base+o[i];
			fr[i][1]=(fr[i-1][1]*base+o[i])%P;
			pw[i][0]=pw[i-1][0]*base;
			pw[i][1]=pw[i-1][1]*base%P;
		}
		for(int i=n;i>=1;i--){
			bk[i][0]=bk[i+1][0]*base+o[i];
			bk[i][1]=(bk[i+1][1]*base+o[i])%P;
		}
		for(int i=1;i<=n;i++){
			int l=0,r=min(i,n-i+1),mid=(l+r+1)>>1;
			while(l<r){
				if(check(i-mid+1,i+mid-1))l=mid;else r=mid-1;
				mid=(l+r+1)>>1;
			}
			f[i-mid+1]++,f[i+1]--;
		}
		for(int i=1;i<n;i++){
			int l=-1,r=min(i,n-i),mid=(l+r+1)>>1;
			while(l<r){
				if(check(i-mid,i+mid+1))l=mid;else r=mid-1;
				mid=(l+r+1)>>1;
			}
			f[i-mid]++,f[i+1]--;
		}
		for(int i=1;i<=n;i++)f[i]+=f[i-1],sum[i]=sum[i-1]+f[i];
		sum[n+1]=sum[n];
	}
}A,B;

int lcp(int x,int y){
	int l=0,r=min(A.n-x+1,B.n-y+1),mid=(l+r+1)>>1;
	while(l<r){
		if(A.frw(x,x+mid-1,0)==B.frw(y,y+mid-1,0)&&A.frw(x,x+mid-1,1)==B.frw(y,y+mid-1,1))l=mid;else r=mid-1;
		mid=(l+r+1)>>1;
	}
	return mid;
}

int q,x,y;

int main(){
	freopen("palindrome.in","r",stdin);
	freopen("palindrome.out","w",stdout);
	scanf("%*s");
	A.read(false);B.read(true);
	cerr<<clock()<<endl;
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&x,&y);
		int l=lcp(x,y);
		ll ans=A.sum[x+l]-A.sum[x]+B.sum[y+l]-B.sum[y]+l;
		printf("%lld\n",ans);
	}
	return 0;
}
