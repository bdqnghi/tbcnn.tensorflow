#pragma once
#include "IPathFinder.h"

namespace Library
{
	class BreadthFirstSearch final: public IPathFinder
	{
	public:
		BreadthFirstSearch() = default;
		BreadthFirstSearch(const BreadthFirstSearch&) = delete;
		BreadthFirstSearch& operator=(const BreadthFirstSearch&) = delete;
		BreadthFirstSearch(const BreadthFirstSearch&&) = delete;
		BreadthFirstSearch& operator=(BreadthFirstSearch&&) = delete;
		~BreadthFirstSearch() = default;

		virtual std::deque<std::shared_ptr<Node>> FindPath(std::shared_ptr<Node> start, std::shared_ptr<Node> end, std::uint32_t& numberOfNodesVisited) override;
	};
}