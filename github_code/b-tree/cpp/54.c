/*
 * st_b+_tree.h
 *
 *  Created on: 2011-12-5
 *      Author: kine
 */

#ifndef ST_B__TREE_CPP_H_
#define ST_B__TREE_CPP_H_

//#include "stlib.h"

//ST_BEGIN_DECLS;
class BTree
{
public:
	int n;       								//�ýڵ������ؼ��ֵĸ���  ���ڵ���2
	BTree *father;
	static int number;							//����   ���ڵ���3
	static BTree *root;
	BTree();
	int *data;
	BTree **down;

	static bool inserttree(int t);				//�����в���t
	static	BTree* searchinsert(int t);			//�������뵽ĳ�ڵ�
	bool insertpoint(int t,BTree *p);			//�ڽڵ����
	void split(int t,BTree *p);  				//����

	static void treedel(int t);
	void  delpoint(int t);
	static BTree*searchdel(int t);				//����ɾ��ĳ�ڵ�
	void combine();

	static int deep;  							//���
	static void deletetree();
};


class dui					// b+tree�Ķѳ���
{
public :
	BTree * data[200];  	//Ԫ��
	int   num[200];    		//��Ԫ���ǵڼ����
	int tp,tl;				//tpΪ��ͷ��tlΪ��β
	dui(){tp=0;tl=0;}		// ��ʼ�����캯��
	BTree* pop();
	void push(BTree*,int);
	bool empty();
};

struct node
{
   BTree* q;
   node *next;
};


extern void Create(int m) ;
extern void searchlink(int t) ;
extern void searchroot(int t) ;
extern void st_bb_tree_cpp_test(void);
extern void bbprinttree(BTree *q);


//ST_END_DECLS;


#endif /* ST_B__TREE_CPP_H_ */
