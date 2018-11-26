/*
		Author		:		Sreejith Sreekantan
		Description	:		Topological Sort algorithm implementation
*/

#ifndef __TOPOLOGICALSORT_H__
#define __TOPOLOGICALSORT_H__

#include "EdgeWeightedDigraph.h"
#include <memory>
#include <vector>
#include <stack>

namespace graph
{

class TopologicalSort
{
public:
	TopologicalSort(std::shared_ptr<EdgeWeightedDigraph> graph_sh_ptr);
	const std::vector<int>& order();
private:
	std::shared_ptr<EdgeWeightedDigraph> graph_sh_ptr_;
	int v_;
	std::vector<int> topological_order_;
	std::stack<int> reverse_post_order_;
	std::vector<bool> visited_;
	void findTopologicalOrder();
	void findTopologicalOrder(int vertex);
};

TopologicalSort::TopologicalSort(std::shared_ptr<EdgeWeightedDigraph> graph_sh_ptr):
graph_sh_ptr_(graph_sh_ptr), v_(graph_sh_ptr_->V()), visited_(v_, false)
{
	findTopologicalOrder();
}

void TopologicalSort::findTopologicalOrder()
{
	for (int i = 0; i < graph_sh_ptr_->V(); ++i)
	{
		findTopologicalOrder(i);
	}
	while(!reverse_post_order_.empty())
	{
		topological_order_.push_back(reverse_post_order_.top());
		reverse_post_order_.pop();
	}
}

void TopologicalSort::findTopologicalOrder(int vertex)
{
	if (!visited_[vertex])
	{
		visited_[vertex] = true;
		for (std::shared_ptr<const Edge> edge : graph_sh_ptr_->edgesOf(vertex))
		{
			int to = edge->to();
			if (!visited_[to])
			{
				findTopologicalOrder(to);
			}
		}
		reverse_post_order_.push(vertex);
	}
}

const std::vector<int>& TopologicalSort::order()
{
	return topological_order_;
}

} // namespace graph



#endif // __TOPOLOGICALSORT_H__