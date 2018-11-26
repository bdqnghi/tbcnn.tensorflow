// ***************************************************************************************************
// Author:			Brandon Olivarez
// Class:			CSCI 3333.02, Spring 2014
// Lab 22:			Graph shortest-path algorithms 
// Date:			4/30/2014
// Comment:			The code here is meant to be revised.
//
//-----------------------------------------------------------------
//
// Description: This program is to implement a generic graph class with  
//				depth-first-search, breadth-first-search and Dijkstra
//				algorithm. A binary min-heap is used. 
// Input file format: The graph data in the input file must follow the 
//				following format:
//			7			=> the first row is the size of the graph
//						=> the following row represent adjacent lsit 
//						   for each node
//			nodeLabel	adjListSize		nodeLabel	weight	nodeLabel	weight nodeLabel	weight
//			0			2				1			2.0		3			1.0
//			1			2				3			3.0		4			10.0
//			2			2				0			4.0		5			5.0
//			3			4				2			2.0		4			2.0		5 8.0		6 4.0
//			4 			1				6			6.0	
//			5			0	
//			6			1				5 1.0
// **************************************************************************************************
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
	/**********************************************************
	 Part A:	Testing graphType class and Dijkstra shortest 
				path algorithm.
				The graph data file is "graphData.txt".
	 **********************************************************/
	ifstream inFile;
	graphType graph; 
	int start, end;  
	//load graph
	inFile.open("graphData.txt"); 
	graph.loadGraph(inFile); 
	inFile.close(); 
	graph.print(); 
	//call Dijkstra shortest path algorithm
	cout<<" Calling Dijkstra shortest path algorithm at starting node 0 ................" <<endl; 
	start = 0; 
	graph.dShortestPath(start); 
	//graph.printShortestPath(4); 
	for (end = 1; end <graph.getSize(); end++)
		graph.printShortestPath(start,end); 
	

	/******************************************************************************
	 Part B:	In my design, each node contains an integer label. Extend this 
				to include some general info. Say, besides an integer label, each 
				node can store a city name of string type. When you implement 
				the breadth-first-search, you shall display the node labels along 
				with city names. use the data file graphCity.txt to test your design.
	 ******************************************************************************/
	//Write your code here
	ifstream myFile;
	graphType graph2;

	myFile.open("GraphCity.txt");
	graph2.loadCityGraph(myFile);
	myFile.close();

	cout << "Performing breadth-first-search" << endl;
	graph2.citybfs(0);
	//complete the program
	return 0; 
}