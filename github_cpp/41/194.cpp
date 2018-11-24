#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>

using namespace std;

struct node {
	node* parent;
	node* left = NULL;
	node* right = NULL;
	int value;
	char color;
};

void insert(node*&);
void remove(node*&);
void read(node* &);
void search(node*);
void addnode(node* &, node*&, int);
void removenode(node*&, int);
void print(node*);
bool find(node*, int);
node* grandparent(node*);
node* uncle(node*);
void ione(node*&, node*&);
void itwo(node*&, node*&);
void ithree(node*&, node*&);
void ifour(node*&, node*&);
void ifive(node*&, node*&);
void rone(node*&, node*&);
void rtwo(node*&, node*&);
void rthree(node*&, node*&);
void rfour(node*&, node*&);
void rfive(node*&, node*&);
void rsix(node*&, node*&);
node* sibling(node*);
node* findnode(node*, int);
node* deleten(node*&);
node* delete_unattached(node*&);
node* next_largest(node*&);

int main() {
	node* head = NULL;
	int r = 0;
	while (r == 0){
		cout << " 1. Add a node";
		cout << "\n 2. Delete a node";
		cout << "\n 3. Read a file of numbers";
		cout << "\n 4. Print the tree";
		cout << "\n 5. Search the tree";
		cout << "\n 6. Quit the program\n";
		int i;
		while (!(cin >> i)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a number\n";
		}
		switch(i) {
			case 1 : insert(head);
				break;
			case 2 : remove(head);
				break;
			case 3 : read(head);
				break;
			case 4 : print(head);
				break;
			case 5 : search(head);
				break;
			case 6 : r = 1;
				break;
			default : cout << "Please enter a valid number\n";
				break;
		}
	}
}

