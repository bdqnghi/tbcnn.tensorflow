#include<iostream>
#include "../../../NonTemplate/ListImpl/Graph_linked_list_inpl.hpp"
#include "../../../../08PriorityQueue/NonTemplet/ArrayImp/PriorityQueue.hpp"

using namespace std;

class Prims_algo : public Graph_List_Weighted
{
  public:
    Prims_algo(char vertex_list[], int size): Graph_List_Weighted(vertex_list,size) {}
    
    void minimum_spanning_tree()
    {
      
    }
  private;
    MinHeap 
};



void test_01()
{
  cout << "//------------------------------------------------------------------test case 1" << endl; 
  char vertex_list[] = { 'A', 'B', 'C', 'D', 'E', 'F'};
  int size = sizeof(vertex_list)/sizeof(vertex_list[0]);
  Prims_algo graph(vertex_list, size);
  graph.connect_vertex('A', 'B', 3);
  graph.connect_vertex('A', 'D', 1);
  graph.connect_vertex('B', 'A', 3);
  graph.connect_vertex('B', 'C', 1);
  graph.connect_vertex('B', 'D', 3);
  graph.connect_vertex('C', 'B', 1);
  graph.connect_vertex('C', 'D', 1);
  graph.connect_vertex('C', 'E', 5);
  graph.connect_vertex('C', 'F', 4);
  graph.connect_vertex('D', 'A', 1);
  graph.connect_vertex('D', 'B', 3);
  graph.connect_vertex('D', 'C', 1);
  graph.connect_vertex('D', 'E', 6);
  graph.connect_vertex('E', 'D', 6);
  graph.connect_vertex('E', 'C', 5);
  graph.connect_vertex('E', 'F', 2);
  graph.connect_vertex('F', 'C', 4);
  graph.connect_vertex('F', 'E', 2);


  cout << "Printing the graph - "<< endl;
  graph.print();
  
}


int main()
{
  test_01();

  return 0;
}
