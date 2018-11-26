/***************************************************************************
 *  @file       TopologicalSort.cpp
 *  @author     jz
 *  @date       25 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	AOV������������(�ڽӱ�)
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����
#define MAX_VERTEX_NUM 20 //��󶥵����
enum GraphKind {DG,DN,UDG,UDN}; //������ͼ��������������ͼ����������
struct ArcNode
{
	int adjvex; //�û���ָ��Ķ����λ��
	ArcNode * nextarc; //ָ����һ������ָ��
	InfoType *info; //�û������Ϣ��ָ��
};
struct VNode
{
	VertexType data; //������Ϣ
	ArcNode * firstarc; //ָ���һ�������ڸö���Ļ���ָ��
};
typedef VNode AdjList[MAX_VERTEX_NUM];
struct ALGraph
{
	AdjList vertices;
	int vexnum,arcnum; //ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind; //ͼ�������־
};

//�Լ�ʵ�ֵ�
Status CreateDG(ALGraph &G)
//�����ڽӱ�洢��ʾ����������ͼG
{
	int i,j,k,IncInfo;
	puts("�����붥�������������Ƿ��л���Ϣ(1����,0��û��) �ո�ָ�");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("������ÿ�������ֵ");
	for(i=0;i<G.vexnum;++i) //���춥������
	{
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL; //��ʼ��ָ��
	}
	puts("������ÿ������ʼ��v1���յ�v2");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d",&i,&j);
		i=i-1; //ȷ��v1��v2��G�е�λ��
		j=j-1;
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)); //�ٶ����㹻�ռ�
		p->adjvex=j; //�Ի�ͷ��㸳ֵ
		p->nextarc=G.vertices[i].firstarc;
		p->info=NULL;
		G.vertices[i].firstarc=p; //�ڳ������뻡��ͷ�Ĳ���
		if(IncInfo)
			;//����ߵ���Ϣ
	}
}//CreateDG

//�Լ�ʵ�ֵ�
Status ShowGraph(ALGraph G)
//�����ڽӱ�,����Ļ�����ͼg������
{
	int i;
	ArcNode *p;
	puts("show �ڽӱ�");
	for(i=0;i<G.vexnum;i++)
	{
		printf("vex:%d ",G.vertices[i].data);
		p=G.vertices[i].firstarc;
		printf("firstarc:(show adjvex): ");
		while(p)
		{
			printf("%d ",(p->adjvex)+1);
			p=p->nextarc;
		}
		putchar('\n');
	}
	return OK;
}//ShowGraph

//�Լ�ʵ�ֵ�
Status FindInDegree(ALGraph G,int *indegree)
//�����ڽӱ�����ÿ����������ȣ�����������indegree��
{
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;++i)
		indegree[i]=0; //��ʼ������
	for(i=0;i<G.vexnum;++i)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			++indegree[p->adjvex];
			p=p->nextarc;
		}
	}
	return OK;
}

//=====����Ϊջ�Ĳ���=====
//__BEGIN -----������SqStack.cpp-----
typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACK_INCREMENT 10 //�洢�ռ��������

struct SqStack
{
	ElemType * base; //�ڹ���֮ǰ������֮��base��ֵΪnull
	ElemType * top; //ջ��ָ��
	int StackSize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
};

Status InitStack (SqStack &S)
//����һ����ջ
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base) //�洢����ʧ��
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,ElemType &e)
//��ջ���� �򷵻�e��ջ��Ԫ��
{
	if(S.top==S.base) //ջΪ��
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,ElemType e)
//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if(S.top-S.base>=S.StackSize)//ջ����׷�Ӵ洢�ռ�
	{
		S.base=(ElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)  //�洢����ʧ��
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,ElemType &e)
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
	if(S.top==S.base) //��ջ
		return ERROR;
	e=*--S.top;
	return OK;
}//Pop

//�Լ�ʵ�ֵ�
Status DestroyStack(SqStack &S)
//����ջS��S���ٴ���
{
	free(S.base);
	S.base=S.top=NULL;
	S.StackSize=0;
	return OK;
}//DestroyStack


//__END -----������SqStack.cpp-----

//__BEGIN -----������Conversion.cpp-----

//�Լ�ʵ�ֵ�
Status StackEmpty(SqStack S)
//��ջSΪ��ջ���򷵻�ture�����򷵻�false
{
	if(S.top==S.base) //��ջ
		return true;
	return false;
}//StackEmpty

//__END -----������Conversion.cpp-----

//__BEGIN -----������LineEdit.cpp-----

//�Լ�ʵ�ֵ�
void ClearStack(SqStack &S)
//��S��Ϊ��ջ
{
	S.top=S.base;
}//ClearStack

//__END -----������LineEdit.cpp-----

//=====����Ϊջ�Ĳ���=====
Status TopologicalSort(ALGraph G)
//����ͼG�����ڽӱ�洢�ṹ����G�޻�·�������G�Ķ����һ���������в�����OK�����򷵻�ERROR
{
	int indegree[MAX_VERTEX_NUM]; //���ÿ��������ȵ�����
	SqStack S;
	int i,j,k,count;
	ArcNode *p;
	FindInDegree(G,indegree); //��ÿ�����������
	InitStack(S);
	for(i=0;i<G.vexnum;++i)
		if(!indegree[i])
			Push(S,i);
	count=0; //������������
	printf("��������Ϊ��");
	while(!StackEmpty(S))
	{
		Pop(S,i);
		printf("%d ",G.vertices[i].data);
		++count; //���i�Ŷ��㲢����
		p=G.vertices[i].firstarc;
		while(p)
		{
			k=p->adjvex;
			if(!(--indegree[k]))
				Push(S,k); //����ȼ�Ϊ0������ջ
			p=p->nextarc;
		}//while
	}//while
	DestroyStack(S);
	if(count<G.vexnum)
		return ERROR;
	return OK;
}//TopologicalSort

//main������������
int main()
{
	ALGraph g;
	CreateDG(g);
	ShowGraph(g);
	TopologicalSort(g);
	return 0;
}
