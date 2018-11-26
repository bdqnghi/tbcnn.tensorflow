/*
 * Search.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#include "SearchDerived.h"

DepthFirstSearch::DepthFirstSearch(map2d<char>::type mapOriginal_):Search(mapOriginal_){
}

DepthFirstSearch::~DepthFirstSearch(){
}

node DepthFirstSearch::conductSearch()
{
	//Note: check for goal when selecting node for expansion

	//initialize state
	startCoord = findChar(startChar);
	node rootNode;
	rootNode.coord = startCoord;
	rootNode.coord.c = 'S';
	rootNode.pathLength = 0;
	rootNode.pathCost = 0;
	
	frontier.push(rootNode);
	markAsExplored(rootNode);

	while(!frontier.empty())
	{
		//Select node for expansion
		node currNode = frontier.top();
		frontier.pop();
		markAsFrontier(currNode);

		totalNodesExamined += 1;
		if(isGoal(currNode))
		{
			goalNode = currNode;
			return currNode;
		}
		markAsExplored(currNode);

		//Generate children nodes
		std::vector<node> childrenVec = generateChildrenNodes(currNode);
		for(int k = childrenVec.size()-1; k>=0;k--)
		{
			//Push child to frontier
			if(isNotExploredNode(childrenVec.at(k)) && isNotInFrontier(childrenVec.at(k)))
			{
				frontier.push(childrenVec.at(k));
				markAsFrontier(childrenVec.at(k));
			}
		}
		markAsNotFrontier(currNode);
	}
	node resultNode;
	return resultNode;
}
