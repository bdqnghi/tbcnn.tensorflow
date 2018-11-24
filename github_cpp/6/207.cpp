#include<iostream>
#include<stdlib.h>
#include<limits.h>
#include<stdio.h>
using namespace std;
struct container
{   
	int source, finalpos, cost;
};

void MinDistanceFromSource(const container edge_list[], int number_of_edges, int minimum_cost_array[], int number_of_vertices, int origin_vertex)
 {
    for(int i=0; i<number_of_vertices; i++)
        minimum_cost_array[i]=INT_MAX;

    minimum_cost_array[origin_vertex]=0;
    for(int i=0; i<number_of_vertices; i++) {
        for(int j=0; j<number_of_edges; j++) {
            if(minimum_cost_array[edge_list[j].source]+edge_list[j].cost<minimum_cost_array[edge_list[j].finalpos])
                minimum_cost_array[edge_list[j].finalpos]=minimum_cost_array[edge_list[j].source]+edge_list[j].cost;
        }
    }
	// to recognize negative cycles
    for(int i=0; i<number_of_edges; i++) {
        if(minimum_cost_array[edge_list[i].source]+edge_list[i].cost<minimum_cost_array[edge_list[i].finalpos]) {
            cout<<"Negative cycle present"<<endl;
        }
    }
}

void PrintResult(int number_of_vertices,int minimum_cost_array[])
	{
	
    cout<<"Vertex"<<" Cost For Vertex"<<endl;
    for(int i=0; i<number_of_vertices; i++) {
        cout<<i<<"   "<<minimum_cost_array[i]<<endl;
    }

}
int main()
{

int number_of_vertices,number_of_edges;

cout<<"Please enter the number of vertices and edges"<<endl;
cin>>number_of_vertices;
cin>>number_of_edges; 
int origin_vertex;
cout<<"enter the starting vertex"<<endl;
cin >>origin_vertex;
container edge_list[number_of_edges];
int minimum_cost_array[number_of_vertices];
for(int i=0; i<number_of_edges; i++)
	{
        cin>> edge_list[i].source >> edge_list[i].finalpos >> edge_list[i].cost;
    }

    MinDistanceFromSource(edge_list,number_of_edges,minimum_cost_array,number_of_vertices, origin_vertex);
	
	PrintResult(number_of_vertices,minimum_cost_array);
    return 0;
}

