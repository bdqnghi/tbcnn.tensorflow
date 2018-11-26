#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include <set>
#include <vector>
#include "Graphs/Graphs.h"

/*
===============================================================================
图的深度优先搜索
===============================================================================
*/
class DepthFirstSearch
{
public:
	// 找出图G中，与s连通的所有顶点
	DepthFirstSearch(Graphs const &G, size_t s);

	// v和s是否连通
	bool Marked(size_t v) const;

	// 与s连通的顶点数
	size_t Count() const;

private:
	void DFS(Graphs const &G, size_t v);

private:
	std::vector<bool>	marked_;  ///< 访问标记，访问过就设为true
	size_t				count_;		///< 与s连通的顶点数
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

#endif // DEPTH_FIRST_SEARCH_H
