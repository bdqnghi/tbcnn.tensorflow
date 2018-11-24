// Author	: Kaylee Gabus
// Date		: 5-1-17
// Kruskal.cpp	: Uses Kruskal's algorithm to find the minimum spanning tree of a graph given an array of node names and an adjacency matrix.

#include "stdafx.h"
#include "Kruskal.h"
#include <iostream>

using namespace std;

Kruskal::Kruskal(int size)
{
	arrayDim = size;

	setArray = new string[arrayDim];
	edgeArray = new Edge[arrayDim * arrayDim];
	outputArray = new string[arrayDim];
}

void Kruskal::runKruskal(string* nameArray, double* adjArray)
{	//runs the Kruskal algorithm and outputs results to the console
	string vertex1 = "";
	string vertex2 = "";

	int v1SetIndex;
	int v2SetIndex;

	for (int pos = 0; pos < arrayDim; pos++)				//make a set for every vertex
		makeAndAddSet(nameArray[pos]);		

	int numberOfEdges = createSortedEdgeArray(adjArray);	//sort the edges by weight
	for (int pos = 0; pos < numberOfEdges; pos++)
	{	//for every edge, check to see if it's vertex has been added to a set
		//if the verticies are not in the same set, take the union of the sets
		//also keeps an ongoing sum of the total weight of the graph
		vertex1 = edgeArray[pos].vertex1;
		vertex2 = edgeArray[pos].vertex2;

		v1SetIndex = searchSets(vertex1);
		v2SetIndex = searchSets(vertex2);

		if (v1SetIndex != v2SetIndex)
		{
			unionSets(v1SetIndex, v2SetIndex);
			addToOutputArray(edgeArray[pos]);
			pathSum += edgeArray[pos].weight;
		}
	}

	sortOutputArray();

	cout << "Total Path Weights' Sum: " << pathSum << endl;
	for (int pos = 0; pos <= outputArrayIndex; pos++)
		cout << outputArray[pos] << endl;
}

void Kruskal::makeAndAddSet(string insertString)
{	//creates a set containing the passed in value and adds it to the set array
	//sets are implemented as strings
	//seperates set elements with a comma
	setArray[itemsInSetArray + 1] = "," + insertString + ",";
	itemsInSetArray++;
}

int Kruskal::searchSets(string searchString)
{	//locates the index indicating the set that contains the search term
	//returns -1 if the term is not found
	//the commas ensure the index of AB isn't returned when looking for A or B
	string searchTerm = searchString;
	size_t location;
	for (int pos = itemsInSetArray; pos >= 0; pos--)
	{
		location = setArray[pos].find(searchTerm);
		if (location != std::string::npos)				//if the string is found in the set, return the index of the set
			return pos;	
	}

	return -1;			//if the string was not found, return -1
}

void Kruskal::unionSets(int set1, int set2)
{	//takes the union of two sets and places it in the lower indexed spot in the set array
	//everything beneath the higher set index is moved up on spot and decrements count of array items
	//set1 and set2 are the index of the respective sets
	if (set1 < set2)
	{
		setArray[set1] += setArray[set2];

		for (int pos = set2; pos < itemsInSetArray; pos++)
			setArray[pos] = setArray[pos + 1];
	}
	else
	{
		setArray[set2] += setArray[set1];

		for (int pos = set1; pos < itemsInSetArray; pos++)
			setArray[pos] = setArray[pos + 1];
	}
	
	itemsInSetArray--;
}

int Kruskal::createSortedEdgeArray(double * adjArray)
{	//generates the array of edges for the adjacancy array
	//only reads the bottom left half of adjArray
	//only has non 0 edges
	//sorted in ascending order
	//returns the number of non 0 edges
	int edgesInArray = 0;

	for (int row = 0; row < arrayDim; row++)
	{
		for (int col = 0; col < row; col++)
		{	//for every non zero item in adjArray, create an edge and store it in edgeArray
			Edge newEdge;
			newEdge.vertex1 = setArray[row];
			newEdge.vertex2 = setArray[col];
			newEdge.weight = adjArray[(arrayDim * row) + col];

			if (newEdge.weight > 0)
			{	//only write the edges that are non-zero
				edgeArray[edgesInArray] = newEdge;
				edgesInArray++;
			}
		}
	}
		
	for (int loop = 0; loop < edgesInArray - 1; loop++)
	{	//bubble sort the edges to get them in ascending order according to weight
		for (int pos = 0; pos < edgesInArray - 1; pos++)
		{	//sort the edges in ascending order
			if (edgeArray[pos].weight > 0)
			{	//if the weight isn't 0
				if (edgeArray[pos].weight > edgeArray[pos + 1].weight)
				{	//swap the two edges
					Edge edge = edgeArray[pos];

					edgeArray[pos].vertex1 = edgeArray[pos + 1].vertex1;
					edgeArray[pos].vertex2 = edgeArray[pos + 1].vertex2;
					edgeArray[pos].weight = edgeArray[pos + 1].weight;

					edgeArray[pos + 1] = edge;
				}
			}
		}
	}
	
	return edgesInArray;
}

void Kruskal::addToOutputArray(Edge node)
{	//formats the output for the algorithm
	//output strings are of the form "x-y	n" where x and y are node names and n is the weight between them
	string node1 = node.vertex1.substr(1, node.vertex1.length() - 2);
	string node2 = node.vertex2.substr(1, node.vertex2.length() - 2);
	string outputString;

	if (node1 < node2)
		outputString = node1 + "-" + node2 + "\t";
	else outputString = node2 + "-" + node1 + "\t";

	outputArray[outputArrayIndex] = outputString + to_string(node.weight);
	outputArrayIndex++;
}

void Kruskal::sortOutputArray()	
{	//uses bubble sort to alphabeticaly sort the output strings		
	string swapString;
	for (int loop = 0; loop < outputArrayIndex - 1; loop++)
		for (int pos = 0; pos < outputArrayIndex - 1; pos++)
			if (outputArray[pos] > outputArray[pos + 1])
			{
				swapString = outputArray[pos];
				outputArray[pos] = outputArray[pos + 1];
				outputArray[pos + 1] = swapString;
			}
}
