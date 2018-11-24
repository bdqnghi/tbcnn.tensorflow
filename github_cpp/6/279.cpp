#include<iostream>
#include<queue>
#include<vector>
#define inf 1000001
#define pii pair<int,int>      //first->wt , second->dest
#define for(i,j,n) for(int i = j; i < n; ++i)
using namespace std;
int V,E;

void make_path(vector<int> parent,int i)
{  if(parent[i]==-1) return;
   else cout<<"<-"<<parent[i];
   make_path(parent,parent[i]);
}
void bf(vector<pii> g,int weight[])
{ vector<int> distance(V,inf),parent(V,-1);
  int flag;
  distance[0]=0;
  for(i,0,V-1)
  { flag=0;
    for(j,0,E)
    {
      if(distance[g[j].first]+weight[j]<distance[g[j].second])
      {
        distance[g[j].second]=distance[g[j].first]+weight[j];
        parent[g[j].second]=g[j].first;
        flag=1;
      }
    }
    if(!flag) break;
  }

   flag=0;
   for(j,0,E)
    {
      if(distance[g[j].first]+weight[j]<distance[g[j].second])
      { 
        distance[g[j].second]=distance[g[j].first]+weight[j];
        parent[g[j].second]=g[j].first;
        flag=1;
      }
    }   
  if(flag==1) 
    { cout<<"-ve cycle present";
      return;
    }
  for(i,1,V)
  {
    cout<<"\n"<<distance[i]<<" "<<i;
    make_path(parent,i);
  }
}

int main() 
{
	int a,b,wt;
  vector<pii> g;
	cin>>V>>E;
  int weight[E];
    for(i,0,E)
    { cin>>a>>b>>wt;
      g.push_back(make_pair(a,b));
      weight[i]=wt;
    } 
    bf(g,weight);
    return 0;
}
/*

 Let us create the following graph
    
INPUT:
5 8
1 4 2
3 1 1
1 3 2
0 1 -1
0 2 4
3 2 5
1 2 3
4 3 -3

OUTPUT:
-1 1<-0
2  2<-1<-0
-2 3<-4<-1<-0
1  4<-1<-0
*/