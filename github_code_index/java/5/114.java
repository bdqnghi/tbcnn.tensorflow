Thus depending on the representation these operations can have different complexities. In case that we’re using adjacency matrix we have:

    Adding an edge – O(1);
    Deleting an edge – O(1);
    Answering the question “is there an edge between i and j” – O(1);
    Finding the successors of a given vertex – O(n);
    Finding (if exists) a path between two vertices – O(n2);

While for an adjacency list we can have:

    Adding an edge – O(log(n));
    Deleting an edge – O(log(n));
    Answering the question “is there an edge between i and j” – O(log(n));
    Finding the successors of a given vertex – O(k), where “k” is the length of the lists containing the successors of i;
    Finding (if exists) a path between two vertices – O(n+m) – where m <= n;


    =========================

    Java Universal Network/Graph Framework

    SCM Repositories - jung


    About JGraphT

JGraphT is a free Java graph library that provides mathematical graph-theory objects and algorithms. JGraphT supports various types of graphs including:

    directed and undirected graphs.
    graphs with weighted / unweighted / labeled or any user-defined edges.
    various edge multiplicity options, including: simple-graphs, multigraphs, pseudographs.
    unmodifiable graphs - allow modules to provide "read-only" access to internal graphs.
    listenable graphs - allow external listeners to track modification events.
    subgraphs graphs that are auto-updating subgraph views on other graphs.
    all compositions of above graphs.

Although powerful, JGraphT is designed to be simple and type-safe (via Java generics). For example, graph vertices can be of any objects. You can create graphs based on: Strings, URLs, XML documents, etc; you can even create graphs of graphs!
    

In a graph database such a task is a typical path finding task. It is solved using algorithms built into the system. For example in Neo4j: http://neo4j.com/docs/stable/rest-api-graph-algos.html

When you find the shortest path between persons you can easily calculate number of edges (hops in terms of your question) between them.

Graph databases has a great advantage in such kind of tasks over relational or key-value databases as they can use effective graph algorithms such as Dijkstra's algorithm.


AdjacencyLists: A Graph as a Collection of Lists 

int n;
    List<Integer>[] adj;
    AdjacencyLists(int n0) {
        n = n0;
        adj = (List<Integer>[])new List[n];
        for (int i = 0; i < n; i++) 
            adj[i] = new ArrayStack<Integer>(Integer.class);
    }


void addEdge(int i, int j) {
        adj[i].add(j);
    }

     void removeEdge(int i, int j) {
        Iterator<Integer> it = adj[i].iterator();
        while (it.hasNext()) {
            if (it.next() == j) {
                it.remove();
                return;
            }
        }    
    }


    This takes $ O(\deg(\ensuremath{i}}))$ time, where $ \deg(\ensuremath{i}})$ (the degree of $i}) counts the number of edges in $ E$ that have $i} as their source. 


    boolean hasEdge(int i, int j) {
        return adj[i].contains(j);
    }


    List<Integer> outEdges(int i) {
        return adj[i];
    }


    he inEdges(i) operation is much more work. It scans over every vertex $ j$ checking if the edge (i,j) exists and, if so, adding j to the output list:

    List<Integer> inEdges(int i) {
        List<Integer> edges = new ArrayStack<Integer>(Integer.class);
        for (int j = 0; j < n; j++)
            if (adj[j].contains(i))    edges.add(j);
        return edges;
    }


This operation is very slow. It scans the adjacency list of every vertex, so it takes n}} +m}})$ time. 

The space used by a AdjacencyLists is n}}+\ensuremath{m}})$.



AdjacencyMatrix:

int n;
    boolean[][] a;
    AdjacencyMatrix(int n0) {
        n = n0;
        a = new boolean[n][n];
    }

    void addEdge(int i, int j) {
        a[i][j] = true;
    }
    void removeEdge(int i, int j) {
        a[i][j] = false;
    }
    boolean hasEdge(int i, int j) {
        return a[i][j];
    }

    Where the adjacency matrix performs poorly is with the outEdges(i) and inEdges(i) operations. To implement these, we must scan all n entries in the corresponding row or column of a and gather up all the indices, j, where a[i][j], respectively a[j][i], is true. 


    List<Integer> outEdges(int i) {
        List<Integer> edges = new ArrayList<Integer>();
        for (int j = 0; j < n; j++) 
            if (a[i][j]) edges.add(j);
        return edges;
    }
    List<Integer> inEdges(int i) {
        List<Integer> edges = new ArrayList<Integer>();
        for (int j = 0; j < n; j++)
            if (a[j][i]) edges.add(j);
        return edges;
    }

    These operations clearly take n}})$ time per operation. 

     In particular, when the graph $ G$ is dense, i.e., it has close to $n}}^2$ edges, then a memory usage of $n}}^2$ may be acceptable.

