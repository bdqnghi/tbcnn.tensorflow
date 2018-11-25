


#include <util/AVLTreeBase.h>

#include <algorithm>

#include <KernelExport.h>


#ifdef _KERNEL_MODE
#	define CHECK_FAILED(message...)	panic(message)
#else
#	include <stdio.h>
#	include <OS.h>
#	define CHECK_FAILED(message...)					\
		do {										\
			fprintf(stderr, message);				\
			fprintf(stderr, "\n");					\
			debugger("AVLTreeBase check failed");	\
		} while (false)
#endif



static const int kMaxAVLTreeHeight = 32;





AVLTreeCompare::~AVLTreeCompare()
{
}





AVLTreeBase::AVLTreeBase(AVLTreeCompare* compare)
	: fRoot(NULL),
	  fNodeCount(0),
	  fCompare(compare)
{
}


AVLTreeBase::~AVLTreeBase()
{
}


void
AVLTreeBase::MakeEmpty()
{
	fRoot = NULL;
	fNodeCount = 0;
}


AVLTreeNode*
AVLTreeBase::LeftMost(AVLTreeNode* node) const
{
	if (node) {
		while (node->left)
			node = node->left;
	}

	return node;
}


AVLTreeNode*
AVLTreeBase::RightMost(AVLTreeNode* node) const
{
	if (node) {
		while (node->right)
			node = node->right;
	}

	return node;
}


AVLTreeNode*
AVLTreeBase::Previous(AVLTreeNode* node) const
{
	if (node) {
		
		if (node->left) {
			
			node = node->left;
			while (node->right)
				node = node->right;
		} else {
			
			
			AVLTreeNode* previous;
			do {
				previous = node;
				node = node->parent;
			} while (node && previous == node->left);
		}
	}

	return node;
}


AVLTreeNode*
AVLTreeBase::Next(AVLTreeNode* node) const
{
	if (node) {
		
		if (node->right) {
			
			node = node->right;
			while (node->left)
				node = node->left;
		} else {
			
			
			AVLTreeNode* previous;
			do {
				previous = node;
				node = node->parent;
			} while (node && previous == node->right);
		}
	}

	return node;
}


AVLTreeNode*
AVLTreeBase::Find(const void* key) const
{
	AVLTreeNode* node = fRoot;

	while (node) {
		int cmp = fCompare->CompareKeyNode(key, node);
		if (cmp == 0)
			return node;

		if (cmp < 0)
			node = node->left;
		else
			node = node->right;
	}

	return NULL;
}


AVLTreeNode*
AVLTreeBase::FindClosest(const void* key, bool less) const
{
	AVLTreeNode* node = fRoot;
	AVLTreeNode* parent = NULL;

	while (node) {
		int cmp = fCompare->CompareKeyNode(key, node);
		if (cmp == 0)
			break;

		parent = node;
		if (cmp < 0)
			node = node->left;
		else
			node = node->right;
	}

	
	if (!node && parent) {
		node = parent;
		int expectedCmp = (less ? 1 : -1);
		int cmp = fCompare->CompareKeyNode(key, node);
		if (cmp != expectedCmp) {
			
			
			
			if (less)
				return Previous(node);
			return Next(node);
		}
	}

	return node;
}


status_t
AVLTreeBase::Insert(AVLTreeNode* nodeToInsert)
{
	int result = _Insert(nodeToInsert);
	switch (result) {
		case OK:
		case HEIGHT_CHANGED:
			return B_OK;
		case NO_MEMORY:
			return B_NO_MEMORY;
		case DUPLICATE:
		default:
			return B_BAD_VALUE;
	}
}


AVLTreeNode*
AVLTreeBase::Remove(const void* key)
{
	
	AVLTreeNode* node = fRoot;
	while (node) {
		int cmp = fCompare->CompareKeyNode(key, node);
		if (cmp == 0)
			break;
		else {
			if (cmp < 0)
				node = node->left;
			else
				node = node->right;
		}
	}

	
	if (node)
		_Remove(node);

	return node;
}


bool
AVLTreeBase::Remove(AVLTreeNode* node)
{
	switch (_Remove(node)) {
		case OK:
		case HEIGHT_CHANGED:
			return true;
		case NOT_FOUND:
		default:
			return false;
	}
}


void
AVLTreeBase::CheckTree() const
{
	int nodeCount = 0;
	_CheckTree(NULL, fRoot, nodeCount);
	if (nodeCount != fNodeCount) {
		CHECK_FAILED("AVLTreeBase::CheckTree(): node count mismatch: %d vs %d",
			nodeCount, fNodeCount);
	}
}


