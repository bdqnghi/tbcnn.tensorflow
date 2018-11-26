// Author	: Kaylee Gabus
// Date		: 5-1-17
// Minimum Spanning Tree.cpp : Defines the entry point for the console application.
	//builds the minimum spanning tree for a graph using both Kruskal's and Prim's algorithms
	//outputs the tree as an alphabetized list of verticies and their weights
	//requires input in the form of number of verticies, vertex names, adjacency matrix


#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Kruskal.h"
#include "Prim.h"

using namespace std;

string filePath = "C:\\Users\\Kaylee\\Desktop\\mst test.txt";			//<--------------------------------------------------------------------set file path here


int main()
{	//reads in the number of nodes to instantiate the two algoriths objects
	//reads in the vertex names and stores in a single dimentional array
	//reads in the adjacency matrix as a single dimentional array
		//items are accessed as row index * number of nodes + column index
	double inputDouble;
	string currentInput;

	ifstream inFile(filePath, ios::binary);
	if (inFile.fail())
	{	//if the file is unable to be read, notify user and close the program
		cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		cin >> currentInput;
		exit(1);
	}

	inFile >> currentInput;
	inputDouble = atoi(currentInput.c_str());		//convert the first thing in the file to a number

	//instantiate the arrays and objects 
	int nValue = inputDouble;
	double* adjMatrix = new double[nValue * nValue];		
	string* nodeNamesMatrix = new string[nValue];

	Kruskal KrsukalAlgorithm(nValue);			
	Prim PrimAlgorithm(nValue);

	for (int pos = 0; pos < nValue; pos++)
	{	//read in the names of the nodes and put them in the names array
		inFile >> nodeNamesMatrix[pos];
	}

	for (int pos = 0; pos < (nValue * nValue); pos++)
	{	//read in the adjancy matrix
		inFile >> currentInput;
		inputDouble = atof(currentInput.c_str());		//convert text to double
		adjMatrix[pos] = inputDouble;
	}

//	KrsukalAlgorithm.runKruskal(nodeNamesMatrix, adjMatrix);
	PrimAlgorithm.runPrim(nodeNamesMatrix, adjMatrix);

    return 0;
}

