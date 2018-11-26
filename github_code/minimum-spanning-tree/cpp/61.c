#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string>
#include<cmath>
#include<cstdint>
//#include<>
using namespace std;

typedef int64_t i64;typedef int32_t i32;
typedef int16_t i16;typedef int8_t i8;
typedef uint64_t ui64;typedef uint32_t ui32;
typedef uint16_t ui16;typedef uint8_t ui8;

typedef i32 int__;
#define rep(i,j) for(int__ i=0;i<j;i++)
#define repeat(i,j,k) for(int__ i=(j);i<(k);i++)
#define repeat_eq(i,j,k) for(int__ i=(j);i<=(k);i++)
#define all(v) begin(v),end(v)

const i32 INF=1<<30;//=10E10

class Path{

  public:
  struct Edge{i32 to,cost;Edge(i32 to_,i32 cost_):to(to_),cost(cost_){;}};


  vector< vector<Edge> > G;//接続リスト
  i32 V_num;
  i32 E_num;
  
  Path(i32 n){G.resize(n);V_num=n;E_num=0;}

  void add_arc(i32 x,i32 y,i32 c)
  {
    G[x].push_back(Edge(y,c));
    E_num+=1;
  }

  struct state{
    int index;
    int cost;
    state(int i,int c):index(i),cost(c){;}
    bool operator<(const state &r)const{return cost<r.cost;}
    bool operator>(const state &r)const{return cost>r.cost;}      
  };

  //連結でないと無限ループ
  i32 Prim(){
    i32 start=0;
    i32 V=G.size();
    priority_queue< state ,vector<state>,greater<state> > que;
    vector<bool> used(V,false);
    
    que.push(state(start,0));

    i32 ans=0,usednum=0;
    while(usednum!=V){
      state now=que.top();que.pop();
      if(used[now.index])continue;
      used[now.index]=true;
      usednum+=1;
      ans+=now.cost;
      for(Edge e : G[now.index]){
	que.push(state(e.to,e.cost));	      
      }
    }
    return ans;
  }
  
  
};



int main()
{
  i32 v,e;cin>>v>>e;
  Path Graph(v);
  rep(i,e){
    i32 s,t,d;cin>>s>>t>>d;
    Graph.add_arc(s,t,d);
    Graph.add_arc(t,s,d);
  }
  cout<<Graph.Prim()<<endl;
  return 0;
}