The AdjacencyMatrix data structure is also commonly used because algebraic operations on the matrix a can be used to efficiently compute properties of the graph $ G$.


 void bfs(Graph g, int r) {
        boolean[] seen = new boolean[g.nVertices()];
        Queue<Integer> q = new SLList<Integer>();
        q.add(r);
        seen[r] = true;
        while (!q.isEmpty()) {
            int i = q.remove();
            for (Integer j : g.outEdges(i)) {
                if (!seen[j]) {
                    q.add(j);
                    seen[j] = true;
                }
            }
        }
    }

    Analyzing the running-time of the bfs(g,i) routine is fairly straightforward. The use of the seen array ensures that no vertex is added to q more than once. Adding (and later removing) each vertex from q takes constant time per vertex for a total of n}})$ time. Since each vertex is processed by the inner loop at most once, each adjacency list is processed at most once, so each edge of $ G$ is processed at most once. This processing, which is done in the inner loop takes constant time per iteration, for a total of m}})$ time. Therefore, the entire algorithm runs in n}}+\ensuremath{m}})$ time. 

    Thus, the bfs(g,r) method visits vertices in increasing order of distance from r and vertices that cannot be reached from r are never visited at all. 


    A particularly useful application of the breadth-first-search algorithm is, therefore, in computing shortest paths.


   
    Depth-First Search

The depth-first-search algorithm is similar to the standard algorithm for traversing binary trees; it first fully explores one subtree before returning to the current node and then exploring the other subtree. Another way to think of depth-first-search is by saying that it is similar to breadth-first search except that it uses a stack instead of a queue. 


 During the execution of the depth-first-search algorithm, each vertex, i, is assigned a colour, c[i]: white if we have never seen the vertex before, grey if we are currently visiting that vertex, and black if we are done visiting that vertex. The easiest way to think of depth-first-search is as a recursive algorithm. It starts by visiting r. When visiting a vertex i, we first mark i as grey. Next, we scan " i's " adjacency list and recursively visit any white vertex we find in this list. Finally, we are done processing i, so we colour i black and return.


    void dfs(Graph g, int r) {
        byte[] c = new byte[g.nVertices()];
        dfs(g, r, c);
    }
    void dfs(Graph g, int i, byte[] c) {
        c[i] = grey;  // currently visiting i
        for (Integer j : g.outEdges(i)) {
            if (c[j] == white) {
                c[j] = grey;
                dfs(g, j, c);
            } 
        }
        c[i] = black; // done visiting i
    }


 Although depth-first-search may best be thought of as a recursive algorithm, recursion is not the best way to implement it. Indeed, the code given above will fail for many large graphs by causing a stack overflow. An alternative implementation is to replace the recursion stack with an explicit stack, s. The following implementation does just that:

    void dfs2(Graph g, int r) {
        byte[] c = new byte[g.nVertices()];
        Stack<Integer> s = new Stack<Integer>();
        s.push(r);
        while (!s.isEmpty()) {
            int i = s.pop();
            if (c[i] == white) {
                c[i] = grey;
                for (int j : g.outEdges(i))
                    s.push(j);
            }
        }
    }


 When given as input a Graph, g, that is implemented using the AdjacencyLists data structure, the dfs(g,r) and dfs2(g,r) algorithms each run in $ O(m+n})$ time.

 An important property of the depth-first-search algorithm is the following: Suppose that when node $ i is coloured $ grey, there exists a path from i to some other node j that uses only white vertices. Then j will be coloured first grey then black before i  is coloured $ black. (This can be proven by contradiction, by considering any path $ P$ from i  to j)

One application of this property is the detection of cycles. Refer to Figure 12.6. Consider some cycle, $ C$, that can be reached from r. Let i be the first node of $ C$ that is coloured grey, and let j be the node that precedes i on the cycle $ C$. Then, by the above property, j will be coloured grey and the edge (j,i) will be considered by the algorithm while i is still grey. Thus, the algorithm can conclude that there is a path, $ P$, from i to j in the depth-first-search tree and the edge (j,i) exists. Therefore, $ P$ is also a cycle. 

 We say that a graph $ G$ is strongly-connected if, for every pair of vertices $ i}$ and $ j}$ in $ G$, there is a path from $i to j. Show how to test if $ G$ is strongly-connected in (n+m) time.


