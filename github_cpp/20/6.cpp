#ifndef RED_BLACK_TREE_IMPLEMENTATION_
#define RED_BLACK_TREE_IMPLEMENTATION_

#include "redBlackTree.h"


template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable& negInf) : ITEM_NOT_FOUND(negInf)
{
	initTree();
}


template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree<Comparable>& rhs)
	: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
	initTree();
	*this = rhs;
}


template <typename Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
 	makeEmpty();
 	delete nullNode;
 	delete header;
}


template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::findMax()const
{
	RedBlackNode *r = header;
	while (r -> right != nullNode)
		r = r -> right;
	return r -> element;
}


template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::findMin() const
{
	RedBlackNode *r = header;
	while (r -> left != nullNode)
		r = r -> left;
	return r -> element;
}


template <typename Comparable>
Comparable RedBlackTree<Comparable>::find(const Comparable& ele)
{
	RedBlackNode *r = findAux(ele);
	if (r == nullNode)
		return ITEM_NOT_FOUND;
	return r -> element;
}


template <typename Comparable>
bool RedBlackTree<Comparable>::contains(const Comparable& ele)
{
	findAux(ele);
	return current != nullNode;
}


template <typename Comparable>
bool RedBlackTree<Comparable>::isEmpty() const
{
	return header -> right == nullNode;
}


template <typename Comparable>
void RedBlackTree<Comparable>::makeEmpty()
{
	makeEmpty(header -> right);
	header -> left = header -> right = nullNode;
}


template <typename Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& ele)
{
	
	insertTopDown(ele);
}


template <typename Comparable>
void RedBlackTree<Comparable>::remove(const Comparable& ele)
{
	std::cout << "Has not implemented yet!" << std::endl;
}



template <typename Comparable>
void RedBlackTree<Comparable>::printTree() const
{
	if (isEmpty())
		std::cout << "Empty tree" << std::endl;
	else { 
		printTree(header -> right);
		std::cout << std::endl;
	}

}


template <typename Comparable>
const RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=(const RedBlackTree<Comparable>& rhs)
{
	if (this != &rhs) {
		makeEmpty();
		header ->left = header -> right = clone(rhs.header -> right);
	}
	return *this;
}




template <typename Comparable>
void RedBlackTree<Comparable>::initTree()
{
 	nullNode = new RedBlackNode;
	nullNode -> left = nullNode -> right = nullNode;
	header = new RedBlackNode(ITEM_NOT_FOUND);
	header -> left = header -> right = nullNode;
	nullNode -> parent = header;
	header -> parent = nullNode;
}


template <typename Comparable>
bool RedBlackTree<Comparable>::isBlack(const typename RedBlackTree<Comparable>::RedBlackNode *rbn) const
{
	return rbn -> color == BLACK;
}


template <typename Comparable>
bool RedBlackTree<Comparable>::isRed(const typename RedBlackTree<Comparable>::RedBlackNode *rbn) const
{
	return rbn -> color == RED;
}


template <typename Comparable>
typename RedBlackTree<Comparable>::RedBlackNode *RedBlackTree<Comparable>::findAux(const Comparable& ele)
{
	grand = parent = header;
	current = parent -> right;
	while (current != nullNode) {
		if (current -> element == ele)
			return current;
		else { 
			grand = parent;
			parent = current;
			if (current -> element < ele)
				current = current -> right;
			else 
				current = current -> left;
		}
	}
	return current;
}


template <typename Comparable>
void RedBlackTree<Comparable>::printTree(const typename RedBlackTree<Comparable>::RedBlackNode* r) const
{
	if (r != nullNode) {
		printTree(r -> left);
		std::cout << r -> element << " ";
		printTree(r -> right);
	}
}


template <typename Comparable>
typename RedBlackTree<Comparable>::RedBlackNode *RedBlackTree<Comparable>::clone(const RedBlackNode* rbn)
{
	if (rbn != nullNode) {
		return new RedBlackNode(rbn -> element, clone(rbn -> left), clone(rbn -> right), rbn, rbn -> color);
	}
	return nullNode;
}


