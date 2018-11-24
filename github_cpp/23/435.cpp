#include <limits>
#include "SkipListNode.h"


	SkipListNode::SkipListNode(int value){ //Contructor
		this->value = value;
		this->up = NULL;
		this->down = NULL;
		this->left = NULL;
		this->right = NULL;
	}

	//I would hope you know what these do...
	int SkipListNode::getValue(){
		return this->value;
	}

	void SkipListNode::setValue(int value){
		this->value = value;
	}

	SkipListNode *SkipListNode::getLeft(){
		if(left != NULL)
			return left;
		else
			return NULL;
	}

	void SkipListNode::setLeft(SkipListNode *left){
		this->left = left;
	}

	SkipListNode *SkipListNode::getRight(){
		if(right != NULL)
			return right;
		else
			return NULL;
	}

	void SkipListNode::setRight(SkipListNode *right){
		this->right = right;
	}

	SkipListNode *SkipListNode::getUp(){
		if(up != NULL)
			return up;
		else
			return NULL;
	}

	void SkipListNode::setUp(SkipListNode *up){
		this->up = up;
	}

	SkipListNode *SkipListNode::getDown(){
		if(down != NULL)
			return down;
		else
			return NULL;
	}

	void SkipListNode::setDown(SkipListNode *down){
		this->down = down;
	}	