void
AVLTreeBase::_RotateRight(AVLTreeNode** nodeP)
{
	
	AVLTreeNode* node = *nodeP;
	AVLTreeNode* left = node->left;

	*nodeP = left;

	left->parent = node->parent;
	node->left = left->right;
	if (left->right)
		left->right->parent = node;
	left->right = node;
	node->parent = left;

	
	
	if (left->balance_factor >= 0)
		node->balance_factor++;
	else
		node->balance_factor += 1 - left->balance_factor;

	
	if (node->balance_factor <= 0)
		left->balance_factor++;
	else
		left->balance_factor += node->balance_factor + 1;
}


void
AVLTreeBase::_RotateLeft(AVLTreeNode** nodeP)
{
	
	AVLTreeNode* node = *nodeP;
	AVLTreeNode* right = node->right;

	*nodeP = right;

	right->parent = node->parent;
	node->right = right->left;
	if (right->left)
		right->left->parent = node;
	right->left = node;
	node->parent = right;

	
	
	if (right->balance_factor <= 0)
		node->balance_factor--;
	else
		node->balance_factor -= right->balance_factor + 1;

	
	if (node->balance_factor >= 0)
		right->balance_factor--;
	else
		right->balance_factor += node->balance_factor - 1;
}


int
AVLTreeBase::_BalanceInsertLeft(AVLTreeNode** node)
{
	if ((*node)->balance_factor < LEFT) {
		
		AVLTreeNode** left = &(*node)->left;
		if ((*left)->balance_factor == LEFT) {
			
			_RotateRight(node);
		} else {
			
			_RotateLeft(left);
			_RotateRight(node);
		}
		return OK;
	}

	if ((*node)->balance_factor == BALANCED)
		return OK;

	return HEIGHT_CHANGED;
}


int
AVLTreeBase::_BalanceInsertRight(AVLTreeNode** node)
{
	if ((*node)->balance_factor > RIGHT) {
		
		AVLTreeNode** right = &(*node)->right;
		if ((*right)->balance_factor == RIGHT) {
			
			_RotateLeft(node);
		} else {
			
			_RotateRight(right);
			_RotateLeft(node);
		}
		return OK;
	}

	if ((*node)->balance_factor == BALANCED)
		return OK;

	return HEIGHT_CHANGED;
}


int
AVLTreeBase::_Insert(AVLTreeNode* nodeToInsert)
{
	struct node_info {
		AVLTreeNode**	node;
		bool			left;
	};

	node_info stack[kMaxAVLTreeHeight];
	node_info* top = stack;
	const node_info* const bottom = stack;
	AVLTreeNode** node = &fRoot;

	
	while (*node) {
		int cmp = fCompare->CompareNodes(nodeToInsert, *node);
		if (cmp == 0)	
			return DUPLICATE;
		else {
			top->node = node;
			if (cmp < 0) {
				top->left = true;
				node = &(*node)->left;
			} else {
				top->left = false;
				node = &(*node)->right;
			}
			top++;
		}
	}

	
	*node = nodeToInsert;
	nodeToInsert->left = NULL;
	nodeToInsert->right = NULL;
	nodeToInsert->balance_factor = BALANCED;
	fNodeCount++;

	if (top == bottom)
		nodeToInsert->parent = NULL;
	else
		(*node)->parent = *top[-1].node;

	
	int result = HEIGHT_CHANGED;
	while (result == HEIGHT_CHANGED && top != bottom) {
		top--;
		node = top->node;
		if (top->left) {
			
			(*node)->balance_factor--;
			result = _BalanceInsertLeft(node);
		} else {
			
			(*node)->balance_factor++;
			result = _BalanceInsertRight(node);
		}
	}

	return result;
}


int
AVLTreeBase::_BalanceRemoveLeft(AVLTreeNode** node)
{
	int result = HEIGHT_CHANGED;

	if ((*node)->balance_factor > RIGHT) {
		
		AVLTreeNode** right = &(*node)->right;
		if ((*right)->balance_factor == RIGHT) {
			
			_RotateLeft(node);
		} else if ((*right)->balance_factor == BALANCED) {
			
			_RotateLeft(node);
			result = OK;
		} else {
			
			_RotateRight(right);
			_RotateLeft(node);
		}
	} else if ((*node)->balance_factor == RIGHT)
		result = OK;

	return result;
}


