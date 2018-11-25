

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

struct listnode { struct listnode *next; int vertexnumber;};
struct double_listnode { struct double_listnode *next; struct double_listnode *previous; int vertexnumber;};



struct listnode *topological_sort(int n, int *precede){
	
	double_listnode** bucket; bucket = new double_listnode*[n];		
	double_listnode** vertex; vertex=new double_listnode*[n];	
	int *verPos = new int[n];	
	listnode* topologList = NULL; 
	
	int i=0,j=0, outDeg=0;
	double_listnode *tmp=NULL;	listnode* ptr=NULL;
	
	for (i=0; i<n;i++) { verPos[i] = -1; vertex[i]=NULL; bucket[i]=NULL;}

	
	for (i=0; i<n; i++)	{
		outDeg=0;
		for (j=0; j<n; j++)	{
			if (*(precede+ i*n + j)==1){	
				outDeg++;
			}
		}
		tmp=new double_listnode; 
		tmp->next = bucket[outDeg];	tmp->previous=NULL; tmp->vertexnumber = i;	
	

		if (tmp->next) {bucket[outDeg]->previous=tmp;}
		bucket[outDeg]=tmp;	vertex[i]=tmp;	verPos[i]=outDeg;
	}

	
	while (bucket[0])	
	{
		ptr=topologList;
		topologList = new listnode;	topologList->next = ptr; topologList->vertexnumber = bucket[0]->vertexnumber;
		tmp=bucket[0];	bucket[0]=bucket[0]->next; 
		if (bucket[0]) {bucket[0]->previous = NULL; }
		if (bucket[0])delete tmp; 
		for (i=0; i<n; i++){
			if(*(precede+i*n + (topologList->vertexnumber)) == 1){	
				
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

