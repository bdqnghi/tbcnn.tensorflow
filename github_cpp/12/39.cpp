

#ifndef ASD2_MST_cpp
#define ASD2_MST_cpp

#include <queue>
#include <vector>
#include <set>
#include <functional>

#include "UnionFind.cpp"




template<typename GraphType> 






class MinimumSpanningTree {
public:
    
    typedef typename GraphType::Edge Edge;
    
    
    typedef std::vector<Edge> EdgeList;
    
private:
    
    typedef std::priority_queue<Edge,std::vector<Edge>,std::greater<Edge>> MinPQ;
    
public:
    
    
    
    static EdgeList LazyPrim(const GraphType& g) {
        EdgeList output; output.reserve(g.V()-1);
        MinPQ pq;
        std::vector<bool> marked(g.V(),false);
        
        marked[0] = true;
        g.forEachAdjacentEdge(0,[&pq](const Edge& e) {
            pq.push(e);
        });
        
        while( !pq.empty() && output.size() < g.V()-1 ) {
            Edge e = pq.top(); pq.pop();
            int v = e.Either();
            int w = e.Other(v);
            
            if(!marked[v] || !marked[w]) {
                output.push_back(e);
                int x = marked[v] ? w : v;
                marked[x] = true;
                g.forEachAdjacentEdge(x,[&](const Edge& e) {
                    if(!marked[e.Other(x)])
                        pq.push(e);
                });
            }
        }
        return output;
    }
    
    
    
    static EdgeList EagerPrim(const GraphType& g) {
        
        EdgeList output; output.reserve(g.V()-1);
        
        typedef std::pair<Edge,int> EdgeVertex;     
        
        
        
        
        std::set<EdgeVertex> pq;                    
        std::vector<Edge> edge(g.V());              
        
        std::vector<bool> marked(g.V(),false);
        
        marked[0] = true;
        g.forEachAdjacentEdge(0,[&](const Edge& e) {
            int w = e.Other(0);
            edge[w] = e;
            pq.insert(std::make_pair(e,w)); 
        });
        
        while ( !pq.empty() && output.size() < g.V()-1 ) {
            
            Edge e = pq.begin()->first;     
            output.push_back(e);
            
            int v = pq.begin()->second;
            marked[v] = true;
            
            pq.erase(pq.begin());            
            
            g.forEachAdjacentEdge(v,[&](const Edge& e) {
                int w = e.Other(v);
                if(!marked[w] && edge[w] > e) {
                    pq.erase(std::make_pair(edge[w],w));    
                    pq.insert(std::make_pair(e,w));
                    edge[w] = e;
                }
            });
        }
        return output;
    }
    
    
    static EdgeList BoruvkaUnionFind(const GraphType& g) {
        EdgeList minimalSpaningTree;
        UnionFind uf(g.V());
        int t = 1;

        while(t < g.V() && len(minimalSpaningTree) < g.V()-1)
        {
            EdgeList closest(g.V());

            this->edgeTo.reserve(g.V());

            g.forEachVertex([&](const Edge& e)
            {
                Edge v = e.Either();
                Edge w = e.Other();
                Edge i = uf.Find(v);
                Edge j = uf.Find(w);

                if(i!=j)
                {
                    if(closest[i] == NULL || e < closest[i])
                    {
                        closest[i] = e;
                    }
                    if(closest[j] == NULL || e < closest[j])
                    {
                        closest[j] = e;
                    }
                }
            });

            
            g.ForEachAdjacentEdges([&](int i)
            {
                Edge e = closest[i];
                if(e is )
                {
                    int v = e.Either();
                    int w = e.Other();

                }

            }
        }
        
    }
    
};

#endif
