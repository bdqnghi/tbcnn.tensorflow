#include "TopologicalSort.h"

namespace TpgSort
{
	void TopologicalSort::dfs(const EWDiGraph& graph, int v)
	{
		marked[v] = true;
		EWDiGraph::EdgesList list = graph.getAdjacentVertex(v);
		for (EWDiGraph::EdgesList::const_iterator i = list.begin(); i != list.end(); ++i)
		{
			if (!marked[i->to()])
				dfs(graph, i->to());
		}
		rPostOrder.push(v);
		PostOrder.push(v);
	}

	TopologicalSort::TopologicalSort(const EWDiGraph& graph) : graph(graph), marked(graph.getVertexCount(), false)
	{
		for (int i = 0; i < graph.getVertexCount(); ++i)
		{
			if (!marked[i])
				dfs(graph, i);
		}
	}

	TopologicalSort::ReversePostOrderContainer TopologicalSort::getReversePostOrder()
	{
		return rPostOrder;
	}

	TopologicalSort::PostOrderContainer TopologicalSort::getPostOrder()
	{
		return PostOrder;
	}
}