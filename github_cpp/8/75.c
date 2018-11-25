#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long 
const int M = 1e6+5;
const int Inf=2147483647;
vector<int> v[M];
stack<int>s;
bool vis[M];
void topsort(int r)
{
	vis[r]=true;
	for(int i=0;i<v[r].size();i++)
	{
		int x=v[r][i];
		if(!vis[x])
		  topsort(x);		  
	}
	s.push(r);
}
int main()
{
	int n,ct=0;
	cin>>n;
	set<int> r;
	set<int> ::iterator it;
	while(n--)
	{
		int a,b;
		cin>>a>>b;
		r.insert(a);
		r.insert(b);
		v[a].push_back(b);
	}
	for(it=r.begin();it!=r.end();it++){
		if(!vis[*it])
		  topsort(*it);
	}
    while(!s.empty())
    {
   	  cout<<s.top()<<" ";
   	  s.pop();
    }
   	
}
