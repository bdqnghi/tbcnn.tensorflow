#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<malloc.h>
#include<time.h>

// ����� ������� ������������
#define BALANCE_FLAG_R	1	// ��������� ��������
#define BALANCE_FLAG_H	2	// ��������� ��������� ������ ������������ ��������

//! AVL ������
class AVL_tree{
protected:
	//! ���� ������
	struct node_st {
		node_st *p1;	//!< ����� �����
		node_st *p2;	//!< ������ �����
		int value;		//!< �������� ����
		int b;			//!< ������ �������
	};
	node_st *tree_root;	//!< ������ ������
private:
	int count;									//!< ����� ����� ������
	node_st *NewItem(int value);				//!< ������� ����
	void DelItem(node_st *node);				//!< ������� ����
	void Clear(node_st *node);					//!< �������  (����������� �����)
	bool Insert(node_st **node,int value);		//!< �������  (����������� �����)
	bool Remove(node_st **node,int value);		//!< �������� (����������� �����)
	bool GetMin(node_st **root,node_st **res);	//!< ����� ����������� ���� (����������� �����)
	node_st *Rotate12(node_st*);				//!< �������� 
	node_st *Rotate21(node_st*);				//!< ��������
	int Balance(node_st**,int);					//!< ������������ ����
public:
	AVL_tree();
	~AVL_tree();				
	void Clear();				//!< ���� ������
	void Insert(int value);		//!< ������� ��������
	void Remove(int value);		//!< �������� ��������
	bool Find(int value);		//!< ����� ��������
	int GetCount();				//!< ������ ���������� ����� ������
};


AVL_tree::AVL_tree()
{
	tree_root=0; count=0;
}

AVL_tree::~AVL_tree()
{
	Clear(tree_root);
}

int AVL_tree::GetCount()
{
	return count;
}

void AVL_tree::Clear()
{
	Clear(tree_root);
	tree_root=0;
}

void AVL_tree::Clear(node_st *node)
{
	if(!node) return;
	Clear(node->p1);
	Clear(node->p2);
	DelItem(node);
}

AVL_tree::node_st *AVL_tree::NewItem(int value)
{
	count++;
	node_st *node=new node_st;
	node->b=0;
	node->value=value;
	node->p1=node->p2=0;
	return node;
}

void AVL_tree::DelItem(node_st *node)
{
	count--;
	delete node;
}

void AVL_tree::Insert(int value)
{
	Insert(&tree_root,value);
}

void AVL_tree::Remove(int value)
{
	Remove(&tree_root,value);
}

bool AVL_tree::Find(int value)
{
	node_st *node=tree_root;
	while(node) {
		if(node->value==value) return true;
		if(node->value>value) node=node->p1; else node=node->p2;
	}
	return false;
}

int AVL_tree::Balance(node_st **root,int res=0)
{
	node_st *node=*root; 
	if(node->b>1) {
		res=BALANCE_FLAG_R;
		if(node->p2->b) res|=BALANCE_FLAG_H;
		if(node->p2->b<0) node->p2=Rotate12(node->p2);
		*root=Rotate21(node);
	}
	if(node->b<-1) {
		res=BALANCE_FLAG_R;
		if(node->p1->b) res|=BALANCE_FLAG_H;
		if(node->p1->b>0) node->p1=Rotate21(node->p1);
		*root=Rotate12(node);
	}
	return res;
}

bool AVL_tree::Insert(node_st **root,int value)
{
	bool res=false;
	node_st *node=*root;
	if(!node) {
		*root=NewItem(value);
		return true;
	}
	if(value==node->value) return false; 
	if(value<node->value) res=Insert(&node->p1,value) && !!--node->b;
	else                  res=Insert(&node->p2,value) && !!++node->b;
	if(Balance(root)&BALANCE_FLAG_R) res=false;
	return res;
}

AVL_tree::node_st *AVL_tree::Rotate12(node_st *node)
{
	static const int array[6][4]={
		-1,-1,+1,+1,
		-1,+0,+1,+0,
		-1,+1,+2,+0,
		-2,-1,+0,+0,
		-2,-2,+0,+1,
		-2,+0,+1,-1 
	};
	node_st *p1=node->p1;
	node_st *p12=p1->p2;
	p1->p2=node;
	node->p1=p12;
	for(int n=0;n<6;n++) if(array[n][0]==node->b && array[n][1]==p1->b) {
		p1->b=array[n][2];
		node->b=array[n][3];
		break;
	}
	return p1;
}

