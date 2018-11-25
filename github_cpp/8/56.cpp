


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class gNode{
public:
  
  string value;
  
  vector<gNode*> nodeys;
  
  int indegree;
  
  gNode(string s);
  
  void connect(gNode* n);
};

gNode::gNode(string s){
  value = s;
  indegree=0;
}

void gNode::connect(gNode* n){
  nodeys.push_back(n);
}

vector<gNode*> nodes;


void sort();

int main(int argc, char **argv){
  if(argc != 2){
    cout << "gimme only 1 parameter" << endl;
    exit(1);
  }

  ifstream file(argv[1], ifstream::binary);
  if(!file.is_open()){
      cout << "couldn't open file "<< argv[1]<<endl;
      exit(2);
    }
  while(file.good()){
      string s1,s2;
      file >> s1;
      file >> s2;
      if(s1=="0"&&s2=="0"){
	break;
      }
      bool b1 = false;
      bool b2 = false;
      int i1 = 0;
      int i2 = 0;

      for(int i=0;i<nodes.size();i++){
	if(nodes[i]->value==s1){
	  b1=true;
	  i1 = i;
	}
      }
      if(!b1){
	gNode* n = new gNode(s1);
	nodes.push_back(n);
	i1=nodes.size()-1;
      }
      for(int i=0;i<nodes.size();i++){
	if(nodes[i]->value==s2){
	  b2=true;
	  i2 = i;
	}
      }
      if(!b2){
	gNode* n = new gNode(s2);
	nodes.push_back(n);
	i2=nodes.size()-1;
      }
      nodes[i2]->indegree++;
      nodes[i1]->connect(nodes[i2]);
    }
  

    sort();

	  

    file.close();
    
    
}

void sort(){
  queue<gNode*> qu;

  gNode* v1;
  gNode* v2;

  for(int i=0;i<nodes.size();i++){
    v1 = nodes[i];
    if(v1->indegree==0){
      qu.push(v1);
    }
  }

  while(!qu.empty()){
    v1 = qu.front();
    qu.pop();
    cout<<v1->value<<" ";
    for(int i=0;i<v1->nodeys.size();i++){
      v2=v1->nodeys[i];
      v2->indegree--;
      if(v2->indegree==0){
	qu.push(v2);
      }
    }
  }
  cout<<endl;
}
    
