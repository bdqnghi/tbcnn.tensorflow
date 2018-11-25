#include <bits/stdc++.h>
#define lli long long int
using namespace std;
inline lli scan( )
{
lli n = 0;
char c;
for( c = getchar_unlocked(); c==' ' || c=='\n' || c == '\t'; c = getchar_unlocked());
for( ; c > 0x2f && c < 0x3a; c = getchar_unlocked())
n = (n * 10) + (c & 0x0f);
return n;
}
lli n,c,arr[100005];
bool min_dist(lli mid)
{
	lli cow_count=1;
	lli prev_stall=arr[0];
	for(lli i=1;i<n;i++)
	{
		if((arr[i]-prev_stall)>=mid)
		{
			prev_stall=arr[i];
			cow_count++;
			if(cow_count==c)
				return true;
		}
	}
	return false;
}
int main(int argc, char const *argv[])
{
	lli t;
	t=scan();
	while(t--)
	{
		n=scan();
		c=scan();
		for(lli i=0;i<n;i++)
			arr[i]=scan();
		sort(arr,arr+n);
		lli l=0,r=arr[n-1];
		while(l<r)
		{
			lli mid=(l+r)/2;
			if(min_dist(mid))
				l=mid+1;
			else
				r=mid;
		}
		cout<<l-1<<endl;
	}
	return 0;
}