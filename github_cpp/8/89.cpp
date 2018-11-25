#include <iostream>
#include <string>
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <list>
using namespace std;


list <string> mylist;

void toplogical_sort(graph *gr);

void dfs(graph *gr);

void dfs_visit(graph *gr , vertex *u);

int TIME = 0 ;

void print_path(graph *gr);

int main(int argc , char * argv[])
{

	graph *gr = new graph();

	vertex *v1 = new vertex();
	vertex *v2 = new vertex();
	vertex *v3 = new vertex();
	vertex *v4 = new vertex();
	vertex *v5 = new vertex();
	vertex *v6 = new vertex();

	v1->element = "U";
	v2->element = "V";
	v3->element = "W";
	v4->element = "Z";
	v5->element = "Y";
	v6->element = "X";	
	

	
	gr->addVertex(v1);
	gr->addVertex(v2);
	gr->addVertex(v3);
	gr->addVertex(v4);
	gr->addVertex(v5);
	gr->addVertex(v6);

	gr->addEdge(v1,v2,1);
	gr->addEdge(v1,v6,1);
	gr->addEdge(v6,v2,1);
	gr->addEdge(v2,v5,1);
	gr->addEdge(v5,v6,1);
	gr->addEdge(v3,v5,1);
	gr->addEdge(v3,v4,1);
	gr->addEdge(v4,v4,1);
	

	toplogical_sort(gr);

	
	return 0;
	
	
}


void toplogical_sort(graph *gr)
{
		
		
	
	dfs(gr);
		
	
	cout << "Topolgically sorted :";
		
	
	for (list<string>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
    
	
		cout << " " << *it;
		
		
	cout<<" "<<endl;
		
		

}

void dfs(graph *gr)
{

	
	
	for(int i = 0 ; i < gr->numVerticies; i++)
	
	{
		
		
		
		gr->verticies[i]->color = 1;
		
		
		
		gr->verticies[i]->parent = NULL;
	
		
		
	}
	
	
	
	for(int i = 0 ; i < gr->numVerticies; i++)
	{
		
		
		if (gr->verticies[i]->color == 1)
		{
		
			
			
		dfs_visit(gr , gr->verticies[i]);

		}

	}

}



void dfs_visit(graph *gr , vertex *u)
{
	
	
	
	TIME = TIME + 1;
	
	
	
	int index = gr->indexOf(u);
	
	
	
	gr->verticies[index]->start_time = TIME;
	
	
	
	gr->verticies[index]->color = 2;
	
	
	
	
	vertex ** arrofadjvert = (vertex**)malloc(sizeof(vertex)*gr->getsizeofadjVerticies(u));
	
	
	
	
	arrofadjvert = gr->arrayofadjacentVertex(u);
	
		
		
		
		for(int i = 0 ; i< gr->getsizeofadjVerticies(u) ; i++)
	
	{
			
			
			vertex *v = new vertex();
			
			
			
			v = arrofadjvert[i];
			
			
			
			if(v->color == 1)
			{
			
				
				
				gr->verticies[gr->indexOf(v)]->parent = gr->verticies[index] ;
				
				
				
				dfs_visit(gr,gr->verticies[gr->indexOf(v)]);
				
			}
	
	
	}
	
	
	gr->verticies[gr->indexOf(u)]->color = 3;
	


	mylist.push_front(gr->verticies[gr->indexOf(u)]->element);
	
	
	TIME = TIME + 1;
	
	
	
	gr->verticies[gr->indexOf(u)]->end_time = TIME;
	
}


