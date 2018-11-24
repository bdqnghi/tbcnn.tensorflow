/*
 * C++ Splay Tree implementation
 * Written by orestisp
 * std06176@di.uoa.gr
 */



#include <iostream>


template <class T>
class SP {
	private:
		struct node {
			T data;
			node *left;
			node *right;
			node(const T& d, node* l = 0, node* r = 0):
				data(d), left(l), right(r) {}
		};
		node *root;
		node *tnode;
		const T* tdata;
		unsigned int size_var;
		void SP_clear(node*);
		inline void SP_R_rotate(node*&);
		inline void SP_L_rotate(node*&);
		inline void SP_splay(node*&);
		void SP_copy(node*&, node*);
		void SP_print(node*) const;
	public:
		SP(void);
		SP(const SP&);
		~SP(void);
		bool empty(void) const;
		unsigned int size(void) const;
		SP<T>& clear(void);
		bool find(const T&);
		SP<T>& insert(const T&);
		SP<T>& extract(const T&);
		void print(void) const;
};


template <class T>
void SP<T>::SP_clear(node* p) {
	if (p->left) SP_clear(p->left);
	if (p->right) SP_clear(p->right);
	delete p;
}


template <class T>
inline void SP<T>::SP_R_rotate(node*& p) {
	node *t = p;
	p = t->left;
	t->left = p->right;
	p->right = t;
}


template <class T>
inline void SP<T>::SP_L_rotate(node*& p) {
	node *t = p;
	p = t->right;
	t->right = p->left;
	p->left = t;
}


template <class T>
inline void SP<T>::SP_splay(node*& p) {
	node *l = tnode, *r = tnode;
	tnode->left = 0;
	tnode->right = 0;
	for (;;)
		if (*tdata < p->data) {
			if (p->left && *tdata < p->left->data)
				SP_R_rotate(p);
			if (!p->left) break;
			r->left = p;
			r = p;
			p = p->left;
		} else if (!(*tdata == p->data)) {
			if (p->right && !(*tdata < p->right->data) &&
			    !(*tdata == p->right->data))
				SP_L_rotate(p);
			if (!p->right) break;
			l->right = p;
			l = p;
			p = p->right;
		} else break;
	l->right = p->left;
	r->left = p->right;
	p->left = tnode->right;
	p->right = tnode->left;
}


template <class T>
void SP<T>::SP_copy(node*& p, node* rp) {
	p = new node(rp->data);
	if (rp->left) SP_copy(p->left, rp->left);
	if (rp->right) SP_copy(p->right, rp->right);
}


template <class T>
void SP<T>::SP_print(node* p) const {
	if (p->left) SP_print(p->left);
	std::cout << p->data << ' ';
	if (p->right) SP_print(p->right);
}


template <class T>
SP<T>::SP(void):
	root(0), tnode(0), size_var(0) {}


template <class T>
SP<T>::SP(const SP& param):
	root(0), tnode(0), size_var(param.size_var) {
	if (param.root) {
		try {
			if (param.tnode)
				tnode = new node(param.tnode->data);
			SP_copy(root, param.root);
		} catch (...) {
			if (tnode) delete tnode;
			clear();
			throw;
		}
	}
}


template <class T>
SP<T>::~SP(void) {
	if (tnode) delete tnode;
	clear();
}


template <class T>
bool SP<T>::empty(void) const {
	return size_var == 0;
}


template <class T>
unsigned int SP<T>::size(void) const {
	return size_var;
}


template <class T>
SP<T>& SP<T>::clear(void) {
	if (root) SP_clear(root);
	root = 0;
	size_var = 0;
	return *this;
}


template <class T>
bool SP<T>::find(const T& d) {
	if (!root) return false;
	tdata = &d;
	SP_splay(root);
	return d == root->data;
}


template <class T>
SP<T>& SP<T>::insert(const T& d) {
	node *t;
	if (!root) {
		if (!tnode) tnode = new node(d);
		root = new node(d);
		size_var++;
		return *this;
	}
	tdata = &d;
	SP_splay(root);
	if (d < root->data) {
		t = new node(d, root->left, root);
		root->left = 0;
		root = t;
		size_var++;
	} else if (!(d == root->data)) {
		t = new node(d, root, root->right);
		root->right = 0;
		root = t;
		size_var++;
	}
	return *this;
}


template <class T>
SP<T>& SP<T>::extract(const T& d) {
	node *t;
	if (!root) return *this;
	tdata = &d;
	SP_splay(root);
	if (!(d == root->data)) return *this;
	if (!root->left)
		t = root->right;
	else {
		t = root->left;
		SP_splay(t);
		t->right = root->right;
	}
	delete root;
	root = t;
	size_var--;
	return *this;
}


template <class T>
void SP<T>::print(void) const {
	if (root) SP_print(root);
	std::cout << std::endl;
}



/* Testing main */

#include <cstdlib>
#include <ctime>
using namespace std;


int main(int argc, char **argv)
{
	int i, j, n;
	double t;
	SP<int> tree;
	if (argc > 3) return EXIT_FAILURE;
	i = time(0);
	if (argc == 1) n = 20;
	else {
		n = atoi(argv[1]);
		if (argc == 3) i = atoi(argv[2]);
	}
	srand((unsigned int)i);
	cout << "Size is " << n << endl;
	cout << "Seed is " << i << endl;
	cout << "Inserting..." << endl;
	t = ((double)clock())/CLOCKS_PER_SEC;
	for (i = 1 ; i <= n ; i++) {
		j = rand()%n+1;
	//	cout << j << ' ';
		tree.insert(j);
	}
	t = ((double)clock())/CLOCKS_PER_SEC-t;
	cout << t << " secs" << endl;
//	cout << "\nPrinting tree..." << endl;
//	tree.print();
	cout << "Size of tree is: " << tree.size() << endl;
	cout << "Extracting..." << endl;
	t = ((double)clock())/CLOCKS_PER_SEC;
	for (i = 1 ; i <= n ; i++) {
		j = rand()%n+1;
	//	cout << j << ' ';
		tree.extract(j);
	}
	t = ((double)clock())/CLOCKS_PER_SEC-t;
	cout << t << " secs" << endl;
//	cout << "\nPrinting tree..." << endl;
//	tree.print();
	cout << "Size of tree is: " << tree.size() << endl;
	cout << "Clearing..." << endl;
	t = ((double)clock())/CLOCKS_PER_SEC;
	tree.clear();
	t = ((double)clock())/CLOCKS_PER_SEC-t;
	cout << t << " secs" << endl;
	return EXIT_SUCCESS;
}
