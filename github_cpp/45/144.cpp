/*
��Ŀ��������һ��Ford-Fulkerson�㷨
��Ŀ��������hihocoder115��
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;
#define N 40005
using namespace std;

const int MaxN=505;
const int inf=0x7fffffff;

struct Edge{
	int u,v,c;
	int next;
}edge[N];

int cnt;
int head[N];

void addedge(int u, int v, int c)
{
	edge[cnt].u=u; edge[cnt].v=v; edge[cnt].c=c;
	edge[cnt].next=head[u]; head[u]=cnt++;

	edge[cnt].u=v; edge[cnt].v=u; edge[cnt].c=0;
	edge[cnt].next=head[v]; head[v]=cnt++;
}

int m,n;
int source,sink;	//	Դ��ͻ��
int gap[MaxN];		//	gap�Ż�
int dep[MaxN];		//	����
int cur[MaxN];		//	��ǰ���Ż�
int stck[MaxN];		//	��һ��ջ��������·��

void rec_bfs()		//	�Բ�����������ֲ�
{
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	queue<int> q;
	dep[sink]=0;	//	���sink�����Ϊ0
	gap[0]=1;		//	����Ϊ0�ĵ�һ��
	q.push(sink);

	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)	//	��uΪ���ı�
		{
			int v=edge[i].v;
			if(edge[i^1].c>0&&dep[v]==-1)		//	ÿ�δ洢�߶���������һ���ģ���Ϊ����������������edge[i^1].c��ʾu->v�ı�
			{
				q.push(v);
				dep[v]=dep[u]+1;
				gap[dep[v]]++;
			}
		}
	}
}

int SAP()
{
	rec_bfs();		//	ֻ��Ҫbfs�ֲ�һ�Σ�֮��Ĳ������²�������bfs
	memcpy(cur, head, sizeof(cur));	//	��ǰ����ʼ��Ϊ�ڽӱ�ĵ�һ��������head[i]
	int maxflow=0;
	int u=source;
	int top=0;
	int i;
	while(dep[source]<n)	//	������ֻ����n��������ڵ���n˵���м��Ѿ��ϲ���
	{
		if(u==sink)	//	�ҵ�һ������·����������·�޸�����
		{
			int delta=inf;
			int flag=n;		//	��¼����·���ϲ����������ٵı�
			for(i=0; i!=top; i++)
			{
				if(delta>edge[stck[i]].c)
				{
					delta=edge[stck[i]].c;
					flag=i;
				}
			}
			for(i=0; i!=top; i++)	//	·���ϸ��߲����������٣�����߲����������ӣ�����������
			{
				edge[stck[i]].c-=delta;
				edge[stck[i]^1].c+=delta;
			}
			maxflow+=delta;
			top=flag;				//	���ݵ�����ǡ�ñ�Ϊ0�����ϲ�ڵ㣬����Ѱ������·��
			u=edge[stck[top]].u;
		}
		for(i=cur[u]; i!=-1; i=edge[i].next)
		{
			int v=edge[i].v;
			if(edge[i].c>0 && dep[u]==dep[v]+1) break;	//	���ҵ�һ�����������ı���ֹͣ
		}
		if(i!=-1)
		{
			cur[u]=i;	//	��Ϊ��ǰ��
			stck[top++]=i;
			u=edge[i].v;
		}
		else	//	�Ҳ��������������ݣ�����Ѱ������·
		{
			//	��u�ڵ�Ĳ��������޸�
			if(--gap[dep[u]]==0) break;//	������ֶϲ㣬����
			int mind=n+1;
			for(i=head[u]; i!=-1; i=edge[i].next)
			//	Ѱ�ҿ����������С���
			{
				if(edge[i].c>0 && mind>dep[edge[i].v])
				{
					mind=dep[edge[i].v];
					cur[u]=i;
				}
			}
			dep[u]=mind+1;
			gap[dep[u]]++;
			u=(u==source)?u:edge[stck[--top]].u;	//	����
		}
	}
	return maxflow;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        int u,v,w;
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }
        source=1,sink=n;
        printf("%d\n",SAP());
    }
    return 0;
}