



#include <functional>
#include <algorithm>

#include "MinimumSpanningTree.hpp"





struct Vertex
{
	int vertex;
	int edge;

	bool operator<(const Vertex& val) const
	{
		return vertex < val.vertex;
	}
};




struct GreaterDistComp
{
	bool operator()(const Vertex& lhs,const Vertex& rhs) const
	{
		return lhs.edge > rhs.edge;
	}
};

void MinimumSpanningTree::PrintMinimumSpanningTree(
	const Graph& graph,
	int sourceVertex)
{
	
	
	
	std::vector<Vertex> closedSet;

	
	
	
	std::vector<Vertex> openSet;

	
	
	
	Vertex source = {sourceVertex, 0};

	openSet.push_back(source);

	
	
	
	for (int i = 0; i < graph.GetNumberOfVertices(); ++i)
	{
		if (i != sourceVertex)
		{
			openSet.push_back({i, INFINITY_INT});
		}
	}

	std::vector<int> neighbours;

	
	
	
	std::make_heap(openSet.begin(), openSet.end(), GreaterDistComp());

	
	
	
	uint32_t mstCost = 0;

	std::string mstPath;

	while (false == openSet.empty())
	{
		
		
		
		std::pop_heap(openSet.begin(), openSet.end(), GreaterDistComp());

		Vertex minPath = openSet.back();

		openSet.pop_back();

		
		
		
		closedSet.push_back(minPath);

		
		
		
		mstCost += minPath.edge;

		if (openSet.empty())
		{
			mstPath = "|" + mstPath + std::to_string(minPath.vertex) + "|";
		}
		else
		{
			mstPath = "|" +  mstPath + std::to_string(minPath.vertex) + "|" + " -> ";
		}

		
		
		
		graph.GetNeighbours(minPath.vertex, neighbours);

		
		
		
		bool updateHeap = false;

		
		
		
		for (int i = 0; i < neighbours.size(); ++i)
		{
			Vertex neighbour =
			{
				neighbours[i],
				graph.GetEdgeValue(minPath.vertex, neighbours[i]),
			};

			for (auto& it : openSet)
			{
				if (neighbour.vertex == it.vertex &&
					neighbour.edge < it.edge)
				{
					it.edge = neighbour.edge;

					updateHeap = true;
				}
			}
		}

		if (updateHeap)
		{
			
			
			
			std::make_heap(openSet.begin(), openSet.end(), GreaterDistComp());
		}
	}

	std::cout << "MST cost is: " << mstCost << std::endl;

	std::cout << "MST path is: " << mstPath << std::endl;

}
