/*
 * **********************
 * By Carl Chinatomby
 * **********************
 * Fall 2009 Algorithms 
 * HW#4 - Toplogical Sort
 * 
 * Assignment: Implement Topological sort using double linked lists
 * and buckets. 
 * 
 * Given Prototypes:
 * struct listnode { struct listnode *next; int vertexnumber;};
 * struct double_listnode { struct double_listnode *next; struct double_listnode *previous; int vertexnumber;}
 * struct listnode *topological_sort(int n, int *precede)
 * 
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

struct listnode { struct listnode *next; int vertexnumber;};
struct double_listnode { struct double_listnode *next; struct double_listnode *previous; int vertexnumber;};

//pre:no directed cycles are present
//post: topological sorted single linked list is returned
struct listnode *topological_sort(int n, int *precede){
	//declarations
	double_listnode** bucket; bucket = new double_listnode*[n];		//bucket[i] denotes vertex with outdegree i
	double_listnode** vertex; vertex=new double_listnode*[n];	//pointer to the vertex in the bucket
	int *verPos = new int[n];	//denotes what bucket the vertex is in
	listnode* topologList = NULL; //stores the final list
	//iterators and temp pointers
	int i=0,j=0, outDeg=0;
	double_listnode *tmp=NULL;	listnode* ptr=NULL;
	//initializations
	for (i=0; i<n;i++) { verPos[i] = -1; vertex[i]=NULL; bucket[i]=NULL;}

	//fill up buckets based on outdegree, and link to vertex then update vertexPos
	for (i=0; i<n; i++)	{
		outDeg=0;
		for (j=0; j<n; j++)	{
			if (*(precede+ i*n + j)==1){	//if i precedes j
				outDeg++;
			}
		}
		tmp=new double_listnode; 
		tmp->next = bucket[outDeg];	tmp->previous=NULL; tmp->vertexnumber = i;	//head insert
	

		if (tmp->next) {bucket[outDeg]->previous=tmp;}
		bucket[outDeg]=tmp;	vertex[i]=tmp;	verPos[i]=outDeg;
	}

	//create topological list based on the buckets
	while (bucket[0])	//infinite loop if precondition fails
	{
		ptr=topologList;
		topologList = new listnode;	topologList->next = ptr; topologList->vertexnumber = bucket[0]->vertexnumber;//head insert
		tmp=bucket[0];	bucket[0]=bucket[0]->next; 
		if (bucket[0]) {bucket[0]->previous = NULL; }
		if (bucket[0])delete tmp; //remove from bucket
		for (i=0; i<n; i++){
			if(*(precede+i*n + (topologList->vertexnumber)) == 1){	//if i precedes current Vertex
				//remove preceding vertex and insert into 1 bucket lower
				if (vertex[i]->previous)	{vertex[i]->previous->next = vertex[i]->next;	}
				if (vertex[i]->next)	{vertex[i]->next->previous = vertex[i]->previous;	}
				vertex[i]->previous = NULL;
				verPos[i]--;
				tmp=bucket[verPos[i]];	bucket[(verPos[i])]=vertex[i];	bucket[verPos[i]]->next = tmp;	
				if (tmp) {tmp->previous = bucket[verPos[i]];}
			}
		}
	}
	return topologList;
}

int main(void)
{  
   /*
    This is the Professor's test code. Scores were either pass
    or fail depending on test code result and time complexity
    of the program.
   */
   int pre[1301*1301];
   int i,j,k;
   struct listnode *tmp;
   for(i=0; i< 1301; i++)
     for( j =0; j< 1301; j++ )
       pre[1301*i + j] = 0;
   for(i=0; i< 1300; i++)
   {   j = (89*i     +100)%1301;
       k = (89*(i+1) +100)%1301;
         pre[1301*j + k] = 1;
   }
   for(i=0; i< 1000; i++)
   {   j = (89*i     +100)%1301;
       k = (89*(i+1+ ((i*i)%201)) +100)%1301;
         pre[1301*j + k] = 1;
   }
   for(i=0; i< 30000; i++)
   {   int l,m;
       l = ( 37*i+987)%1301;
       m = (619*i+654)%1301;
       if( l < m ) 
       {  j = (89*l     +100)%1301;
          k = (89*m +100)%1301;
          pre[1301*j + k] = 1;
       }
   }
   printf("precondition matrix for directed graph with 1301 vertices\n");
   tmp =  topological_sort(1301, pre);
   printf("Testing the claimed sequence\n");
   i=0;
   while( tmp != NULL )
   {  if( tmp->vertexnumber != (89*i+100)%1301 )
      {  printf( "wrong sequence.\n");
         printf(" failed on %d list position\n", i);
         exit(0);
      }
      i +=1;
      tmp = tmp->next;
   }
   printf("Reached %d: last vertex. End test\n", i);
   exit(0);
}

