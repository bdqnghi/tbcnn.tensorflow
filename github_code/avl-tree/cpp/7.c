#pragma once

// NAME: Adam Armstrong
// SECTION: CS 2420 - 002
// PROFESSOR: Todd S. Peterson
// Due: 3/24/2016

// DISCLAIMER:
// I, Adam Armstrong, have not used any code other than my own (or that in the textbook) for this project.
// I also have not used any function or data-structure from the Standard-Template Library.
// I also have not shared my code with any student in this class.
// I understand that any violation of this disclaimer will result in a 0 for the project.

//	Project 08: AVL Tree

#include "AVLtree.h"


// __________________
// Constructor:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
AVLtree::AVLtree()
{
	root = nullptr;
	height = 0;
}


// __________________
// Destructor:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
AVLtree::~AVLtree()
{
	if (root != nullptr)
		Destruct_Helper(root);
}


// __________________
//	Destruct Helper:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Insert:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Insert Helper:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Print:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
void AVLtree::Print()
{
	int depth = 0;

	if (root != nullptr)
		Print_Helper(root, depth);
}


// __________________
//	Print Helper:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Num Children:
/// Purpose: Checks to see how many children the passed Node has.
/// Parameters: Node pointer
/// Returns: int
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Rotate Left:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
Node* AVLtree::RotateLeft(Node*& n) // L
{
	Node* tempNode = nullptr;

	tempNode = n->left_child;
	tempNode->right_child = n;
	n->left_child = nullptr;

	return tempNode;
}


// __________________
//	Rotate Right:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
Node* AVLtree::RotateRight(Node*& n) // R
{
	Node* tempNode = nullptr;

	tempNode = n.right;
	n.right = tempNode->left;
	tempNode.left = n;

	return tempNode;
}


// __________________
//	Rotate Left-Right:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
Node* AVLtree::RotateLeftRight(Node*& n) // LR
{
	Node* tempNode = nullptr;

	tempNode = n->left->right;
	tempNode->left = n->left;
	tempNode->left->right = nullptr;
	tempNode->right = n;
	n->left = nullptr;

	return tempNode;
}


// __________________
//	Rotate Right-Left:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
Node* AVLtree::RotateRightLeft(Node*& n) // RL
{
	Node* tempNode = nullptr;

	tempNode = n.right->left;
	tempNode.left = n;
	n.right.left = tempNode->right;
	tempNode->right = n->right;
	n->right = nullptr;

	return tempNode;
}


// __________________
//	Rebalance:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Rebalance Helper:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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
				if (current_n->left->bal <= 0) // LR
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

				else if (current_n->left->bal >= 1) // L
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
				if (current_n->right->bal == -1) // R
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

				else if (current_n->right->bal == 1) // RL
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


// __________________
//	Is Unbalanced:
/// Purpose: Checks to see if the passed Node is the root of an unbalanced tree.
/// Parameters: Node pointer
/// Returns: bool
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Update Height:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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


// __________________
//	Update Balance:
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
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



/*	4 rotations:
		1. left
		2. right
		3. left-right (double)
		4. right-left (double)

	Left Rotation:
		1. Pivot becomes new Root
		2. Old Root becomes pivot's left child
		3. Pivot's left child becomes right child of old root

	BalanceFactor = height(left) - height(right);

	node *a = root->left;
	node **b = &(root->left);
	*b = nullptr;
*/


// __________________
//	// Left Rotation (by Reference):
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
void AVLtree::LeftRotation_reference(Node*& root, Node*& pivot)
{
	//Node *temp = pivot->left;
	//pivot->left = root;
	//root->right = temp;

	//	1. Pivot becomes new Root
	//root = pivot;

	//	2. Old Root becomes pivot's left child


	//	3. Pivot's left child becomes right child of old root
}


// __________________
//	Left Rotation (by pointer):
/// Purpose:
/// Parameters:
/// Returns:
/// Pre-Conditions:
/// Post-Conditions:
void AVLtree::LeftRotation_pointer(Node **root, Node *pivot)
{
	//Node *temp = pivot->left;
	//pivot->left = *root;
	//*root->right = temp;

	//*root = pivot;
}