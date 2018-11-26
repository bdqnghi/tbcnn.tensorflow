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

           /**
            *  The A* search algorithm based on graph search.
            *
            *  Like graph search, this variant of A* keeps a list of the states that have been visited before.
            *  If A* encounters a state for a second time, it will keep only the node with the shortest path so far in the list
            *  and ignore the other Node.
            *
            *
            *  @param[in] problem the problem for which a solution will be searched
            *  @param[in] heuristicFunction the heuristic function that is used to estimate how far a state is from a goal state.
            *  @tparam StateType the type of the states of the problem
            *  @tparam ActionType the type of the actions that can be made to get from one state to the next
            *  @tparem CostType the type of the costs of the actions
            *  @return The solution, which is a path from the problem node to the goal node or
            *			NULL if no solution was found.
            */
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

#endif // BREADTHFIRSTSEARCH_H
