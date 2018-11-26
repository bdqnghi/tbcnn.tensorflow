// Solution to assignment 3. 
// The class declarations are followed by the class definitions. 
//
// To compile this program on Linux: 
//      $CC -std=c++11 a3.cpp 
//      where CC = g++ or clang++
//
// I have not compiled it on windows, but don't see why there would be any issues. Just make 
// sure that C++11 support is turned on. 
//
// There are primarily 2 classes: Graph, and MinimumSpanningTree.
//
// There are 2 examples run from main(), one is a hand-crafted graph to make sure there is sanity. 
// The other example reads 'sampledata.txt' and generates a graph based on the input data.
//
// To get the minimum cost of the MST, call the compute_prim() method first, then get_min_cost(). 
// To get the mimimum spanning tree itself, get_mst() is the correct call which will return a map of nodes and children.  

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

// Maximum number of nodes in a graph
// anonymous namespace is the C++ way to declare static variable in a class.
namespace { 
    const int MAXV = 100; 
}

// Node has the most fundamental information about itself (index) and (cost). 
// Its implicitly associated with a source node to which its connected.
class Node
{ 
    public: 
        Node(const uint32_t index, const uint32_t path_cost):
          idx(index), cost(path_cost) {}

        ~Node() {}

        uint32_t idx; 
        double cost; 
};  

// data structure to hold edge data from one node to another node
// including cost. also has a pointer to the next node in the edgelist
// primarily intended for edgelist information for the graph.
class EdgeNode 
{
    public: 
        EdgeNode(const uint32_t index, const uint32_t c):
            idx(index), cost(c), next(nullptr)
        {}

        uint32_t idx;       // index of the node in the graph
        double cost;        // cost distance of the edge - unsigned int since all positive weights
        EdgeNode* next;     // pointer to the next node in the list
};

// class - Graph 
//
// implementation of a edgelist form for the graph. 
// e.g. consider the graph below with 4 vertices
//      0 -> 1 -> 3 
//      1 -> 2 -> 0 
//      2 -> 1 
//      3 -> 1 
class Graph
{ 
    public: 
        // constructor to setup the graph. 
        // expects user to input the total number of vertices in the graph 
        Graph(const uint32_t num_vertices): 
            nvertices(num_vertices), num_edges(0)
        {
            Initialize(); 
        }

        // construct a graph by reading the edge information from a text file
        Graph(const string& filename); 

        // destructor - empty as there is no dynamically allocated memory
        ~Graph(){}

        // setup the nodelist and the outward degree value for each node to 0. 
        void Initialize() 
        {
            nodelist.resize(MAXV);
            degree.resize(MAXV); 
            fill(nodelist.begin(), nodelist.end(), nullptr); // initialize empty nodelist
            fill(degree.begin(), degree.end(), 0);           // initialize the degree to 0 for each node
        }

        // return total number of vertices in the graph
        int V() const { return nvertices; }      

        // return total number of num_edges in the graph
        int E() const { return num_edges; }          
    
        // print the contents of the graph 
        void print() const;
    
        // create an edge from node x to y
        void add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse);

        // delete an edge from the graph  
        void del(const uint32_t x, const uint32_t y, bool IsReverse);

        // set the value of an edge
        void set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v);

        // get the cost of an edge 
        uint32_t get_edge_value(const uint32_t x, const uint32_t y) const;

        // return a list of neighbors associated with a vertex
        vector<Node> neighbours(const uint32_t x) const; 
           
        // method returns true if x and y are connected by an edge, else false. 
        bool adjacent(const uint32_t x, const uint32_t y);
    
    private:
        // adjacency list for each node in a linked list. 
        vector<EdgeNode*> nodelist; 

        // degree of each node in the graph  
        vector<uint32_t> degree;  
        
        // total number of vertices currently on graph 
        uint32_t nvertices;             
        
        // total number of edges on the graph
        uint32_t num_edges;               
};

// This constructor generates a graph based on edge information in the text file.
// The first entry is always the number of nodes followed by tuples which contain
// the edge information
Graph::Graph(const string& filename) 
{
   Initialize(); 
   ifstream infile(filename);  

   // read in the number of vertices 
   infile >> nvertices; 

   uint32_t s, d, w; 

   // read the source, destination and weight and add it as an edge to the graph
   while (infile >> s >> d >> w) { 
       add(s, d, w, true); 
   } 
}

// method returns true if x and y are connected by an edge, else false. 
bool Graph::adjacent(const uint32_t x, const uint32_t y) 
{ 
    bool ret = false;
    EdgeNode* p = nodelist[x]; 
    
    // iterate through all nodes to find a match
    while (p) { 
       if (p->idx == y) { 
          ret = true; 
          break; 
       }
       p = p->next;  
    }

    return ret; 
} 

