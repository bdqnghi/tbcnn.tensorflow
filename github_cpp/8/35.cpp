

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stack>

using namespace std; 


class graphNode {
public:
  
  vector<graphNode*> adjacencyList;
  
  string label; 
  
  int indegree;
  
  graphNode(string s){
    label = s;
    indegree = 0;
  }
  
  void addNode(graphNode* n){
    adjacencyList.push_back(n);
  }
};



vector<graphNode*> list; 


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



int main (int argc, char **argv){

  
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
    
    int i1 = 0;
    int i2 = 0;
    bool c1 = false;
    bool c2 = false; 
   
    if( s1 == "0" && s2 == "0" ){
      break;
    }

    
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
    
    
    graphNode* temp = list[i2];
    temp->indegree++;
    list[i1]->addNode(temp);
  }

  topSort();
  file.close();
  return 0;
}



