#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <set>
#include <vector>
#include "Graphs/Graphs.h"


class DepthFirstSearch
{
public:
	
	DepthFirstSearch(Graphs const &G, size_t s);

	
	bool Marked(size_t v) const;

	
	size_t Count() const;

private:
	void DFS(Graphs const &G, size_t v);

private:
	std::vector<bool>	marked_;  
	size_t				count_;		
};



inline DepthFirstSearch::DepthFirstSearch(Graphs const &G, size_t s)
{
	marked_.resize(G.V(), false);
	DFS(G, s);
}


inline void DepthFirstSearch::DFS(Graphs const &G, size_t v)
{
	marked_[v] = true;
	++count_;
	for (auto w : G.Adj(v)) {
		if (!marked_[w]) { 
			DFS(G, w);
		}
	}
}


inline bool DepthFirstSearch::Marked(size_t v) const
{
	return marked_[v];
}


inline size_t DepthFirstSearch::Count() const
{
	return count_;
}

#endif 
