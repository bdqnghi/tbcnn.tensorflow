#include<iostream>
#include<stdlib.h>
using namespace std; 

static int Height(Position p) {
	if (p == NULL) {
		return -1; //����Ϊʲô��-1�� 
	}else {
		return p->height;
	}
}

static ElementType Max(ElementType a, ElementType b) {
	return a > b? a : b;
}

//�����ڲ�ƽ��ڵ��������ĵ���ת 
static Position SingleRotateWithLeft(Position k2) {
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	
	k2->height = Max(Height(k2->left),Height(k2->right)) + 1;
	
	k1->height = Max(Height(k1->left),k2->height) + 1;
	
	return k1; 
} 

//�����ڲ�ƽ��ڵ��������ĵ���ת 

static Position SingleRotateWithRight(Position k1) {
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	
	k1->height = Max(Height(k1->left),Height(k1->right)) + 1;
	
	k2->height = Max(Height(k2->left),k1->height) + 1;
	
	return k2; 
} 

//�����ڲ�ƽ��ڵ���������˫��ת
//˫��ת����Ҫ���������������֮һ 
static Position DoubleRotateWithLeft(Position k3) { //�������д�������Ǿ��� 
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3); 
} 

//�����ڲ�ƽ��ڵ���������˫��ת
//˫��ת����Ҫ���������������֮һ 
static Position DoubleRotateWithRight(Position k2) { //�������д�������Ǿ��� 
	k2->right = SingleRotateWithLeft(k2->left);
	return SingleRotateWithRight(k2); 
} 



//�����ڲ�ƽ��ڵ���������˫��ת



//����Ӧ����ɶ������Ĵ���insert����
AvlTree Insert(ElementType x, AvlTree T) { 
	 
	if (T == NULL) {
		T = (AvlTree) malloc(sizeof(struct AvlNode));
		if (T == NULL) {
			cout << "Insert����ʧ�ܣ�����"; 
			exit(-1);
		} 
		
		T->value = x;
		T->left = T->right = NULL;
		T->height = 0;  //����ǵ�һ���޸���߶ȵ�ֵ 
	}else if (x < T->value) {
			T->left = Insert(x, T->left);
			//��������ɵ�ʱ������Ӧ�öԲ�����ɺ��������ƽ�⴦��
			if (Height(T->left) - Height(T->right) == 2) { //֤���ڲ�ƽ��ڵ���������Ͻ��в��� 
				if (x < T->left->value) { //�ж����ڲ�ƽ��ڵ���������������� 
					T = SingleRotateWithLeft(T); 
				}else {
					T = DoubleRotateWithLeft(T);	
				}
			} 
		}else if (x > T->value) {
			T->right = Insert(x, T->right);
			
			if (Height(T->right) - Height(T->left) == 2) {
				if (x > T->right->value) {
					T = SingleRotateWithRight(T); 
				}else {
					T = DoubleRotateWithRight(T);	
				}
			}
	} 
	
	//������¸߶���Ϣ,����Ҫ 
	T->height = Max(Height(T->left),Height(T->right)) + 1;  
} 

AvlTree MakeEmpty(AvlTree T) {
	if (T == NULL) {
		return NULL;
	}else {
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		cout <<"ֵΪ��"<< T->value << endl;
		free(T);
	}
	
	
}
 
