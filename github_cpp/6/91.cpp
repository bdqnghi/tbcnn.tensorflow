





#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

const int MAX_VEX_NUM = 20;
		    	      
bool visited[MAX_VEX_NUM];    
			      
typedef enum {DG, DN, UDG, UDN} GraphKind;

typedef string vextype; 

typedef struct ArcNode{  
	int adjvex;   
	struct ArcNode *nextarc;   
	int info;
}ArcNode;

typedef struct VNode{  
	vextype data;
	ArcNode *firstarc;
}VNode, AdjList[MAX_VEX_NUM];  

typedef struct ALGraph{   
	AdjList adjlist;  
	int vexnum;   
	int arcnum;   
	int kind;
}ALGraph;


void CreateAdjList(ALGraph &G, int kind);
void print(const ALGraph &G);
int clear(ALGraph &G);
void DFSTraverse(ALGraph &G);
void DFS(ALGraph &G, int v);
int FirstAdjVex(ALGraph &G, int v);  
int NextAdjVex(ALGraph &G, int v, int w);   


static ArcNode *next;  

void CreateAdjList(ALGraph &G, int kind)
{
	int i,j,k;
	int weight;
	G.kind = kind;
	cout << "输入顶点个数:";
	cin >> G.vexnum;
	cout << "输入弧或边个数:";
	cin >> G.arcnum;

	cout << "输入每个顶点信息(V1,V2,V3...):\n";
	for(i = 0; i < G.vexnum; ++i)  
	{
		cin >> G.adjlist[i].data;
		G.adjlist[i].firstarc = NULL;
	}
	cout << "输入弧或边的两头顶点序号(若是有向的，则输入循序为:尾 头，例如1 2代表顶点1指向顶点2):\n";
	for(k = 0; k < G.arcnum; ++k)
	{
		cin >> i;
		cin >> j;
		
		next = new ArcNode;
		next->adjvex = j-1;
		next->nextarc = G.adjlist[i-1].firstarc;
		G.adjlist[i-1].firstarc = next;

		if(G.kind == DN || G.kind == UDN)
		{
			cout << "输入顶点" << i << "和顶点" << j << "之间的权值:";
			cin >> next->info;
			weight = next->info;
		}
		
		if(G.kind == UDG || G.kind == UDN)
		{
			next = new ArcNode;
			next->adjvex = i-1;
			next->nextarc = G.adjlist[j-1].firstarc;
			G.adjlist[j-1].firstarc = next;
			if(G.kind == UDN)
			{
				next->info = weight;
			}
		}
	}
}

void print(const ALGraph &G)
{
	int i;
	ArcNode *node;  

	cout << "图的邻接表:\n";
	for(i = 0; i < G.vexnum; ++i)
	{
		node = G.adjlist[i].firstarc;
		cout << i << "-" << G.adjlist[i].data << ": ";
		if(G.kind == DN || G.kind == UDN)
		{
			while(NULL != node)
			{
				cout << node->adjvex << "(weight:" << node->info << ")  ";
				node = node->nextarc;
			}
		}
		else
		{
			while(NULL != node)
			{
				cout << node->adjvex << " ";
				node = node->nextarc;
			}
		}
		cout << endl;
	}
}


int clear(ALGraph &G)
{
	if(NULL == G.adjlist[0].firstarc) return 0;

	ArcNode *p, *q;
	for(int i = 0; i < G.vexnum; ++i)
	{
		p = G.adjlist[i].firstarc;
		while(p)
		{
			q = p->nextarc;
			delete p;
			p = q;
		}
		G.adjlist[i].firstarc = NULL;
	}

	return 0;
}


int FirstAdjVex(ALGraph &G, int v)  
{
	if(v < 0 || v >= G.vexnum)
		return -1;
	
	if(G.adjlist[v].firstarc != NULL)
		return G.adjlist[v].firstarc->adjvex;  
	else
		return -1;
}


int NextAdjVex(ALGraph &G, int v, int w)   
{
	if(v < 0 || v >= G.vexnum)
		return -1;

	ArcNode *p = G.adjlist[v].firstarc;
	if(NULL == p)
		return -1;
	while(1)
	{
		if(p->adjvex == w && p->nextarc != NULL)
		{
			return p->nextarc->adjvex;
		}
		else if(p->adjvex != w && p->nextarc != NULL)
		{
			p = p->nextarc;
		}
		else if(p->adjvex == w && p->nextarc == NULL)
		{
			return -1;
		}
		else if(NULL == p || (p->adjvex != w && p->nextarc == NULL)) 
			return -1;
	}
}


void DFSTraverse(ALGraph &G)
{
	int i;
	for(i = 0; i < G.vexnum; ++i)  
	{
		visited[i] = false;
	}
	for(i = 0; i < G.vexnum; ++i)
	{
		if(!visited[i])  
		{
			DFS(G, i);
		}
	}
}
void DFS(ALGraph &G, int v)
{
	int w;
	
	visited[v] = true;  
	cout << "访问顶点:" << v << endl;  
	
	for(w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))  
	{ 
		if(!visited[w])  
		{
			DFS(G, w); 
		}		   
	}
}




int main()
{
	int i=0,j=0;
	ALGraph G;
	
	cout << "无向网:\n";
	CreateAdjList(G, UDN);
	print(G);
	clear(G);

	cout << "有向图:\n";
	CreateAdjList(G, DG);
	print(G);
	cout << "深度优先搜索:\n";
	DFSTraverse(G);

	clear(G);

	cout << "无向图:\n";
	CreateAdjList(G, UDG);
	print(G);
	cout << "深度优先搜索:\n";
	DFSTraverse(G);
	clear(G);

	cout << "有向网:\n";
	CreateAdjList(G, DN);
	print(G);
	clear(G);

	return 0;
}