int
AVLTreeBase::_BalanceRemoveRight(AVLTreeNode** node)
{
	int result = HEIGHT_CHANGED;

	if ((*node)->balance_factor < LEFT) {
		
		AVLTreeNode** left = &(*node)->left;
		if ((*left)->balance_factor == LEFT) {
			
			_RotateRight(node);
		} else if ((*left)->balance_factor == BALANCED) {
			
			_RotateRight(node);
			result = OK;
		} else {
			
			_RotateLeft(left);
			_RotateRight(node);
		}
	} else if ((*node)->balance_factor == LEFT)
		result = OK;

	return result;
}


int
AVLTreeBase::_RemoveRightMostChild(AVLTreeNode** node, AVLTreeNode** foundNode)
{
	AVLTreeNode** stack[kMaxAVLTreeHeight];
	AVLTreeNode*** top = stack;
	const AVLTreeNode* const* const* const bottom = stack;

	
	while ((*node)->right) {
		*top = node;
		top++;
		node = &(*node)->right;
	}

	
	
	
	*foundNode = *node;
	AVLTreeNode* left = (*node)->left;
	if (left)
		left->parent = (*node)->parent;
	*node = left;
	(*foundNode)->left = NULL;
	(*foundNode)->parent = NULL;

	
	int result = HEIGHT_CHANGED;
	while (result == HEIGHT_CHANGED && top != bottom) {
		top--;
		node = *top;
		(*node)->balance_factor--;
		result = _BalanceRemoveRight(node);
	}

	return result;
}


int
AVLTreeBase::_Remove(AVLTreeNode* node)
{
	if (!node)
		return NOT_FOUND;

	
	AVLTreeNode* parent = node->parent;
	bool isLeft = (parent && parent->left == node);
	AVLTreeNode** nodeP
		= (parent ? (isLeft ? &parent->left : &parent->right) : &fRoot);
	int result = HEIGHT_CHANGED;
	AVLTreeNode* replace = NULL;

	if (node->left && node->right) {
		
		result = _RemoveRightMostChild(&node->left, &replace);
		replace->parent = parent;
		replace->left = node->left;
		replace->right = node->right;
		if (node->left)	
			node->left->parent = replace;
		node->right->parent = replace;
		replace->balance_factor = node->balance_factor;
		*nodeP = replace;

		if (result == HEIGHT_CHANGED) {
			replace->balance_factor++;
			result = _BalanceRemoveLeft(nodeP);
		}
	} else if (node->left) {
		
		replace = node->left;
		replace->parent = parent;
		replace->balance_factor = node->balance_factor + 1;
		*nodeP = replace;
	} else if (node->right) {
		
		replace = node->right;
		replace->parent = node->parent;
		replace->balance_factor = node->balance_factor - 1;
		*nodeP = replace;
	} else {
		
		*nodeP = NULL;
	}

	fNodeCount--;

	
	while (result == HEIGHT_CHANGED && parent) {
		node = parent;
		parent = node->parent;
		bool oldIsLeft = isLeft;
		isLeft = (parent && parent->left == node);
		nodeP = (parent ? (isLeft ? &parent->left : &parent->right) : &fRoot);
		if (oldIsLeft) {
			
			node->balance_factor++;
			result = _BalanceRemoveLeft(nodeP);
		} else {
			
			node->balance_factor--;
			result = _BalanceRemoveRight(nodeP);
		}
	}

	return result;
}


int
AVLTreeBase::_CheckTree(AVLTreeNode* parent, AVLTreeNode* node,
	int& _nodeCount) const
{
	if (node == NULL) {
		_nodeCount = 0;
		return 0;
	}

	if (parent != node->parent) {
		CHECK_FAILED("AVLTreeBase::_CheckTree(): node %p parent mismatch: "
			"%p vs %p", node, parent, node->parent);
	}

	int leftNodeCount;
	int leftDepth = _CheckTree(node, node->left, leftNodeCount);

	int rightNodeCount;
	int rightDepth = _CheckTree(node, node->right, rightNodeCount);

	int balance = rightDepth - leftDepth;
	if (balance < LEFT || balance > RIGHT) {
		CHECK_FAILED("AVLTreeBase::_CheckTree(): unbalanced subtree: %p", node);
	} else if (balance != node->balance_factor) {
		CHECK_FAILED("AVLTreeBase::_CheckTree(): subtree %p balance mismatch: "
			"%d vs %d", node, balance, node->balance_factor);
	}

	_nodeCount = leftNodeCount + rightNodeCount + 1;
	return std::max(leftDepth, rightDepth) + 1;
}
