#pragma once
#include <vector>

#include "RedBlackTreeNode.h"

using namespace std;

template <typename T>
//����1 ÿ������Ǻ�ɫ���ߺ�ɫ
//����2 ������Ǻ�ɫ
//����3 Ҷ��㣨NIL���Ǻ�ɫ��
//����4 ������Ϊ��ɫ�������������ӽ�㶼Ϊ��ɫ
//����5 ��ÿ����㣬�Ӹý�㵽����Ҷ���ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ��㡣
class RedBlackTree
{
public:
	RedBlackTree()
	{
		_nil=new RedBlackTreeNode<T>();
		//�ڱ����������Բ�����Ҫ
		_nil->Color=RedBlackTreeNode<T>::Black;
		//����ʡ���ж�
		_nil->Left=_nil;
		_nil->Right=_nil;
		_nil->Parent=_nil;
		_root=_nil;
	}
	~RedBlackTree()
	{
		RedBlackTreeNode<T>* node=_root;
		DeletePoint(_root);
		delete _nil;
	}

	//���
    RedBlackTreeNode<T>* Insert(T key)
	{
		RedBlackTreeNode<T>* node=new RedBlackTreeNode<T>();
		node->Key=key;
		Insert(node);
		return node;
	}

	//ɾ��
	void Delete(RedBlackTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		//�������x���ĺ�̽��y
		RedBlackTreeNode<T>* fillNodeY=_nil;
		//�������y�����ӽ��z
		RedBlackTreeNode<T>* fillNodeZ=_nil;
		//����˫����ɫ�Ľ��
		RedBlackTreeNode<T>* doubleColorNode=_nil;
		//color��ʾ��ǰ��ʧ����ɫ
		bool color;
		//����ǰ�����жϣ���Ϊ����������x��y��㣬��û�н�y����ɫ��ֵΪx��㣬����ԭ��x������ɫ��ʧ���ˣ�y��Ϊ˫����ɫ���
		if(nodeX->Left==_nil)
		{
			color=nodeX->Color;
			//y��������nil������nil��parent����Transplant�����и�ֵ������������ʹ��
			fillNodeY=nodeX->Right;
			Transplant(nodeX,fillNodeY);
			doubleColorNode=fillNodeY;
		}
		else if(nodeX->Right==_nil)
		{
			color=nodeX->Color;
			fillNodeY=nodeX->Left;
			Transplant(nodeX,fillNodeY);
			doubleColorNode=fillNodeY;
		}
		//��xyz��㶼�߱�ʱ����Ϊy�ḳֵΪx����ɫ����z�滻y��������ʧ��y����ɫ��z��Ϊ˫����ɫ���
		else
		{
			//�ҵ�x�ĺ��
			fillNodeY=Minimum(nodeX->Right);
			color=fillNodeY->Color;
			fillNodeZ=fillNodeY->Right;
			//����ж���Ҫ��Ӧ��z���Ϊnil���������Ϊnil��parent�������
			//���Ǻ���DeleteFixUp����Ҫ�õ�parent���ԣ�����Ҫ���丳ֵ������������Transplant���и�ֵ
			//�����ڷ�nil��㣬��ôz����parent�������y���˾����������
			if(fillNodeY->Parent==nodeX)
			{
				fillNodeZ->Parent=fillNodeY;
			}
			else
			{
				//������y����z�Ľ���򽻻�y��z
				Transplant(fillNodeY,fillNodeZ);
				fillNodeY->Right=nodeX->Right;
				fillNodeY->Right->Parent=fillNodeY;
			}
			//����y��x
			Transplant(nodeX,fillNodeY);
			fillNodeY->Left=nodeX->Left;
			fillNodeY->Left->Parent=fillNodeY;
			fillNodeY->Color=nodeX->Color;
			doubleColorNode=fillNodeZ;
		}
		//�����ʧ�˺�ɫ����ô����Ծ���˫����ɫ�Ľ������޸�
		if(color==RedBlackTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	//����
	RedBlackTreeNode<T>* Search(T key)
	{
		return Search(_root,key);
	}
	//�����������
	int CheckRedBlack()
	{
		//���ڵ�ӦΪ��ɫ
		if(_root->Color==RedBlackTreeNode<T>::Red)
		{
			return 2;
		}
		//ÿ��Ҷ���Ϊ��ɫ
		if(_nil->Color==RedBlackTreeNode<T>::Red)
		{
			return 3;
		}
		vector<RedBlackTreeNode<T>*> error4;
		Check4(_root,error4);
		if(!error4.empty())
		{
			return 4;
		}
		vector<RedBlackTreeNode<T>*> error5;
		Check5(_root,error5);
		return error5.empty()?0:5;
	}
	//�Ƿ��ǿս��
	bool IsNil(RedBlackTreeNode<T>* node)
	{
		return node==_nil;
	}
	//��ÿս��
	RedBlackTreeNode<T>* Root()
	{
		return _root;
	}
	/**
	 * ��ú�̽��
	 * @param node ���
	 * @return ����к�̽���򷵻أ����򷵻��ڱ�
	 */
	RedBlackTreeNode<T>* Successor(RedBlackTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return _nil;
		}
		if(node->Right!=_nil)
		{
			return Minimum(node->Right);
		}
		RedBlackTreeNode<T>* parent=node->Parent;
		while(parent!=_nil&&node==parent->Right)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}
	/**
	 * ���ǰ�����
	 * @param node ���
	 * @return �����ǰ������򷵻أ����򷵻��ڱ�
	 */
	RedBlackTreeNode<T>* Predecessor(RedBlackTreeNode<T>* node)
	{
		T tempKey=node->Key;
		RedBlackTreeNode<T>* temp=node;
		if(node==_nil)
		{
			return _nil;
		}
		if(node->Left!=_nil)
		{
			return Maximum(node->Left);
		}

		RedBlackTreeNode<T>* parent=node->Parent;

		while(parent!=_nil&&node==parent->Left)
		{
			node=parent;
			parent=parent->Parent;
		}
		return parent;
	}
	/**
	 * �����Сֵ
	 * @param node ���
	 * @return ��Сֵ��㣬û����Сֵʱ�����ڱ�
	 */
	RedBlackTreeNode<T>* Minimum(RedBlackTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	/**
	 * ������ֵ
	 * @param node ���
	 * @return ���ֵ��㣬û�����ֵʱ�����ڱ�
	 */
	RedBlackTreeNode<T>* Maximum(RedBlackTreeNode<T>* node)
	{
		while(node->Right!=_nil)
		{
			node=node->Right;
		}
		return node;
	}
private:
	//�ڱ�
	RedBlackTreeNode<T>* _nil;
	//�����
	RedBlackTreeNode<T>* _root;
	//����ת
	void LeftRotate(RedBlackTreeNode<T>* parent)
	{
		//�ҽ���������Ϊ�������ҽ��
		RedBlackTreeNode<T> *right=parent->Right;
		parent->Right=right->Left;
		if(right->Left!=_nil)
		{
			right->Left->Parent=parent;
		}
		//�ҽ���Ϊ�����
		right->Parent=parent->Parent;
		if(parent->Parent==_nil)
		{
			_root=right;
		}
		else if(parent==parent->Parent->Left)
		{
			parent->Parent->Left=right;
		}
		else
		{
			parent->Parent->Right=right;
		}
		//������Ϊ����
		right->Left=parent;
		parent->Parent=right;
	}
	//����ת
	void RightRotate(RedBlackTreeNode<T>* parent)
	{
		//������ҽ����Ϊ����������
		RedBlackTreeNode<T> *left=parent->Left;
		parent->Left=left->Right;
		if(left->Right!=_nil)
		{
			left->Right->Parent=parent;
		}
		//������Ϊ�����
		left->Parent=parent->Parent;
		if(parent->Parent==_nil)
		{
			_root=left;
		}
		else if(parent==parent->Parent->Right)
		{
			parent->Parent->Right=left;
		}
		else
		{
			parent->Parent->Left=left;
		}
		//�������Ϊ�ҽ��
		left->Right=parent;
		parent->Parent=left;
	}
	//���
    void Insert(RedBlackTreeNode<T>* node)
	{
		//�ҵ���ȷλ��
		RedBlackTreeNode<T>* tempNode=_nil;
		RedBlackTreeNode<T>* currentNode=_root;
		while(currentNode!=_nil)
		{
			tempNode=currentNode;
			if(node->Key<currentNode->Key)
			{
				currentNode=currentNode->Left;
			}
			else
			{
				currentNode=currentNode->Right;
			}
		}
		//���½����Ϣ
		//��һ��������ʱ��tempNodeΪnil����ʱ�ͱ�֤��root��parentΪnil
		node->Parent=tempNode;
		if(tempNode==_nil)
		{
			_root=node;
		}
		else if(node->Key<tempNode->Key)
		{
			tempNode->Left=node;
		}
		else 
		{
			tempNode->Right=node;
		}
		//���ﱣ֤��ÿ��Ҷ�����ӽ��Ϊnil
		node->Left=_nil;
		node->Right=_nil;
		//��Ϊ��ɫ
		node->Color=RedBlackTreeNode<T>::Red;
		InsertFixUp(node);
	}
	//��ӻָ�
	void InsertFixUp(RedBlackTreeNode<T>* node)
	{
		//Ĭ��nodeΪ��ɫ
		//�������Ϊ��ɫ
		while(node->Parent->Color==RedBlackTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				//����
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Right;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.����Ϊ��ɫ��node���ҽ��
				else if(node==node->Parent->Right)
				{
					//����ת��node��Ϊ����㣬������Ϊ����
					LeftRotate(node->Parent);
					node=node->Left;
				}
				//3.��ڵ�Ϊ��ɫ��node����ڵ�
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Left;
				//1.�����ǰ���Ϊ��ɫ������Ϊ��ɫ������Ҫ�Ѹ������������Ϊ��ɫ���游�����Ϊ��ɫ
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				//2.����Ϊ��ɫ��node���ҽ��
				else if(node==node->Parent->Left)
				{
					//����ת��node��Ϊ����㣬������Ϊ�ҽ��
					RightRotate(node->Parent);
					node=node->Right;
				}
				//3.��ڵ�Ϊ��ɫ��node����ڵ�
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=RedBlackTreeNode<T>::Black;
	}
	//ɾ���ָ�
	//�ܵ�˼���ǽ�˫�ؽ��������֪��ʡ��һ�����������
	void DeleteFixUp(RedBlackTreeNode<T>* node)
	{
		//�ֵܽ��
		RedBlackTreeNode<T>* brother=_nil;
		//��˫�ؽ��Ϊ��ɫ���ʱ��ԭ������ɫȨ��Ϊ0�����ú��ɫȨ��Ϊ1
		//��˫�ؽ��Ϊ��ʹ������߱�����Ȩ��Ҳ����Ӱ����������н�㣬��Ϊÿ����㶼������1
		while(node!=_root&&node->Color==RedBlackTreeNode<T>::Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				//1.�ֵܽ���Ǻ�ɫ��
				//��ת�󣬶��ڸ�����֧������ԭ״�����ֵܽ���Ϊ��ɫ������ʹ��234����
				if(brother->Color==RedBlackTreeNode<T>::Red)
				{
					brother->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Color=RedBlackTreeNode<T>::Red;
					//����ת��ԭ�������
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				//2.�ֵܽ���Ǻ�ɫ���ֵܽ��������ӽ�㶼�Ǻ�ɫ
				//���ֵܽ����Ϊ��ɫ���ֵܽ���֧����һ����ɫȨ��
				if(brother->Left->Color==RedBlackTreeNode<T>::Black && brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Color=RedBlackTreeNode<T>::Red;
					//�������
					node=node->Parent;
					continue;
				}
				//3.�ֵܽ���Ǻ�ɫ���ֵܽ��������ɫ���ҽ���Ǻ�ɫ
				//��ת���ֵܽ��������Ϊ�ֵܽ����ҽڵ㣬����4
				else if(brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Left->Color=RedBlackTreeNode<T>::Black;
					brother->Color=RedBlackTreeNode<T>::Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				//4.�ֵܽ���Ǻ�ɫ���ֵܽ����Һ����Ǻ�ɫ
				//�ڽ���֧�ϣ������˸����ĺ�ɫ���ֵܽ������Ҳ��ɺ�ɫ�������ֵܽ���֧����
				brother->Color=node->Parent->Color;
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				brother->Right->Color=RedBlackTreeNode<T>::Black;
				LeftRotate(node->Parent);
				node=_root;
			}
			else
			{
				brother=node->Parent->Left;
				if(brother->Color==RedBlackTreeNode<T>::Red)
				{
					brother->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Color=RedBlackTreeNode<T>::Red;
					RightRotate(node->Parent);
					brother=node->Parent->Left;
				}
				if(brother->Left->Color==RedBlackTreeNode<T>::Black && brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent;
					continue;
				}
				else if(brother->Left->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Right->Color=RedBlackTreeNode<T>::Black;
					brother->Color=RedBlackTreeNode<T>::Red;
					LeftRotate(brother);
					brother=node->Parent->Left;
				}
				brother->Color=node->Parent->Color;
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				brother->Left->Color=RedBlackTreeNode<T>::Black;
				RightRotate(node->Parent);
				break;
			}
		}
		node->Color=RedBlackTreeNode<T>::Black;
	}
	//��ֲ���
	void Transplant(RedBlackTreeNode<T>* removeNode,RedBlackTreeNode<T>* fillNode)
	{
		if(removeNode->Parent==_nil)
		{
			_root=fillNode;
		}
		else if(removeNode==removeNode->Parent->Left)
		{
			removeNode->Parent->Left=fillNode;
		}
		else
		{
			removeNode->Parent->Right=fillNode;
		}
		//���ﲻ���ж�fillNode����Ϊ��ʹ��nil��Ҳ����NULL
		fillNode->Parent=removeNode->Parent;
	}
	//����
	RedBlackTreeNode<T>* Search(RedBlackTreeNode<T>* node,T key)
	{
		if(node==_nil||node->Key==key)
		{
			return node;
		}
		if(key<node->Key)
		{
			return Search(node->Left,key);
		}
		return Search(node->Right,key);
	}
	//�������4
	void Check4(RedBlackTreeNode<T>* node,vector<RedBlackTreeNode<T>*>& error)
	{
		if(node==_nil)
		{
			return ;
		}
		if(node->Color==RedBlackTreeNode<T>::Red&&(node->Left->Color==RedBlackTreeNode<T>::Red||node->Right->Color==RedBlackTreeNode<T>::Red))
		{
			error.push_back(node);
		}
		Check4(node->Left,error);
		Check4(node->Right,error);
	}
	//�������5
	void Check5(RedBlackTreeNode<T>* node,vector<RedBlackTreeNode<T>*>& error)
	{
		if(node==_nil)
		{
			return; 
		}
		vector<int> list;
		GetBlackCount(node,list,0);
		int temp=-1;
		for(int i=0;i<list.size();++i)
		{
			if(temp==-1)
			{
				temp=list.at(i);
			}
			else if(temp==list.at(i))
			{
				continue;
			}
			else 
			{
				error.push_back(node);
				break;
			}
		}
		Check5(node->Left,error);
		Check5(node->Right,error);
	}
	//��ȡ��ÿ��Ҷ���ĺ�ɫ�������
	void GetBlackCount(RedBlackTreeNode<T>* node,vector<int>& list,int count)
	{
		if(node==_nil)
		{
			list.push_back(count);
			return;
		}
		if(node->Color==RedBlackTreeNode<T>::Black)
		{
			++count;
		}
		GetBlackCount(node->Left,list,count);
		GetBlackCount(node->Right,list,count);
	}
	//ɾ�����
	void DeletePoint(RedBlackTreeNode<T>* node)
	{
		if(node==_nil)
		{
			return;
		}
		DeletePoint(node->Left);
		DeletePoint(node->Right);
		delete node;
	}
};

