#ifndef __DEPTH_FIRST_SEARCH_H_
#define __DEPTH_FIRST_SEARCH_H_

#include "graph.hpp"

namespace DevinLib
{
	namespace Algorithm
	{
		class DepthFirstSearch
		{
		public:
			DepthFirstSearch() = delete;
			DepthFirstSearch(const DepthFirstSearch&) = delete;
			DepthFirstSearch(DepthFirstSearch&&) = delete;
			DepthFirstSearch& operator=(DepthFirstSearch&&) = delete;
			DepthFirstSearch& operator=(const DepthFirstSearch&) = delete;

			DepthFirstSearch(const Graph& g, int s) : _marked(g.vertex())
			{
				assert_valid_vertex(s);
				dfs(g, s);
			}

			bool marked(int w) const 
			{
				assert_valid_vertex(w);
				return _marked[w]; 
			}

			constexpr int size() const noexcept { return _count; }

		private:
			Array<bool> _marked;
			int _count;

			void dfs(const Graph& g, int v)
			{
				_marked[v] = true;
				++_count;
				for (int w : g.adj(v))
				{
					if (!_marked[w])
						dfs(g, w);
				}
			}

			void assert_valid_vertex(int v) const
			{
				if (v < 0 || v >= _marked.size())
					throw std::out_of_range(OUT_OF_RANGE_STRING_ONE_GIVEN(0, _marked.size() - 1, v));
			}
		};
	}
}

#endif 
