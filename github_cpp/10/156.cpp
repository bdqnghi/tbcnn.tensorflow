#include<iostream>
#include<stack>

#define VERTICES 6
#define NOTVISITED -1
#define VISITED 0
#define EXPLORED 1

using namespace std;

/*
http://en.wikipedia.org/wiki/File:6n-graph2.svg
*/
int adjacencyMatrix[][VERTICES+1] = 
{
{-1, -1, -1, -1, -1, -1, -1},
{-1, 1 , 1 , 0 , 0 , 1 , 0},
{-1, 1 , 0 , 1 , 0 , 1 , 0},
{-1, 0 , 1 , 0 , 1 , 0 , 0},
{-1, 0 , 0 , 1 , 0 , 1 , 1},
{-1, 1 , 1 , 0 , 1 , 0 , 0},
{-1, 0 , 0 , 0 , 1 , 0 , 0}
};

class Vertex{

	private :
	int vertexNumber;
	int status;

	public :

	Vertex(){
	}

	Vertex(int number){	
		vertexNumber = number;
		status = NOTVISITED;
	}

	void markVisited(){
		status = VISITED;
	}

	void markExplored(){
		status = EXPLORED;
	}

	int getVertexNumber(){
		return vertexNumber;
	}

	bool IsExplored(){
		if(status == EXPLORED)
			return true;
		else
			return false;
	}

	bool IsVisited(){
		if(status == VISITED)
			return true;
		else
			return false;
	}

	int getStatus(){
		return status;
	}
	
};

int main(){

	int i,j,k,l;

	for(i = 1; i <= VERTICES; i++){
		for( j = 1; j <= VERTICES; j++)
			cout << adjacencyMatrix[i][j] << " ";
		cout << endl;
	}

	Vertex vertices[VERTICES+1];

	for(i = 1; i <= VERTICES; i++)
		vertices[i] = Vertex(i);

	stack<Vertex> s;
	Vertex curr;
	Vertex neighbor;
	s.push(vertices[1]);
	int explored[VERTICES+1];
	int inQueue[VERTICES+1];
	for(i = 1; i <= VERTICES; i++){
		explored[i] = 0;
		inQueue[i] = 0;
	}

	while(s.size() != 0){
			curr = s.top();
			s.pop();
			cout << "Current Node :" << curr.getVertexNumber() << endl;
			explored[curr.getVertexNumber()] = 1;
			for(i = 1; i <= VERTICES; i++){
				if(curr.getVertexNumber() == i ||  adjacencyMatrix[curr.getVertexNumber()][i] != 1)
					continue;
				neighbor = vertices[i];
				if(explored[i] == 1){
					cout  << "Explored :" << i << endl;
					continue;
				}
				else if(inQueue[i] == 1){
					cout  << "In Queue :" << i << endl;
					continue;
				}
				else{
					cout << "Neighbor :" << i << " Status :" << neighbor.getStatus() << endl;
					s.push(vertices[i]);
					inQueue[i] = 1;
				}
			}
			curr.markExplored();
	}

	return 0;
}
