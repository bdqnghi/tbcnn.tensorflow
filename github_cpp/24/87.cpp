#include <iostream>
#include <string>
#include <queue>
#include "BinarySearchTree.h"
using namespace std;

BinarySearchTree::BinarySearchTree(int item)
{
	m_parent = NULL;
	m_left = NULL;
	m_right = NULL;
	m_level = 0;
	m_value = item;
}

BinarySearchTree* BinarySearchTree::getParent()
{
	return m_parent;
}
BinarySearchTree* BinarySearchTree::getLeft()
{
	return m_left;
}
BinarySearchTree* BinarySearchTree::getRight()
{
	return m_right;
}
int BinarySearchTree::getItem()
{
	return m_value;
}
BinarySearchTree* BinarySearchTree::search(int item)
{
	return NULL;
}
BinarySearchTree* BinarySearchTree::min()
{
	if(this->getLeft() == NULL)
		return this;
	else
		return this->getLeft()->min();
}
BinarySearchTree* BinarySearchTree::max()
{
	if(this->getRight() == NULL)
		return this;
	else
		return this->getRight()->max();
}
string BinarySearchTree::toString()
{
	return to_string(m_value);
}


void BinarySearchTree::inorder()
{
	_inorder(this);
}
void BinarySearchTree::breadthFirstOrder()
{
	_breadthFirstOrder(this);
}
int BinarySearchTree::getLevel()
{
	return m_level;
}




void BinarySearchTree::setLeft(BinarySearchTree* tree)
{

}
void BinarySearchTree::setRight(BinarySearchTree* tree)
{

}
void BinarySearchTree::setParent(BinarySearchTree* tree)
{

}
void BinarySearchTree::setLevel(int level)
{

}
void BinarySearchTree::setItem(int item)
{

}
bool BinarySearchTree::_delete(BinarySearchTree* t)
{
	return false;
}
bool BinarySearchTree::_insert(BinarySearchTree* p, int item)
{
	return false;
} 
BinarySearchTree* BinarySearchTree::_search(BinarySearchTree* tree, int item)
{
	return NULL;
} 
void BinarySearchTree::_inorder(BinarySearchTree* tree)
{
	if(tree->getLeft() != NULL)
		_inorder(tree->getLeft());
	
	cout << tree->toString() << endl;

	if(tree->getRight() != NULL)
		_inorder(tree->getRight());
}
void BinarySearchTree::_breadthFirstOrder(BinarySearchTree* tree)
{
	queue<BinarySearchTree*> currentLevel;
	queue<BinarySearchTree*> nextLevel;

	currentLevel.push(tree);
        
        while (!currentLevel.empty()) 
        {
            BinarySearchTree* node = currentLevel.front();
            currentLevel.pop();
            
            cout << "Level: " << m_level << " Value: " << node->toString() << endl;
            
            if (node->getLeft() != NULL)
            {
                nextLevel.push(node->getLeft());
            }
            
            if (node->getRight() != NULL)
            {
                nextLevel.push(node->getRight());
            }
            
            if (currentLevel.empty()) 
            	currentLevel.swap(nextLevel);            
        }
}




