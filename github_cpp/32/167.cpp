# include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int source,dest,weight;
};
struct Graph
{
    int v,e;
    struct Edge *edge;
};
struct Graph *createGraph(int nodes,int edges)
{
    struct Graph *graph=(struct Graph*)malloc(sizeof(struct Graph));
    graph->v=nodes;
    graph->e=edges;
    graph->edge=(struct Edge*)malloc(edges*sizeof(struct Edge));
    return graph;
};
struct Subset
{
    int parent;
    int rank;
};
int find(struct Subset subsets[],int i)
{
    if(subsets[i].parent!=i)
        subsets[i].parent=find(subsets,subsets[i].parent);
    return subsets[i].parent;
}
void Union(struct Subset subsets[],int x,int y)
{
    int xroot=find(subsets,x);
    int yroot=find(subsets,y);
    if(subsets[xroot].rank<subsets[yroot].rank)
        subsets[xroot].parent=yroot;
    else if(subsets[yroot].rank<subsets[xroot].rank)
        subsets[yroot].parent=xroot;
    else
    {
        subsets[yroot].parent=xroot;
        subsets[xroot].rank++;
    }
}
int cmp(const void* a,const void* b)
{
    struct Edge *a1=(struct Edge*)a;
    struct Edge *b1=(struct Edge*)b;
    return a1->weight>b1->weight;
}
int kruskal(struct Graph *graph)
{
	int answer=0;
    int V=graph->v;
    struct Edge result[V];
    int e=0;
    int i=0;
    qsort(graph->edge,graph->e,sizeof(graph->edge[0]),cmp);
    struct Subset *subsets=(struct Subset*)malloc(V*sizeof(struct Subset));
    for(int j=0;j<V;j++)
    {
        subsets[j].parent=j;
        subsets[j].rank=0;
    }
    while(e<V-1)
    {
        struct Edge nextEdge=graph->edge[i++];
        int x=find(subsets,nextEdge.source);
        int y=find(subsets,nextEdge.dest);
        if(x!=y)
        {
            result[e++]=nextEdge;
			answer+=nextEdge.weight;
            Union(subsets,x,y);
        }
    }
	return answer;
}
int main(void)
{
    int t,p,n,m,a,b,c;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&p,&n,&m);
        struct Graph *graph=createGraph(n,m);
        int i=0;
        while(m--)
        {
            scanf("%d%d%d",&a,&b,&c);
			a--,b--;
            graph->edge[i].source=a;
            graph->edge[i].dest=b;
            graph->edge[i].weight=c;
            i++;
        }
        printf("%d\n",kruskal(graph)*p);;
    }
}           
