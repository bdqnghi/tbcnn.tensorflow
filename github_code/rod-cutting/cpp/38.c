#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define vll vector<ll>
#define F first
#define S second
#define pll pair<ll,ll>
#define FOR1(i,a) for(i=0;i<=a;i++)
#define FOR2(i,a,b) for(i=a;i<=b;i++)
#define endl '\n'
#define clr(a) memset(a,0,sizeof(a))
#define all(x) x.begin(),x.end()
typedef long long ll;


int main()
{
	int n,i,j;cin>>n;
	int p[n+1],r[n+1],s[n+1];
	FOR1(i,n-1)
	cin>>p[i];

	clr(s);
	clr(r);
	for(i=1;i<=n;i++)
	{	int q=-1;
		for(j=0;j<i;j++)
			if(q<p[j]+r[i-j-1]){
				q=p[j]+r[i-j-1];s[i]=j+1;
			}
		// cout<<s[i];//int t;cin>>t;
		r[i]=q;
	}
	cout<<endl;
	
	FOR1(i,n-1)
	cout<<p[i]<<" ";
	cout<<endl;
	FOR1(i,n)
	cout<<r[i]<<" ";
	cout<<endl;
	FOR1(i,n-1)
	cout<<s[i]<<" ";
	int len;
	// cin>>len;
	cout<<"answer:"<<r[n];
	cout<<"\nsol:";
	while(n>0)
		{cout<<s[n]<<"("<<n<<")";int t;cin>>t;n=n-s[n];}
	return 0;
}