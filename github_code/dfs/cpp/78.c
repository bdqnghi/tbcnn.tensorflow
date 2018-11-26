/*
 * DepthFirstSearch.h
 *
 *  Created on: Apr 6, 2016
 *      Author: vibhanshu
 */

#ifndef DEPTHFIRSTSEARCH_H_
#define DEPTHFIRSTSEARCH_H_
#include"Graph.h"
class DepthFirstSearch {
private:
	bool *marked ;
	std::size_t count;
	void dfs(const Graph &, std::size_t ) ;  // Depth first Search from given source vertex
public:
	DepthFirstSearch(const Graph& , std::size_t );
	virtual ~DepthFirstSearch();
	std::size_t Count() { return count;}  // return number of vertices connected to the source vertex
	bool Marked(const std::size_t &v) { return marked[v];}   // used to check whether there is a path between the source vertex and the vertex
};

#endif /* DEPTHFIRSTSEARCH_H_ */
