#include "minimumspanningtree.h"


int MinimumSpanningTree::minCost(std::vector<int> cost, std::vector<bool> isInMST, int verticesNumber)
{
	int min = INT_MAX;
	int minIndex;
	
	for(int i=0; i<verticesNumber; i++)
		if (isInMST[i]==false && cost[i]<min)
		{
			min = cost[i];
			minIndex = i;
		}
 
   return minIndex;
}

bool** MinimumSpanningTree::getMatrix(std::vector<int> constructedMST, int verticesNumber)
{
	bool** matrix = new bool*[verticesNumber];
	for(int i=0; i<verticesNumber; i++)
		matrix[i] = new bool[verticesNumber];

	for(int i=0; i<verticesNumber; i++)
		for(int j=0; j<verticesNumber; j++)
			matrix[i][j] = false;

	for(int i = 1; i<verticesNumber; i++)
		matrix[i][constructedMST[i]] = matrix[constructedMST[i]][i] = true;

	return matrix;
}

bool** MinimumSpanningTree::getMST(Graph* graph)
{
	int verticesNumber = graph->getVerticesNumber();
	int** Matrix = graph->getWeightMatrix();

	std::vector<int> constructedMST(verticesNumber); //przechowuje utworzone drzewo rozpinajace
	std::vector<int> cost(verticesNumber); //wartosci uzywane do wyboru minimalnej wagi
	std::vector<bool> isInMST(verticesNumber); //do sprawdzania czy dany wierzchołek jest już w mst

	for(int i=0; i<verticesNumber; i++)
	{
		cost[i] = INT_MAX;
		isInMST[i] = false;
	}

	/*dodanie pierwszego wierzchołka do mst*/
	cost[0] = 0;
	constructedMST[0] = -1; 

	for(int i=0; i<verticesNumber-1; i++)
	{
		int w = MinimumSpanningTree::minCost(cost, isInMST, verticesNumber);
		isInMST[w] = true;

		for(int v=0; v<verticesNumber; v++)
		{
			if(Matrix[w][v] && isInMST[v] == false && Matrix[w][v] < cost[v])
			{
				constructedMST[v] = w;
				cost[v] = Matrix[w][v];
			}
		}
	}
	return MinimumSpanningTree::getMatrix(constructedMST, verticesNumber);
}