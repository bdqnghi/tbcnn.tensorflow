

#include "AVL.h"

using namespace std;


AVL::AVL() : root(NULL){ }

AVL::AVL(const AVL &Tree)
{
	root = clone(Tree.root);
}

AVL::~AVL()
{
	makeEmpty(root);
	delete root;
}


void AVL::clear()
{
	makeEmpty(root);
}

void AVL::insert(const Type& typeIn)
{
	
	insert(typeIn, root);
}

void AVL::remove(const Type& typeIn)
{
	
	remove(typeIn, root);
}



AVL::Node* AVL::clone(Node *NodeIn) const
{
	if (NodeIn == nullptr)
		return nullptr;
	else
		return new Node{ NodeIn->NodeElement, clone(NodeIn->left), clone(NodeIn->right), NodeIn->height };
}

void AVL::makeEmpty(Node *&NodeIn)
{
	if (NodeIn != nullptr)
	{
		makeEmpty(NodeIn->left);
		makeEmpty(NodeIn->right);
		delete NodeIn;
	}
	NodeIn = nullptr;
}

const Type& AVL::findMin(Node *NodeIn) const
{
	if (NodeIn == nullptr)
		return NO_Type;
	if (NodeIn->left == nullptr)
		return NodeIn->NodeElement;
	return findMin(NodeIn->left);
}

void AVL::insert(const Type &TypeIn, Node *&NodeIn)
{
	if (NodeIn == nullptr)
		NodeIn = new Node{ TypeIn, nullptr , nullptr, 0 };
	else if (TypeIn < NodeIn->NodeElement)
		insert(TypeIn, NodeIn->left);
	else if (NodeIn->NodeElement < TypeIn)
		insert(TypeIn, NodeIn->right);
	else
	{
		
	}
		balance(NodeIn);
}

void AVL::remove(const Type &TypeIn, Node *&NodeIn)
{
	if (NodeIn == nullptr)
		return; 
	if (TypeIn < NodeIn->NodeElement)
		remove(TypeIn, NodeIn->left);
	else if (NodeIn->NodeElement < TypeIn)
		remove(TypeIn, NodeIn->right);
	else if (NodeIn->left != nullptr && NodeIn->right != nullptr) 
	{
		NodeIn->NodeElement = findMin(NodeIn->right);
		remove(NodeIn->NodeElement, NodeIn->right);
	}
	else
	{
		Node *oldNode = NodeIn;
		NodeIn = (NodeIn->left != nullptr) ? NodeIn->left : NodeIn->right;
		delete oldNode;
	}
	balance(NodeIn);
}


void AVL::balance(Node *&NodeIn)
{
	if (NodeIn == nullptr)
		return;
	if (height(NodeIn->left) - height(NodeIn->right) > ALLOWED_IMBALANCE)
	{
		if (height(NodeIn->left->left) >= height(NodeIn->left->right))
			rotateLL(NodeIn);
		else
			doubleWithLeftChild(NodeIn);
	}
	else
	{
		if (height(NodeIn->right) - height(NodeIn->left) > ALLOWED_IMBALANCE)
		{
			if (height(NodeIn->right->right) >= height(NodeIn->right->left))
				rotateRR(NodeIn);
			else
				doubleWithRightChild(NodeIn);
		}
	}
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
}

void AVL::rotateLL(Node *&NodeIn)
{
	Node *tempnode = NodeIn->left;
	NodeIn->left = tempnode->right;
	tempnode->right = NodeIn;
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
	tempnode->height = max(height(tempnode->left), NodeIn->height) + 1;
	NodeIn = tempnode;
}

void AVL::rotateRR(Node *&NodeIn)
{
	Node *tempnode = NodeIn->right;
	NodeIn->right = tempnode->left;
	tempnode->left = NodeIn;
	NodeIn->height = max(height(NodeIn->right), height(NodeIn->left)) + 1;
	tempnode->height = max(height(tempnode->right), NodeIn->height) + 1;
	NodeIn = tempnode;
}

void AVL::doubleWithLeftChild(Node *&NodeIn)
{
	rotateRR(NodeIn->left);
	rotateLL(NodeIn);
}

void AVL::doubleWithRightChild(Node *&NodeIn)
{
	rotateLL(NodeIn->right);
	rotateRR(NodeIn);
}


int AVL::height(Node *NodeIn) const
{
	return NodeIn == nullptr ? -1 : NodeIn->height;
}

int AVL::max(int left, int right)
{
	if (left < right)
		return right;
	else if (right < left)
		return left;
	else
		return left;
}



