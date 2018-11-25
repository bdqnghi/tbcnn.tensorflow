#include "StdAfx.h"
#include "MinimumSpanningTree.h"


MinimumSpanningTree::MinimumSpanningTree(void)
{
}


MinimumSpanningTree::~MinimumSpanningTree(void)
{
}


void MinimumSpanningTree::MakeSet(Vertex* x)
{
	x->Pre=x;
	x->Rank=0;
}

void MinimumSpanningTree::Link(Vertex* x,Vertex* y)
{
	if(x->Rank>y->Rank)
	{
		y->Pre=x;
	}
	else 
	{
		x->Pre=y;
		if(x->Rank==y->Rank)
		{
			y->Rank=y->Rank+1;
		}
	}
}

Vertex* MinimumSpanningTree::FindSet(Vertex* x)
{
	if(x!=x->Pre)
	{
		x->Pre=FindSet(x->Pre);
	}
	return x->Pre;
}

void MinimumSpanningTree::Union(Vertex* x,Vertex* y)
{
	Link(FindSet(x),FindSet(y));
}
//����������ɭ�������Ų�ͬ���ı����棬�ҵ�Ȩ����С�ı�
void MinimumSpanningTree::Kruskal(Graph& g,Edge* list[])
{
	//�����н����Ϊһ����
	for(int i=0;i<g._verCount;++i)
	{
		MakeSet(g._verteies[i]);
	}
	//�ҵ�Ȩ����С�ı�����������
	InsertionSort<Edge*> is;
	//���ߵ�Ȩ����������
	is.SortP(g._edges,g._edgeCount);
	int index=0;
	for (int i=0;i<g._edgeCount;++i)
	{
		//��֤�����ߵ�������㲢����һ������������γɻ�·
		if(FindSet(g._edges[i]->Start)!=FindSet(g._edges[i]->End))
		{
			list[index++]=g._edges[i];
			//���ӱߵ��������ĸ��ڵ�
			Union(g._edges[i]->Start,g._edges[i]->End);
		}
	}
}
//��������ĸ��ڵ㿪ʼһֱ���󵽸������н��Ϊֹ
void MinimumSpanningTree::Prim(Graph& g,Vertex* v)
{
	//Key ��ʾ���в��ڵ�ǰ���еĽ���ܹ����ӵ����н�����С��Ȩ��
	//��ʼ�������
	for(int i=0;i<g._verCount;++i)
	{
		g._verteies[i]->Key=INT_MAX;
		g._verteies[i]->Pre=NULL;
	}
	//���ÿ�ʼ���
	v->Key=0;
	//���б�����δ���ӵ����еĽ��
	FibonacciHeap heap;
	for(int i=0;i<g._verCount;++i)
	{
		HeapNode<int>* node=new HeapNode<int>;
		node->Key=g._verteies[i]->Key;
		node->Tag=g._verteies[i]->Index;
		g._verteies[i]->Tag=node;
		g._verteies[i]->IsInHeap=true;
		heap.Insert(node);
	}
	//ÿ��ȡ���������ӵ����е���СȨ�صĽ��
	HeapNode<int>* temp=heap.ExtractMin();
	while(temp!=NULL)
	{
		//�ҵ����п�����u������ӵĽ��v
		//���v��δ���ӵ����в���w(u,v)С�ڵ�ǰv��key�������
		Vertex* u=g._verteies[temp->Tag];
		u->IsInHeap=false;
		for(int i=0;i<g._verCount;++i)
		{
			Vertex* v=g._verteies[i];
			if(g._adj[temp->Tag][i]!=INT_MAX&&v->IsInHeap&&g._adj[temp->Tag][i]<v->Key)
			{
				v->Pre=u;
				v->Key=g._adj[temp->Tag][i];
				//������Ҫ���¶��еļ�
				heap.DecreaseKey((HeapNode<int>*)v->Tag,v->Key);
			}
		}
		temp=heap.ExtractMin();
	}
}