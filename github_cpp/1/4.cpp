

























#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <cstdlib>
#include <ctime>
#include "graphType.h"	

using namespace std; 

int main()
{
	
	ifstream inFile;
	graphType graph; 
	int start, end;  
	
	inFile.open("graphData.txt"); 
	graph.loadGraph(inFile); 
	inFile.close(); 
	graph.print(); 
	
	cout<<" Calling Dijkstra shortest path algorithm at starting node 0 ................" <<endl; 
	start = 0; 
	graph.dShortestPath(start); 
	
	for (end = 1; end <graph.getSize(); end++)
		graph.printShortestPath(start,end); 
	

	
	
	ifstream myFile;
	graphType graph2;

	myFile.open("GraphCity.txt");
	graph2.loadCityGraph(myFile);
	myFile.close();

	cout << "Performing breadth-first-search" << endl;
	graph2.citybfs(0);
	
	return 0; 
}