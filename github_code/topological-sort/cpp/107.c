/** Toplolgical sort using DFS algorithm implemented by Arpan Pathak **/
#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;

/* Edge Class will contain description of edge (end vertex and weight) */
template<class K,class V>
class Edge
{
        public:
            K vertex; V weight;
            Edge(K vertex,V weight): vertex(vertex),weight(weight) { }
};

/** Graph Template class where K specifies data type of vertex value and V specifies data type of edge weight **/
template<class K,class V>
class Graph
{
    map<K,list<Edge<K,V>> > G; // map will map each vertex to a linked list which contains all adjacent vertices
    set<K> Vertices; // set is used to keep track of all vertices because we are using adjacency list

    public:
        void addEdge(K u,K v,V w) { G[u].push_front(Edge<K,V>(v,w));  Vertices.insert(u); Vertices.insert(v); }
        vector<K> topologically_sorted_order(K start)
        {
            stack<K> s; map<K,bool> status;
            vector<K> result;
            for(auto i: Vertices)
                status[i]=(i==start?true:false); // N indicate Not Processed, P indicates Processing and F indicate Finished
            s.push(start);
            while(!s.empty())
            {
                int c=0;
                K explore=s.top();
                for(auto i: G[explore])
                {
                    if(!status[i.vertex]){
                        s.push(i.vertex); status[i.vertex]=true; c++;
                        break;
                    }
                }
                if(!c) { result.insert(result.begin(),s.top()); s.pop();  }
            }
            return result;
        }
};

int main()
{
    Graph<string,int> G;
    G.addEdge("A","G",10);
    G.addEdge("B","A",10);
    G.addEdge("B","F",10);
    G.addEdge("X","B",10);
    G.addEdge("B","C",10);
    G.addEdge("F","G",10);
    G.addEdge("C","F",10);
    G.addEdge("D","C",10);
    G.addEdge("E","C",10);
    G.addEdge("E","D",10);
    // start with a vertex which has a in degree of zero
    for(string x: G.topologically_sorted_order("A"))
        cout<<x<<",";
}
