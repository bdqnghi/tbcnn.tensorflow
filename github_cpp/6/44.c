#include "GraphUtil.h"
#include <vector>

int main (int argc, char* argv[])
{
  
  CGraphAdjList* testGraphAdjListUndirected1 = CreateTestGraphAdjListUndirected1();
  CGraphAdjList* testGraphAdjListDirected1 = CreateTestGraphAdjListDirected1();

  CGraphAdjList* testGraphAdjListUndirected2 = CreateTestGraphAdjListUndirected2();
  CGraphAdjList* testGraphAdjListDirected2 = CreateTestGraphAdjListDirected2();

  std::cout<<"--------Test DepthFirstSearchRecursively start from Node#0 -------"<<std::endl;
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListUndirected1, 0):"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListUndirected1, 0);
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListDirected1, 0)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListDirected1, 0);

  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 0)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 0);
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListDirected2, 0)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListDirected2, 0);
  std::cout<<"-----------------------------------"<<std::endl;

  std::cout<<"--------Test DepthFirstSearchRecursively start from Node#1 -------"<<std::endl;
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 1)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 1);
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListDirected2, 1)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListDirected2, 1);
  std::cout<<"-----------------------------------"<<std::endl;

  std::cout<<"--------Test DepthFirstSearchRecursively start from Node#11 -------"<<std::endl;
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 11)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListUndirected2, 11);
  std::cout<<"DepthFirstSearchRecursively(*testGraphAdjListDirected2, 11)"<<std::endl;
  DepthFirstSearchRecursively(*testGraphAdjListDirected2, 11);
  std::cout<<"-----------------------------------"<<std::endl;

  
  delete testGraphAdjListUndirected1;
  delete testGraphAdjListDirected1;
  delete testGraphAdjListUndirected2;
  delete testGraphAdjListDirected2;

  std::cout << "bye" << std::endl;

  return 0;
}
