#ifndef FORD_FULKERSON_HPP
#define FORD_FULKERSON_HPP

#include "Algorithm.hpp"

namespace algorithms
{
	class FordFulkerson : public Algorithm
	{
		int source, target;
		int fordFulkerson(int source, int target);
		bool bfs(const Matrix & residualGraph, int s, int t, VecInt & parent);
	public:
		FordFulkerson(const Graph & _graph1, int _source, int _target) : Algorithm(_graph1), source(_source), target(_target) {}
		virtual void run();
		virtual void showResults();
		virtual ~FordFulkerson() {}
	};
}

#endif