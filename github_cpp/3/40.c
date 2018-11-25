#include "avl-tree.h"
#include <iostream>
using namespace std;

template<class T>
T max(T a, T b)
{
	return a > b ? a : b;
}


void print(AVLNode *r)
{
	std::cout << r->data << "\t";
}


void inOrderTrav(AVLNode *r)
{
	if (!r)
		return;
	if (r->left)
		inOrderTrav(r->left);
	print(r);
	if (r->right)
		inOrderTrav(r->right);
}

short height(AVLNode *r)
{
	if (r)
		return r->height;
	return -1;
}


void LL(AVLNode *&r)
{
	AVLNode *p = r->left;
	r->left = p->right;
	p->right = r;

	r->height = max(height(r->left), height(r->right)) + 1;
	p->height = max(height(p->left), height(p->right)) + 1;

	r = p;
}


void RR(AVLNode *&r)
{
	AVLNode *p = r->right;
	r->right = p->left;
	p->left = r;

	r->height = max(height(r->left), height(r->right)) + 1;
	p->height = max(height(p->left), height(p->right)) + 1;

	r = p;
}


void LR(AVLNode *&r)
{
	RR(r->right);
	LL(r);
}


void RL(AVLNode *&r)
{
	LL(r->left);
	RR(r);
}

void destroyAVL(AVLNode *r);

AVLNode *initialAVL()
{
	AVLNode *r = new AVLNode;
	return r;
}

AVLNode *findNode(AVLNode *r, int val)
{
	AVLNode *p = r;
	while (p)
	{
		if (p->data == val)
			return r;
		else if (p->data > val)
			p = p->left;
		else
			p = p->right;
	}
	return nullptr;
}


void insertNode(AVLNode *&r, int val)
{
	if (!r)
	{
		r = new AVLNode(val);
		return;
	}
	if (val > r->data)
	{
		insertNode(r->right, val);
		if (r->left && r->right && (height(r->right) - height(r->left) == 2))
		{
			if (val > r->right->data)               
				RR(r);
			else									
				RL(r);
		}
	}
	else if (val < r->data)
	{
		insertNode(r->left, val);
		if (r->left && r->right && (height(r->left) - height(r->right) == 2))
		{
			if (val < r->left->data)					
				LL(r);
			else									
				LR(r);
		}
	}
	else
		++(r->freq);
	r->height = max(height(r->left), height(r->right)) + 1;
}

void swapNode(AVLNode &a, AVLNode &b)
{
    swap(a.data, b.data);
    swap(a.freq, b.freq);
}
void deleteNode(AVLNode *&r, int val)
{
	if (!r)
		return;
    if (val == r->data)
    {
        if (!r->right && !r->left)      
        {
            delete(r);
            r = nullptr;
            return;
        }
        else if ((!r->left && r->right) || (r->left && !r->right))
        {
            AVLNode *temp = nullptr;
            if (r->left)    
            {
                temp = r->left;
            }
            else            
            {
                temp = r->right;
            }
            r->data = temp->data;
            r->left = temp->left;
            r->right = temp->right;
            r->freq = r->freq;
            r->height = temp->height;
            delete(temp);
            temp = nullptr;
            return;
        }
        else
        {
            AVLNode *temp = nullptr;
            if (height(r->right) - height(r->left) >= 0)        
            {
                temp = r->right;
                while (temp->left)
                {
                    temp = temp->left;
                }
            }
            else                                                
            {
                temp = r->left;
                while (temp->right)
                {
                    temp = temp->right;
                }
            }
            swapNode(*r, *temp);
            deleteNode(temp, val);
        }
    }
    else if (val < r->data)
	{
		deleteNode(r->left, val);
		if ((height(r->right) - height(r->left) == 2))
		{
			if (r->right->left != NULL &&height(r->right->left)>height(r->right->right))
				RL(r);
			else
				RR(r);
		}
	}
	else
	{
		deleteNode(r->right, val);
		if ((height(r->right) - height(r->left) == 2))
		{
			if (r->left->right != NULL && (height(r->left->right) > height(r->left->left)))
				LR(r);
			else
				LL(r);
		}
    }
    r->height = max(height(r->left), height(r->right)) + 1;
}