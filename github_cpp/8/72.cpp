

#include <bits/stdc++.h>
using namespace std;

int c=0;
void dfs(vector <int >v[],int sn,bool vi[],int s[],int e[])
{
	vi[sn]=1;
	++c;
	s[sn]=c;
	for(int i=0;i<v[sn].size();i++)
	  {
	  	 if(vi[v[sn][i]]==0)
	  	   {
	  	   	  dfs(v,v[sn][i],vi,s,e);
	  	   	  
	  	   }
	  }
	++c;
	e[sn]=c;  
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	long int n,i,x,y;
	cin>>n;
	vector <int >v[n+1];
	for(i=0;i<n-1;i++)
	  {
	  	 cin>>x>>y;
	  	 v[x].push_back(y);
	  	 v[y].push_back(x);
	  }
	 bool vi[n+1];
	 int s[n+1],e[n+1];
	 memset(vi,0,sizeof(vi));
	 memset(s,0,sizeof(s));
	 memset(e,0,sizeof(e));
	 dfs(v,1,vi,s,e);
	 int q;
	 
	 
	 
	 cin>>q;
	 
             while(q--)
               {
                 cin>>i>>x>>y;
                 if(i==1)
                   {
                   	swap(x,y);
                   }
                  if(s[x]<=s[y] && e[y]<=e[x])
                   	  {
                   	  	cout<<"YES"<<'\n';
                   	  	
                   	  }
                   	  else
                   	    cout<<"NO"<<'\n'; 
               }
	return 0;
}
