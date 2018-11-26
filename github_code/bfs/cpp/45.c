#ifndef SYMBOLIC_BREADTH_FIRST_SEARCH_H
#define SYMBOLIC_BREADTH_FIRST_SEARCH_H

#include <vector>
#include <iostream>

#include "sym_bucket.h"
#include "unidirectional_search.h"

namespace symbolic {

class BreadthFirstSearch : public UnidirectionalSearch  {  
    Bucket open;   // States in open 
    //Bucket closed; // States in closed
    BDD closedTotal;
    
    SymStepCostEstimation estimation;

    std::shared_ptr<BreadthFirstSearch> parent;

    void filterDuplicates(BDD & bdd) {
	/* for(const BDD & c : closed) */
	bdd *=  !closedTotal;
    }
    
    void filterDuplicates(Bucket & bucket) {
	for (BDD & bdd : bucket)
	    filterDuplicates(bdd);
    }

    void close (const BDD & bdd) {
	closedTotal += bdd;
	//closed.push_back(bdd);
	//mgr->mergeBucket(closed);
    }
 public:
  BreadthFirstSearch(const SymParamsSearch & params);
  BreadthFirstSearch(const BreadthFirstSearch & ) = delete;
  BreadthFirstSearch(BreadthFirstSearch &&) = default;
  BreadthFirstSearch& operator=(const BreadthFirstSearch& ) = delete;
  BreadthFirstSearch& operator=(BreadthFirstSearch &&) = default;
  ~BreadthFirstSearch() {}

  bool init(std::shared_ptr<SymStateSpaceManager> manager, bool forward);

  bool init(const std::shared_ptr<BreadthFirstSearch> & other, 
	    std::shared_ptr<SymStateSpaceManager> manager, int maxRelaxTime, int maxRelaxNodes);


  virtual int getF() const override {
      return 0;
  }

  virtual void getPlan(const BDD &, int , int , std::vector <const GlobalOperator *> &) const {
  }
  BDD pop();

  virtual bool finished() const {
    return open.empty(); 
  }
  
  BDD getUnreachableStates() const ;

  bool foundSolution () const {
      if (parent && parent->foundSolution()) return true;

      BDD target = (fw ? mgr->getGoal() : mgr->getInitialState());
      return !((closedTotal*target).IsZero()); 
      /* for (auto & bdd : closed) { */
      /* 	  if (!((bdd*target).IsZero())) { */
      /* 	      return true; */
      /* 	  } */
      /* } */
  }

  bool isBetter(const BreadthFirstSearch & other) const{
      return nextStepTime() < other.nextStepTime();
  }

  virtual void getHeuristic(std::vector<ADD> & /*heuristics*/,
			    std::vector <int> & /*maxHeuristicValues*/) const {
      
  }

  virtual bool stepImage(int maxTime, int maxNodes);

  virtual long nextStepTime() const;
  virtual long nextStepNodes() const;
  virtual long nextStepNodesResult() const;

  virtual bool isUseful(double ratio) const;
  virtual bool isSearchableWithNodes(int maxNodes) const; 
  void violated(TruncatedReason reason , double time, int maxTime, int maxNodes);

  void notifyMutexes (const BDD & bdd);

};

}

#endif 
