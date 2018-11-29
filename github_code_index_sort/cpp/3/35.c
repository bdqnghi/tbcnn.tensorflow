/** @brief This is topological.cpp 
 * @details This class topologically sorts a text file input 
 * @author Ashley Nguyen - apn2my
 * @date 4/24/16
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>

using namespace std; 

/** @code{.cpp}
 * @brief graphNode class to create a node with specified fields
 * 
 */
class graphNode {
public:
  /** @var vector<graphNode*> adjacencyList 
   * @brief vector that holds nodes that are adjacent
   *
   */
  vector<graphNode*> adjacencyList;
  /** @var string label 
   * @brief string that labels the node (i.e the location on the map)
   *
   */
  string label; 
  /** @var int indegree
   * @brief integer value of the node's indegree value
   * @details indegree is the number of incoming edges of the node
   */
  int indegree;
  /** @fn graphNode(string s )
   * @brief graphNode constructor 
   * @details constructs node with destined label and initializes its indegree to 0 as it is a newly constructed node 
   *
   * @param string s, label of node 
   *
   */
  graphNode(string s){
    label = s;
    indegree = 0;
  }
  /** @fn addNode(graphNode* n)
   * @brief adds a node onto the list of adjacent nodes 
   *
   * @param graphNode* n, the node to be included into the vector
   *
   */
  void addNode(graphNode* n){
    adjacencyList.push_back(n);
  }
};
/**@endcode
 */

/** @var vector<graphNode*> list
 * @brief internal list of graphNodes to construct sort 
 *
 */
vector<graphNode*> list; 

/** @fn void topSort()
 * @brief performs an algorithmic topological sort, referenced slides from class 
 * @details iterate through the stack 
 * @if first node's indegree is 0
 * push n1 onto the stack
 * @endif 
 * @cond stack is not empty 
 * first node is the top 
 * pop it off the stack and print it out 
 * loop through node's adjacency list 
 * assign node2 to its elements 
 * decrement node2's indegree 
 * @if n2->indegree == 0
 * push n2 onto the stack 
 * @endif 
 * @endcond
 *
 */
void topSort(){
  stack<graphNode*> s;
  graphNode *v;
  graphNode *w; 

  for( int counter = 0; counter < list.size(); counter++ ){
    v = list[counter];
    if( v->indegree == 0 ){
      s.push(v);
    }
  }
  
  while(!s.empty()){
    v = s.top();
    s.pop();
    cout << v->label << " ";
    int size1 = v->adjacencyList.size();
    //for each w adjacent to v 
    for( int i = 0; i < size1; i++){
      w = v->adjacencyList[i];
      w->indegree--;
      if( w->indegree == 0 ){
	s.push(w);
      }
    }
  }
  cout << endl;
}

/** @code{.cpp}
 * @brief main function that receives one command-line parameter input
 *
 */
// we want to use parameters 
int main (int argc, char **argv){

  // verify the correct number of parameters 
  if( argc != 2 ){
    cout << "Must supply the input file name as the one and only parameter" << endl;
    exit(1);
  }

  // attempt to open the supplied file 
  ifstream file( argv[1], ifstream::binary);

  // report any problems opening the file and then exit
  if( !file.is_open()){
    cout << "Unable to open file '" << argv[1] << "'." << endl;
    exit(2);
  }

  // read in two strings
  while( !file.eof() ){
    string s1, s2; 
    file >> s1; 
    file >> s2; 
    // resetters 
    int i1 = 0;
    int i2 = 0;
    bool c1 = false;
    bool c2 = false; 
   
    if( s1 == "0" && s2 == "0" ){
      break;
    }

    // Handling first string 
    for( int i = 0; i < list.size(); i++ ){
      if( list[i]->label == s1 ){
	i1 = i;
	c1 = true;
      }
    }
    
    if( !c1 ){
      graphNode* n1 = new graphNode( s1 );
      list.push_back(n1);
      i1 = list.size()-1;
    }

    // Handling second string
    for( int k = 0; k < list.size(); k++){
      if( list[k]->label == s2 ){
	i2 = k;
	c2 = true;
      }
    }

    if( !c2 ){
      graphNode* n2 = new graphNode(s2);
      list.push_back(n2);
      i2 = list.size()-1;
    }
    
    //increment indegree and add 
    graphNode* temp = list[i2];
    temp->indegree++;
    list[i1]->addNode(temp);
  }

  topSort();
  file.close();
  return 0;
}
/**@endcode
 */


