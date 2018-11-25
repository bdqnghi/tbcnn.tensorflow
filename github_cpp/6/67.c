












#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;






struct vertex
{
    char value;
    int visited;
    int popCount;
    int pushCount;
    int componentStart;  
    vector<int> adjacentVertices; 
};






void DFS(vector<vertex> &graph);







int dfs(vertex &V, vector<vertex> &graph, int &pushCount, int &popCount);






void readAdjacencyMatrixFile(vector<vertex> &graph1, vector<vertex> &graph2);





void printGraph(vector<vertex> &graph);





bool newComponent(int i, vector<vertex> graph);





void updatePushAndPopOrdering(vector<vertex> graph);


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
                
            }
            vertex input_vertex =  {letter_value, 0, 0, 0, 0, graphVertex};
            graph2.push_back(input_vertex);
        }
    }
    cout << "\n" << endl;
    infile.close();
}







void DFS(vector<vertex> &graph)
{
    int pushCount = 0;
    int popCount = 0;

    for (int i = 0; i < graph.size(); i++) 
    {
        if( graph[i].visited == 0 )
        {
            graph[i].componentStart = 1;
            popCount = dfs(graph[i], graph, pushCount, popCount);
            popCount++;
            graph[i].popCount = popCount;
            pop_ordering.push_back(graph[i].value);
        }
    }
}








int dfs(vertex &aVertex, vector<vertex> &graph, int &pushCount, int &popCount)
{
    pushCount = pushCount + 1;
    aVertex.pushCount = pushCount;  
    push_ordering.push_back(aVertex.value);
    aVertex.visited = 1;        

    int numAdjacentVertices = 0;
    for(int i = 0; i < aVertex.adjacentVertices.size(); i++)
    {
        if (aVertex.adjacentVertices[i] == 1) 
        {
            numAdjacentVertices++;
            if (graph[i].visited == 0) 
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






void updatePushAndPopOrdering(vector<vertex> graph)
{
    for (int i = 0; i < graph.size(); i++)
    {
        pop_ordering.pop_back();
        push_ordering.pop_back(); 
    }
}


