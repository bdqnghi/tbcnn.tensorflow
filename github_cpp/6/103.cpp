#include<stdio.h>
#include<conio.h>
#include<limits.h>
#include<stdlib.h>
int edge[10][10],size,item;
char vertex[10];
int visited[10],d_time[10],f_time[10];
int i,j,t=0;
void dfs_visit(int);
void build_graph()
{
	printf("enter number of vertices");
	scanf("%d",&size);
	printf("enter %d vertices of graph",size);
	for(i=0;i<size;i++)
	{
		fflush(stdin);
		scanf("%c",&vertex[i]);
	}
	printf("enter the adjancy matrix for the graph\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			scanf("%d",&edge[i][j]);
		}
	}
	printf("\nthe adjecy amtrix is given as:\n");
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			printf("%d\t",edge[i][j]);
		}
		printf("\n");
	}
}
void dfs()
{
	for(i=0;i<size;i++)
	{
		visited[i]=0;
	}
	for(j=0;j<size;j++)
	{
		if(!visited[j])
		{
			dfs_visit(j);
		}
	}
}
void dfs_visit(int item)
{
	t=t+1;
	d_time[item]=t;
	visited[item]=1;
	for(i=0;i<size;i++)
	{
		if(edge[item][i]==1 && !visited[i])
		{
			dfs_visit(i);
		}
	}
	t=t+1;
	f_time[item]=t;
}
int main()
{
	build_graph();
	dfs();
	printf("\nafter applying depth first search\n vertex \t discovery time \t finish time \n");
	for(i=0;i<size;i++)
	{
		printf("%c \t\t %d \t\t\t %d \n",vertex[i],d_time[i],f_time[i]);
	}
	getch();
	return 0;
}


