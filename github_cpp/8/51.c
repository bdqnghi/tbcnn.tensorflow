






#define _RELATIVE_

#ifdef _RELATIVE_
#include "../include/TopologicalSort.h"
#include "../include/DFS.h"
#elif

#include "TopologicalSort.h"
#include "DFS.h"
#endif


#ifndef __CXX14


_jcode::TopologicalSort::TopologicalSort() {
#ifdef _DEBUG_ON_
	std::cout << "TopologicalSort::TopologicalSort()" << std::endl;
#endif
};

_jcode::TopologicalSort::~TopologicalSort() {
#ifdef _DEBUG_ON_
	std::cout << "TopologicalSort::~TopologicalSort()" << std::endl;
#endif
};

#endif



_jcode::TopologicalSort::TopologicalSort(std::vector<std::vector<int>>& argrGraph_) : Graph_(argrGraph_) {
#ifdef _DEBUG_ON_
	std::cout << "TopologicalSort::TopologicalSort()" << std::endl;
#endif
};


std::vector<int> _jcode::TopologicalSort::run(int argvStartingNode_) {
	
#ifdef _DEBUG
	std::cout << "TopologicalSort::run()" << std::endl;
#endif	
	
	std::vector<bool> isVisited_(Graph_.size(), false);
	std::vector<bool> isFinished_(Graph_.size(), false);
	
	std::function<void(int)> DFS = [&](int argvSrc_) {
		
		isVisited_.at(argvSrc_) = true;
	
		
		for(unsigned itor_ = 0; itor_ < Graph_.size(); itor_++) {
			
			if(Graph_[argvSrc_][itor_] != 0 && !isVisited_[itor_]) {
#ifdef _DEBUG
				std::cout << "	> Moving from "<< argvSrc_ << " to " << itor_ << std::endl;
#endif								
				DFS(itor_);
				
			} else if (Graph_[argvSrc_][itor_] != 0 && isVisited_[itor_]) { 
				
				isFinished_.at(itor_) = true;
				
			}
		}
	};
	
	
	Sort_.push_back(argvStartingNode_);
	
	std::reverse(Sort_.begin(), Sort_.end());
	
	return Sort_;
};
