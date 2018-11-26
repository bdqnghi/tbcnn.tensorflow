#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 5
struct vertex{
	char label;
	bool visited;
};
int stack[MAX];
int top=-1;
struct vertex* lstVertex[MAX];
int adjMatrix[5][5];
int vertexCount;
void push(int item){
	stack[++top]=item;
}
int pop(){
	return stack[top--];
}
int peek(){
	return stack[top];
}
bool isEmpty(){
	return top==-1;
}
//graph func
void addVertex(char label){
	struct vertex* vertex=(struct vertex*)malloc(sizeof(struct vertex));
	vertex->label=label;
	vertex->visited=false;
	lstVertex[vertexCount++]=vertex;
}
void addEdge(int start, int end){
	adjMatrix[start][end]=1;
	adjMatrix[end][start]=1;
}
void displayVertex(int vertexIndex){
	printf("%c",lstVertex[vertexIndex]->label);
}
int getAdjUnvisitedvertex(int vertexIndex){
	int i;
	for(i=0;i<vertexCount;i++){
		if(adjMatrix[vertexIndex][i]==1&&lstVertex[i]->visited==false){
			return i;
		}
	}
	return -1;
}
void depthFirstSearch(){
	int i;
	//mark first vertex visited
	lstVertex[0]->visited=true;
	displayVertex(0);
	push(0);
	while(!isEmpty()){
		int unVisitedVertex=getAdjUnvisitedvertex(peek());
		if(unVisitedVertex==-1){
			pop();
		}
		else{
			lstVertex[unVisitedVertex]->visited=true;
			displayVertex(unVisitedVertex);
			push(unVisitedVertex);
		}
	}
	for(i = 0;i < vertexCount;i++) {
 		lstVertex[i]->visited = false;
 }
}
int main(){
	int i,j;
	for(i = 0; i<MAX; i++){
		for(j = 0; j<MAX; j++){
			adjMatrix[i][j] = 0;
			adjMatrix[j][i] = 0;

		}	
	}
 		addVertex('s');
 		addVertex('a');
 		addVertex('b');
 		addVertex('c');
 		addVertex('d');
 		addEdge(0, 1); 
 		addEdge(0, 2);
 		addEdge(0, 3);
 		addEdge(1, 4);
 		addEdge(2, 4);
 		addEdge(3, 4);
 		depthFirstSearch();
		return 0;
	}
 		
