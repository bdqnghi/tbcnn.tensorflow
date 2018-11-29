#include<stdio.h>
#include<iostream>
using namespace std;

class Node
{
    public:
        int data;
        Node *next;
};

class ll
{
    public:
    Node *head;
    void push(int data);    
};

void ll::push(int data)
{
    Node *temp = new Node;
    temp->next = head;
    temp->data = data;
    head = temp;
};

class Stack
{
    Node *top;
    public:
    Stack(){top=NULL;}
    void push(int data);
    int pop();
    bool isEmpty();
};

void Stack::push(int data)
{
    Node *temp = new Node;
    (*temp).data = data;
    (*temp).next = top;
    top = temp;
}

int Stack::pop()
{
    int ret = (*top).data;
    top = (*top).next;
    return ret;
}

bool Stack::isEmpty()
{
    return top==NULL;
}

class Graph
{
    ll *adjList;
    int N;
public:
    Graph(int n);
    void addEdge(int src,int dest);
    void topologicalSort();
    void printGraph();
    void dfs();
    void dfsutil(int i, int visited[], Stack *s);
};

Graph::Graph(int n)
{
    N=n; 
    adjList = new ll [n];
    for(int i=0;i<N;i++)
        adjList[i].head = NULL;
}

void Graph::addEdge(int src,int dest)
{
    adjList[src].push(dest);
};

void Graph::printGraph()
{
    for(int i=0;i<N;i++)
    {
        Node *cur;
        cur = adjList[i].head;
        printf("Adjacency of %d\n",i);
        
        while(cur)
        {
            printf("%d\n",cur->data);
            cur = cur->next;
        }
    }
}


void Graph::dfsutil(int i, int visited[],Stack *s)
{
    
            Node *cur,*prev=NULL;
            cur = adjList[i].head;

            visited[i] = 1;
            
            printf("%d ",i);
            
            while(cur)
            {
                if(!visited[cur->data])
                    dfsutil(cur->data,visited, s);
                
                prev = cur;    
                cur = cur ->next;
            }
            
            (*s).push(i);
}

void Graph::dfs()
{
    printf("Printing dfs\n");
    int visited[N];
    for(int i=0;i<N;i++)
        visited[i] = 0;
    
    Stack s;
    for(int i=0;i<N;i++)
    {
        if(!visited[i])
            dfsutil(i,visited,&s);
    }

    while(!s.isEmpty())
        printf("%d-",s.pop());
}

int main()
{
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    
    cout << "Following is a Topological Sort of the given graph \n";
    g.topologicalSort();
    g.printGraph();   
    g.dfs();
    return 0;
}