Given a graph $ G=(V,E)$ and some special vertex $ \ensuremath{\mathtt{r}}\in V$, show how to compute the length of the shortest path from $ \ensuremath{\mathtt{r}}$ to $ \mathtt{i}$ for every vertex $ \ensuremath{\mathtt{i}}\in V$.


 A universal sink in a graph $ G$ is a vertex that is the target of $ \ensuremath{\mathtt{n}}-1$ edges and the source of no edges.12.1 Design and implement an algorithm that tests if a graph $ G$, represented as an AdjacencyMatrix, has a universal sink. Your algorithm should run in $ O(\ensuremath{\mathtt{n}})$ time.

============================================
Graph Sink Detection

O(N) algo ..

 for each vertex v:
      v.might_be_sink := true

    for each vertex v:

      if v.might_be_sink:
        for each other vertex w:
          if v -> w:
            give up on v and try next candidate
          else:
            w.might_be_sink := false

          if w -> v:
            w.might_be_sink := false
          else:
            give up on v and try next candidate

      hooray! v is a sink.

      ========================================================

      O(n + m) Algo. which is O(n) if m is O(n). 

      The best I can think of is O(n + m) which is O(n) if m is O(n).

Assuming a sink exists, do a topological sort of the graph. The minimal node in the sort is a sink. Note that topological sort is O(n + m).

====================================================
      O(V) algo :

      //pseudo code
    //M -> adjacency matrix

      int a=0
      for(int i=1;i<vertices;++i)
      {
          if(M[a,i]) a=i;
      }

        //check that a is sink by reading out 2V entries from the matrix
      return a; //if a is a sink, otherwise -1

==========================================================================

Finding Universal Sink

  Is-Sink(A, k)
  1   let A be |V|×|V|
  2   for j = 1 to |V|
  3      if akj == 1
  4         return FALSE
  5   for i = 1 to |V|
  6      if aik == 1 and i ≠ k
  7         return FALSE
  8   return TRUE
        

        Universal-Sink(A)
  1   let A be |V|×|V|
  2   i = j = 1
  3   while i≤|V| and j≤|V|
  4      if aij == 1
  5          i = i + 1
  6      else
              j = j + 1
  7   if i > |V|
  8      return “no universal sink”
  9   elsif Is-Sink(A,i) == FALSE
 10      return “no universal sink”
 11  else
           return i “is a universal sink”

