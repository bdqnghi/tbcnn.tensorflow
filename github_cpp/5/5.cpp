#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <string>

struct CNode // структура для представления узлов дерева
{
	int key;
	int height;
	int count;
	CNode* left;
	CNode* right;
	CNode() : left(nullptr), right(nullptr), height(0), key(0) {}
};

class avlTree {
public:
	~avlTree();
	avlTree() : root(nullptr) {};
	int height(CNode* p);
	int count(CNode* p);
	int bfactor(CNode* p);
	void fixheight(CNode* p);
	void fixcount(CNode* p);
	bool add(int k);
	bool deletekey(int k);
	void Show();
	void printAsTree(CNode* node, int currentLevel);
	int findplace(CNode* p, int k);
	CNode* rotateright(CNode* p);
	CNode* rotateleft(CNode* q);
	CNode* balance(CNode* p);
	CNode* insert(CNode* p, int k);
	std::pair<CNode*, CNode*> removemin(CNode* p);
	CNode* remove(CNode* p, int k);
	CNode* getroot();
	int findstat(CNode* current, int y);
	void DestroyTree(CNode* node);
private:
	CNode* root;
};

avlTree::~avlTree() {
	DestroyTree(root);
}

void avlTree::DestroyTree(CNode* node) {
	if (node == nullptr) {
		return;
	}
	DestroyTree(node->left);
	node->left = nullptr;
	DestroyTree(node->right);
	node->right = nullptr;
	delete node;
}

CNode* avlTree::getroot() {
	return root;
}

int avlTree::height(CNode* p)
{
	return p ? p->height : 0;
}

int avlTree::count(CNode* p)
{
	return p ? p->count : 0;
}

int avlTree::bfactor(CNode* p) //разность высот
{
	return height(p->right) - height(p->left);
}

void avlTree::fixheight(CNode* p) // восстановление  height
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

void avlTree::fixcount(CNode* p) //восстановление count 
{
	int hl = count(p->left);
	int hr = count(p->right);
	p->count = hl + hr + 1;
}

CNode* avlTree::rotateright(CNode* p) // правый поворот вокруг p
{
	CNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	fixcount(p);
	fixcount(q);
	return q;
}

CNode* avlTree::rotateleft(CNode* q) // левый поворот вокруг q
{
	CNode* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	fixcount(q);
	fixcount(p);
	return p;
}

CNode* avlTree::balance(CNode* p) // балансировка узла p
{
	fixheight(p);
	fixcount(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

bool avlTree::add(int k) { //добавление ключа в дерево
	root = insert(root, k);
	return true;
}

int avlTree::findplace(CNode* p, int k) // нахождение номера элемента по ключу
{
	if (p == nullptr) {
		return 0;
	}
	if (k > p->key)
		return findplace(p->right, k);
	else
		return findplace(p->left, k) + count(p->right) + 1;
}
		
CNode* avlTree::insert(CNode* p, int k) // вставка ключа k в дерево с корнем p
{
	if (p == nullptr) {
		CNode* newNode = new CNode();
		newNode->key = k;
		newNode->height = 1;
		newNode->count = 1;
		return newNode;
	}
	if (k < p->key) {
		p->left = insert(p->left, k);
	}
	else {
		p->right = insert(p->right, k);
	}
	return balance(p);
}

std::pair<CNode*, CNode*> avlTree::removemin(CNode* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return std::make_pair(p->right, p);
	std::pair<CNode*, CNode*> answer = removemin(p->left);
	p->left = answer.first;
	return std::make_pair(balance(p), answer.second);
}

bool avlTree::deletekey(int k) {
	root = remove(root, k);
	return true;
}

CNode* avlTree::remove(CNode* p, int k) // удаление ключа k из дерева p
{
	if (p == nullptr) return nullptr;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else 
	{
		CNode* q = p->left;
		CNode* r = p->right;
		delete p;
		if (!r) return q;
		std::pair<CNode*, CNode*> subtree = removemin(r);
		CNode* min = subtree.second;
		min->left = q;
		min->right = subtree.first;
		return balance(min);
	}
	return balance(p);
}

int avlTree::findstat(CNode* current, int y) {
	if (count(current->right) == y) {
		return current->key;
	} else if (count(current->right) < y) {
		return findstat(current->left, y - count(current->right) - 1);
	} else if (count(current->right) > y) {
		return findstat(current->right, y);
	}
}

void avlTree::Show() {
	printAsTree(root, 0);
}

void avlTree::printAsTree(CNode* node, int currentLevel) { // Делает обход дерева слева-направо и печатает в консоль дерево, положенное на бок.
	if (node == 0) {
		return;
	}
	printAsTree(node->left, currentLevel + 1);
	std::cout << std::string(currentLevel, '\t') << "(" << node->key << ' ' << node->height << ' ' << node->count << ")" << std::endl;
	printAsTree(node->right, currentLevel + 1);
}

int main() {
	
	avlTree tree;
	int n, k, m;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> k >> m;
		if (k == 1) {
			tree.add(m);
			std::cout << tree.findplace(tree.getroot(), m) - 1 << ' ' ;
		}
		if (k == 2) {
			tree.deletekey(tree.findstat(tree.getroot(), m));
		}
	}
	return 0;
}
