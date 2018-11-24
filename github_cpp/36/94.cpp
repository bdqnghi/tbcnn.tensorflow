/*
 * B-tree implementation with classes
 *
 * TODO: test
 */

#include <string>
#include <vector>

class Index {
	int value;
	string key;
public:
	Index(string key, int value) : key(key), value(value) {}
	string getKey() {
		return this->key;
	}
	int getValue() {
		return this->value;
	}
	bool operator > (Index param) {
		return (key.compare(cmp.key)>0);
	}
	bool operator = (Index param) {
		return (key.compare(cmp.key)==0);
	}
};

/* A node contains up to 2*K indices and 2*K+1 pointers */
class B-node {
	enum { L, R, K=5; }
	vector<Index> indices;
	vector<B-node*> children;
	B-node *parent;
	/* Index in parent->children */
	int pos;
public:
	B-node(Index first) : indices[0](first) {}
	B-node(Index first, B-node *child, B-node *parent) : indices[0](first), children[0](child), parent(parent) {}
	B-node(vector<Index> partIndices, int startInd, int endInd, vector<B-node*> partChildren, int startChd, int endChd) {
		int i=0;
		while(startInd<=endInd)
			this->indices[i++] = partIndices[startInd++];
		i=0;
		while(startChd<=endChd)
			this->children[i++] = partChildren[startChd++];
	}
	void addIndex(Index i) {
		int size = this->indices.size();
		int pos = findPos(i, 0, size);
		vector<Index>::iterator start = indices.begin();
		this->indices.insert(start+pos+1, i);
		size++;
		if(size==2*K+1) {
			B-node newNode = new B-node(this->indices, size/2+1, size, this->children, this->children.size()/2+1, this->children.size());
			startInd = indices.begin();
			vector<B-node*>::iterator startChd = children.begin();
			this->indices.erase(startInd, startInd+size/2+1);
			this->children.erase(startChd, startChd+this->children.size()/2+1);
			if(this->parent) {
				newNode->parent = this->parent;
				this->parent.addChild(&newNode);
				*this->parent.addIndex(this->indices[size/2]);
			} else {
				B-node newRoot = new B-node(this->indices[this->indices.size()/2]);
				newNode->parent = &newRoot;
				this->parent = &newRoot;
				newRoot.addChild(this);
				newRoot.addChild(newNode);
			}
		}
	}
	void addChild(B-node *child) {
		this->children.push_back(child);
	}
	void removeIndex(Index i) {
		int size = this->indices.size();
		int pos = findPos(i, 0, size);
		vector<Index>::iterator startInd = this->indices.start();
		this->indices.erase(startInd+pos);
		if(this->indices.size()==K-1) {
			B-node* left = this->getLeft();
			if(left->indices.size()==K) {
				this->merge(left, L);
				return;
			}
			B-node* right = this->getRight();
			if(right->indices.size()==K) {
				this->merge(right, R);
				return;
			}
			if(right->indices.size()>left->indices.size()) {
				this->merge(right, R);
				this->split();
			} else {
				this->merge(left, L);
				this->split();
			}
		}
	}
private:
	int findPos(Index i, int start, int end) {
		if(end-start<=0)
			return start;
		int half = (start+end)/2;
		if(indices[half]>i)
			return findPos(i, start, half);
		else if(i>indices[half])
			return findPos(i, half+1, end);
		else
			return half;
	}
	/* Returns the node on the left, if there is one */
	B-node* getLeft(B-node* cur) {
		if(!cur->parent || !cur->pos)
			return NULL;
		return cur->parent->children[cur->pos-1];
	}
	B-node* getRight(B-node* cur) {
		if(!cur->parent || cur->pos==2*K+1)
			return NULL;
		return cur->parent->children[cur->pos+1];
	}
	/* Merge left or right sibling into current node */
	void merge(B-node* sibling, bool LR) {
		if(LR==L) {
			this->children.insert(this->children.begin(), sibling->children.begin(), sibling->children.end()+1);	
			this->indices.insert(this->indices.begin(), sibling->indices.begin(), sibling->indices.end()+1);
		} else {
			this->children.insert(this->children.end()+1, sibling->children.begin(), sibling->children.end()+1);	
			this->indices.insert(this->indices.end()+1, sibling->indices.begin(), sibling->indices.end()+1);
		}
		vector<B-node*>::iterator pChdStart = sibling->parent->children.begin(); 
		sibling->parent->children.remove(pChdStart + sibling->pos);
		delete(sibling);	
	}
	/* Split into itself and newSibling 
	 * newSibling will be positioned LR */
	void split(bool LR) {
		if(LR==L) {
			B-node* sibling = new B-node(this->indices, 0, this->indices.size()/2, this->children, 0, this->children.size()/2);
			this->children.erase(this->children.begin(), this->children.begin()+this->children.size()/2+1);
			this->indices.erase(this->indices.begin(), this->indices.begin()+this->indices.size()/2+1);
			this->parent->children.insert(this->pos, sibling);
		} else {
			B-node* sibling = new B-node(this->indices, this->indices.size()/2+1, this->indices.size(), this->children, this->children.size()/2+1, this->children.size());
			this->children.erase(this->children.begin()+this->children.size()/2+1, this->children.end());
			this->indices.erase(this->indices.begin()+this->indices.size()/2+1, this->children.end());
			this->parent->children.insert(this->pos+1, sibling);
		}
	}
};

class B-tree {
	B-node* root;
public:
	B-tree() {
		this->root = new B-node();
	}
	/* Also updates existing key */
	void add(Index i) {
		B-node* cur = findNode(this->root, i);
		pos->addIndex(i);
	}
	void remove(Index i) {
		B-node* cur = findNode(this->root, i);
		pos->removeIndex(i);
	}
	int search(string key) {
		/* -1 is returned if no key found */
		Index n = new Index(key, -1);
		int pos;
		B-node* cur = findNode(this->root, n);
		pos = cur->findPos(n, 0, cur->indices.size());
		return cur->indices[pos].getValue();
	}
private:
	/* Returns the node where Index i belongs to */ 
	B-node* findNode(B-node* cur, Index i) {
		/* Root with no elements */
		if(cur->indices.size()==0)
			return cur;
		/* Leaf node */
		if(cur->children.size()==0)
			return cur;
		vector<Index>::iterator it;
		for(it=cur->indices.start();it<cur->indices.end();it++)
			/* Keys in the B-tree cannot be equal */
			if(i>cur->indices[it])
				break;
		vector<B-node*>::iterator firstChd = cur->children.start();
		return findPos(cur->children[firstChd+it], i);
	}
};

class B-nodeTest {
	static void main() {
		char buffer[10];
		B-tree tree = new B-tree();
		for(int i=0;i<100;i++) {
			itoa(i*i*i, buffer, 16);
			tree.add(new Index(buffer, i));
		}
		itoa(57*57*57, buffer, 16);
		printf("The value associated with %s is %d.\n", buffer, tree.search(buffer)); 
		Index toRemove = new Index(buffer, 57);
		tree.remove(toRemove);
		int result = tree.search(toRemove);
		if(result==-1)
			printf("Delete proceeded successfully.\n");
	}
};