====================================================================



      In o(v) :

      int graph::containsUniversalSink() {
/****************************************************************
 Returns: Universal Sink, or -1 if it doesn't exist
 Paramters: Expects an adjacency-matrix to exist called matrix
****************************************************************/

//a universal sink is a Vertex with in-degree |V|-1 and out-degree 0
//a vertex in a graph represented as an adjacency-matrix is a universal sink
//if and only if its row is all 0s and its column is all 1s except the [i,i] entry - path to itself (hence out-degree |V|-1)
//for i=0..|V|-1, j=0..|V|-1
//if m[i][j]==0 then j is not universal sink (unless i==j) - column is not all 1s
//if m[i][j]==1 then i is not universal sink - row is not all 0s
int i=0,j=1;
while (i<numVertices && j<numVertices) {
    if (j>i && matrix[i][j]==true) {
        //we found a 1, disqualifying vertex i, and we're not in the last row (j>i) so we move to that row to see if it's all 0s
        i=j;
        if (j<numVertices-1) {
            //if the row we're moving to is not the last row
            //we want to start checking from one element after the identity element
            //to avoid the possibility of an infinite loop
            j++;
        }
        continue;
    }
    if (j==numVertices-1 && matrix[i][j]==false) {
        //the last element in a row is a 0
        //thus this is the only possible universal sink
        //we have checked the row for 0s from i+1 (or i if we're in the last row) to numVertices-1 (inclusive)
        //we need to check from 0 to i (inclusive)
        for (j=0; j<i+1; j++) {
            if (matrix[i][j]==true || (matrix[j][i]==false && i!=j)) {
                //this row is not all 0s, or this column is not all 1s so return -1 (false)
                return -1;
            }
        }

        //row is all 0s, but we don't know that column is all 1s
        //because we have only checked the column from 0 to i (inclusive), so if i<numVertices-1
        //there could be a 0 in the column
        //so we need to check from i+1 to numVertices-1 (inclusive)
        for (j=i+1; j<numVertices; j++) {
            if (matrix[j][i]==false) {
                return -1;
            }
        }
        //if we get here we have a universal sink, return it
        return i;
    }
    j++;
}

//if we exit the loop there is no universal sink
return -1;


/********************
*/
 Runtime Analysis
 The while loop will execute at most |V| times: j is incremented by 1 on every iteration
 If we reach the end of a row - this can only happen once - then the first for loop will
 execute i times and the second will execute numVertices-i times, for a combined numVertices iterations
 So we have 2|V| loop executions for a run-time bound of O(|V|)



======================================================





*/
Theorem (Parenthesis Theorem) In any depth-first search of a directed or undirected graph G = (V,E), for any two vertices u and v, exactly one of the following three conditions holds:

    The intervals [u.d, u.f] and [v.d, v.f] are entirely disjoint; or
    The interval [u.d, u.f] is contained entirely in [v.d, v.f], and u is a descendant of v in a depth-first tree; or
    The interval [v.d, v.f] is contained entirely in [u.d, u.f], and v is a descendant of u in a depth-first tree.



DFS: Four Types of Edges

    Tree edges: Part of the depth-first forest
    Back edges: (u.v) connecting u to an ancestor, v, of u
    Forward edges: Non-tree edge (u,v) connecting u to a descendant, b, of u
    Cross edges: All other edges


 Theorem In depth-first search of an undirected graph every edge is either a tree edge or a back edge.

Claim An undirected graph is cyclic if an only if there exist back edges after a depth-first search of the graph. 



Note that all paths in a directed acyclic graph are necessarily simple (by virtue of acyclicity). 

Finding all possible paths is a hard problem, since there are exponential number of simple paths. Even finding the kth shortest path [or longest path] are NP-Hard.

Find all Paths Between Two Given Nodes :
This I tackled previously when working on the design and implementation of routing optimization algorithms for telecommunications networks. 

A simple modification of DFS will compute this given as

def dfs(u, t):
    if u == t:
        return 1
    else:
        if not u.npaths:
            # assume sum returns 0 if u has no children
            u.npaths = sum(dfs(c, t) for c in u.children)
        return u.npaths
  
    
I assume your graph is a DAG (otherwise there is no point on talking about topological sort, nor about number of paths, there could be infinite number of those)




It can be done using Dynamic Programming and topological sort as follows:

Topological sort the vertices, let the ordered vertices be v1,v2,...,vn
create new array of size t, let it be arr
init: arr[t] = 1
for i from t-1 to 1 (descending, inclusive):
    arr[i] = 0  
    for each edge (v_i,v_j) such that i < j <= t:
         arr[i] += arr[j]

When you are done, for each i in [1,t], arr[i] indicates the number of paths from vi to vt

Now, proving the above claim is easy (comparing to your algorithm, which I have no idea if its correct and how to prove it), it is done by induction:

Base: arr[t] == 1, and indeed there is a single path from t to t, the empty one.
Hypothesis: The claim is true for each k in range m < k <= t
Proof: We need to show the claim is correct for m.
"Let's" look at each out edge from vm: (v_m,v_i).
Thus, the number of paths to vt starting from v_m that use this edge (v_m,v_i). is exactly arr[i] (induction hypothesis). Summing all possibilities of out edges from v_m, gives us the total number of paths from v_m to v_t - and this is exactly what the algorithm do.
Thus, arr[m] = #paths from v_m to v_t

QED

Time complexity:
The first step (topological sort) takes O(V+E).
The loop iterate all edges once, and all vertices once, so it is O(V+E) as well.
This gives us total complexity of O(V+E)


 



===================
Give an algorithm that determines whether or not a give undirected graph G = (V,E) contains cycle in O(|V|) time.

An undirected graph is acyclic (i.e., a forest) iff a DFS yields no back edges.

Since back edges are those edges (u,v) connecting a vertexu
to an ancestor v in a depth-first tree, so no back edges means there are only tree 
edges,so there is no cycle.

So we can simply fun DFS. If find a back edge, there is a cycle. The complexity is  O(V) instead ofO(E+V). Since if there is a back edge, it mustbe found before seeing|V|distinct edges. This is because in a acyclic (undi-rected ) forest,|E|≤|V|+ 1
=====================

Grsph file saved in browser..good question on graphs...






