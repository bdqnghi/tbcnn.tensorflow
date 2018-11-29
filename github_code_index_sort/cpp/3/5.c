//Nico Salafranca nms6dz topological.cpp
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <string>

using namespace std; 

/** @code{.cpp}
 * @brief Node class
 * 
 */

class Node {
public:

  /** @var vector<Node*> adj 
   * @brief vector of Node pointers
   *
   */
  vector<Node*> adj;

  /** @var string str 
   * @brief the information of the Node
   *
   */

  string str; 
  /** @var int indegree
   * @details indegree == incoming edges
   */
  int indegree;

  /** @fn Node(string s )
   * @brief constructor
   * @param string s 
   *
   */

  Node(string s){
    str = s;
    indegree = 0;
  }

  /** @fn addNode(Node* n)
   * @brief adds node into adj 
   *
   * @param Node* n
   *
   */

  void addNode(Node* n){
    adj.push_back(n);
  }
};
/**@endcode
 */

/** @var vector<Node*> vec;
 *
 */
vector<Node*> vec; 

/** @fn void topSort()
 * @brief topological sort
 *
 */

void topSort(){
  queue<Node*> q;
  Node *v;
  Node *w; 
    
  for( int i = 0; i < vec.size(); i++ ){
    v = vec[i];
    if( v->indegree == 0 ){
      q.push(v);//enqueue - linear
    }
  }
  
  while(!q.empty()){
    v = q.front();
    q.pop();//dequeue
    cout << v->str << endl; // linear
    int size1 = v->adj.size();
    for( int j = 0; j < size1; j++){ // theta(n)
      w = v->adj[j];
      w->indegree--;
      if( w->indegree == 0 ){
	q.push(w);
      }
    }
  }
  cout << endl;
}

/*
 * @brief main function
 *
 */ 

int main (int argc, char *argv[]){

  if( argc != 2 ){
    cout << "Must supply the input file name as the one and only parameter" << endl;
    exit(1);
  }

  ifstream file( argv[1], ifstream::binary);

  if( !file.is_open()){
    cout << "Unable to open file '" << argv[1] << "'." << endl;
    exit(2);
  }

  while( !file.eof() ){
    string s1, s2; 
    file >> s1; 
    file >> s2; 

    int x = 0;
    int y = 0;

    bool b1 = false;
    bool b2= false; 

    //conditions
    if( s1 == "0" && s2 == "0" ){
      break;
    }
    for( int i = 0; i < vec.size(); i++ ){
      if( vec[i]->str == s1 ){
	x = i;
	b1 = true;
      }
    }
    if( !b1 ){
      Node* n1 = new Node( s1 );
      vec.push_back(n1);
      x = vec.size()-1;
    }
    for( int k = 0; k < vec.size(); k++){
      if( vec[k]->str == s2 ){
	y = k;
	b2 = true;
      }
    }
    if( !b2 ){
      Node* n2 = new Node(s2);
      vec.push_back(n2);
      y = vec.size()-1;
    }
    
    Node* node = vec[x];
    node->indegree++;
    vec[x]->addNode(node);
  }

  topSort();
  file.close();
  return 0;
}
/**@endcode
 */
