////////////////////////////////////////////////////////////////////////////////
// Filename:    MinimumSpanningTree.h                                         //
// Author:      Terence Munro (s2587341)                                      //
// Email:       terence.munro@griffithuni.edu.au                              //
// Created:     27/05/2014                                                    //
// Modified:    30/05/2014 (Clarified a few comments)                         //
// Description: Minimum Spanning Tree implementation inherting from the       //
//              templated Graph                                               //
////////////////////////////////////////////////////////////////////////////////

#ifndef MINIMUMSPANNINGTREE_H
#define MINIMUMSPANNINGTREE_H

////////////////////////// INCLUDES ////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Graph.h"

////////////////////////// NAMESPACES //////////////////////////////////////////
using namespace std;

////////////////////////// CLASS DEFINITION ////////////////////////////////////
template <typename Vertex, int size>
class MinimumSpanningTree: public Graph<Vertex, size>
{
public:
    MinimumSpanningTree();              //- Constructor

    void createSpanningGraph(int);      //- Creates the graph and the weight
                                        //  matrix from one of three inputs
                                        //  (calls inherited createGraph)

    void minimumSpanning(Vertex);       //- Create the edges of the minimum
                                        //  spanning tree. The weight of the
                                        //  edges is also saved in the vertex
                                        //  edgeWeights array

    void prims2(Vertex);                //- Same as minimum spanning function
                                        //  except slightly more optimised

    void printTreeAndWeight();          //- Function to output the edges and the
                                        //  weight of the minimum spanning tree

    void clearGraph();                  //- Clears the graph and weightings

protected:
    Vertex source;                      //- Source vertex or root of the tree
    int edges[size];                    //- The minimal edges
    double edgeWeights[size];           //- The weights for the minimal edges
    double weights[size][size];         //- Array of weightings for each edge

    virtual void addEdge(Vertex, Vertex, int); //- Overriding base addEdge to save weights

private:
    Vertex findSmallestWeightedVertex(const bool[]) const; // find non-visited
};

////////////////////////// CLASS FUNCTIONS /////////////////////////////////////

/*******************************************************************************
 * Description:     Add an edge between startVertex and endVertex              *
 * Returns:         NIL                                                        *
 * Parameters:      Vertex start;   Starting point                             *
 *                  Vertex end;     Ending point                               *
 * Preconditions:   NIL                                                        *
 * Postconditions:  Increment edge count and add the edge to the linked list   *
 *                  entry for start vertex, save weight of edge in weights     *
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::addEdge(Vertex start, Vertex end, int weight)
{
    Graph<Vertex, size>::addEdge(start, end, weight);

    if (weight <= 0)
        weight = infinity;

    weights[start][end] = weight;
}

/*******************************************************************************
 * Description:     Default constructor                                        *
 *******************************************************************************/
template <typename Vertex, int size>
MinimumSpanningTree<Vertex, size>::MinimumSpanningTree()
{
    clearGraph();
}