// create an edge from node x to y
// this requires to also create a node from y to x since the graph is undirected
void Graph::add(const uint32_t x, const uint32_t y, const uint32_t c, const bool IsReverse)
{ 
    EdgeNode* tmp = new EdgeNode(y, c);         // create a new empty node 
    tmp->next = nodelist[x];                    // insert at the beginning of list
    nodelist[x] = tmp;                          // append the rest of the list 
    degree[x]++;                                // increment the edge degree of node

    // create an edge from y to x as well
    if (!IsReverse) { 
        num_edges++;                                    // increment total edges
        add(y, x, c, true); 
    }
} 

// delete an edge from the graph  
void Graph::del(const uint32_t x, const uint32_t y, bool IsReverse) 
{
    // iterate with two pointers till we find the node 
    // once found, then have the previous node's next point to the 
    // next node.  
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

    // delete the reverse edge as well from y to x
    if (!IsReverse) { 
        del(y, x, true); 
    }
}

// set the cost of an edge based on its two coordinates
void Graph::set_edge_value(const uint32_t x, const uint32_t y, const uint32_t v) 
{
   EdgeNode* p = nodelist[x]; 
  
   // iterate to find the edge from x to y and set the value(cost) correctly 
   while(p) { 
      if (p->idx == y) { 
         p->cost = v; 
         break; 
      }

      p = p->next; 
   }
}

// get the cost of an edge 
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

// return a list of neighbors associated with a vertex
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

// print the contents of a graph
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
 

// implements Minimum Spanning Tree algorithm using Prims' algorithm 
class MinimumSpanningTree
{ 
    public: 
        // constructor takes Graph object reference 
        MinimumSpanningTree(const Graph& g): graph(g), min_cost(0)
        {};

        ~MinimumSpanningTree() {}

        // compute the minimum spanning tree for the given graph. 
        void compute_prims();

        // return the cost of the minimum spanning tree 
        uint32_t get_min_weight() { 
           return min_cost; 
        } 

        // returns the minimum spanning tree
        map<uint32_t, vector<uint32_t>> get_mst() {
            return mst; 
        }

    private: 
        // store the reference to graph object on which to operate
        Graph graph;

        // this is a representation of a minimum spanning tree where the map 
        // has an index to the node and the associated vector represents 
        // children to this node. This is because there is no default 
        // tree representation in C++ STL so using a generic approach to build 
        // a tree. An alternative would be to create a complete NodeTree structure
        // to insert and search nodes, but it would be beyond the scope of this 
        // assignment 
        map<uint32_t, vector<uint32_t>> mst; 

        // the min cost for the minimum spanning tree 
        uint32_t min_cost;

        // max number of children in a graph
        const uint32_t MAXC = 100; 
}; 

void MinimumSpanningTree::compute_prims()
{
    // this struct holds the information for an edge - src, dst, and cost
    struct Edge { 
        Edge(uint32_t s, uint32_t d, uint32_t c): 
            src(s), dst(d), cost(c) {} 

        uint32_t src;
        uint32_t dst; 
        uint32_t cost; 
    }; 

    // setup priority queue to sort items based on cost of the edges
    struct LessThan { 
        bool operator() (const Edge& lhs, const Edge& rhs) const { 
            return lhs.cost > rhs.cost; 
        }
    };

    priority_queue<Edge, vector<Edge>, LessThan> pq; 

    // this tracks if a vertex has been visited or not 
    vector<bool> visited (graph.V(), false); 

    // we start with vertex 0 so mark it visited 
    visited[0] = true; 

    // push all the neighbors of vertex 0 to the priority queue 
    auto neighbors = graph.neighbours(0); 

    for (const auto& x: neighbors) { 
        pq.push(Edge(0, x.idx, x.cost));
    }

    // run till the priority_queue is empty  
    while (!pq.empty()) { 
        
        // priority queue is based on minheap, so the min cost edge is always picked
        Edge e = pq.top();
        pq.pop();

        // if vertex is not visited 
        if (!visited[e.dst]) { 
            // add the cost of the edge to the min cost; 
            min_cost += e.cost;
            // mark the dest node as visited 
            visited[e.dst] = true;  
            // add the node to the minimum spanning tree 
            mst[e.src].push_back(e.dst); 

            vector<Node> nbrs = graph.neighbours(e.dst); 
   
            // add each edge to each neighbor to the priority queue  
            for (auto & neighbor: nbrs) {
                // if the neigbor is already visited, then skip it because its part othe MST.
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