template <typename Comparable>
void RedBlackTree<Comparable>::makeEmpty(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{
	if (rbn != nullNode) {
		makeEmpty(rbn -> left);
		makeEmpty(rbn -> right);
		delete rbn;
	}
}


template <typename Comparable>
void RedBlackTree<Comparable>::fixUp(RedBlackNode *rbn)
{	
	while (isRed(rbn -> parent)) {
		if (rbn -> parent == rbn -> parent -> parent -> left) {	
			if (isRed(rbn -> parent -> parent -> right)) {	
				colorExchange(rbn -> parent -> parent);
				rbn = rbn -> parent -> parent;
			}					
			else {
				if (rbn == rbn -> parent -> right)	{	
					rotateWithRightChild(rbn -> parent);
					rbn = rbn -> left;
				}
				rotateWithLeftChild(rbn -> parent -> parent);	
				rbn -> parent -> color = BLACK;
				rbn -> parent -> right -> color = RED;
				break;
			}
		}
		else {							
			if (isRed(rbn -> parent -> parent -> left)) {		
				colorExchange(grand);
				rbn = rbn -> parent -> parent;
			}
			else {
				if (rbn == rbn -> parent -> left) {	
					rotateWithLeftChild(rbn -> parent);
					rbn = rbn -> right;
				}
				rotateWithRightChild(rbn -> parent -> parent);
				rbn -> parent -> color = BLACK;
				rbn -> parent -> left -> color = RED;
				break;
			}
		}
	}
	header -> right -> color = BLACK;
}


template <typename Comparable>
void RedBlackTree<Comparable>::colorExchange(typename RedBlackTree<Comparable>::RedBlackNode* rbn)
{
	if (isBlack(rbn) && isRed(rbn -> left) && isRed(rbn -> right)) {
		rbn -> color = RED;
		rbn -> left -> color = rbn -> right -> color = BLACK;
		return;
	}
	if (isRed(rbn) && isBlack(rbn -> left) && isBlack(rbn -> right)) {
		rbn -> color = BLACK;
		rbn -> left -> color = rbn -> right -> color = RED;
		return;
	}
}


template <typename Comparable>
void RedBlackTree<Comparable>::rotateWithLeftChild(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{


	RedBlackNode *tmp = rbn -> left;
	rbn -> left = tmp -> right;
	tmp -> right -> parent = rbn;
	tmp -> right = rbn;
	tmp -> parent = rbn -> parent;
	if (rbn == header -> left) {
		header -> left = header -> right = tmp;
	}
	else {
		if (rbn -> parent -> left == rbn) {
			rbn -> parent -> left = tmp;
		}
		else {
			rbn -> parent -> right = tmp;
		}
	}
	rbn -> parent = tmp;
}

template <typename Comparable>
void RedBlackTree<Comparable>::rotateWithRightChild(typename RedBlackTree<Comparable>::RedBlackNode *rbn)
{


	RedBlackNode *tmp = rbn -> right;
	rbn -> right = tmp -> left;
	tmp -> left -> parent = rbn;
	tmp -> left = rbn;
	tmp -> parent = rbn -> parent;
	if (rbn == header -> left) {
		header -> left = header -> right = tmp;
	}
	else {
		if (rbn == rbn -> parent -> left) {
			rbn -> parent -> left = tmp;
		}
		else {
			rbn -> parent -> right = tmp;
		}
	}
	rbn -> parent = tmp;
}


template <typename Comparable>
void RedBlackTree<Comparable>::insertButtomUp(const Comparable& ele)
{
	RedBlackNode *r = findAux(ele);
	if (r != nullNode)	
		return;
	r = new RedBlackNode(ele, nullNode, nullNode, parent, RED);
	if (parent == header) {	
		header -> left = header -> right = r;
		r -> color = BLACK;
		return;
	}
	if (r -> element < parent -> element)
		parent -> left = r;
	else 
		parent -> right = r;
	fixUp(r);
}


template <typename Comparable>
void RedBlackTree<Comparable>::insertTopDown(const Comparable& ele)
{	
	parent = header;
	current = parent -> left;
	while (current != nullNode) {
		if (isBlack(current) && isRed(current -> left) && isRed(current -> right)) {
			colorExchange(current);
			fixUp(current);
		}
		if (current -> element == ele) {
			break;
		}
		else {
			parent = current;
			if (current -> element < ele) {
				current = current -> right;
			}
			else {
				current = current -> left;
			}
		}
	}

	if (current != nullNode)	
		return;
	RedBlackNode *r = new RedBlackNode(ele, nullNode, nullNode, parent, RED);
	if (parent == header) {
		header -> left = header -> right = r;
		r -> color = BLACK;
		return;
	}
	if (parent -> element > ele) 
		parent -> left = r;
	else 
		parent -> right = r;
	fixUp(r);
}

#endif	