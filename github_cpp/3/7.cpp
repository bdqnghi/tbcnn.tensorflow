#pragma once














#include "AVLtree.h"









AVLtree::AVLtree()
{
	root = nullptr;
	height = 0;
}









AVLtree::~AVLtree()
{
	if (root != nullptr)
		Destruct_Helper(root);
}









void AVLtree::Destruct_Helper(Node* root)
{
	if (root == nullptr)
		return;

	else
	{
		Destruct_Helper(root->left_child);
		Destruct_Helper(root->right_child);
		delete root;
		root = nullptr;
	}
}









void AVLtree::Insert(int d)
{
	if (root == nullptr)
	{
		Node* temp = new Node(d);
		root = temp;
		height = UpdateHeight(root);
	}

	else
	{
		Insert_Helper(root, d);
		Rebalance();
	}
}









void AVLtree::Insert_Helper(Node*& n, int d)
{
	if (d == n->data_field)
		return;

	if (d < n->data_field)
	{
		if (n->left_child == nullptr)
		{
			Node* temp = new Node(d);
			n->left_child = temp;
		}

		else
			Insert_Helper(n->left, d);
	}

	else
	{
		if (n->right_child == nullptr)
		{
			Node* temp = new Node(d);
			n->right_child = temp;
		}

		else
			Insert_Helper(n->right_child, d);
	}
}









void AVLtree::Print()
{
	int depth = 0;

	if (root != nullptr)
		Print_Helper(root, depth);
}









void AVLtree::Print_Helper(Node* n, int depth)
{
	cout << setw(4 * depth) << "";

	if (n == nullptr)
		cout << "[Empty]" << endl;

	else if (NumChildren(n) == 0)
		cout << n->data_field << " [Leaf]" << endl;

	else
	{
		cout << n->data_field << " " << endl;
		Print_Helper(n->left_child, depth + 1);
		Print_Helper(n->right_child, depth + 1);
	}
}









int AVLtree::NumChildren(Node* root)
{
	int tempChildren = 0;

	if (root->left_child != nullptr)
	{
		if (root->right_child != nullptr)
			tempChildren = 3;

		else
			tempChildren = 1;
	}

	else if (root->right_child != nullptr)
			tempChildren = 2;

	return tempChildren;
}









Node* AVLtree::RotateLeft(Node*& n) 
{
	Node* tempNode = nullptr;

	tempNode = n->left_child;
	tempNode->right_child = n;
	n->left_child = nullptr;

	return tempNode;
}









Node* AVLtree::RotateRight(Node*& n) 
{
	Node* tempNode = nullptr;

	tempNode = n.right;
	n.right = tempNode->left;
	tempNode.left = n;

	return tempNode;
}









Node* AVLtree::RotateLeftRight(Node*& n) 
{
	Node* tempNode = nullptr;

	tempNode = n->left->right;
	tempNode->left = n->left;
	tempNode->left->right = nullptr;
	tempNode->right = n;
	n->left = nullptr;

	return tempNode;
}









Node* AVLtree::RotateRightLeft(Node*& n) 
{
	Node* tempNode = nullptr;

	tempNode = n.right->left;
	tempNode.left = n;
	n.right.left = tempNode->right;
	tempNode->right = n->right;
	n->right = nullptr;

	return tempNode;
}









void AVLtree::Rebalance()
{
	if (root != nullptr)
	{
		UpdateHeight(root);
		UpdateBalance(root);

		while (Is_Unbalanced(root))
		{
			Rebalance_Helper(root, nullptr);
			UpdateHeight(root);
			UpdateBalance(root);
		}
	}
}









void AVLtree::Rebalance_Helper(Node *& current_n, Node * previous_n)
{
	if (current_n != nullptr)
	{
		if (current_n->left != nullptr)
			Rebalance_Helper(current_n->left, current_n);
		if (current_n->right != nullptr)
			Rebalance_Helper(current_n->right, current_n);

		if (current_n->bal < -1 || current_n->bal > 1)
		{
			if (current_n->bal > 1)
			{
				if (current_n->left->bal <= 0) 
				{
					if (previous_n == nullptr)
						root = RotateLeftRight(current_n);

					else
					{
						if (previous_n->left == current_n)
							previous_n->left = RotateLeftRight(current_n);
						else if (previous_n->right == current_n)
							previous_n->right = RotateLeftRight(current_n);
					}
				}

				else if (current_n->left->bal >= 1) 
				{
					if (previous_n == nullptr)
						root = RotateLeft(current_n);

					else
					{
						if (previous_n->left == current_n)
							previous_n->left = RotateLeft(current_n);
						else if (previous_n->right == current_n)
							previous_n->right = RotateLeft(current_n);
					}
				}
			}

			else if (current_n->bal < -1)
			{
				if (current_n->right->bal == -1) 
				{
					if (previous_n == nullptr)
						root = RotateRight(current_n);

					else
					{
						if (previous_n->left == current_n)
							previous_n->left = RotateRight(current_n);
						else if (previous_n->right == current_n)
							previous_n->right = RotateRight(current_n);
					}
				}

				else if (current_n->right->bal == 1) 
				{
					if (previous_n == nullptr)
						root = RotateRightLeft(current_n);
					else
					{
						if (previous_n->left >= current_n)
							previous_n->left = RotateRightLeft(current_n);
						else if (previous_n->right == current_n)
							previous_n->right = RotateRightLeft(current_n);
					}
				}
			}
		}
	}
}









bool AVLtree::Is_Unbalanced(Node* n)
{
	if (n == nullptr)
		return false;

	else
	{
		if (n->bal > 1 || n->bal < -1)
			return true;

		else
			return (Is_Unbalanced(n->left) || Is_Unbalanced(n->right));
	}
}









int AVLtree::UpdateHeight(Node*& n)
{
	if (n == nullptr)
		return 0;

	else
	{
		n->bal = 1 + n->max(UpdateHeight(n->left), UpdateHeight(n->right));
		return n->bal;
	}
}









int AVLtree::UpdateBalance(Node*& n)
{
	int tempLeft;
	int tempRight;

	if (n->left == nullptr)
		tempLeft = 0;

	else
		tempLeft = n->left->bal;

	if (n->right == nullptr)
		tempRight = 0;

	else
		tempRight = n->right->bal;

	n->bal = tempLeft - tempRight;

	if (n->left != nullptr)
		UpdateBalance(n->left);

	if (n->right != nullptr)
		UpdateBalance(n->right);
}













void AVLtree::LeftRotation_reference(Node*& root, Node*& pivot)
{
	
	
	

	
	

	


	
}









void AVLtree::LeftRotation_pointer(Node **root, Node *pivot)
{
	
	
	

	
}