#include<iostream>
#include <list>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;
#define MAXCHARLEN 10
#define GSIZE 101
#define INPUTNAME "/Users/josephvalentine/Documents/code/c/ecen_521/graph1.txt"



class Graph
{
    int numVertices; 
 
    
    list<int> *adj;
 
    void DFS(int v, bool discovered[]);
public:
    Graph(int numVertices);   
    void addEdge(int v, int w);
    void connectedComponents();
   
};
 

void Graph::connectedComponents(){
    
    bool *discovered = new bool[numVertices];
    for(int v = 0; v < numVertices; v++)
        discovered[v] = false;
 
    for (int v=1; v<numVertices; v++){
    
        if (discovered[v] == false){
            
            

            
            discovered[v] = true;
            cout << v << " ";
            DFS(v, discovered);
            cout << "\n";
        }
    }
}
 
void Graph::DFS(int v, bool discovered[]){
	

    
    
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i){
        if(!discovered[*i]){ 
        	
        	
        	
        	discovered[*i] = true;
            cout << *i << " ";
            
            DFS(*i, discovered);
        } 
        
        
        
        
        
        
    }
    
    
}
 
Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    adj = new list<int>[numVertices];
}
 

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void fillGraphFromFile(Graph g, std::string value, int index){
	int v1;
	int v2;
    if(index == 0){
    	cout<<"vert num"<<value<<endl;
    	
    } else if(index == 1){

    } else {
    	std::string delimiter = " ";

	    size_t pos = 0;
	    std::string token;

	    token = value.substr(0, value.find(delimiter));
	    v1 = stoi(token);
	    value.erase(0, value.find(delimiter) + delimiter.length());

	    token = value.substr(0, value.find(delimiter));
	    v2 = stoi(token);
	    value.erase(0, value.find(delimiter) + delimiter.length());

	    g.addEdge(v1,v2);
	    
    }
  }
int main()
{
  
    Graph g(GSIZE);
    string filename = INPUTNAME;
   	ifstream myfile (filename);
   	std::string value;

  
   if (myfile.is_open()){

    int count = 0;
    while(getline(myfile, value)){

      fillGraphFromFile(g, value, count);
      count++; 
    }
    myfile.close();
  } else {
  	std::cout << "Unable to open file ";
  }

 
    cout << "these are the connected vertices \n";
    g.connectedComponents();
 
    return 0;
}