AVL_tree::node_st *AVL_tree::Rotate21(node_st *node)
{
	static const int array[6][4]={
		+1,-1,-2,+0,
		+1,+0,-1,+0,
		+1,+1,-1,-1,
		+2,+0,-1,+1,
		+2,+1,+0,+0,
		+2,+2,+0,-1 
	};
	node_st *p2=node->p2;
	node_st *p21=p2->p1;
	p2->p1=node;
	node->p2=p21;
	for(int n=0;n<6;n++) if(array[n][0]==node->b && array[n][1]==p2->b) {
		p2->b=array[n][2];
		node->b=array[n][3];
		break;
	}
	return p2;
}

// \retval res ���������� ������ �� �������� ����
bool AVL_tree::GetMin(node_st **root,node_st **res)
{
	node_st *node=*root;
	if(node->p1) {
		if(GetMin(&node->p1,res) && !++node->b) return true;
		return !!(Balance(root)&BALANCE_FLAG_H);
	}
	*res=node;
	*root=node->p2;
	return true;
}


bool AVL_tree::Remove(node_st **root,int value)
{
	bool ok=false;
	node_st *node=*root;
	if(!node) return ok;
	if(node->value<value) {
		if(Remove(&node->p2,value) && !--node->b) ok=true;
	}else if(node->value>value) {
		if(Remove(&node->p1,value) && !++node->b) ok=true;
	}else {							// ����� ������� ���. ���� �������
		if(!node->p2) {				// ���� ���� ����������� �������� �����, ��������
			*root=node->p1;DelItem(node);
			return true;
		}
		ok=GetMin(&node->p2,root);	// ������� �������, ������� ��������� �� ����� ��������
		(*root)->b =node->b;		// ������ �� ����� �������� �������, ���� ������
		(*root)->p1=node->p1;
		(*root)->p2=node->p2;
		DelItem(node);
		if(ok) ok=!--(*root)->b;
	} 
	return !!(Balance(root,ok?BALANCE_FLAG_H:0)&BALANCE_FLAG_H);
}


//======================================================================
// ������ ������

class Test:public AVL_tree{
	int max(int a,int b) {return a<b?b:a;}
	bool Walk(node_st *node,bool *array,int size);
	int CheckBalance(node_st *node);
	bool CheckStruct(node_st *node);
public:
	void Check(bool *array,int size);
};

bool Test::Walk(node_st *node,bool *array,int size)
{
	if(!node) return false;
	int v=node->value;
	if(v<0 || v>=size || array[v]) 
		return true;
	array[v]=true;
	return Walk(node->p1,array,size) || Walk(node->p2,array,size);
}


int Test::CheckBalance(node_st *node)
{
	int h1,h2;
	if(!node) return 0;
	h1=CheckBalance(node->p1);
	h2=CheckBalance(node->p2);
	if(h1<0 || h2<0) return -1;
	if(node->b!=h2-h1) return -1;
	if(abs(node->b)>1) return -1;
	return max(h1,h2)+1;
}

bool Test::CheckStruct(node_st *node)
{
	if(node->p1) {
		if(node->value<=node->p1->value) return true;
		if(CheckStruct(node->p1)) return true;
	}
	if(node->p2) {
		if(node->value>=node->p2->value) return true;
		if(CheckStruct(node->p2)) return true;
	}
	return false;
}


void Test::Check(bool *array,int size)
{
	bool *temp=(bool*)alloca(size);
	memset(temp,false,size);
	if(tree_root && Walk(tree_root,temp,size)) printf("value error1 !\n\a");
	if(memcmp(array,temp,size))  printf("value error2 !\n\a");
	if(CheckStruct(tree_root))  printf("struct error !\n\a");
	if(CheckBalance(tree_root)<0) printf("balance error!\n\a");
}


#define SIZE 10000

int main()
{
	Test obj; int n,i;
	bool array[SIZE]; 
	memset(array,false,sizeof(array));
	clock_t c1=clock();
	for(n=0; n<SIZE*100; n++) {
		i=rand()%SIZE;
		if(array[i]) obj.Remove(i),array[i]=false;
		else obj.Insert(i),array[i]=true;
	}
	clock_t c2=clock();
	printf("nodes count: %d\n",obj.GetCount());
	printf("time: %dms\n",c2-c1);
	obj.Check(array,SIZE);
	obj.Clear();
	printf("[press enter]\n");
	getchar();
	return 0;
}


