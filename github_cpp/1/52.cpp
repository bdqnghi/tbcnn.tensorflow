
#include<iostream>
#include<queue>
using namespace std;

struct node{
	int val;
	node *next=NULL;
};

struct AdjList{
	node *head=NULL;
};

class graph{
private:
	AdjList *listMap;
	string type;
	int size;
public:
	graph(int numOfNodes, string type)
	{
		listMap = new AdjList[numOfNodes];
		
		type = type;
		size = numOfNodes;
		
	}

	void addEdge(int i, int j)
	{
		node *newNode = new node;
		newNode->val = j;
		newNode->next = listMap[i].head;
		listMap[i].head = newNode;

		if (type == "undirected")
		{
			node *newNode = new node;
			newNode->val = i;
			newNode->next = listMap[j].head;
			listMap[j].head = newNode;
		}
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			node *ptr = getAdjListHead(i);
			cout << i << " -> ";
			while (ptr != NULL)
			{
				cout << ptr->val << ", ";
				ptr = ptr->next;
			}
			cout << endl;
		}
	}

	node *getAdjListHead(int node)
	{
		return listMap[node].head;
	}

	int getSize()
	{
		return size;
	}
};

void breadthFirstSearch(graph G, int startNode)
{
	std::queue<int> traverseQueue;
	int *visited = new int[G.getSize()];

	for (int i = 0; i < G.getSize(); i++)
		visited[i] = 0;

	traverseQueue.push(startNode);

	node *ptr;
	while (!traverseQueue.empty())
	{
		ptr = G.getAdjListHead(traverseQueue.front());
		traverseQueue.pop();
		while (ptr != NULL)
		{
			int nodeVal = ptr->val;

			if (visited[nodeVal] == 0)
			{
				visited[nodeVal] = 1;
				cout << "visited node " << nodeVal << endl;
				traverseQueue.push(nodeVal);
			}
			ptr = ptr->next;
		}
	} 
}


int main()
{
	int size = 8;
	graph G(size,"directed");
	G.addEdge(0, 0);
	G.addEdge(1, 2);
	G.addEdge(1, 4);
	G.addEdge(2, 4);
	G.addEdge(2, 7);
	G.addEdge(3, 4);
	G.addEdge(3, 5);
	G.addEdge(4, 5);
	G.addEdge(5, 6);

	G.print();

	breadthFirstSearch(G, 1);

	getchar();
	return 1;
}























