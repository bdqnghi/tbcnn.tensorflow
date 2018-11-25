

















#include <algorithm> 
#include <cstdio> 
#include <functional> 
#include <fstream> 
#include <iostream> 
#include <map> 
#include <queue>
#include <random>
#include <stdint.h> 
#include <vector> 

using namespace std; 



namespace { 
    const int MAXV = 100; 
}



class Node
{ 
    public: 
        Node(const uint32_t index, const uint32_t path_cost):
          idx(index), cost(path_cost) {}

        ~Node() {}

        uint32_t idx; 
        double cost; 
};  




class EdgeNode 
{
    public: 
        EdgeNode(const uint32_t index, const uint32_t c):
            idx(index), cost(c), next(nullptr)
        {}

        uint32_t idx;       
        double cost;        
        EdgeNode* next;     
};









class Graph
{ 
    public: 
        
        
        Graph(const uint32_t num_vertices): 
            nvertices(num_vertices), num_edges(0)
        {
            Initialize(); 
        }

        
        Graph(const string& filename); 

        
        ~Graph(){}

        
        void Initialize() 
        {
            nodelist.resize(MAXV);
            degree.resize(MAXV); 
            fill(nodelist.begin(), nodelist.end(), nullptr); 
            fill(degree.begin(), degree.end(), 0);           
        }

        
        int V() const { return nvertices; }      

        
        int E() const { return num_edges; }          
    
        
        void print() const;
    
        
        void add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse);

        
        void del(const uint32_t x, const uint32_t y, bool IsReverse);

        
        void set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v);

        
        uint32_t get_edge_value(const uint32_t x, const uint32_t y) const;

        
        vector<Node> neighbours(const uint32_t x) const; 
           
        
        bool adjacent(const uint32_t x, const uint32_t y);
    
    private:
        
        vector<EdgeNode*> nodelist; 

        
        vector<uint32_t> degree;  
        
        
        uint32_t nvertices;             
        
        
        uint32_t num_edges;               
};




Graph::Graph(const string& filename) 
{
   Initialize(); 
   ifstream infile(filename);  

   
   infile >> nvertices; 

   uint32_t s, d, w; 

   
   while (infile >> s >> d >> w) { 
       add(s, d, w, true); 
   } 
}


bool Graph::adjacent(const uint32_t x, const uint32_t y) 
{ 
    bool ret = false;
    EdgeNode* p = nodelist[x]; 
    
    
    while (p) { 
       if (p->idx == y) { 
          ret = true; 
          break; 
       }
       p = p->next;  
    }

    return ret; 
} 



void Graph::add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse)
{ 
    EdgeNode* tmp = new EdgeNode(y, c);         
    tmp->next = nodelist[x];                    
    nodelist[x] = tmp;                          
    degree[x]++;                                

    
    if (!IsReverse) { 
        num_edges++;                                    
        add(y, x, c, true); 
    }
} 


void Graph::del(const uint32_t x, const uint32_t y, bool IsReverse) 
{
    
    
    
    EdgeNode* curr = nodelist[x]; 
    EdgeNode* prev = nodelist[x]; 
    
    while(curr) { 
        if (curr->idx == y) { 
            prev->next = curr->next; 
            delete curr; 
            break; 
        }
        prev = curr; 
        curr=curr->next; 
    }

    
    if (!IsReverse) { 
        del(y, x, true); 
    }
}


void Graph::set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v) 
{
   EdgeNode* p = nodelist[x]; 
  
   
   while(p) { 
      if (p->idx == y) { 
         p->cost = v; 
         break; 
      }

      p = p->next; 
   }
}


uint32_t Graph::get_edge_value(const uint32_t x, const uint32_t y) const
{
   EdgeNode* p = nodelist[x]; 
   uint32_t c = 0; 

   while(p) { 
      if (p->idx == y) { 
        c = p->cost; 
      }
      p = p->next; 
   } 

   return c; 
}


vector<Node> Graph::neighbours(const uint32_t x) const
{ 
    vector<Node> n; 
    EdgeNode* p = nodelist[x]; 

    while(p) { 
        n.emplace_back(p->idx, p->cost); 
        p = p->next; 
    }

    return n; 
}


void Graph::print() const
{
   cout << "graph contents\n"; 

   for (int i=0; i<nvertices; ++i) { 
        cout << i << ": ";  
        EdgeNode* p = nodelist[i]; 

        while(p) {
            cout << p->idx ; 
            p = p->next;
            
            if (p)  
                cout << ",";
        }

        cout << endl; 
   }
}               
 


class MinimumSpanningTree
{ 
    public: 
        
        MinimumSpanningTree(const Graph& g): graph(g), min_cost(0)
        {};

        ~MinimumSpanningTree() {}

        
        void compute_prims();

        
        uint32_t get_min_weight() { 
           return min_cost; 
        } 

        
        map<uint32_t, vector<uint32_t>> get_mst() {
            return mst; 
        }

    private: 
        
        Graph graph;

        
        
        
        
        
        
        
        map<uint32_t, vector<uint32_t>> mst; 

        
        uint32_t min_cost;

        
        const uint32_t MAXC = 100; 
}; 

void MinimumSpanningTree::compute_prims()
{
    
    struct Edge { 
        Edge(uint32_t s, uint32_t d, uint32_t c): 
            src(s), dst(d), cost(c) {} 

        uint32_t src;
        uint32_t dst; 
        uint32_t cost; 
    }; 

    
    struct LessThan { 
        bool operator() (const Edge& lhs, const Edge& rhs) const { 
            return lhs.cost > rhs.cost; 
        }
    };

    priority_queue<Edge, vector<Edge>, LessThan> pq; 

    
    vector<bool> visited (graph.V(), false); 

    
    visited[0] = true; 

    
    auto neighbors = graph.neighbours(0); 

    for (const auto& x: neighbors) { 
        pq.push(Edge(0, x.idx, x.cost));
    }

    
    while (!pq.empty()) { 
        
        
        Edge e = pq.top();
        pq.pop();

        
        if (!visited[e.dst]) { 
            
            min_cost += e.cost;
            
            visited[e.dst] = true;  
            
            mst[e.src].push_back(e.dst); 

            vector<Node> nbrs = graph.neighbours(e.dst); 
   
            
            for (auto & neighbor: nbrs) {
                
                if (!visited[neighbor.idx]) { 
                    pq.push(Edge(e.dst, neighbor.idx, neighbor.cost));
                }
            }
        }
    }   
}

void run_example1()
{ 
    const int N = 6;  
    Graph g(N); 

    g.add(0, 1, 2, false); 
    g.add(0, 3, 4, false); 
    g.add(1, 2, 2, false); 
    g.add(2, 5, 2, false); 
    g.add(3, 4, 2, false); 
    g.add(3, 5, 1, false); 
    g.add(4, 5, 2, false); 
  
    g.print();

    MinimumSpanningTree st(g); 
    st.compute_prims(); 
    cout << "minimum weight of the spanning tree: ";  
    cout << st.get_min_weight() << endl; 
}

void run_example2() 
{
    Graph g(string("sampledata.txt")); 
    g.print(); 
    MinimumSpanningTree st(g); 

    st.compute_prims(); 
    cout << "minimum weight of the spanning tree: ";
    cout << st.get_min_weight() << endl;  
}   

int main() 
{
    run_example1(); 
    run_example2();
    return 0; 
}
