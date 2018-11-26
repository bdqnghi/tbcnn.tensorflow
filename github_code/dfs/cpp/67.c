//@file depthfirstsearch.cpp
//@author Miranda Myers (mmyers4)
//@author Sarah Prata
//@date 3/6/15

//Program accomplishes the following:
// * Reads adjacency matrices representing graphs from a file int.dat in a specified format
//      The file contains information for two graphs, one connected, one with 3 components
// * Uses the adjacency matrices to perform depth first search on each graph
// * Prints the number of connected components, which vertices are in each connected
//      component with its push and pop orderings


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


//A structure that defines a vertex
//Contains 6 items, a value, whether the vertex is visited, pop and push counts,
//  whether the vertex is the start of a new component, and a vector of its adjacent
//  vertices
struct vertex
{
    char value;
    int visited;
    int popCount;
    int pushCount;
    int componentStart;  //Flag whether or not the vertex is the start of a new component
    vector<int> adjacentVertices; //Keeps track of the vertices adjacent to the vertex
};

// Implements a depth-first search traversal of a given graph
//  Keeps track of the number of components in the graph
//@pre A graph in the format of a vector of vertices exists
//@post The graph is updated according to the traversal with push and pop counts
//@usage DFS(graph)
void DFS(vector<vertex> &graph);

// Visits recursively all the unvisited vertices connected to a given vertex
//  by a path and numbers them in the order they are encountered,
//  Keeps track of push and pop count
//@pre a vertex and graph in the correct format exist, variables pushCount and popCount exist
//@post Variables aVertex, graph, pushCount, popCount are updated according to the traversal
//@usage dfs(aVertex, graph, pushCount, popCount)
int dfs(vertex &V, vector<vertex> &graph, int &pushCount, int &popCount);

// Reads two adjacency matrices from a file in5.dat
//@pre the file in5.dat exists and is in the correct format, two graph variables exist
//@post the matrices are read into the passed in graph structures, each in the format of 
//      a vector of vertices where each vertex is a struct, defined above
//@usage readAdjacencyMatrixFile(graph1, graph2)
void readAdjacencyMatrixFile(vector<vertex> &graph1, vector<vertex> &graph2);

// Prints the push order, pop order, and number of connected components of each graph
//@pre A graph in the format of a vector of vertices exists
//@post Prints the graph push order, pop order, and number of components
//@usage printGraph(graph)
void printGraph(vector<vertex> &graph);

// Determines when a new component of the graph is reached
//@pre A graph in the format of a vector of vertices exists
//@post Returns true if new component, false otherwise
//@usage newComponent(i, graph)
bool newComponent(int i, vector<vertex> graph);

// Updates push and pop ordering to be clear for next graph to be read
//@pre a graph exists
//@post pop and push ordering are cleared
//@usage updatePushAndPopOrdering(graph)
void updatePushAndPopOrdering(vector<vertex> graph);

// Global variables used to keep track of the push and pop ordering of vertices
vector<char> pop_ordering;
vector<char> push_ordering;

int main()
{
    vector<vertex> graph, graph2;
    readAdjacencyMatrixFile(graph, graph2);

    DFS(graph);
    printGraph(graph);

    updatePushAndPopOrdering(graph);

    DFS(graph2);
    printGraph(graph2);
    return(0);
}


// Reads two adjacency matrices from a file in5.dat
//@pre the file in5.dat exists and is in the correct format, two graph variables exist
//@post the matrices are read into the passed in graph structures, each in the format of 
//      a vector of vertices where each vertex is a struct, defined above
//@usage readAdjacencyMatrixFile(graph1, graph2)
void readAdjacencyMatrixFile(vector<vertex> &graph1, vector<vertex> &graph2)
{
    ifstream infile;
    int NumPoints;
    infile.open ("in5.dat");
    vector<vertex> graphVertex;
    if (infile.is_open())
    {
        string random;
        int NumPoints = 10;

        getline(infile, random);
        char letter_value;
        for(int i = 0; i < NumPoints; i++)
        {
            vector<int> graphVertex;
            int placement;
            infile >> letter_value;
            for(int j = 0; j < NumPoints; j++)
            {
                infile >> placement;
                graphVertex.push_back(placement);
                ///infile >> pointVector[i].x;
                //v1.push_back(0);
            }
            vertex input_vertex =  {letter_value, 0, 0, 0, 0, graphVertex};
            graph1.push_back(input_vertex);
        }
        getline(infile, random);
        getline(infile, random);
        getline(infile, random);
        NumPoints += 2;
        for(int i = 0; i < NumPoints; i++)
        {
            vector<int> graphVertex;
            int placement;
            infile >> letter_value;
            for(int j = 0; j < NumPoints; j++)
            {
                infile >> placement;
                graphVertex.push_back(placement);
                ///infile >> pointVector[i].x;
            }
            vertex input_vertex =  {letter_value, 0, 0, 0, 0, graphVertex};
            graph2.push_back(input_vertex);
        }
    }
    cout << "\n" << endl;
    infile.close();
}


