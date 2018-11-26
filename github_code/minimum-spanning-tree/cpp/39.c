/* 
 * File:   KruskalMST.h
 * Author: Olivier Cuisenaire
 * Modified by: Fabien Dutoit
 * Modified by: INDIQUER VOTRE NOM
 * Created on 27. octobre 2014, 14:58
 */

#ifndef ASD2_MST_cpp
#define ASD2_MST_cpp

#include <queue>
#include <vector>
#include <set>
#include <functional>

#include "UnionFind.cpp"

// Classe définissant les difféents algorithmes de calcul de l'arbre
// couvrant de poids minimum sous forme de methodes statiques.

template<typename GraphType> // Type du graphe pondere non oriente a traiter
// GraphType doit se comporter comme un
// EdgeWeightedGraph et definir forEachEdge(Func),
// forEachAdjacentEdge(int,Func) ainsi que le
// type GraphType::Edge, qui doit se comporter
// comme ASD2::Edge, c-a-dire definir Either(),
// Other(int), et operator<
class MinimumSpanningTree {
public:
    // Type d'arête du graphe. Normalement ASD2::Edge
    typedef typename GraphType::Edge Edge;
    
    // Type liste d'arêtes.
    typedef std::vector<Edge> EdgeList;
    
private:
    // Type queue de priorite. MinPQ::top() retourne l'élément le plus petit.
    typedef std::priority_queue<Edge,std::vector<Edge>,std::greater<Edge>> MinPQ;
    
public:
    
    // Algorithme de Prim en version paresseuse. Utilise une queue de priorite
    // pour les aretes a traiter.
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
    
    // Algorithme de Prim en version stricte. Utilise une queue de priorite
    // pour les sommets a traiter. Celle ci est mise en oeuvre avec std::set.
    static EdgeList EagerPrim(const GraphType& g) {
        
        EdgeList output; output.reserve(g.V()-1);
        
        typedef std::pair<Edge,int> EdgeVertex;     // paire arc/sommet.
        // operator< s'applique sur le premier
        // element de la paire, puis le deuxieme
        // si egalite.
        
        std::set<EdgeVertex> pq;                    // queue de priorite
        std::vector<Edge> edge(g.V());              // arc le plus leger pour joindre chaque sommet
        // a l'arbre courrant.
        std::vector<bool> marked(g.V(),false);
        
        marked[0] = true;
        g.forEachAdjacentEdge(0,[&](const Edge& e) {
            int w = e.Other(0);
            edge[w] = e;
            pq.insert(std::make_pair(e,w)); // set::insert() correspond à priority_queue::push().
        });
        
        while ( !pq.empty() && output.size() < g.V()-1 ) {
            
            Edge e = pq.begin()->first;     // set::begin() correspond à priority_queue::top().
            output.push_back(e);
            
            int v = pq.begin()->second;
            marked[v] = true;
            
            pq.erase(pq.begin());            // correspond à priority_queue::pop().
            
            g.forEachAdjacentEdge(v,[&](const Edge& e) {
                int w = e.Other(v);
                if(!marked[w] && edge[w] > e) {
                    pq.erase(std::make_pair(edge[w],w));    // deux operations pour decrease_key
                    pq.insert(std::make_pair(e,w));
                    edge[w] = e;
                }
            });
        }
        return output;
    }
    
    // Algorithme de Boruvka. Implemente avec UnionFind
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

            // 
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
        /* A IMPLEMENTER */
    }
    
};

#endif