/*******************************************************************************
 * Description:     Clears the graph of all edges, vertices and weights        *
 * Returns:         NIL                                                        *
 * Parameters:      NIL                                                        *
 * Preconditions:   NIL                                                        *
 * Postconditions:  NIL                                                        *
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::clearGraph()
{
    source = 0;
    for (int row = 0; row < size; ++row)
    {
        edges[row] = 0;
        edgeWeights[row] = 0;
        for (int col = 0; col < size; ++col)
            weights[row][col] = infinity;
    }
    Graph<Vertex, size>::clearGraph();
}

/*******************************************************************************
 * Description:     Creates a spanning graph from one of three sources         *
 * Returns:         NIL                                                        *
 * Parameters:      int input;  determines how the graph is created            *
 *                      input > 0: Random edges with input number of vertices  *
 *                      input = 0: Specific case hardcoded from the text book  *
 *                      input < 0: Input read from file named graph.txt        *
 * Preconditions:   size must be larger than input                             *
 * Postconditions:  LinkedList contains nodes populated from inputted source   * 
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::createSpanningGraph(int input)
{
    createGraph(input);
}

/*******************************************************************************
 * Description:     Find the minimum spanning tree starting at source vertex   *
 * Returns:         NIL                                                        *
 * Parameters:      Vertex s;   Source vertex                                  *
 * Preconditions:   NIL                                                        *
 * Postconditions:  Edge list and edgeWeights are populated with the minimum   *
 *                  spanning tree.                                             *
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::minimumSpanning(Vertex s)
{
    int i, j, k;
    double minWeight;
    Vertex startVertex, endVertex;

    source = s;

    bool mstv[size];

    for (j = 0; j < vertexCount; j++)
    {
        mstv[j] = false;
        edges[j] = source;
        edgeWeights[j] = weights[source][j];
    }

    mstv[source] = true;
    edgeWeights[source] = 0;

    for (i = 0; i < vertexCount - 1; i++)
    {
        minWeight = infinity;

        for (j = 0; j < vertexCount; j++)
            if (mstv[j])
                for (k = 0; k < vertexCount; k++)
                    if (!mstv[k] && weights[j][k] < minWeight)
                    {
                        endVertex = k;
                        startVertex = j;
                        minWeight = weights[j][k];
                    }
        mstv[endVertex] = true;
        edges[endVertex] = startVertex;
        edgeWeights[endVertex] = minWeight;
    }
}

/*******************************************************************************
 * Description:     Find the minimum spanning tree starting at source vertex   *
 *                  using an optimised prims algorithm                         *
 * Returns:         NIL                                                        *
 * Parameters:      Vertex s;  Source vertex                                   *
 * Preconditions:   NIL                                                        *
 * Postconditions:  Edge list and edgeWeights are populated with the minimum   *
 *                  spanning tree.                                             *
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::prims2(Vertex s)
{
    bool *visited = new bool[vertexCount];
    source = s;

    //- Initialize data structures
    for (Vertex v = 0; v < vertexCount; v++)
    {
        edgeWeights[v] = weights[s][v];
        edges[v] = s;
        visited[v] = false;
    }

    // Visit the source vertex
    edgeWeights[s] = 0;
    visited[s] = true;

    // Run the algorithm atleast once for every vertex to ensure every vertex,
    //   even disconnected ones, are visited.
    for (int _ = 0; _ < vertexCount; ++_) // (variable is unused so it's named _) 
    {
        // Find the smallest and let it be k
        Vertex k = findSmallestWeightedVertex(visited);

        // No valid edges will return with source which is already visited
        //   so we can safely skip
        if (k == source)
            continue;

        // Visit Vertex k and for every Vertex v
        visited[k] = true;
        for (Vertex v = 0; v < vertexCount; v++)
        {
            // Checking if v hasn't been already visited and
            // if k to v edges weight is smaller than the current
            // edgeWeight stored for v
            if (!visited[v] && weights[k][v] < edgeWeights[v])
            {
                edges[v] = k;
                edgeWeights[v] = weights[k][v];
            }
        }
    }

    delete[] visited;
}

/*******************************************************************************
 * Description:     Prints the minimum spanning tree of the graph along with   *
 *                  the weights of edges and combined tree weight              *
 * Returns:         NIL                                                        *
 * Parameters:      NIL                                                        *
 * Preconditions:   NIL                                                        *
 * Postconditions:  NIL                                                        *
 *******************************************************************************/
template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::printTreeAndWeight()
{
    double treeWeight = 0;

    cout << fixed << showpoint << setprecision(2);

    cout << "Source Vertex: " << source << endl << endl;
    cout << "  Edges\t\tWeight" << endl;
    cout << "  =====\t\t======" << endl;

    for (Vertex j = 0; j < vertexCount; j++)
    {
        if (edges[j] != j)
        {
            if (edgeWeights[j] < infinity)
                treeWeight = treeWeight + edgeWeights[j];
            
            // Print the edge (extra space padding for single digit)
            cout << "(" << (edges[j] < 10 ? " " : "") << edges[j] << ", "
                << (j < 10 ? " " : "") << j << ")";

            // Separate with a tab
            cout << "\t";

            // Print the weight
            if (edgeWeights[j] == infinity) // replace infinity with i
                cout << " i";               //- if its infinity its probably
            else // print weight padded for single
                cout << (edgeWeights[j] < 10 ? " " : "") << edgeWeights[j];
            cout << endl;
        }
    }

    cout << endl;
    cout << "Tree Weight:\t\t" << treeWeight << endl;
    cout << "Number of vertices:\t" << vertexCount << endl;
    cout << "Number of edges:\t" << edgeCount << endl;
}

/*******************************************************************************
 * Description:     Find the vertex with the smallest weight that hasn't been  *
 *                  already visited.                                           *
 * Returns:         (Vertex) Unvisted vertex with smallest weight              *
 * Parameters:      bool const visited[];   array of visited vertexes          *
 * Preconditions:   source, edgeWeights and visited are initialized            *
 * Postconditions:  NIL                                                        *
 *******************************************************************************/
template <typename Vertex, int size>
Vertex MinimumSpanningTree<Vertex, size>::findSmallestWeightedVertex(const bool visited[]) const
{
    Vertex k = source;
    double minWeight = infinity;

    for (Vertex v = source; v < vertexCount; ++v)
        if (!visited[v] && edgeWeights[v] < minWeight)
        {
            k = v;
            minWeight = edgeWeights[v];
        }

    return k;
}

#endif