#include <iostream.h>
#include <conio.h>
#include <timer.h>
#include <stdlib.h>



typedef enum bool {false = 0,true} boolean;

#define MAX 20

class Graph
{
     int edges[MAX][MAX],*visited,nodes,sides,*order,x;
     void dfs(int);
   public:
     Graph()
     {
	 sides = nodes = 0;
	 x = -1;
     }
     void input();
     void traverse();
     boolean isConnected();
     void print();
     void randomize();
};

void Graph :: input()
{
     while(1)
     {
	 cout << "\nGive the number of nodes : ";cin >> nodes;
	 if(nodes >= MAX) cout << "\nGive the nodes lesser than 20\n";
	 else break;
     }
     cout << "\nGive the number of edges : ";cin >> sides;
     visited = new int [nodes];order = new int [nodes];

     for(int i = 0;i < nodes;i++) visited[i] = false;

     for(int e = 0;e < nodes;e++)
	 for(int j = 0;j < nodes;j++) edges[e][j] = false;

     cout << "\nNow give the edges one-by-one\n\n";
     while(sides--)
     {
	 int start,end;
	 cout << "From : ";cin >> start;
	 cout << "To : ";cin >> end;cout << "\n";
	 edges[start - 1][end - 1] = 1;edges[end - 1][start - 1] = 1;
     }
}

boolean Graph :: isConnected()
{
    
    for(int f = 0;f < nodes;f++) visited[f] = false;
    visited[0] = true;

    for(int i = 1;i < nodes;i++)
	   if(edges[0][i] && !visited[i])
	   {
	      visited[i] = true;
	      dfs(i);
	   }

    for(int w = 0;w < nodes;w++)
	if(!visited[w]) return false;

    return true;
}

void Graph :: traverse()
{
     for(int i = 0;i < nodes;i++)
	if(!visited[i])
	{
	   visited[i] = true;
	   order[++x] = i + 1;
	   dfs(i);
	}
}

void Graph :: dfs(int source)
{
     for(int i = 0;i < nodes;i++)
	if(edges[source][i] && !visited[i])
	{
	   visited[i] = true;
	   order[++x] = i + 1;
	   dfs(i);
	}
}

void Graph :: print()
{
    cout << "\n[ " << order[0];
    for(int i = 1;i < nodes;i++) cout << " , " << order[i];
    cout << " ]\n";
    x = -1;
}

void Graph :: randomize()
{
    Timer t;
    cout << "\nNow comes the data to be tabulated\n";
    for(int i = 1;i < MAX;i++)
    {
	nodes = i;
	visited = new int [nodes];order = new int [nodes];
	for(int c = 0;c < nodes;c++) visited[c] = false;

	for(int j = 0;j < nodes;j++)
	    for(int k = 0;k < nodes;k++)
		edges[j][k] = -1;

	for(int row = 0;row < nodes;row++)
	   for(int col = 0;col < nodes;col++)
	   {
	       if(edges[row][col] != -1) continue;
	       int tmp = rand() % 2;
	       edges[row][col] = edges[col][row] = tmp;
	   }
	t.start();traverse();t.stop();
	cout << "For nodes : " << nodes << " time taken is : " << t.time();
	cout << " seconds\n";t.reset();
    }
}

int main()
{
    Graph G;
    Timer t;
    clrscr();

    G.input();
    t.start();G.traverse();t.stop();
    if(G.isConnected() == false) cout << "\nThe graph is UN-connected\n";
    else cout << "\nThe graph is connected\n";
    G.print();
    
    cout << "\nTime taken for this operation is : " << t.time() << " seconds\n";
    G.randomize();
    getch();
    return 0;
}
