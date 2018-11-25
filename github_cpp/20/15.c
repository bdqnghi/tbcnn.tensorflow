#pragma once
#include <vector>

#include "RedBlackTreeNode.h"

using namespace std;

template <typename T>





class RedBlackTree
{
public:
	RedBlackTree()
	{
		_nil=new RedBlackTreeNode<T>();
		
		_nil->Color=RedBlackTreeNode<T>::Black;
		
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

	
    RedBlackTreeNode<T>* Insert(T key)
	{
		RedBlackTreeNode<T>* node=new RedBlackTreeNode<T>();
		node->Key=key;
		Insert(node);
		return node;
	}

	
	void Delete(RedBlackTreeNode<T>* nodeX)
	{
		if(nodeX==_nil)
		{
			return;
		}
		
		RedBlackTreeNode<T>* fillNodeY=_nil;
		
		RedBlackTreeNode<T>* fillNodeZ=_nil;
		
		RedBlackTreeNode<T>* doubleColorNode=_nil;
		
		bool color;
		
		if(nodeX->Left==_nil)
		{
			color=nodeX->Color;
			
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
		
		else
		{
			
			fillNodeY=Minimum(nodeX->Right);
			color=fillNodeY->Color;
			fillNodeZ=fillNodeY->Right;
			
			
			
			if(fillNodeY->Parent==nodeX)
			{
				fillNodeZ->Parent=fillNodeY;
			}
			else
			{
				
				Transplant(fillNodeY,fillNodeZ);
				fillNodeY->Right=nodeX->Right;
				fillNodeY->Right->Parent=fillNodeY;
			}
			
			Transplant(nodeX,fillNodeY);
			fillNodeY->Left=nodeX->Left;
			fillNodeY->Left->Parent=fillNodeY;
			fillNodeY->Color=nodeX->Color;
			doubleColorNode=fillNodeZ;
		}
		
		if(color==RedBlackTreeNode<T>::Black)
		{
			DeleteFixUp(doubleColorNode);
		}
		delete nodeX;
	}
	
	RedBlackTreeNode<T>* Search(T key)
	{
		return Search(_root,key);
	}
	
	int CheckRedBlack()
	{
		
		if(_root->Color==RedBlackTreeNode<T>::Red)
		{
			return 2;
		}
		
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
	
	bool IsNil(RedBlackTreeNode<T>* node)
	{
		return node==_nil;
	}
	
	RedBlackTreeNode<T>* Root()
	{
		return _root;
	}
	
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
	
	RedBlackTreeNode<T>* Minimum(RedBlackTreeNode<T>* node)
	{
		while(node->Left!=_nil)
		{
			node=node->Left;
		}
		return node;
	}
	
	RedBlackTreeNode<T>* Maximum(RedBlackTreeNode<T>* node)
	{
		while(node->Right!=_nil)
		{
			node=node->Right;
		}
		return node;
	}
private:
	
	RedBlackTreeNode<T>* _nil;
	
	RedBlackTreeNode<T>* _root;
	
	void LeftRotate(RedBlackTreeNode<T>* parent)
	{
		
		RedBlackTreeNode<T> *right=parent->Right;
		parent->Right=right->Left;
		if(right->Left!=_nil)
		{
			right->Left->Parent=parent;
		}
		
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
		
		right->Left=parent;
		parent->Parent=right;
	}
	
	void RightRotate(RedBlackTreeNode<T>* parent)
	{
		
		RedBlackTreeNode<T> *left=parent->Left;
		parent->Left=left->Right;
		if(left->Right!=_nil)
		{
			left->Right->Parent=parent;
		}
		
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
		
		left->Right=parent;
		parent->Parent=left;
	}
	
    void Insert(RedBlackTreeNode<T>* node)
	{
		
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
		
		node->Left=_nil;
		node->Right=_nil;
		
		node->Color=RedBlackTreeNode<T>::Red;
		InsertFixUp(node);
	}
	
	void InsertFixUp(RedBlackTreeNode<T>* node)
	{
		
		
		while(node->Parent->Color==RedBlackTreeNode<T>::Red)
		{
			if(node->Parent==node->Parent->Parent->Left)
			{
				
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Right;
				
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				
				else if(node==node->Parent->Right)
				{
					
					LeftRotate(node->Parent);
					node=node->Left;
				}
				
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				RightRotate(node->Parent->Parent);

			}
			else
			{
				RedBlackTreeNode<T>* uncle=node->Parent->Parent->Left;
				
				if(uncle->Color==RedBlackTreeNode<T>::Red)
				{
					node->Parent->Color=RedBlackTreeNode<T>::Black;
					uncle->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
					node=node->Parent->Parent;
					continue;
				}
				
				else if(node==node->Parent->Left)
				{
					
					RightRotate(node->Parent);
					node=node->Right;
				}
				
				node->Parent->Color=RedBlackTreeNode<T>::Black;
				node->Parent->Parent->Color=RedBlackTreeNode<T>::Red;
				LeftRotate(node->Parent->Parent);

			}

		}
		_root->Color=RedBlackTreeNode<T>::Black;
	}
	
	
	void DeleteFixUp(RedBlackTreeNode<T>* node)
	{
		
		RedBlackTreeNode<T>* brother=_nil;
		
		
		while(node!=_root&&node->Color==RedBlackTreeNode<T>::Black)
		{
			if(node==node->Parent->Left)
			{
				brother=node->Parent->Right;
				
				
				if(brother->Color==RedBlackTreeNode<T>::Red)
				{
					brother->Color=RedBlackTreeNode<T>::Black;
					node->Parent->Color=RedBlackTreeNode<T>::Red;
					
					LeftRotate(node->Parent);
					brother=node->Parent->Right;
				}
				
				
				if(brother->Left->Color==RedBlackTreeNode<T>::Black && brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Color=RedBlackTreeNode<T>::Red;
					
					node=node->Parent;
					continue;
				}
				
				
				else if(brother->Right->Color==RedBlackTreeNode<T>::Black)
				{
					brother->Left->Color=RedBlackTreeNode<T>::Black;
					brother->Color=RedBlackTreeNode<T>::Red;
					RightRotate(brother);
					brother=node->Parent->Right;
				}
				
				
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
		
		fillNode->Parent=removeNode->Parent;
	}
	
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

