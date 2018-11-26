#ifndef MyAVL_h
#define MyAVL_h
//��ͷ�ļ��ж�����MyAVLTree���࣬��ʵ������������insert��search��adjust�ȷ���
//MyAVLTree��˽�г�Ա����ΪMyAVLTreeNode�࣬������Ѷ������·�

#include <iomanip>
#include <iostream>
#include "MyString.h"
#include "MyDocuList.h"
using namespace std;

template <class T>
class MyAVLTreeNode{
    public:
        T key;                // �ؼ���(��ֵ)
        int height;         // �߶�
		int DF;      //���ʳ����ڶ���������
		int occur;   //���ʳ��ֵ��ܴ���
		int current_docID; //�ֽ׶ε�����ID
        MyAVLTreeNode *left;    // ����
        MyAVLTreeNode *right;    // �Һ���
		MyDoculist<T>* html_docuList;  // ���ʶ�Ӧ���ĵ�����

        MyAVLTreeNode(T value, MyAVLTreeNode *l, MyAVLTreeNode *r):
			key(value), height(0),DF(0),occur(0),left(l),right(r),html_docuList(nullptr),current_docID(-1) {}
};

template <class T>
class MyAVLTree
{
    private:
        MyAVLTreeNode<T> *mRoot;    // �����

    public:
        MyAVLTree();
        ~MyAVLTree();

        // ��ȡ���ĸ߶�
        int height();
        // ��ȡ���ĸ߶�
        int max(int a, int b);

        // (�ݹ�ʵ��)����"AVL��"�м�ֵΪkey�Ľڵ�
        MyAVLTreeNode<T>* search(T key);
        // (�ǵݹ�ʵ��)����"AVL��"�м�ֵΪkey�Ľڵ�
        MyAVLTreeNode<T>* iterativeSearch(T key);

        // ������С��㣺������С���ļ�ֵ��
        T minimum();
        // ��������㣺���������ļ�ֵ��
        T maximum();

		//�ڲ���������õ���adjust����,�ú�����insert�����е��ã��Ա�֤�㷨Ч�ʡ�
		//���ÿ�β����ŵ��ô˺������ᵼ��Ҫ��εݹ������㲻ͬ�����ĸ߶ȣ������㷨Ч�ʽ��͡�
		//�ýӿ�ֻ����insert�����е��ã���insert�ݹ�ʱʵ�����ķ�ת�Լ����������߶ȸ��µĹ��ܡ�insert�������иú���ʹ�÷���
		//adjust��������ֱ�ӵ���
		void adjust(MyAVLTreeNode<T>* &tree, T key);

        // �����(keyΪ�ڵ��ֵ)���뵽AVL����
        void insert(T key);

        // ɾ�����(keyΪ�ڵ��ֵ)
        void remove(T key);

        // ����AVL��
        void destroy();

        // ��ӡAVL��
        void print();
		 // ǰ�����"AVL��"
        void preOrder();
        // �������"AVL��"
        void inOrder();
        // �������"AVL��"
        void postOrder();

    private:
        // ��ȡ���ĸ߶�
        int height(MyAVLTreeNode<T>* tree) ;

        // ǰ�����"AVL��"
        void preOrder(MyAVLTreeNode<T>* tree) const;
        // �������"AVL��"
        void inOrder(MyAVLTreeNode<T>* tree) const;
        // �������"AVL��"
        void postOrder(MyAVLTreeNode<T>* tree) const;

        // (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
        MyAVLTreeNode<T>* search(MyAVLTreeNode<T>* x, T key) const;
        // (�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
        MyAVLTreeNode<T>* iterativeSearch(MyAVLTreeNode<T>* x, T key) const;

        // ������С��㣺����treeΪ������AVL������С��㡣
        MyAVLTreeNode<T>* minimum(MyAVLTreeNode<T>* tree);
        // ��������㣺����treeΪ������AVL��������㡣
        MyAVLTreeNode<T>* maximum(MyAVLTreeNode<T>* tree);

