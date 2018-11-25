#include <bits/stdc++.h>
using namespace std;
template <class T>
class avltree {
	struct node {
		T key;
		int height;
		node *left, *right;
		node(T val) {
			key = val;
			height = 1;
			left = right = nullptr;
		}
	};
	node *root;
	int sz;
	int getheight(node *tree) {
		return (tree == nullptr) ? 0 : tree->height;
	}
	int getbalance(node *tree) {
		if (tree == nullptr) return 0;
		return getheight(tree->left) - getheight(tree->right);
	}
	void upd(node *tree) {
		if (tree == nullptr) return;
		tree->height = 1 + max(getheight(tree->left), getheight(tree->right));
	}
	node* rotateleft(node* tree) {
		node* ans = tree->right;
		tree->right = ans->left;
		ans->left = tree;
		upd(tree);
		upd(ans);
		return ans;
	}
	node* rotateright(node* tree) {
		node* ans = tree->left;
		tree->left = ans->right;
		ans->right = tree;
		upd(tree);
		upd(ans);
		return ans;
	}
	node* bigrotateleft(node* tree) {
		tree->right = rotateright(tree->right);
		return rotateleft(tree);
	}
	node* bigrotateright(node* tree) {
		tree->left = rotateleft(tree->left);
		return rotateright(tree);
	}
	node* balancing(node* tree) {
		upd(tree);
		if (abs(getbalance(tree)) < 2) return tree;
		if (getbalance(tree) == -2) {
			if (getbalance(tree->right) == 1) return bigrotateleft(tree);
			return rotateleft(tree);
		}
		else {
			if (getbalance(tree->left) == -1) return bigrotateright(tree);
			return rotateright(tree);
		}
	}
	node* _insert(node* tree, T key) {
		if (tree == nullptr) return new node(key);
		if (key < tree->key) tree->left = _insert(tree->left, key);
		else tree->right = _insert(tree->right, key);
		return balancing(tree);
	}
	bool _find(node* tree, T key) {
		if (tree == nullptr) return 0;
		if (tree->key == key) return 1;
		return (key < tree->key) ? _find(tree->left, key) : _find(tree->right, key);
	}
	node* getmin(node* tree) {
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr) return tree;
		return getmin(tree->left);
	}
	node* getmax(node* tree) {
		if (tree->right == nullptr) return tree;
		return getmax(tree->right);
	}
	node* erasemin(node* tree) {
		if (tree == nullptr) return nullptr;
		if (tree->left == nullptr) return tree->right;
		tree->left = erasemin(tree->left);
		return balancing(tree);
	}
	node* _erase(node* tree, T key) {
		if (key < tree->key) tree->left = _erase(tree->left, key);
		if (key > tree->key) tree->right = _erase(tree->right, key);
		if (tree->key == key) {
			if (tree->right == nullptr) return tree->left;
			else {
				node* left = tree->left;
				node* right = tree->right;
				delete tree;
				node* minn = getmin(right);
				minn->right = erasemin(right);
				minn->left = left;
				return balancing(minn);
			}
		}
		return balancing(tree);
	}
	void _print(node* tree) {
		if (tree == nullptr) return;
		_print(tree->left);
		cout << tree->key << " ";
		_print(tree->right);
	}
	void _clear(node* tree) {
		if (tree->left != nullptr) _clear(tree->left);
		if (tree->right != nullptr) _clear(tree->right);
		delete tree;
	}
	void _upper_bound(node* tree, T key, T &ans) {
		if (tree == nullptr) return;
		if (key < tree->key) {
			ans = min(ans, tree->key);
			_upper_bound(tree->left, key, ans);
		}
		else _upper_bound(tree->right, key, ans);
	}
public:
	avltree() {
		root = nullptr;
		sz = 0;
	}
	~avltree() {
		clear();
	}
	void insert(T key) {
		root = _insert(root, key);
		sz++;
	}
	int size() {
		return sz;
	}
	bool empty() {
		return sz == 0;
	}
	bool find(T key) {
		return _find(root, key);
	}
	bool erase(T key) {
		if (!find(key)) return 0;
		root = _erase(root, key);
		sz--;
		return 1;
	}
	void clear() {
		_clear(root);
		root = nullptr;
		sz = 0;
	}
	void print() {
		_print(root);
	}
	T upper_bound(T key) {
		if (root == nullptr) return key - 1;
		T ans = getmax(root)->key;
		if (ans <= key) return key - 1;
		_upper_bound(root, key, ans);
		return ans;
	}
	T lower_bound(T key) {
		if (find(key)) return key;
		return upper_bound(key);
	}
};
int main() {
	avltree<int> avl;
	for (int i = 0; i < 10; i++) avl.insert(i + 1);
	avl.print(); cout << endl;
	avl.erase(1); avl.erase(5);
	avl.print(); cout << endl;
	cout << avl.size() << " " << avl.empty() << endl;
	avl.erase(3);
	avl.print(); cout << endl;
	cout << "upper_bound 5 : " << avl.upper_bound(5) << endl;
	cout << "upper_bound 1 : " << avl.upper_bound(1) << endl;
	cout << "upper_bound 2 : " << avl.upper_bound(2) << endl;
	cout << "lower_bound 2 : " << avl.lower_bound(2) << endl;
	cout << "lower_bound 3 : " << avl.lower_bound(3) << endl;
	avl.clear();
	const int N = 30;
	int a[N];
	for (int i = 0; i < N; i++) a[i] = rand() % 10;
	random_shuffle(a, a + N);
	cout << "sort:" << endl;
	for (int i = 0; i < N; i++) {
		cout << a[i] << " ";
		avl.insert(a[i]);
	}
	cout << endl;
	avl.print();
}
