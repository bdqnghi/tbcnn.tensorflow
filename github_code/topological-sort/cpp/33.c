/*
 * TopologicalSort.h
 *
 *  Created on: Jul 8, 2013
 *      Author: Avinash
 */
//
// Testing Status
//
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <functional>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <hash_map>
#include <stack>
#include <queue>
#include <limits.h>

using namespace std;
using namespace __gnu_cxx;

#define null NULL
#define PRINT_NEW_LINE printf("\n")
//int main(){
//	return -1;
//}

#ifndef TOPOLOGICALSORT_H_
#define TOPOLOGICALSORT_H_

struct adjacencyListDS{
	int adjacentVertex;
	int edgeName;
};

void GiveVerticesInTopologicalSort(vector<vector<adjacencyListDS>> adjacencyList,int source,vector<int> &arrivalTimes,vector<int> &departureTimes,vector<int> &topologicalSort){
	if(adjacencyList.size() == 0){
		return null;
	}
	static int timeCounter = -1;
	vector<adjacencyListDS> currentNodeNeighbours;
	currentNodeNeighbours = adjacencyList[source];
	for(int neighbourCounter = 0;neighbourCounter < currentNodeNeighbours.size();neighbourCounter++){
		if(arrivalTimes[adjacencyList[source][neighbourCounter]] == -1){
			arrivalTimes[adjacencyList[source][neighbourCounter]] = ++timeCounter;
			GiveVerticesInTopologicalSort(adjacencyList,adjacencyList[source][neighbourCounter],arrivalTimes,departureTimes,topologicalSort);
		}
	}
	departureTimes[source] = ++timeCounter;
	topologicalSort.push_back(source);
}

#endif /* TOPOLOGICALSORT_H_ */