        // LL�������Ӧ�����(����ת)��
        MyAVLTreeNode<T>* leftLeftRotation(MyAVLTreeNode<T>* k2);

        // RR�����Ҷ�Ӧ�����(�ҵ���ת)��
        MyAVLTreeNode<T>* rightRightRotation(MyAVLTreeNode<T>* k1);

        // LR�����Ҷ�Ӧ�����(��˫��ת)��
        MyAVLTreeNode<T>* leftRightRotation(MyAVLTreeNode<T>* k3);

        // RL�������Ӧ�����(��˫��ת)��
        MyAVLTreeNode<T>* rightLeftRotation(MyAVLTreeNode<T>* k1);	

        // �����(z)���뵽AVL��(tree)��
        MyAVLTreeNode<T>* insert(MyAVLTreeNode<T>* &tree, T key);

        // ɾ��AVL��(tree)�еĽ��(z)�������ر�ɾ���Ľ��
        MyAVLTreeNode<T>* remove(MyAVLTreeNode<T>* &tree, MyAVLTreeNode<T>* z);

        // ����AVL��
        void destroy(MyAVLTreeNode<T>* &tree);

        // ��ӡAVL��
        void print(MyAVLTreeNode<T>* tree, T key, int direction);

};

//���캯��
template <class T>
MyAVLTree<T>::MyAVLTree():mRoot(NULL)
{
}

// ��������
template <class T>
MyAVLTree<T>::~MyAVLTree() 
{
    destroy(mRoot);
}

// ��ȡ���ĸ߶�
template <class T>
int MyAVLTree<T>::height(MyAVLTreeNode<T>* tree) 
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
int MyAVLTree<T>::height() 
{
    return height(mRoot);
}

// �Ƚ�����ֵ�Ĵ�С
template <class T>
int MyAVLTree<T>::max(int a, int b) 
{
    return a>b ? a : b;
}


