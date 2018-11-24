#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

int N;
int E;

typedef struct edge
{
	int from;
	int to;
	int len;
	int w;
}edge;

edge e[MAX];
int nodeset[MAX];

int com(void* a,void* b)
{
	edge* aa=(edge*)a;
	edge* bb=(edge*)b;
	return aa->w<bb->w;
}
int init()
{
	int i=0;
	while(i<E)
	{
		scanf("%d%d%d%d",&e[i].from,&e[i].to,&e[i].len,&e[i].w);
		i++;
	}

	for(i=0;i<N;i++)
	{
		nodeset[i]=i;
	}

}
int kruskal()
{
	int j=0;
	int tem;
	int sum=0;
	int len=0;
	for(j=0;j<E;j++)
	{
		if(nodeset[e[j].from]!=nodeset[e[j].to])
		{
			
			sum+=e[j].w;
			len+=1;
			tem=e[j].from;
			nodeset[e[j].from]=nodeset[e[j].to];
			for(int k=0;k<N;k++)
				if(nodeset[k]==tem)
					nodeset[k]=nodeset[tem];
			if(len>=N-1)
				break;
		}
	}

	if(len>=N-1)
		return sum ;
	else
		return 0;
}

int main()
{
	freopen("in.txt","r",stdin);
	int res;
	while(scanf("%d%d",&N,&E)!=EOF)
	{
		init();
		res=kruskal();
		if(res>0)
			printf("%d %d",N-1,res);
		else
			printf("no exit");


	}
	return 0;
}

