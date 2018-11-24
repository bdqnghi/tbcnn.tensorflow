#include "topological-sort.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <streambuf>
#include <sstream>

// IMPLEMENTATIONS OF THE TOPOLOGICAL SORTING
std::vector <unsigned int> topologicalSort (Graph dag) {
  // check whether the given matrix can be an adjacency matrix
  if (dag.cols() != dag.rows())
    throw std::invalid_argument ("Adjacency matrix is not quadratic and therefor not valid.");
  
  // if the matrix is empty, it is considered to be a valid DAG and an empty list is
  // returned
  if (dag.isEmpty())
    return std::vector <unsigned int> ();
  
  // list which will contain the sorted vertex-indices
  std::vector <unsigned int> L;

  // set of vertices with no incomming edges
  std::set <unsigned int> S;
  for (unsigned int n = 0; n < dag.rows(); n++)
    if (! hasIncommingEdges (dag, n))
      S.insert (n);
    
  while (! S.empty()) {
    // NOTE: The sorting is not unique. The strategy of removing the vertices from 
    //       S is determining the order of the sorting.
    auto n = *S.begin();
    L.push_back (n);
    // remove n from S
    S.erase (S.begin());
    
    // check the adjacency-row for the current vertex    
    for (unsigned int m = 0; m < dag.cols(); m++) {
      // check whether there is an egde e from n to m
      if (dag(n, m) != 0) {
        // delete edge e from DAG
        dag(n, m) = 0;
        // check whether m has incomming edges
        if (! hasIncommingEdges (dag, m))
          S.insert (m);
      }
    }
  }
  
  // if the graph still has edges, there has been a cycle
  if (hasDAGEdges (dag))
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph");
  
  return L;
}

std::vector <unsigned int> topologicalSortAdjList (GraphAdjList posDag, GraphAdjList negDag) {
  // if the matrix is empty, it is considered to be a valid DAG and an empty list is
  // returned
  if (posDag.isEmpty())
    return std::vector <unsigned int> ();
  
  // list which will contain the sorted vertex-indices
  std::vector <unsigned int> L;
  
  // set of vertices with no incoming edges
  std::set <unsigned int> S;
  for (size_t sourceNodeId = 0; sourceNodeId < negDag.nNodes(); sourceNodeId++)
    if (negDag[sourceNodeId].empty())
      // O(n log n), with n is the size of the set
      S.insert (sourceNodeId);
    
  while (! S.empty()) {
    // NOTE: The sorting is not unique. The strategy of removing the vertices from 
    //       S is determining the order of the sorting.
    auto n = *S.begin();
    L.push_back (n);
    // remove n from S
    // O(1) 
    S.erase (S.begin());
    
    // get the adjacency list for the current vertex and delete all edges from n to m
    while (! posDag[n].empty()) {
      // delete n as precondition (incoming edge) from m
      negDag.deleteEdge (Edge (posDag[n].front(), n));
      // check whether m has still incoming edges
      if (negDag[posDag[n].front()].empty())
        // O(log n), with n is the size of the set
        S.insert (posDag[n].front());
      // delete edge e from DAG
      posDag[n].pop_front();
    }
  }
  
  // if the graph still has edges, there has been a cycle
  if (! posDag.isEmpty())
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph");
  
  return L;    
}

std::vector <unsigned int> topologicalSortAdjList2 (GraphAdjList posDag, GraphAdjList negDag) {
  // if the matrix is empty, it is considered to be a valid DAG and an empty list is
  // returned
  if (posDag.isEmpty())
    return std::vector <unsigned int> ();
  
  // list which will contain the sorted vertex-indices
  std::vector <unsigned int> L;
  
  // set of vertices with no incoming edges
  std::set <unsigned int> S;
  for (size_t sourceNodeId = 0; sourceNodeId < negDag.nNodes(); sourceNodeId++)
    if (negDag[sourceNodeId].empty())
      // O(n log n), with n is the size of the set
      S.insert (sourceNodeId);
    
  while (! S.empty()) {
    // NOTE: The sorting is not unique. The strategy of removing the vertices from 
    //       S is determining the order of the sorting.
    auto n = *S.begin();
    L.push_back (n);
    // remove n from S
    // O(1) 
    S.erase (S.begin());
    
    // get the adjacency list for the current vertex and delete all edges from n to m
    while (! posDag[n].empty()) {
      // delete n as precondition (incoming edge) from m
      negDag[posDag[n].front()].pop_front();
      // check whether m has still incoming edges
      if (negDag[posDag[n].front()].empty())
        // O(log n), with n is the size of the set
        S.insert (posDag[n].front());
      // delete edge e from DAG
      posDag[n].pop_front();
    }
  }
  
  // if the graph still has edges, there has been a cycle
  if (! posDag.isEmpty())
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph");
  
  return L;    
}

