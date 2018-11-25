#include<iostream>
#include<vector>
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cmath>
#include "edge.h"
using namespace std;

class Ford_Fulkerson{
     public:
        ~Ford_Fulkerson();

        void Initialize(int n, int s, int t);

        void AddEdge(int u, int v, int cap);

        int DFS(int u, int bottleneck);

        void Maxflow();

        int get_maxflow() const;
        void print();

        void clearflow();

     private:
        int maxflow;
        int n; 
        int s, t; 
        vector<edge> G[N]; 
        int visited[N];
};

void Ford_Fulkerson::AddEdge(int u, int v, int cap){
     int u_index = G[u].size();
     int v_index = G[v].size();
     G[u].push_back((edge){v_index, v, cap, 0});
     G[v].push_back((edge){u_index, u, 0, 0});
}

void Ford_Fulkerson::Initialize(int s, int t, int n){
     this->maxflow = 0;
     this->n = n;
     this->s = s;
     this->t = t;
     memset(visited, 0, sizeof(visited));
}

Ford_Fulkerson::~Ford_Fulkerson(){
     clearflow();

}

void Ford_Fulkerson::clearflow(){
     this->maxflow = 0;
     for(int i= 0; i < n; ++i){
         G[i].clear();
     }
     memset(visited, 0, sizeof(visited));
}

int Ford_Fulkerson::get_maxflow() const{
    return this->maxflow;
}

void Ford_Fulkerson::Maxflow(){
  
  int f = 0;
  while(true){
     memset(visited, 0, sizeof(visited));

     visited[s] = 1;
     f = DFS(s, INF);
     if(f > 0){
       this->maxflow += f;
     }
     else{
       break;
     }
  }
}

int Ford_Fulkerson::DFS(int u, int bottleneck){
    int f = 0;
    if(u == this->t){
       return bottleneck;
     }
    
    for(int i = 0; i < G[u].size(); ++i){
        edge& e = G[u][i];
        int v = e.v;
        if(!visited[v] && e.cap > e.flow){
           
           visited[v] = 1;
           
           f = DFS(v, min(e.cap - e.flow, bottleneck));

           if(f > 0){
              e.flow += f;

              G[v][e.inverse_index].flow -= f;
              
              return f;
           }
           visited[v] = 0;
        }
    }
    return 0;
}



void Ford_Fulkerson::print(){
     if(maxflow > 0){
         cout << "Maxflow found! The value of Maxflow is " << this->maxflow << endl;
       }

     cout << "Show the flow below: " << endl;
     queue<int> node;
     node.push(s);

     memset(visited, 0, sizeof(visited));
     visited[s] = 1;
     int idx;
     while(node.size() > 0){
       idx = node.front();
       node.pop();
       for(int i = 0; i < G[idx].size() ; ++i){
           if(G[idx][i].flow > 0){
              int v = G[idx][i].v;
              if(!visited[v]){
                 visited[v] = 1;
                 node.push(v);
              }
              cout << "node " << idx << " -> node " << i << " : " << G[idx][i].flow << endl;
           }

       }

}
}
