#include<iostream>
#include<list>

using namespace std;
int V;
list<int> *adj;

struct graph{
       int v;
       };

graph* createGraph(int v){
       graph *Graph=new graph;
       Graph->v=v;
       V=v;
       adj=new list<int>[v];
       return Graph;
       }

void addEdge(int v,int w){
     adj[v].push_back(w);
     }
     
void dfsUtil(int v,bool visited[]){
     visited[v]=true;
     cout<<v<<" ";
     list<int>::iterator it;
     for(it=adj[v].begin();it!=adj[v].end();it++){
                                                  if(!visited[*it]){
                                                                  dfsUtil(*it,visited);
                                                                  }
                                                  }
     }

void dfs(int v){
     bool *visited=new bool[5];
     for(int i=0;i<v;i++){
             visited[i]=false;                                           //mark all un-visted
             }
     dfsUtil(v,visited);
     }
int main(){
    int v; 
    cout<<"\nEnter the number of vertices:";
    cin>>v;
    graph *graph1=createGraph(v);
    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,2);
    addEdge(2,0);
    addEdge(2,3);
    addEdge(3,3);
    addEdge(3,4);
    addEdge(4,1);
    addEdge(4,2);
    cout<<"\nEnter the vertex for traversal:";
    cin>>v;
    cout<<"\nDFS:"<<endl;
    dfs(v);
    system("pause");
    return 0;
    }
