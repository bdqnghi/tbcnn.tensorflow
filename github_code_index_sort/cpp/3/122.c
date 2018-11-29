//
// Created by vivek on 12/16/2017.
//

#include "iostream"
#include "unordered_map"
#include "vector"
#include "unordered_set"
#include "stack"

#ifndef C_TOPOLOGICALSORT_H
#define C_TOPOLOGICALSORT_H

class DAGraph{
private:
    std::unordered_map<size_t, std::vector<size_t> > _graph;

public:

    DAGraph()
    {
    }

    void addNode(size_t iFrom, size_t iTo)
    {
        _graph[iFrom].push_back(iTo);
    }

    void addNode(size_t iFrom)
    {
        _graph[iFrom] = std::vector<size_t >();
    }

    void topologicalSortUtil(size_t iNode,std::unordered_set<size_t>& ioVisited, std::stack<size_t >& ioStackOfNodes)
    {
        std::vector<size_t >& aAdj = _graph[iNode];

        ioVisited.insert(iNode);

        for (size_t i = 0; i < aAdj.size(); ++i)
        {
            if (ioVisited.find(aAdj[i]) == ioVisited.end())
            {
                topologicalSortUtil(aAdj[i], ioVisited, ioStackOfNodes);
            }
        }

        ioStackOfNodes.push(iNode);
    }
    void topologicalSort()
    {
        std::unordered_set<size_t> aVisited;
        std::stack<size_t > aStackOfNodes;

        std::unordered_map<size_t, std::vector<size_t> >::const_iterator aIter = _graph.begin();
        std::unordered_map<size_t, std::vector<size_t> >::const_iterator aEndIter = _graph.end();

//        for(size_t i = 0; i < _graph.size(); ++i)
        while( aIter != aEndIter)
        {
            if (aVisited.find(aIter->first) == aVisited.end())
                topologicalSortUtil(aIter->first, aVisited, aStackOfNodes);

            ++aIter;
        }

        std::cout << "Order : ";
        while (!aStackOfNodes.empty())
        {
            std:: cout << aStackOfNodes.top() << " ";
            aStackOfNodes.pop();
        }
        std::cout << std::endl;
    }
};

class TopologicalSort {

public:
    TopologicalSort(){}

    void runTopologicalSort()
    {
        DAGraph aGraph;

        aGraph.addNode(5,2);
        aGraph.addNode(0);
        aGraph.addNode(5,0);
        aGraph.addNode(4,0);
        aGraph.addNode(4,1);
        aGraph.addNode(2,3);
        aGraph.addNode(3,1);
        aGraph.addNode(1);


        aGraph.topologicalSort();
    }
};


#endif //C_TOPOLOGICALSORT_H
