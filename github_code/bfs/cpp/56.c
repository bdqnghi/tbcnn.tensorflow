/*BFS - Graph Traversal */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<iostream>
#define maxVertices  100

using namespace std;


typedef struct queue
{
	int capacity;
	int size;
	int front;
	int rear;
	int *elements;
}Queue;


Queue *CreateQueue(int maxElements)
{
	Queue *Q=(Queue *)malloc(sizeof(Queue));
	Q->size=0;
	Q->capacity=maxElements;
	Q->front=0;
	Q->rear=-1;
	Q->elements=(int *)malloc(sizeof(int)*maxElements);
	return Q;
}


void Enqueue(Queue *Q,int element)
{
	if(Q->size==Q->capacity)
	{
		printf("Queue Full\n");
		exit(0);
	}
	else
	{
		Q->rear++;
	       	Q->size++;
		if(Q->rear==Q->capacity)
		{
			Q->rear=0;
		}
		Q->elements[Q->rear]=element;
		return;
	}
}

void Dequeue(Queue *Q)
{
	if(Q->size==0)
	{
		printf("Queue Full\n");
		exit(0);
	}
	else
	{
		Q->front+=1;
		Q->size-=1;
		if(Q->front==Q->capacity)
		{
			Q->front=0;
		}
		return;
	}
}

int front(Queue *Q)
{
	if(Q->size==0)
	{
		printf("Queue Empty\n");
		exit(0);
	}
	else
	{
		return Q->elements[Q->front];
	}
}


void bfs(int graph[][maxVertices], int *visited , int *size, int presentVertex)
{
	int i;
	visited[presentVertex]=1;
	Queue *Q=CreateQueue(maxVertices);
	Enqueue(Q,presentVertex);
	while(Q->size!=0)
	{
		presentVertex=front(Q);
		printf("Now we are visiting %d\n",presentVertex);
		Dequeue(Q);
	for(i=0;i<size[presentVertex];i++)
	{
		if(visited[graph[presentVertex][i]]==0)
		{
			visited[graph[presentVertex][i]]=1;
			Enqueue(Q,graph[presentVertex][i]);
		}
	}

	}
	return;
}

int  main()
{
	int graph[maxVertices][maxVertices],size[maxVertices]={0},visited[maxVertices]={0};
	int vertices,edges,i;
	scanf("%d%d",&vertices,&edges);
	int vertex1,vertex2;
	for(i=0;i<edges;i++)
	{
		scanf("%d%d",&vertex1,&vertex2);
		assert(vertex1>=0 && vertex1<vertices);
		assert(vertex2>=0 && vertex2<vertices);
		graph[vertex1][size[vertex1]++]=vertex2;
	}
	int presentVertex=0;
	for(i=0;i<vertices;i++)
	{
		if(visited[i]==0)
		{
			bfs(graph,visited,size,i);
		}
	}
	return 0;
}
