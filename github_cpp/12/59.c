









#ifndef MINIMUMSPANNINGTREE_H
#define MINIMUMSPANNINGTREE_H


#include <iostream>
#include <fstream>
#include <iomanip>
#include "Graph.h"


using namespace std;


template <typename Vertex, int size>
class MinimumSpanningTree: public Graph<Vertex, size>
{
public:
    MinimumSpanningTree();              

    void createSpanningGraph(int);      
                                        
                                        

    void minimumSpanning(Vertex);       
                                        
                                        
                                        

    void prims2(Vertex);                
                                        

    void printTreeAndWeight();          
                                        

    void clearGraph();                  

protected:
    Vertex source;                      
    int edges[size];                    
    double edgeWeights[size];           
    double weights[size][size];         

    virtual void addEdge(Vertex, Vertex, int); 

private:
    Vertex findSmallestWeightedVertex(const bool[]) const; 
};




template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::addEdge(Vertex start, Vertex end, int weight)
{
    Graph<Vertex, size>::addEdge(start, end, weight);

    if (weight <= 0)
        weight = infinity;

    weights[start][end] = weight;
}


template <typename Vertex, int size>
MinimumSpanningTree<Vertex, size>::MinimumSpanningTree()
{
    clearGraph();
}


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


template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::createSpanningGraph(int input)
{
    createGraph(input);
}


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


template <typename Vertex, int size>
void MinimumSpanningTree<Vertex, size>::prims2(Vertex s)
{
    bool *visited = new bool[vertexCount];
    source = s;

    
    for (Vertex v = 0; v < vertexCount; v++)
    {
        edgeWeights[v] = weights[s][v];
        edges[v] = s;
        visited[v] = false;
    }

    
    edgeWeights[s] = 0;
    visited[s] = true;

    
    
    for (int _ = 0; _ < vertexCount; ++_) 
    {
        
        Vertex k = findSmallestWeightedVertex(visited);

        
        
        if (k == source)
            continue;

        
        visited[k] = true;
        for (Vertex v = 0; v < vertexCount; v++)
        {
            
            
            
            if (!visited[v] && weights[k][v] < edgeWeights[v])
            {
                edges[v] = k;
                edgeWeights[v] = weights[k][v];
            }
        }
    }

    delete[] visited;
}


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
            
            
            cout << "(" << (edges[j] < 10 ? " " : "") << edges[j] << ", "
                << (j < 10 ? " " : "") << j << ")";

            
            cout << "\t";

            
            if (edgeWeights[j] == infinity) 
                cout << " i";               
            else 
                cout << (edgeWeights[j] < 10 ? " " : "") << edgeWeights[j];
            cout << endl;
        }
    }

    cout << endl;
    cout << "Tree Weight:\t\t" << treeWeight << endl;
    cout << "Number of vertices:\t" << vertexCount << endl;
    cout << "Number of edges:\t" << edgeCount << endl;
}


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