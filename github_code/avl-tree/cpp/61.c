#include<iostream>
using namespace std;
#include"AVLTree.h"
#include"RBTree.h"

void TestAVLTree()
{
	/*int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };*/
	/*int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };*/
	int arr[] = {8,5,15,16,10,12,2};   //�������ݣ������ǲ����ʱ��ͻ�������⣬��Ϊ���������� ������ʱ��ֱ�� ��ƽ������
								//��Ϊ��0������ʵ���У�������ִ�е�����12֮��8��ƽ�����Ӳ�Ӧ����0��������Ի�ͼ������
								//����ֻ�Ǵ��������������ǣ������ǲ���2֮��ͳ��������ˣ���Ϊ8��ƽ��������0�����Բ���2
								//֮��8��ƽ�����ӱ�Ӧ����-2���������ڱ����-1������Ҫ����
	int len = sizeof(arr) / sizeof(arr[0]);
	AVLTree<int> tree;
	for (int i = 0; i < len; i++)
	{
		tree.Insert(arr[i]);
	}

	//tree.Insert(5);
	//tree.Insert(8);
	//tree.Insert(1);
	//tree.Insert(7);
	//tree.Insert(9);
	//tree.Insert(-5);
	///*tree.Insert(2);
	//tree.Insert(3);
	//tree.Insert(4);*/
	//tree.Insert(-4);
	tree.IsBanlance();


}

void TestRBTree()
{
	RBTree<int> tree;
	tree.Insert(16);
	tree.Insert(8);
	tree.Insert(32);
	tree.Insert(4);
	tree.Insert(2);
	tree.Insert(3);
	tree.IsBanlance();
}


int main()
{
	/*TestAVLTree();*/
	TestRBTree();
	return 0;
}