std::vector <unsigned int> topologicalSortAdjList3 (GraphAdjList dag) {
  // if the matrix is empty, it is considered to be a valid DAG and an empty list is
  // returned
  if (dag.isEmpty())
    return std::vector <unsigned int> ();
  
  auto inDegree = getInDegree (dag);
  
  // list which will contain the sorted vertex-indices
  std::vector <unsigned int> L (dag.nNodes());
  unsigned int nodeCounter = 0;
  
  // set of vertices with no incoming edges
  std::stack <unsigned int> S;
  for (size_t nodeId = 0; nodeId < dag.nNodes(); nodeId++)
    if (inDegree[nodeId] == 0)
      S.push (nodeId);
  
  while (! S.empty()) {
    auto n = S.top();
    S.pop();
    
    L[nodeCounter++] = n;
    
    // get the adjacency list for the current vertex and delete all edges from n to m
    while (! dag[n].empty()) {
      // delete n as precondition (incoming edge) from m
      inDegree[dag[n].front()]--;
      // check whether m has still incoming edges
      if (inDegree[dag[n].front()] == 0)
        S.push (dag[n].front());
      // delete edge e from DAG
      dag[n].pop_front();
    }
  }
  
  // if the graph still has edges, there has been a cycle
  if (! dag.isEmpty())
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph");
  
  return L;    
}

std::vector <unsigned int> topologicalSortCormanAdjList (GraphAdjList posDag) {
  if (posDag.isEmpty())
    return std::vector <unsigned int> ();
  
  // vector which will contain the sorted vertex-indices
  std::vector <unsigned int> L;
  
  unsigned int nodeIds [posDag.nNodes()];
  std::iota (nodeIds, nodeIds + posDag.nNodes(), 0);
  std::set <unsigned int> unmarkedNodes (nodeIds, nodeIds + posDag.nNodes());
  
  while (! unmarkedNodes.empty()) {
    auto sourceNodeId = *(unmarkedNodes.rbegin());
    visit (sourceNodeId, posDag, L, unmarkedNodes);
  }
  
  std::reverse (L.begin(), L.end());
  return L;
}

std::vector <unsigned int> topologicalSortCormanAdjList2 (const GraphAdjList & posDag) {
  if (posDag.isEmpty())
    return std::vector <unsigned int> ();
  
  // vector which will contain the sorted vertex-indices
  std::vector <unsigned int> L (posDag.nNodes());
  unsigned int nodeCounter = 0;
  
  std::vector <NodeColor> nodeColors (posDag.nNodes(), NodeColor::UNMARKED);
  
  std::iota (L.begin(), L.end(), 0);
  std::set <unsigned int> unmarkedNodes (L.begin(), L.end());
  
  while (! unmarkedNodes.empty()) {
    auto sourceNodeId = *(unmarkedNodes.rbegin());
    visit2 (sourceNodeId, posDag, L, unmarkedNodes, nodeCounter, nodeColors);
  }
  
  std::reverse (L.begin(), L.end());
  return L;
}

// HELPER FUNCTION FOR THE SORTING ALGORITHMS
bool hasIncommingEdges (const Graph & dag, unsigned int vertexInd) {
  for (unsigned int sourceVertexId = 0; sourceVertexId < dag.rows(); sourceVertexId++) 
    if (dag(sourceVertexId, vertexInd) != 0) 
      return true;
    
    return false;
}

