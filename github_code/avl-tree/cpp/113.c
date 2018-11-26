#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>    // std::max
#include <string>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::endl;
using std::max;
using std::vector;
using std::string;


class node{
public:
	int value;
	node* left;
	node* right;
	node* parent;
	node(){
		left = right = parent = NULL;
	}
	node(int val){
		value = val;
		left = right = parent = NULL;
	}
};

class AVLTree{
private:
	node*   root;
	void    rprint(node* root);
	void    radd(node* r, node* n);
	node*   uncle(node *n);
	node*   grandpa(node* n);
	// int     count_seeds(node* r);
static	int     count_depth(node* r);

	void    lleft_rotate(node *n);
	void    gleft_rotate(node *n);
	void    lright_rotate(node *n);
	void    gright_rotate(node *n);
	void	balance(node *n);
public:
	AVLTree();
	int     get_depth();
	void    print();
	void    add(int val);
	void    remove(int val);
};

AVLTree::AVLTree(){
	root = NULL;
}


int AVLTree::count_depth(node *r){
	if (r == NULL)
		return 0;
	return 1 + max(count_depth(r->left), count_depth(r->right));
}

int AVLTree::get_depth(){
	return count_depth(root);
}

int pow(int base, int power){
	int res = 1;
	for (int i = 0; i < power; i++)
		res *= base;
	return res;
}

void print_slice(int shift, vector<node*> v){
	bool odd = true;
	if (v.size() > 1){
		for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++) cout << " ";
		for (size_t j = 1; j <= v.size(); j++){
			cout << (odd ? "  /-" : "--\\ ");
			if (j != v.size())
				for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++) cout << (odd ? "--" : "  ");
			odd = !odd;
		}
		cout << endl;
	}

	for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++) cout << " ";
	//cout << " ";
	for (auto n : v){
		if (n)
			cout << " " << setfill('0') << setw(2) << n->value << " ";
		else
			cout << " ** ";
		for (int i = 0; i < pow(2, shift - 1) * 2 - 2; i++) cout << "  ";
	}
	cout << endl;
}
void AVLTree::print(){
	vector<node*> v;
	int depth = get_depth();
	v.push_back(root);      // Инициализиуем наше очередь
	print_slice(depth, v);
	for (int i = 1; i < depth; i++){
		vector<node*> v_tmp;
		for (auto n : v){
			if (n != NULL){
				v_tmp.push_back(n->left);
				v_tmp.push_back(n->right);
			}
			else{
				v_tmp.push_back(NULL), v_tmp.push_back(NULL);
			}
		}
		v = v_tmp;
		print_slice(depth - i, v);
	}
}

node* AVLTree::grandpa(node *n){
	if (n->parent)
		return n->parent->parent;
	else
		return NULL;
}

node* AVLTree::uncle(node *n){
	if (n->parent && n->parent->parent)
		return (n->parent == n->parent->parent->left) ? n->parent->parent->right : n->parent->parent->left;
	else
		return NULL;
}


// AVL дерево, малое левое вращение, node - a	
void AVLTree::lleft_rotate(node *a){
	// http://upload.wikimedia.org/wikipedia/ru/b/bc/AVL_LR.GIF
	node * parent = a->parent;

	node * b = a->right;
	node * c = b->left;

	if (parent && parent->left == a)
		parent->left = b;
	if (parent && parent->left == a)
		parent->right = b;

	if (a == root)
		root = b;

	a->right = c; if (c) c->parent = a;
	if (b) b->parent = parent;
	a->parent = b;
	b->left = a;
}

// AVL дерево, большое левое вращение, node - a	
void AVLTree::gleft_rotate(node *a){
	// http://upload.wikimedia.org/wikipedia/ru/1/16/AVL_BR.GIF
	node * parent = a->parent;

	node * b = a->right;
	node * c = b->left;
	node * m = c->left;
	node * n = c->right;

	if (parent && parent->left == a)
		parent->left = c;
	if (parent && parent->left != a)
		parent->right = c;

	if (a == root)
		root = c;

	c->parent = parent;
	c->left = a; a->parent = c;
	c->right = b; b->parent = c;

	a->right = m;
	if (m) {
		m->parent = a;
	}
	b->left = n;
	if (n) {
		n->parent = b;
	}
}

void AVLTree::lright_rotate(node *a){
	// http://upload.wikimedia.org/wikipedia/ru/e/e8/AVL_LL.GIF
	node * parent = a->parent;

	node * b = a->left;
	node * c = b->right;

	if (parent && parent->left == a)
		parent->left = b;
	if (parent && parent->left != a)
		parent->right = b;
	if (a == root)
		root = b;

	a->left = c; if (c) c->parent = a;
	if (b) b->parent = parent;
	a->parent = b;
	b->right = a;
}

// AVL дерево, большое правое вращение, node - a	
void AVLTree::gright_rotate(node *a){
	// http://upload.wikimedia.org/wikipedia/ru/7/74/AVL_BL.GIF
	node * parent = a->parent;

	node * b = a->right;
	node * c = b->left;
	node * m = c->left;
	node * n = c->right;

	if (parent && parent->left == a)
		parent->left = c;
	if (parent && parent->left == a)
		parent->right = c;

	if (a == root)
		root = c;

	c->parent = parent;
	c->left = b; b->parent = c;
	c->right = a; a->parent = c;

	a->left = n;
	if (n) {
		n->parent = a;
	}
	b->right = m;
	if (m) {
		m->parent = b;
	}
}

void AVLTree::balance(node *n) {
	int depth_left = count_depth(n->left);
	int depth_right = count_depth(n->right);

	if (depth_right - depth_left == 2) {
		if (count_depth(n->right->left) <= count_depth(n->right->right)) {
			cout << "little left rotate" << endl;
			return lleft_rotate(n);
		}
		if (count_depth(n->right->left) > count_depth(n->right->right)) {
			cout << "great left rotate" << endl;
			return gleft_rotate(n);
		}
	}
	else if (depth_left - depth_right == 2) {
		if (count_depth(n->left->right) <= count_depth(n->left->left)) {
			cout << "little right rotate" << endl;
			return lright_rotate(n);
		}
		if (count_depth(n->left->right) > count_depth(n->left->left)) {
			cout << "great right rotate" << endl;
		 	return gright_rotate(n);
		}
	}
	else if (abs(depth_left - depth_right) < 2) {
		if (n->parent){
			balance(n->parent);
		}
	}
}

// r = root, n = элемент, который добавляем
void AVLTree::radd(node* r, node *n){
	if (n->value < r->value){
		if (r->left == NULL){
			r->left = n;
			n->parent = r;
		}
		else{
			return radd(r->left, n);
		}
	}
	else{
		if (r->right == NULL){
			r->right = n;
			n->parent = r;
		}
		else{
			return radd(r->right, n);
		}
	}
}

void AVLTree::add(int val){
	node * n = new node(val);
	if (root == NULL){
		root = n;
	}
	else{
		radd(root, n);
	}
	balance(n);
}

int main(){
	AVLTree rbt;
	vector<int> values = { 10, 5, 2, 1, 3, 7, 15, 25, 30 };
	for (auto v : values) {
		rbt.add(v);
	}

	values = { 45, 36, 67, 90, 04, 23, 52, 11 };

	for (auto v : values){
		rbt.add(v);
		rbt.print();
		cin.ignore(1);
	}
	return 0;
}