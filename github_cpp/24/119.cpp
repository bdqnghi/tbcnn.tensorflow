//============================================================================
// Name        : Minimum spanning tree.cpp
// Version     : 1.0
// Created on  : May 16, 2017
/* Description :
 * The idea of Minimum spanning tree is to only make the 
 * minimum weight path between all Nodes in the Graph to be 
 * able to communicate with each other with min cost
 * hope it will be useful 
 */
//============================================================================
#include <iostream>
#include <stdio.h>
using namespace std;

#define dim 7		//dimension of the Graph =no.of nodes
#define inf 99		//assume infinity=99

int weight[dim][dim] =
{ { 0, 3, inf, inf, inf, inf, 5 },
{ 3, 0, 2, inf, inf, inf, 5 },
{ inf, 2, 0, 7, 1, 1, 3 },
{ inf, inf, 7, 0, 6, 7, inf },
{ inf, inf, 1, 6, 0, 4, inf },
{ inf, inf, 1, 7, 4, 0, 8 },
{ 5, 5, 3, inf, inf, 8, 0 } };

void print_matrix(int array[dim][dim])
{
	int r, c;		//r:Row , c:Column
	for (c = 0; c < dim; c++)	cout << "\t" << c;
	cout << "\n";
	for (r = 0; r < dim; r++)
	{
		cout << "\n" << r << "\t";
		for (c = 0; c < dim; c++)
			if (array[r][c] == inf)		
				cout << "#\t";
			else
				cout << array[r][c] << "\t";
	}
	cout << "\n";
}

int main(void)
{
	int z[dim], min_span[dim][dim];
	int min, rmin, cmin,r,c;
	int total_weight=0;			//The total cost of the final graph
	int group=0;				//group of nodes

	print_matrix(weight);		//print original matrix
	// create intial spanning tree  matrix with all values = inf
	// except of the diagonal =0
	for (r = 0; r < dim; r++)
	{
		for (c = 0; c < dim; c++)
		{
			if (r == c)	
				min_span[r][c] = 0;
			else
				min_span[r][c] = inf;
		}
			
	}
	// Create intial array that indicate the node position
	// if -1 then node is outside else it's inside	
	for (r = 0; r < dim; r++)
	{
	  z[r] = -1;
	}
	while (1)
	{
		min = inf;
		//Search for the two nodes with the least cost
		for (r = 0; r < dim; r++)
		{
			for (c = 0; c < r; c++)
			{
				if (min > weight[r][c])
				{
					rmin = r; cmin = c; min = weight[r][c];
				}
			}
						
		}
		if (min==inf) 
			break;
		cout << "\nUpdated Minimum spanning tree ="<<endl;
		print_matrix(min_span);
		cout << "\nrmin= " << rmin << "\t cmin = " << cmin << "\t min = " << min << "\n";
		cout << "position array z:"<<endl;
		for (r = 0; r < dim; r++)
			cout << "\t" << r << "\t" << z[r] <<endl;

		if ((z[rmin] != z[cmin]) || (z[rmin] == -1) || (z[cmin] == -1))
		{	
			//update min_span matrix by putting the cost between the rmin and cmin in it
			min_span[rmin][cmin] = min_span[cmin][rmin] = min;
					
			total_weight += min;		//totalcost=totalcost+min
			//Node position Cases:-			
			if ((z[rmin] == -1) && (z[cmin] == -1))
			{
				//1-both node outside
				group++; 
				z[rmin] = z[cmin] = group;	//both enter 
			}
			else if ((z[rmin] == -1) && (z[cmin] != -1))
			{	
				//2-row node outside and the column node inside
				z[rmin] = z[cmin];	//the outside one enter
			}	
			else if ((z[cmin] == -1) && (z[rmin] != -1))
			{
				//3-column node outside and the row node inside
				z[cmin] = z[rmin];	//the outside one enter
			}
			else    //z[rmin] != -1 && z[cmin] != -1 && z[rmin] != z[cmin]
			{
				//4-All node inside but not in the same group
				int temp = z[cmin];		
				//make all nodes in the same group
				for (int i = 0; i < dim; i++)
					if (z[i] == temp) z[i] = z[rmin];
			}
		}
		weight[rmin][cmin] = inf;		//delete the cost from the original matrix
	}
	//print final updated matrix
	cout << "\nFinal Minimum spanning tree ="<<endl;
	print_matrix(min_span);
	//Print total cost
	cout << "\nMinimum Total Weight =" << total_weight << endl;
	return 0;
}