bool hasDAGEdges (const Graph & dag) {
  for (unsigned int i = 0; i < dag.rows(); i++) for (unsigned int j = 0; j < dag.cols(); j++)
    if (dag(i, j) != 0) 
      return true;
    
    return false;
}

std::vector <unsigned int> getInDegree (const GraphAdjList & dag) {
  std::vector <unsigned int> inDegree (dag.nNodes(), 0);
  
  for (size_t sourceNodeId = 0; sourceNodeId < dag.nNodes(); sourceNodeId++)
    for (auto targetNodeId : dag[sourceNodeId])
      inDegree[targetNodeId]++;
    
    return inDegree;
}

void visit (const unsigned int sourceNodeId, GraphAdjList & posDag, std::vector <unsigned int> & L, std::set <unsigned int> & unmarkedNodes) {
  if (posDag.getNodeColor(sourceNodeId) == NodeColor::TEMPORARILY_MARKED)
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph"); 
  
  if (posDag.getNodeColor(sourceNodeId) == NodeColor::UNMARKED) {
    posDag.setNodeColor(sourceNodeId, NodeColor::TEMPORARILY_MARKED);
    
    for (auto targetNodeId : posDag[sourceNodeId])
      visit (targetNodeId, posDag, L, unmarkedNodes);
    
    posDag.setNodeColor(sourceNodeId, NodeColor::PERMANENTLY_MARKED);
    L.push_back(sourceNodeId);
    unmarkedNodes.erase (sourceNodeId);
  }
}

void visit2 (const unsigned int sourceNodeId, const GraphAdjList & posDag, std::vector <unsigned int> & L, std::set <unsigned int> & unmarkedNodes, unsigned int & nodeCounter, std::vector <NodeColor> & nodeColors) {
  if (nodeColors[sourceNodeId] == NodeColor::TEMPORARILY_MARKED)
    throw std::invalid_argument ("The given graph is not (D)irected (A)cyclic (G)raph"); 
  
  if (nodeColors[sourceNodeId] == NodeColor::UNMARKED) {
    nodeColors[sourceNodeId] = NodeColor::TEMPORARILY_MARKED;
    
    for (auto targetNodeId : posDag[sourceNodeId])
      visit2 (targetNodeId, posDag, L, unmarkedNodes, nodeCounter, nodeColors);
    
    nodeColors[sourceNodeId] = NodeColor::PERMANENTLY_MARKED;
    L[nodeCounter++] = sourceNodeId;
    unmarkedNodes.erase (sourceNodeId);
  }
}

// FUNCTIONS TO CHECK A GIVEN TOPOLOGICAL SORTING FOR CORRECTNESS
bool checkTopologicalSorting (const std::vector <unsigned int> & topologicalSorting, Graph dag) {
  // check whether the given matrix can be an adjacency matrix
  if (dag.cols() != dag.rows())
    throw std::invalid_argument ("Adjacency matrix is not quadratic and therefor not valid.");
  
  // check whether the sorting contain enought nodes
  if (dag.rows() != topologicalSorting.size())
    throw std::invalid_argument ("The topological sorting and the matrix does not fit considering there dimension");
  
  for (auto node = topologicalSorting.begin(); node != topologicalSorting.end(); ++node) {
    // if there are incomming edges there are preconditions, which has not been done 
    if (hasIncommingEdges (dag, *node)) 
      return false;
    
    // delete the current not from all the not done preconditions
    for (unsigned int i = 0; i < dag.cols(); i++)
      dag (*node, i) = 0;
  }
  
  return true;
}

bool checkTopologicalSorting (const std::vector <unsigned int> & topologicalSorting, const GraphAdjList & dag) {
  // check whether the sorting contain enough nodes
  if (dag.nNodes() != topologicalSorting.size())
    throw std::invalid_argument ("The topological sorting and the adjacency list does not fit considering there dimension");
  
  auto negDag = mapFromPosIndecencyToNegIndecency (dag);
  
  for (auto node = topologicalSorting.begin(); node != topologicalSorting.end(); ++node) {
    // If a node has incoming edged, than there are preconditions (other nodes), which has not been done (deleted) till now.
    if (! negDag[*node].empty())
      return false;
    
    // Delete the current node to indicate, that it is now precondition anymore. To do this, all incoming edges outgoing from the current node has to be deleted.
    for (unsigned int preconditionNodeId = 0; preconditionNodeId < negDag.nNodes(); preconditionNodeId++) {
      negDag.deleteEdge (Edge (preconditionNodeId, *node));
    }
  }
  
  return true;
}

