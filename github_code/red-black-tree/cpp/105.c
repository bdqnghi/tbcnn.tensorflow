// chapter13.cpp : �������̨Ӧ�ó������ڵ㡣
//������������ƽ��������������

#include "stdafx.h"
#include<stdlib.h>
#include<time.h>
int main()
{
	BSTree T;
	AVL TB;
	RBTree rb;
	NodePoint rbHead=NULL;
	NodePoint head = TB.getHead();
	//srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int temp = 100+rand() % 1000;
		NodePoint p = new  Node{temp,NULL,NULL,NULL,0,BLACK};
		T.addNode(p);
		TB.addNode(head, NULL, temp);
		rb.insertNode(rbHead, temp);
		printf("%-8d", temp);
	}
	T.travers_BSTree(T.getHead());
	T.deleteNode(T.getHead(), 141);
	T.travers_BSTree(T.getHead());
	printf("\n");
	TB.travers_AVL(head);
	TB.deleteNode(head,124);
	TB.deleteNode(head, 100);
	printf("\n");
	TB.travers_AVL(head);
	printf("\n%d\n",head->height);
	//������Ĳ���
	printf("red-black-tree:\n");
	rb.travers_RBTree(rbHead);
	//�������ɾ��
	printf("\ndelete:\n");
	rb.deleteNode(rbHead, 567);
	rb.deleteNode(rbHead,600);
	rb.deleteNode(rbHead, 824);
	rb.travers_RBTree(rbHead);
    return 0;
}

