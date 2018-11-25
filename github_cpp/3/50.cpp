#include "AVLTree.h"

AVLTree::AVLTree(){
	this->treeRoot = NULL;
}


void AVLTree::rightDoubleRot(Node **node){ 
	
	

	
	Node *leftChildNode = (*node)->left;
	Node *rightGrandChild = leftChildNode->right;

	if(rightGrandChild->balance == +1){
		(*node)->balance = 0;
		leftChildNode->balance = +1;
	}else
	if(rightGrandChild->balance == 0){
		(*node)->balance = 0;
		leftChildNode->balance = 0;
	}else{
		(*node)->balance = +1;
		leftChildNode->balance = 0;
	}

	rightGrandChild->balance = 0;
	leftChildNode->right = rightGrandChild->left;
	rightGrandChild->left = leftChildNode;
	(*node)->left = rightGrandChild->right;
	rightGrandChild->right = (*node);
	*node = rightGrandChild;
}



void AVLTree::leftDoubleRot(Node **node){ 
	
	

	
	
	Node *rightChildNode = (*node)->right;
	Node *leftGrandChild = rightChildNode->left;

	if(leftGrandChild->balance == -1){
		(*node)->balance = 0;
		rightChildNode->balance = -1;
	}else
	if(leftGrandChild->balance == 0){
		(*node)->balance = 0;
		rightChildNode->balance = 0;
	}else{
		(*node)->balance = +1;
		rightChildNode->balance = 0;
	}

	leftGrandChild->balance = 0;
	rightChildNode->left = leftGrandChild->right;
	leftGrandChild->right = rightChildNode;
	(*node)->right = leftGrandChild->left;
	leftGrandChild->left = (*node);
	*node = leftGrandChild;



}

void AVLTree::leftSimpleRot(Node **node, Node *nodeFather){
	Node *rightChild = (*node)->right;
	Node *leftGrandChild = rightChild->left;
	
	Node *pNode = (*node);
	
	
	if(nodeFather == NULL) 
		treeRoot = pNode->right;else 
	if(nodeFather->left == pNode)
		nodeFather->left = pNode->right;else
	if(nodeFather->right == pNode)
		nodeFather->right = pNode->right;
	
	pNode->balance = 0;
	rightChild->balance = 0;	

	rightChild->left = pNode;
	pNode->right = leftGrandChild; 
}

string AVLTree::internalViewTree(Node *node){
	stringstream buffer;	
	
	if(node == NULL)
		return "";

	buffer<<"------------------------------------"<<endl;
	buffer<<"Node:"<<node->value<<"("<<node->balance<<")"<<endl;
	
	if(node->left!=NULL)
	buffer<<"LEFT:"<<node->left->value<<endl;else
	buffer<<"LEFT: NDA"<<endl;

	if(node->right!=NULL)
	buffer<<"RIGHT:"<<node->right->value<<endl;else
	buffer<<"RIGHT: NDA"<<endl;

	buffer<<internalViewTree(node->left);
	buffer<<internalViewTree(node->right);
	
	return buffer.str(); 
}

string AVLTree::viewTree(){
	return internalViewTree(treeRoot);
}

void AVLTree::rightSimpleRot(Node **node, Node *nodeFather){

	Node *leftChild = (*node)->left;
	Node *rightGrandChild = leftChild->right;
	
	Node *pNode = (*node);
	
	
	if(nodeFather == NULL) 
		treeRoot = pNode->left;else 
	if(nodeFather->left == pNode)
		nodeFather->left = pNode->left;else
	if(nodeFather->right == pNode)
		nodeFather->right = pNode->left;
	
	pNode->balance = 0;
	leftChild->balance = 0;	

	leftChild->right = pNode;
	pNode->left = rightGrandChild; 
		
	
}

bool AVLTree::adjustLeftUnbalanced(Node **node, Node *nodeFather){
	Node *pNode = *node;
	
	if(pNode->left->balance == -1){ 
		rightSimpleRot(node, nodeFather);
	}else{ 
		
		this->rightDoubleRot(node);
	}

	return false;
}

bool AVLTree::adjustRightUnbalanced(Node **node,  Node *nodeFather){
	Node *pNode = *node;
	
	if(pNode->right->balance == +1){ 
		leftSimpleRot(node, nodeFather);
	}else{ 
		leftDoubleRot(node);
	}

	
	return false;
}

bool AVLTree::internalInsert(Node **node, Node *nodeFather, int value){
	
	if( *node == NULL){
		*node = new Node(value, 0, NULL, NULL);
		return true; 
	}else{
		Node *pNode  = *node;

		if( value <= pNode->value ){ 
			bool updateBalance = internalInsert(&pNode->left, pNode, value);

			if(updateBalance){
				
				if(pNode->balance == -1){
					return adjustLeftUnbalanced(node, nodeFather); 
				}else
				if(pNode->balance == 0){
					pNode->balance = -1;
					return true;
				}else{ 
					pNode->balance = 0;
					return false;
				}

			}else
				return false;


		}else{ 
			bool updateBalance = internalInsert(&pNode->right, pNode, value);
						
			if(updateBalance){
				
				if(pNode->balance == -1){
					pNode->balance = 0;
					return false;
				}else
				if(pNode->balance == 0){
					pNode->balance = +1;
					return true;
				}else{ 
					return adjustRightUnbalanced(node, nodeFather); 
				}

			}else
				return false;

		}

	}

	return false;
}

void AVLTree::insert(int value){
	
	if(treeRoot == NULL){
		treeRoot = new Node(value, 0, NULL, NULL); 
	}else{
		internalInsert(&treeRoot, NULL, value);	
	}	
}

string AVLTree::internalPreOrderedState(Node *node){
	stringstream buffer;
	
	if(node == NULL){
		return "()";
	}

	buffer<< "(" << node->value << ",";
	buffer<< internalPreOrderedState(node->left) << ",";
	buffer<< internalPreOrderedState(node->right) << ")";

	return buffer.str(); 
}

string AVLTree::preOrderedState(){	
	return internalPreOrderedState(this->treeRoot);;
}

bool AVLTree::remove(int value){

	return true;
}

bool AVLTree::internalFind(Node *node, int value){

	if(node == NULL)
		return false;
	
	
	if(value > node->value)
		return internalFind(node->right, value);else
	if(value < node->value)
		return internalFind(node->left, value);else
		return true;

	return false;
}

bool AVLTree::find(int value){
	return internalFind(treeRoot, value);
}

string AVLTree::internalTraceFind(Node *node, int value){

	if(node == NULL){
		return "";
	}
	
	stringstream buffer;
	
	if(node != treeRoot){
		buffer<<",";
	}
	buffer<< node->value;
	
	
	
	if(value < node->value){
		buffer<<internalTraceFind(node->left, value);
	}else
	if(value > node->value){
		buffer<< internalTraceFind(node->right, value);
	}

	return buffer.str();
}

string AVLTree::traceFind(int value){
	return internalTraceFind(treeRoot, value);
}

void AVLTree::internalRelease(Node *node){
	if(node == NULL)
		return;
	
	internalRelease(node->left);
	internalRelease(node->right);
		
	delete node;
	
}

void AVLTree::release(){
	internalRelease(treeRoot);
	treeRoot = NULL;
}

AVLTree::~AVLTree(){
	release();
}
