#include<bits/stdc++.h>
using namespace std;
vector<vector<int > >g;
vector<int >v;
int a=0;
void topsort(int u,stack <int>&s){
    v[u]=1;
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(!v[*it]){
          topsort(*it,s);
        }
    }
//cout<<a+1<<" ";
s.push(u);
}


int main(){

ios_base::sync_with_stdio(false);
cin.tie(NULL);
int n,m,a,b;
cin>>n>>m;
v.assign(n+1,0);
g.assign(n+1,vector<int>());
for(int i=0;i<m;i++){
  cin>>a>>b;
  g[a].push_back(b);
  //g[b].push_back(a);

}
stack<int >s;

for(int i=1;i<n+1;i++){
    if(!v[i]){
     topsort(i,s);
    }
}
cout<<s.size();
while(!s.empty()){
    //s.pop();
    cout<<s.top()<<" ";
    s.pop();

}
return 0;
}
