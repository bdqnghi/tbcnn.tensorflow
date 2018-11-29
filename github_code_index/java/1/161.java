




//BFS
import java.util.*;
import java.io.*;
class Queue
{
 final int size = 20;
 int[] quearray;
 int front;
 int rear;

 Queue()
{
quearray = new int[size];
front = 0;
rear = -1;
}
 void insert(int j) 
{
if(rear == size-1)
rear = -1;
quearray[++rear] = j;
}

 int remove()

{
int temp = quearray[front++];
if(front == size)
front = 0;
return temp;

}

 boolean isempty() 
{
return ( rear+1==front || (front+size-1==rear) );
}

} 

class Vertex
{
 char label;
 boolean wasVisited;
 Vertex(char lab)
{
label = lab;
wasVisited = false;
}
}
class Graph
{
 final int MAX_VERTS = 20;
 Vertex vertexList[]; 
 int adjMat[][];

 int nVerts;

 Queue theQueue;

Graph()

{
vertexList = new Vertex[MAX_VERTS];

adjMat = new int[MAX_VERTS][MAX_VERTS];
nVerts = 0;
for(int j=0; j<MAX_VERTS; j++)

for(int k=0; k<MAX_VERTS; k++)


adjMat[j][k] = 0;
theQueue = new Queue();
}

public void addVertex(char lab)
{
vertexList[nVerts++] = new Vertex(lab);
}

 void addEdge(int start, int end)
{
adjMat[start][end] = 1;
adjMat[end][start] = 1;
}

public void displayVertex(int v)
{
System.out.print(vertexList[v].label);
}

public void bfs()

{

vertexList[0].wasVisited = true;
displayVertex(0);

theQueue.insert(0);

int v2;
while( !theQueue.isempty() )

{
int v1 = theQueue.remove();

while( (v2=getAdjUnvisitedVertex(v1)) != -1 )
{

vertexList[v2].wasVisited = true; 
displayVertex(v2);

theQueue.insert(v2);

}

} 
for(int j=0; j<nVerts; j++)

vertexList[j].wasVisited = false;
}
public int getAdjUnvisitedVertex(int v)
{
for(int j=0; j<nVerts; j++)
if(adjMat[v][j]==1 && vertexList[j].wasVisited==false)
return j;
return -1;
}
} 
class breadthfirstsearch
{
public static void main(String args[])
{
Graph theGraph = new Graph();
theGraph.addVertex('A');

theGraph.addVertex('B');

theGraph.addVertex('C');

theGraph.addVertex('D');

theGraph.addVertex('E');

theGraph.addEdge(0,1);
theGraph.addEdge(1,2);
theGraph.addEdge(0,3);
theGraph.addEdge(3,4);

System.out.print("Visits: ");
theGraph.bfs();

System.out.println();
}
}