void insert(node* &root) {
	cout << "Number to be added?\n";
	int i;
	while (!(cin>>i)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a valid number\n";
	}
	addnode(root, root, i);
}
void remove(node* &root) {
	cout << "Number to be removed?\n";
	int i;
	while (!(cin>>i)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a valid number\n";
	}
	removenode(root, i);
}
void read(node* &n) {
	char* filename = new char[100];
	cout << "What is the file name for which you would like to read in?" << endl;
	cout << "File content requirements: must have all numbers, only seperated by spaces" << endl;
	cin >> filename;
	cin.ignore(1000, '\n');	
	strcat(filename, ".txt");
	ifstream file;
	file.open(filename);
	int num[50];
	int index = 0;
	while (!file.eof()) {
		file >> num[index];
		addnode(n, n, num[index]);
		index++;
	}
	file.close();
}
void print(node* root) {
    if (root == NULL) {
        return;
    }
    else {
		cout << endl;
		queue<node*> currentLevel;
		queue<node*> nextLevel;
		currentLevel.push(root);
		while (!currentLevel.empty()) {
			node* currNode = currentLevel.front();
			currentLevel.pop();
			if (currNode) {
				cout << currNode->value;
				cout << currNode->color;
				if (currNode->parent != NULL) {
					cout << '(' << currNode->parent->value << ") ";
				}
				nextLevel.push(currNode->left);
				nextLevel.push(currNode->right);
			}
			if (currentLevel.empty()) {
				cout << endl;
				swap(currentLevel, nextLevel);
			}
		}
	}
}
void search(node* root) {
	cout << "Number to be searched?\n";
	int i;
	while (!(cin>>i)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Enter a valid number\n";
	}
	bool r = find(root, i);
	if (r == true) cout << "Node is in the tree\n";
	else cout << "Node is not in the tree\n";
}
void addnode(node* &root, node* &n, int num) {
	node* trail;
	node* carry = n;
	if (root == NULL) {
		root = new node;
		root->value = num;
		root->color = 'b';
		ione(root, n);
		return;
	}
	else if (carry->value > num && carry->left == NULL) {
		node* temp = new node;
		carry->left = temp;
		temp->value = num;
		temp->color = 'r';
		temp->parent = carry;
		if (carry->color == 'r') {
			temp->color = 'b';
		}
		ione(root, temp);
	}
	else if (carry->value < num && carry->right == NULL) {
		node* temp = new node;
		carry->right = temp;
		temp->value = num;
		temp->color = 'r';
		temp->parent = carry;
		if (carry->color == 'r') {
			temp->color = 'b';
		}
		ione(root, temp);
	}
	else if (carry->value > num && carry->left != NULL) {
		carry = carry->left;
		addnode(root, carry, num);
	}
	else if (carry->value < num && carry->right != NULL) {
		carry = carry->right;
		addnode(root, carry, num);
	}
	else if (carry->value == num && carry->right == NULL) {
		node* temp = new node;
		carry->right = temp;
		temp->value = num;
		temp->color = 'r';
		temp->parent = carry;
		if (carry->color == 'r') {
			temp->color = 'b';
		}
		ione(root, temp);
	}
	else {
		carry = carry->right;
		addnode(root, carry, num);
	}
}
void removenode(node* &root, int v) {
	node* n = findnode(root, v);
	if (n == NULL) {
		cout << "Sorry that number is not in the tree\n";
		return;
	}
	if (root->value == v) {
		node* r;
		if (root->right == NULL && root->left == NULL) {
			root = NULL;
			r = NULL;
		}
		else {
			if (root->left == NULL && root->right != NULL) {
				node* savedr = root->right->right;
				root->value = root->right->value;
				root->right = savedr;
				savedr->parent = root;
				r = root->right;
			}
			else {
				node* next = root->left;
				node* trail;
				if (next->right == NULL) {
					int number = next->value;
					node* savedl = next->left; 
					root->value = number;
					root->left = savedl;
					savedl->parent = root;
					r = root->left;
				}
				else {
					while (next->right != NULL) {
						trail = next;
						next = next->right;
					}
					int number;
					number = next->value;
					root->value = number;
					if (next->left != NULL) {
						node* savedl = next->left;
						trail->right = savedl;
						savedl->parent = trail;
						r = trail->right;
					}
					else {
						trail->right = NULL;
						r = NULL;
					}
				}
			}
		}
		if (r == NULL) {
			return;
		}
		rone(root, r);
	}
	else {
		if (n->left == NULL && n->right == NULL) {
			if (n->parent->left == n) {
				n->parent->left = NULL;
			}
			else {
				n->parent->right = NULL;
			}
		}
		else if (n->left != NULL && n->right == NULL) {
			node* r = deleten(n);
			rone(root, r);
		}
		else if (n->right != NULL && n->left == NULL) {
			node* r = deleten(n);
			rone(root, r);
		}
		else {
			node* r = deleten(n);
			if (r == NULL) {
				return;
			}
			rone(root, r);
		}
	}
}
bool find(node* n, int v) {
	if (n == NULL) {
		return false;
	}
	node* trailling;
	node* travel = n;
	if (n->value == v) {
		return true;
	}
	while (travel != NULL) {
		if (travel->value != v && travel->value > v) {
			trailling = travel;
			travel = travel->left;
		}
		else if (travel->value != v && travel->value < v) {
			trailling = travel;
			travel = travel->right;
		}
		else {
			return true;
		}
	}
	return false;
}
void ione(node* &root, node* &n) {
	if (n->parent == NULL) n->color = 'b';
	else itwo(root, n);
}
void itwo(node* &root, node* &n) {
	if (n->parent->color == 'b') return;
	else ithree(root, n);
}
void ithree(node* &root, node* &n) {
	node* u = uncle(n);
	node* g = grandparent(n);
	if (n->parent->color == 'r' && u != NULL && u->color == 'r') {
		n->color = 'r';
		n->parent->color = 'b';
		u->color = 'b';
		g->color = 'r';
		ione(root, g);
	}
	else {
		ifour(root, n);
	}
}
void ifour(node* &root, node* &n) {
    if (n == n->parent->right && n->parent == grandparent(n)->left) {
		node* g = grandparent(n);
		if (g != NULL && g->value == root->value) {
			node* savedp = n->parent;
			node* savedl = n->left;
			root->left = n;
			n->left = savedp;
			savedp->parent = n;
			savedp->right = savedl;
			n->parent = root;
		}
		else {
			node* savedp = n->parent;
			node* savedl = n->left;
			g->left = n;
			n->left = savedp;
			savedp->parent = n;
			savedp->right = savedl;
			n->parent = g;
		}
        n = n->left;
	}
    else if (n == n->parent->left && n->parent == grandparent(n)->right) {
		node* g = grandparent(n);
		if (g != NULL && g->value == root->value) {
			node* savedp = n->parent;
			node* savedr = n->right;
			root->right = n;
			n->right = savedp;
			savedp->parent = n;
			savedp->left = savedr;
			n->parent = root;
		}
		else {
			node* savedp = n->parent;
			node* savedr = n->right;
			g->right = n;
			n->right = savedp;
			savedp->parent = n;
			savedp->left = savedr;
			n->parent = g;			
		}
        n = n->right;
    }
    ifive(root, n);
}
void ifive(node* &root, node* &n) {
	node* g = grandparent(n);
	n->color = 'r';
	n->parent->color = 'b';
	g->color = 'r';
	if (n == n->parent->left) {
		if (g != NULL && g->parent == NULL) {
			node* savedr = n->parent->right;
			root = n->parent;
			n->parent->parent = NULL;
			n->parent->right = g;
			g->parent = root;
			g->left = savedr;
		}
		else {
			node* savedr = n->parent->right;
			g->parent->right = n->parent;
			n->parent->parent = g->parent;
			n->parent->right = g;
			g->parent = n->parent;
			g->left = savedr;
		}
	}
	else {
		if (g != NULL && g->parent == NULL) {
			node* savedl = n->parent->left;
			root = n->parent;
			n->parent->parent = NULL;
			n->parent->left = g;
			g->parent = root;
			g->right = savedl;
		}
		else {
			node* savedl = n->parent->left;
			g->parent->right = n->parent;
			n->parent->parent = g->parent;
			n->parent->left = g;
			g->parent = n->parent;
			g->right = savedl;			
		}
	}
}
node* grandparent(node* n) {
	if (n != NULL && n->parent != NULL) {
		return n->parent->parent;
	}
	else return NULL;
}
node* uncle(node* n) {
	node* g = grandparent(n);
	if (g == NULL) return NULL;
	else if (n->parent == g->right) return g->left;
	else return g->right;
}
node* sibling(node* n) {
	if (n == NULL) {
		return NULL;
	}
	else {
		if (n->parent == NULL) {
			return NULL;
		}
		else {
			if (n->parent->right == n) {
				return n->parent->left;
			}
			else {
				return n->parent->right;
			}
		}
	}
}