//(�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::search(MyAVLTreeNode<T>* x, T key) const
{
    if (x == NULL || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::search(T key) 
{
    return search(mRoot, key);
}

//(�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::iterativeSearch(MyAVLTreeNode<T>* x, T key) const
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

//������С��㣺����treeΪ������AVL������С��㡣
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::minimum(MyAVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T MyAVLTree<T>::minimum()
{
    MyAVLTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}
 
// ��������㣺����treeΪ������AVL��������㡣
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::maximum(MyAVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T MyAVLTree<T>::maximum()
{
    MyAVLTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

// LL�������Ӧ�����(����ת)����ֵ����ת��ĸ��ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::leftLeftRotation(MyAVLTreeNode<T>* k2)
{
    MyAVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}

//RR�����Ҷ�Ӧ�����(�ҵ���ת),����ֵ����ת��ĸ��ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::rightRightRotation(MyAVLTreeNode<T>* k1)
{
    MyAVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}

// LR�����Ҷ�Ӧ�����(��˫��ת),����ֵ����ת��ĸ��ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::leftRightRotation(MyAVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

//RL�������Ӧ�����(��˫��ת),����ֵ����ת��ĸ��ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::rightLeftRotation(MyAVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

//�������㷨
template <class T>
void MyAVLTree<T>::adjust(MyAVLTreeNode<T>* &tree, T key)
{
	 if (height(tree->left) - height(tree->right) == 2)
     {
        if (key < tree->left->key)
		{
            tree = leftLeftRotation(tree);//LL��
		}
        else
		{
            tree = leftRightRotation(tree);//LR��
		}
     }
	 else if (height(tree->right) - height(tree->left) == 2)
	 {
        if (key > tree->right->key)
		{
            tree = rightRightRotation(tree);//RR��
		}
        else
		{
            tree = rightLeftRotation(tree);//RL��
		}
     }
	 else
	 {}
}



// �������뵽AVL���У������ظ��ڵ㣬����˵����   tree AVL���ĸ���㣬  key ����Ľ��ļ�ֵ�� ����ֵ: ���ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::insert(MyAVLTreeNode<T>* &tree, T key)
{
    if (tree == NULL) 
    {
        // �½��ڵ�
        tree = new MyAVLTreeNode<T>(key, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create MyAVLTree node failed!" << endl;
            return NULL;
        }
    }
    else if ( key < tree->key ) // Ӧ�ý�key���뵽"tree��������"�����
    {
		//�ݹ����ڵ�
        tree->left = insert(tree->left, key);
		//�Բ�������������Ӧ�ĵ���
		adjust(tree,key);
		
    }
    else if ( key > tree->key ) // Ӧ�ý�key���뵽"tree��������"�����
    {
		//�ݹ����ڵ�
        tree->right = insert(tree->right, key);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		adjust(tree,key);
       
    }
    else //key == tree->key)
    {
       // cout << "���ʧ�ܣ������������ͬ�Ľڵ㣡" << endl;
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void MyAVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}

// ɾ�����(z)�����ظ��ڵ㣻����˵����  tree AVL���ĸ���㣬z ��ɾ���Ľ�㣬 ����ֵ�� ���ڵ�
template <class T>
MyAVLTreeNode<T>* MyAVLTree<T>::remove(MyAVLTreeNode<T>* &tree, MyAVLTreeNode<T>* z)
{
    // ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        // ��ɾ���Ľڵ���"tree��������"��
    {
        tree->left = remove(tree->left, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->right) - height(tree->left) == 2)
        {
            MyAVLTreeNode<T> *r =  tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)// ��ɾ���Ľڵ���"tree��������"��
    {
        tree->right = remove(tree->right, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->left) - height(tree->right) == 2)
        {
            MyAVLTreeNode<T> *l =  tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    // tree�Ƕ�ӦҪɾ���Ľڵ㡣
    {
        // tree�����Һ��Ӷ��ǿ�
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                // ���tree�����������������ߣ�
                // ���ҳ�tree���������е����ڵ�
                // �������ڵ��ֵ��ֵ��tree��
                //  ɾ�������ڵ㡣
                MyAVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // ���tree��������������������(��������ȣ�������������������1)
                // ���ҳ�tree���������е���С�ڵ�
                //   ������С�ڵ��ֵ��ֵ��tree��
                //   ɾ������С�ڵ㡣          
                MyAVLTreeNode<T>* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            MyAVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void MyAVLTree<T>::remove(T key)
{
    MyAVLTreeNode<T>* z; 

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}

// ����AVL��
template <class T>
void MyAVLTree<T>::destroy(MyAVLTreeNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T>
void MyAVLTree<T>::destroy()
{
    destroy(mRoot);
}

/*
 * ��ӡ"���������"
 *
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
template <class T>
void MyAVLTree<T>::print(MyAVLTreeNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree�Ǹ��ڵ�
            wcout << setw(2) << tree->key << " is root" << endl;
        else                // tree�Ƿ�֧�ڵ�
            wcout << setw(2) << tree->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void MyAVLTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}

// ǰ�����"AVL��"
template <class T>
void MyAVLTree<T>::preOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        wcout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void MyAVLTree<T>::preOrder() 
{
    preOrder(mRoot);
}

//�������"AVL��"
template <class T>
void MyAVLTree<T>::inOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        wcout<< tree->key << " " ;
        inOrder(tree->right);
    }
}

template <class T>
void MyAVLTree<T>::inOrder() 
{
    inOrder(mRoot);
}

//�������"AVL��"
template <class T>
void MyAVLTree<T>::postOrder(MyAVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        wcout<< tree->key << " " ;
    }
}

template <class T>
void MyAVLTree<T>::postOrder() 
{
    postOrder(mRoot);
}


//�����ļ�
void MyAVLTree_Test1();

#endif


