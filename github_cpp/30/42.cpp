#include "dijkstra.h"
#include "graph.h"
#include "iostream"


Dijkstra::Dijkstra(){}
Dijkstra::Dijkstra(Graph &_g )
{
    this->graph = &_g;
}

//Initizialition
void Dijkstra::init(){
    for (int i=0; i <= this->graph->_V(); ++i){
        this->distances[i] = INF; //Initiate all distances with valor infinte.
        this->visited[i] = false; // Initiate all vertexs as no visited.
        this->previus[i] = -1; // Initiate the previus of vertex i with -1
    }
}




//Function of relaxation
void Dijkstra::relaxation(int current, int adjacent, int weight){
    //If the distance of source to current vertex + weight is least to the distance of the source to adjacent vertex.
    if (distances[current] +  weight < distances[adjacent]){
        distances[adjacent] = distances[current] + weight; // Relax the vertex update the distance.
        previus[adjacent] = current; // Update the previus vertex.
        Q.push(Router (adjacent, distances[adjacent])); // Add the adjacent to the priority_queue
    }
}

void Dijkstra::dijkstra_algorithm(int initial, int destination, double &average, int &count){
    init(); // Initiate the array.
    Q.push(Router (initial,0)); // Insert the vertex initial to the priority_queue
    distances[initial] = 0; // Initialise the distance of initial as 0.
    int current , adjacent , weight;
    while(!Q.empty()) { // While the queue is not empty.
        current = Q.top().first; // Get of the queue a router with least cost, in begin will be the initial.
        Q.pop(); // Pop out the element of the queue.
        if (visited[current]) continue; //If the router current was visited, then continue removing routers of the queue.
        visited[current] = true; //Put the current as visited.
        for (unsigned int i=0; i < this->graph->Adj()[current].size(); ++i){ // Review the adjacencies of the vertex current.
            adjacent = this->graph->Adj()[current][i].first; // Id of the vertex adjacent.
            weight = this->graph->Adj()[current][i].second; // Weight of the edge that join the current with adjacent(current, adjacent)
            if(!visited[adjacent]){
                relaxation(current, adjacent, weight); // Make it the pass of relaxation.
            }
        }
    }

    std::cout << "Distances more short starting in node " << initial << std::endl;
    for( int i = 0 ; i <= this->graph->_V() ; ++i ){
        if (distances[i] == 0 || distances[i] == 1073741824) continue;
        std::cout << "Node " << i << " : distance more short = " << distances[i] << std::endl;
    }
    std::cout << "\nPath more short...." << std::endl;
    std::cout << "Node destination: " << destination << std::endl;

    average += static_cast<double>(distances[destination]);
    count++; //Amount of iterations.
    //cout << "Paths traveled: " << count <<" | Total sum of short paths: " << average << " | Average: " << static_cast<double>(average/count) << endl;
    //graph->neighbors(destination);
    //print( destination );
    graph->neighbors(destination,initial,this->previus);
    std::cout<<std::endl;
}

Graph Dijkstra::getGraph()
{
    return *this->graph;
}
