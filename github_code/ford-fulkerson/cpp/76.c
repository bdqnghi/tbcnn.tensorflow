#include <stdio.h>
#include <limits.h>
#include <iostream>
using namespace std;
#define V 6

int max(int a,int b)
{
    return a>b?a:b;
}

int min(int a,int b)
{
    return a<b?a:b;
}

class Queue
{
    int front;
    int rear;
    int size;
    int cap;
    int *arr;
public:
    void Enqueue(int i);
    int Dequeue();
    Queue(int cap);
    bool isFull();
    bool isEmpty();
};

Queue::Queue(int c)
{
    arr = new int[c];
    front=0;
    rear=c-1;
    size = 0;
    cap=c;
}

void Queue::Enqueue(int i)
{
    if(isFull())
        return;

    size++;
    rear = (rear+1)%cap;
    arr[rear] = i;
}

int Queue::Dequeue()
{
    if(isEmpty())
        return -1;

    size--;
    int data = arr[front];
    front = (front+1)%cap;
    return data;
}

bool Queue::isFull()
{
    return size==cap;
}

bool Queue::isEmpty()
{
    return (!size);
}

bool bfs(int graph[V][V],int src,int dest,int parent[])
{
    int visited[V];
    for(int i=0;i<V;i++)
        visited[i] = 0;

    Queue q(V);
    visited[src] = 1;
    q.Enqueue(src);
   
    while(!q.isEmpty())
    {
        src = q.Dequeue();

        for(int i=0;i<V;i++)
        {
            if(graph[src][i] and not visited[i])
            {
                parent[i] = src;
                visited[i] = 1;
                q.Enqueue(i);
            }
        }
    }

    return visited[dest];
}

int fordFulkerson(int graph[V][V],int src,int dest)
{
    int parent[V];
    for(int i=0;i<V;i++)
        parent[i] = -1;
    
    int max_flow = 0;

    while(bfs(graph,src,dest,parent))
    {

        int path_flow = INT_MAX;
        for(int cur=dest;cur!=src;cur=parent[cur])
            path_flow = min(path_flow,graph[parent[cur]][cur]);

        for(int cur=dest;cur!=src;cur=parent[cur])
        {
            graph[parent[cur]][cur] -= path_flow;
            graph[cur][parent[cur]] += path_flow;
        }
        
        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{
    //Let us create a graph shown in the above example
    int graph[V][V] = { {0, 16, 13, 0,  0,  0},
                        {0, 0,  10, 12, 0,  0},
                        {0, 4,  0,  0,  14, 0},
                        {0, 0,  9,  0,  0,  20},
                        {0, 0,  0,  7,  0,  4},
                        {0, 0,  0,  0,  0,  0}
                        };
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);
       
    return 0;
}
