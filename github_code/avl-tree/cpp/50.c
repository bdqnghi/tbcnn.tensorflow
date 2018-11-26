#include "AVLTree.h"

AVLTree::AVLTree(){
	this->treeRoot = NULL;
}

// Usado no caso esquerda-direita
void AVLTree::rightDoubleRot(Node **node){ 
	// Aplicar rota��o simples a esquerda no filho de node
	// Aplicar rota��o simples a direita em node

	// Atualizando fatores de balanceamento
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


// Usado no caso direita-esquerda
void AVLTree::leftDoubleRot(Node **node){ 
	// Rota��o simples a direita no filhode de node
	// Rota��o simples a esquerda em node

	
	// Atualizando fatores de balanceamento
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
	
	// Atualiza o Pai de node para apontar para o filho correto ap�s balanceamento
	if(nodeFather == NULL) // N� raiz desbalanceado
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
	
	// Atualiza o Pai de node para apontar para o filho correto ap�s balanceamento
	if(nodeFather == NULL) // N� raiz desbalanceado
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
	
	if(pNode->left->balance == -1){ // Caso esquerda-esquerda		
		rightSimpleRot(node, nodeFather);
	}else{ // Caso esquerda-direita
		
		this->rightDoubleRot(node);
	}

	return false;
}

bool AVLTree::adjustRightUnbalanced(Node **node,  Node *nodeFather){
	Node *pNode = *node;
	
	if(pNode->right->balance == +1){ // Caso direita-direita		
		leftSimpleRot(node, nodeFather);
	}else{ // Caso direito-esquerda
		leftDoubleRot(node);
	}

	
	return false;
}

bool AVLTree::internalInsert(Node **node, Node *nodeFather, int value){
	
	if( *node == NULL){
		*node = new Node(value, 0, NULL, NULL);
		return true; // Atualiza o fator de balan�o do n� acima
	}else{
		Node *pNode  = *node;

		if( value <= pNode->value ){ // Pula para sub-arvore esquerda
			bool updateBalance = internalInsert(&pNode->left, pNode, value);

			if(updateBalance){
				
				if(pNode->balance == -1){
					return adjustLeftUnbalanced(node, nodeFather); //Aplica rota��o ( o n� vai ficar -2 infringindo a regra AVL)
				}else
				if(pNode->balance == 0){
					pNode->balance = -1;
					return true;
				}else{ // if(pNode->value == +1)  //Desbalanceado a direita
					pNode->balance = 0;
					return false;
				}

			}else
				return false;


		}else{ // Pula para sub-arvore direita
			bool updateBalance = internalInsert(&pNode->right, pNode, value);
						
			if(updateBalance){
				
				if(pNode->balance == -1){
					pNode->balance = 0;
					return false;
				}else
				if(pNode->balance == 0){
					pNode->balance = +1;
					return true;
				}else{ // if(pNode->value == +1)  //Desbalanceado a direita
					return adjustRightUnbalanced(node, nodeFather); //Aplica rota��o ( o n� vai ficar -2 infringindo a regra AVL)
				}

			}else
				return false;

		}

	}

	return false;
}

void AVLTree::insert(int value){
	
	if(treeRoot == NULL){
		treeRoot = new Node(value, 0, NULL, NULL); // Primeiro n� na �rvore
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