// FUNCTIONS TO READ GRAPHS FROM FILES AND CREATE REPRESENTATIONS TO PROCESS THEM
std::vector <Edge> readEdgesFromFile (const std::string & filename) {
  std::ifstream inFile (filename);
  if (! inFile) 
    throw std::invalid_argument ("Cannot open file: " + filename);

  std::vector <Edge> edges; 
  unsigned int sourceNodeId, targetNodeId;
  // NOTE: >> uses WHITESPACE and NEWLINE as delimiters 
  while (inFile >> sourceNodeId >> targetNodeId) {
    edges.push_back (Edge (sourceNodeId, targetNodeId));
    
//     std::cout << "add edge to graph:" << std::endl
//               << "(" << edges.back().first << ")"
//               << " --> "
//               << "(" << edges.back().second << ")"
//               << std::endl;
  }
    
  inFile.close();
  
  return edges;
}

void readEdgesFromFile (const std::string & filename, std::vector <Edge> & posEdges, std::vector <Edge> & negEdges) {
  std::ifstream inFile (filename);
  if (! inFile) 
    throw std::invalid_argument ("Cannot open file: " + filename);
  
  unsigned int sourceNodeId, targetNodeId;
  while (inFile >> sourceNodeId >> targetNodeId) {
    posEdges.push_back (Edge (sourceNodeId, targetNodeId));
    negEdges.push_back (Edge (targetNodeId, sourceNodeId));
  }
  
  inFile.close();
}

Graph createGraphFromEdges (const std::vector <Edge> & edges) {
  if (edges.size() < 1)
    return Graph();
  
  auto maxNodeId = getMaxNodeId (edges);
  
  // initialize a empty graph
  // NOTE: a node can have id 0
  Graph graph (maxNodeId + 1, maxNodeId + 1, false);
  
  std::for_each (edges.begin(), edges.end(), [&graph](Edge e) {
    graph(e.first, e.second) = 1;
  });
  
  return graph;
}

GraphAdjList createGraphAdjListFromEdges (const std::vector <Edge> & edges) {
  if (edges.size() < 1)
    return GraphAdjList();
  
  auto maxNodeId = getMaxNodeId (edges);
  
  // initialize a empty graph
  // NOTE: a node can have id 0
  GraphAdjList graph (maxNodeId + 1);
  
  std::for_each (edges.begin(), edges.end(), [&graph](Edge e) {
    graph.insertEdge (e, false);
  });
  
  return graph;
}

GraphAdjList mapFromPosIndecencyToNegIndecency (const GraphAdjList & posIndecencyGraph) {
  if (posIndecencyGraph.isEmpty())
    return GraphAdjList();
  
  GraphAdjList negIndecencyGraph (posIndecencyGraph.nNodes());
  for (unsigned int sourceNodeId = 0; sourceNodeId < posIndecencyGraph.nNodes(); sourceNodeId++) {
    if (posIndecencyGraph[sourceNodeId].empty())
      continue;
    
    auto bgn = posIndecencyGraph[sourceNodeId].begin();
    auto end = posIndecencyGraph[sourceNodeId].end();
    
    for (auto targetNode = bgn; targetNode != end; ++targetNode)
      negIndecencyGraph.insertEdge (Edge (*targetNode, sourceNodeId));
  }
  
  return negIndecencyGraph;
}

unsigned int getMaxNodeId (const std::vector <Edge> edges) {
  unsigned int maxNodeId = 0;
  for (auto & edge : edges)
    maxNodeId = std::max (maxNodeId, std::max (edge.first, edge.second));
  return maxNodeId;
}




