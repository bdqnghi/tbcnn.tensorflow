#include<bits/stdc++.h>
bool v[100001];
#define ll long long 
using namespace std;
ll cancut(ll time,ll h[],ll r[],ll l,ll n)
{
	ll sum=0,i;
	for(i=0;i<n;i++)
	{
		if(h[i]+r[i]*time>=l)
		{
			sum=sum+h[i]+r[i]*time;
		}
	}
	return sum;
}
struct st
{
	ll height;
	ll rate;
};
bool comp(st s1,st s2)
{
	return s1.rate<s2.rate;
}
int main()
{
	ll n,w,l,ans;
	cin>>n>>w>>l;
	ll h[n],r[n],i,j,h1[n],r1[n],l1[n],sr[n];
	st s[n];
	for(i=0;i<n;i++)
	{
		cin>>h[i]>>r[i];
//		st[i].height=h[i];
//		st[i].rate=r[i];
	}
	if(w%l==0)
	{
		ans=w/l;
	}
	else
	{
		ans=w/l+1;
		
	}
	ll count=0;
	for(i=0;i<n;i++)
	{
		if(h[i]>=l)
		{
			count++;
			v[count-1]=true;
		}
	}
	
	if(ans>n)
	{
	   ll max1=*max_element(r,r+n),max2=*max_element(h,h+n);
		ll low=-1, high=w/max1,mid;
		if(w/max1==0)
		high=(w/max1)+1;
		else
		high=(w/max1);
		while(low<high)
		{
			mid=(low)+(high-low)/2;
			ll su=cancut(mid,h,r,l,n);
			if(su==w)
			{
				break;
			}
			else if(su<w)
			{
				low=mid;
			}
			else if(su>w)
			{
				high=mid;
			}
		}
		cout<<mid<<endl;
	}
	else if(ans-count<=0)
	{
		cout<<0<<endl;
	}
	else
	{
		
	ans=ans-count;
	ll size1=0;
	for(i=0;i<n;i++)
	{
		if(!v[i])
		{
			h1[size1]=h[i];
			r1[size1]=r[i];
			if((l-h1[size1])%r[size1]==0)
			l1[size1]=(l-h1[size1])/r[size1];
			else
			l1[size1]=((l-h1[size1])/r[size1])+1;
			size1++;
		}
	}
	sort(l1,l1+size1);
//	ll low=0,high=size1-1,mid=()
	cout<<l1[ans-1]<<endl;
	
	
	}
	
	
	
}
