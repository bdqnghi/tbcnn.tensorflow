#include<bits/stdc++.h>
#include "Graph.cpp"

class DepthFirstSearch{
private:
    bool*marked;    
    int count;           
public:
    DepthFirstSearch(Graph& G,int s){
        marked=new bool [G.V()];
        memset(marked,0,sizeof(marked));
        dfs(G,s);
    }
    
    void dfs(Graph&G, int v){
        count++;
        marked[v] = true;
        for (int w:G.Adj(v)){
            if (!marked[w]){
                dfs(G, w);
            }
        }
    }
    bool Marked(int v){return marked[v];}
    int Count(){return count;}
};

int main(){
    ifstream infile ("tinyG.txt");
    if(!infile)cout<<"error"<<endl;
    Graph G(infile);
    DepthFirstSearch(G,0);
}
