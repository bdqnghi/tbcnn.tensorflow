/*
cos(x)=d/l

cos(nx)=2cos(x)cos((n−1)x)−cos((n−2)x)  

proof of above -> https://math.stackexchange.com/questions/1017668/prove-that-cosnx-2-cosn-1x-cosx-cosn-2x

that means we can write cos(tx) in a matrix-multiplication form:
(cos(tx)cos((t−1)x))=(2cos(x)1−10)(cos((t−1)x)cos((t−2)x)),
and therefore
( cos(tx) )
( cos((t−1)x)=(2cos(x) -1)^t-1	( cos(x) )
			 (	1      0)      *(	1	)
Thus we can compute cos(tx) by fast matrix exponentiation in O(logt) time.
ans=cos(tx)*l
*/
#include <bits/stdc++.h>
using namespace std;
#define MOD (1000000000+7)
typedef long long ll;

ll inverse(ll a,ll b) {
	ll ans=1;
	while(b) {
		if(b&1==1) {
			ans=(ans*a)%MOD;
		}
		a=(a*a)%MOD;
		b=b/2;
	}
	return ans;
}

void multiply(ll A[2][2],ll M[2][2]) {
  ll fValue =(((A[0][0]%(MOD))*(M[0][0]%(MOD))%(MOD)+((A[0][1]%(MOD))*(M[1][0]%(MOD)))%(MOD)))%(MOD);
  ll sValue=(((A[0][0]%(MOD))*(M[0][1]%(MOD))%(MOD)+((A[0][1]%(MOD))*(M[1][1]%(MOD)))%(MOD)))%(MOD);
  ll tValue=(((A[1][0]%(MOD))*(M[0][0]%(MOD))%(MOD)+((A[1][1]%(MOD))*(M[1][0]%(MOD)))%(MOD)))%(MOD);
  ll lValue=(((A[1][0]%(MOD))*(M[0][1]%(MOD))%(MOD)+((A[1][1]%(MOD))*(M[1][1]%(MOD)))%(MOD)))%(MOD);

  A[0][0]=fValue;
  A[0][1]=sValue;
  A[1][0]=tValue;
  A[1][1]=lValue;
}

void power(ll A[2][2],ll t,ll cos) {
	if(t==1)
		return;
	power(A,t/2,cos); 
	multiply(A,A);
	if(t%2!=0) {
    ll F[2][2]={{2*cos,MOD-1},{1,0}};
    multiply(A,F);
  }
}

ll matrixExpo(ll cos,ll t) {
	if(t==0) 
		return 0;
	ll A[2][2]={{2*cos,MOD-1},{1,0}};
	power(A,t,cos);
	//cout<<A[0][0]<<" ";
	return (A[0][0]*cos+A[0][1])%MOD;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long t;
	cin>>t;
	while(t--) {
		long l,d;
		long long t;
		cin>>l>>d>>t;
		ll cos = (d*inverse(l,MOD-2))%MOD;
		//cout<<cos<<" ";
		ll ans=matrixExpo(cos,t-1);
		if(t==1) {
			cout<<d<<"\n";
		} else {
			ans=(ans*l)%MOD;
			cout<<ans<<"\n";
		}
	}
	return 0;
}