// Implements a depth-first search traversal of a given graph
//  Keeps track of the number of components in the graph
//@pre A graph in the format of a vector of vertices exists
//@post The graph is updated according to the traversal with push and pop counts
//@usage DFS(graph)
void DFS(vector<vertex> &graph)
{
    int pushCount = 0;
    int popCount = 0;

    for (int i = 0; i < graph.size(); i++) //each vertex in the graph do
    {
        if( graph[i].visited == 0 )//v is marked with 0
        {
            graph[i].componentStart = 1;//componentStart; //Mark the vertex as the start of a component
            popCount = dfs(graph[i], graph, pushCount, popCount);
            popCount++;
            graph[i].popCount = popCount;
            pop_ordering.push_back(graph[i].value);
        }
    }
}


// Visits recursively all the unvisited vertices connected to a given vertex
//  by a path and numbers them in the order they are encountered,
//  Keeps track of push and pop count
//@pre a vertex and graph in the correct format exist, variables pushCount and popCount exist
//@post Variables aVertex, graph, pushCount, popCount are updated according to the traversal
//@usage dfs(aVertex, graph, pushCount, popCount)
int dfs(vertex &aVertex, vector<vertex> &graph, int &pushCount, int &popCount)
{
    pushCount = pushCount + 1;
    aVertex.pushCount = pushCount;  //mark V with count
    push_ordering.push_back(aVertex.value);
    aVertex.visited = 1;        //mark V as visited

    int numAdjacentVertices = 0;
    for(int i = 0; i < aVertex.adjacentVertices.size(); i++)
    {
        if (aVertex.adjacentVertices[i] == 1) //Check if adjacent
        {
            numAdjacentVertices++;
            if (graph[i].visited == 0) //Check if visited
            {
                dfs(graph[i], graph, pushCount, popCount);
                popCount = popCount + 1;
                graph[i].popCount = popCount;
                pop_ordering.push_back(graph[i].value);
            }
        }
    }
    return popCount;
}


// Determines when a new component of the graph is reached
//@pre A graph in the format of a vector of vertices exists
//@post Returns true if new component, false otherwise
//@usage newComponent(i, graph)
bool newComponent(int i, vector<vertex> graph)
{
    for(int j = 0; j < graph.size(); j++)
    {
        if((graph[j].value == push_ordering[i]) && (graph[j].componentStart == 1)){
            return true;
        }
    }
    return false;
}


// Prints the push order, pop order, and number of connected components of each graph
//@pre A graph in the format of a vector of vertices exists
//@post Prints the graph push order, pop order, and number of components
//@usage printGraph(graph)
void printGraph(vector<vertex> &graph)
{
    int counter = 0;
    int start = 0;
    int numberComponents = 0;
    while(counter < push_ordering.size())
    {
        if(newComponent(counter, graph))
        {
            cout << "\n\nconnected component\n" << endl <<"\tpush ordering: ";
            numberComponents++;
        }
        cout << push_ordering[counter] << ",";
        counter++;
        if(newComponent(counter, graph) || counter == push_ordering.size())
        {
            cout << "\n\tpop ordering:  ";
            for(int i = start; i < counter; i++)
            {
                cout << pop_ordering[i] << ",";
            }
            start = counter;
        }
    }
    
    cout << endl << endl << numberComponents << " connected component(s)";
    cout << endl << endl << endl;
}


// Updates push and pop ordering to be clear for next graph to be read
//@pre a graph exists
//@post pop and push ordering are cleared
//@usage updatePushAndPopOrdering(graph)
void updatePushAndPopOrdering(vector<vertex> graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        pop_ordering.pop_back();
        push_ordering.pop_back(); 
    }
}