node* findnode(node* n, int i) {
	if (n == NULL) {
		return NULL;
	}
	node* trailling;
	node* travel = n;
	if (n->value == i) {
		return travel;
	}
	while (travel != NULL) {
		if (travel->value != i && travel->value > i) {
			trailling = travel;
			travel = travel->left;
		}
		else if (travel->value != i && travel->value < i) {
			trailling = travel;
			travel = travel->right;
		}
		else {
			return travel;
		}
	}
	return NULL;
}

void rone(node* &root, node* &n) {

}
void rtwo(node* &root, node* &n) {

}
void rthree(node* &root, node* &n) {
	
}
void rfour(node* &root, node* &n) {
	
}
void rfive(node* &root, node* &n) {
	
}
void rsix(node* &root, node* &n) {
	
}
node* deleten(node*& n) {
	if (n->right != NULL && n->left == NULL) {
		node* savedr = n->right;
		node* savedp = n->parent;
		savedp->right = savedr;
		savedr->parent = savedp;
		return savedp->right;
	}
	else if (n->left != NULL && n->right == NULL) {
		node* savedl = n->left;
		node* savedp = n->parent;
		savedp->left = savedl;
		savedl->parent = savedp;
		return savedp->left;
	}
	else {
		node* next = next_largest(n->left);
		n->value = next->value;
		if (next->parent == n) {
			node* savedl = next->left;
			n->left = next->left;
			savedl->parent = n;
			return n->left;
		}
		else {
			if (next->left == NULL) {
				next->parent->right = NULL;
				return NULL;
			}
			else {
				node* savedl = next->left;
				node* savedp = next->parent;
				next->parent->right = savedl;
				savedl->parent = savedp;
				return savedp->right;
			}
		}
	}
}
node* next_largest(node*& n) {
	node* travel = n;
	if (travel->right == NULL) {
		return travel;
	}
	else {
		while (travel->right != NULL) {
			travel = travel->right;
		}
		return travel;
	}
}