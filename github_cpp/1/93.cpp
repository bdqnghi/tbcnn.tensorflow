#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include "SearchAlgorithm.hpp"
#include "FifoFringe.hpp"

#include <stdio.h>

extern "C++"
{
namespace searchAlgorithms
{
    template <typename ProblemType, typename Hasher>
    class BreadthFirstSearch: public SearchAlgorithm<ProblemType, Hasher>
    {
        public:
            typedef typename ProblemType::State  State;
            typedef typename ProblemType::Action Action;
            typedef typename ProblemType::Cost   Cost;

            typedef typename SearchAlgorithm<ProblemType, Hasher>::NodeType NodeType;
            typedef typename NodeType::Ptr NodePtr;
            typedef typename NodeType::ConstPtr ConstNodePtr;

            typedef typename SearchAlgorithm<ProblemType, Hasher>::SolutionType SolutionType;
            typedef typename SearchAlgorithm<ProblemType, Hasher>::SolutionPtr SolutionPtr;

            BreadthFirstSearch();

            virtual ~BreadthFirstSearch();

           
            SolutionPtr operator() ( const ProblemType& problem );

        protected:
            typedef typename SearchAlgorithm<ProblemType, Hasher>::FringeType FringeType;

            virtual FringeType* createFringe();
    };

    template <typename ProblemType, typename Hasher>
    BreadthFirstSearch<ProblemType, Hasher>::BreadthFirstSearch()
    :SearchAlgorithm<ProblemType, Hasher>()
    {
        this->fringe = this->createFringe();
    }

    template <typename ProblemType, typename Hasher>
    BreadthFirstSearch<ProblemType, Hasher>::~BreadthFirstSearch()
    {
    }

    template <typename ProblemType, typename Hasher>
    typename BreadthFirstSearch<ProblemType, Hasher>::SolutionPtr BreadthFirstSearch<ProblemType, Hasher>::operator() ( const ProblemType& problem )
    {
        SolutionPtr solution(nullptr);

        NodePtr initialStateNode = this->createNode( problem.initialState() );

        this->fringe->push(initialStateNode);

        while( !solution && !this->fringe->empty() )
        {
            NodePtr currentNode = this->fringe->pop();
            this->notifyNodeVisitListeners(currentNode);

            if( problem.isGoal( currentNode->getState() ) )
            {
                std::cout << "currentNode cost = " << currentNode->getPathCost() << std::endl;
                solution = SolutionPtr(new SolutionType(currentNode));
                continue;
            }

            std::pair<const State*, NodePtr> entry(&currentNode->getState(), currentNode);
            this->closedList.insert(entry);
            this->notifyNodeClosureListeners(currentNode);

            std::list<NodePtr> successors = this->expand(currentNode, problem);

            for(auto node: successors) {
                if(this->closedList.find(&node->getState()) == this->closedList.end())
                this->fringe->push(successors);
            }
        }

        this->cleanUp();
        return solution;
    }

    template <typename ProblemType, typename Hasher>
    typename BreadthFirstSearch<ProblemType, Hasher>::FringeType* BreadthFirstSearch<ProblemType, Hasher>::createFringe()
    {
        return new FifoFringe<ProblemType, Hasher>();
    }
}
}

#endif 
