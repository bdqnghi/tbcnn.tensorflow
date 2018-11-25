
#include <cassert>
#include <iostream>

#include "btree.h"


void diskRead(Node *x)
{

}
void diskWrite(Node *x)
{

}

Node* allocateNode()
{
	return new Node;
}

void btreeCreate(BTree *T)
{
	Node* x = allocateNode();
	x->leaf = true;
	x->n = 0;
	diskWrite(x);
	T->root = x;
}

void btreeSplitChild(Node *x, int i)
{
	
	assert(x->n < 2*t-1);
	Node* z = allocateNode();
	Node* y = x->c[i];
	
	assert(y->n == 2*t-1);

	z->leaf = y->leaf;
	z->n = t-1;
	for(int j=0; j<t-1; j++)
	{
		z->key[j] = y->key[j+t];
	}
	if(!y->leaf)
	{
		for(int j=0; j<t; j++)
		{
			z->c[j] = y->c[j+t];
		}
	}
	y->n = t-1;
   for(int j=x->n; j>=i+1; j--) 
	{
		x->c[j+1] = x->c[j];
	}
	x->c[i+1] = z;
	for(int j=x->n-1; j>=i; j--) 
	{
		x->key[j+1] = x->key[j];
	}
	x->key[i] = y->key[t-1];
	x->n += 1;

	diskWrite(y);
	diskWrite(z);
	diskWrite(x);
}

void btreeInsertNofull(Node* x, char k)
{
	int i = x->n-1;
	if (x->leaf) {
		while (i>=0 && k<x->key[i]) {
			x->key[i+1] = x->key[i];
			i = i-1;
		}
		x->key[i+1] = k;
		x->n += 1;
	} else {
		while(i>=0 && k<x->key[i]) {
			i = i-1;
		}
		i += 1;
		diskRead(x->c[i]);
		if(x->c[i]->n == 2*t-1) {
			btreeSplitChild(x, i);
			if(k>x->key[i]){
				i = i+1;
			}
		}
		btreeInsertNofull(x->c[i], k);
	}
}

void btreeInsert(BTree *T, char k)
{
	Node* r = T->root;
	if (r->n == 2*t-1) {
		Node *s = allocateNode();
		T->root = s;
		s->leaf = false;
		s->n = 0;
		s->c[0] = r;

		btreeSplitChild(s,0);
		btreeInsertNofull(s, k);
	}else {
		btreeInsertNofull(r,k);
	}
}

bool keyIsInNode(Node *x, char k){
	for (int i=0; i<x->n; i++) {
		if (k == x->key[i]) return true;
	}
   return false;
}

bool index(Node *x, char k) {
	for (int i=0; i<x->n; i++) {
		if (k == x->key[i]) return i;
	}
   return -1;
}

char predecessorK(Node *x) {
	if(x->leaf) {
		return x->key[x->n-1];
	} else {
		return predecessorK(x->c[x->n]);
	}
}

char soccessorK(Node *x) {
	if(x->leaf) {
		return x->key[0];
	} else {
		return soccessorK(x->c[0]);
	}
}

void mergeNodes(Node *y, char k, Node *z) {
	y->key[y->n] = k;
	for(int i=0; i<z->n; i++) {
		y->key[y->n+1+i] = z->key[i];
	}
	for(int i=0; i<z->n+1; i++) {
		y->key[y->n+1+i] = z->key[i];
	}
}

void removeKey(Node *x, char k) {
	int i = index(x, k);
	for (int j=i; j<x->n-1; j++) {
		x->key[j] = x->key[j+1];
	}
	if(!x->leaf) {
		for (int j=i+1; j<x->n; j++) {
			x->key[j] = x->key[j+1];
		}
	}

	x->n -= 1;
}

void btreeDeleteKey(Node *x, char k)
{
	
	if (x->leaf) {
		int i;
		for (i=0; i<x->n; i++) {
			if (k == x->key[i]) break;
		}
		for (int j=i; j<x->n-1; j++) {
			x->key[j] = x->key[j+1];
		}
		x->n -= 1;
		
	} else {
		if (keyIsInNode(x,k)) {
			int i = index(x,k);
			Node *y = x->c[i];
			if(y->n >= t) { 
				char k1 = predecessorK(y);
				btreeDeleteKey(y, k1);
				x->key[i] = k1;
			} else if(y->n < t) {
				Node *z = x->c[i+1];
				if(z->n >=t) { 
					char k1 = soccessorK(z);
					btreeDeleteKey(z, k1);
					x->key[i] = k1;
				} else { 
					mergeNodes(y,k,z);
					
					removeK(x,k);
					btreeDeleteKey(y,k);
				}
			}
		} else { 


		}
	}





}

void btreeDelete(BTree *T, char k)
{
    btreeDeleteKey(T->root, k);

}



void btreeDumpNodes(Node *x)
{
	if (x->leaf) {
		for (int i=0; i<x->n; i++) {
			std::cout<<x->key[i];
		}
	} else {
		for (int i=0; i<x->n; i++) {
			std::cout<<"[";
			btreeDumpNodes(x->c[i]);
			std::cout<<"]";
			std::cout<<x->key[i];
		}
		std::cout<<"[";
		btreeDumpNodes(x->c[x->n]);
		std::cout<<"]";
	}
}

void btreeDump(BTree *T)
{
	btreeDumpNodes(T->root);
	std::cout<<std::endl;
}

BTree gT;
BTree *T = &gT;
int main()
{
	btreeCreate(T);
	btreeInsert(T, 'H');
	btreeInsert(T, 'F');
	btreeInsert(T, 'G');
	btreeInsert(T, 'E');
	btreeInsert(T, 'P');
	btreeInsert(T, 'C');
	btreeInsert(T, 'D');
	btreeInsert(T, 'P');

	btreeDump(T);

}
