//====================================
// Title:   Implementation of B-tree
// Author:  Cai Jieying
// Version: 2017/05/05_v1
//====================================
#include <iostream>
#include <deque>
#define T 2

typedef struct BTnode{
	int keyNum;         /* number of keys */
	int* keyValue;      /* array storing the keys */
	BTnode** children;  /* array storing the pointers to child nodes */
	bool leaf;          /* true when the node is a leaf, otherwise false */
	BTnode(bool il=true, int n=0):leaf(il), keyNum(n){} 
}BTnode, *PBTnode;

class Btree{
private:
	PBTnode root;
	void DELETE_TREE(PBTnode pNode);
	PBTnode ALLOACT_NODE();
	void B_TREE_SPLIT_CHILD(PBTnode x, int i);
	void B_TREE_INSERT_NONFULL(PBTnode x, int k);
	void DELETE_NODE(PBTnode &node);
	void B_TREE_MERGE_CHILD(PBTnode x, int index);
	int B_TREE_FIND_PREDECESSOR(PBTnode x); // ǰ���ؼ��� 
	int B_TREE_FIND_SUCCESSOR(PBTnode x);   // ��̹ؼ��� 
	void B_TREE_DELETE_RECURSIVE(PBTnode x, int k);	
	
public:
	Btree(){
		root = NULL;
	}
	~Btree(){
		DELETE_TREE(root);
	}
	PBTnode getRoot(){
		return root;
	}
	
	PBTnode B_TREE_SEARCH(PBTnode x, int k, int& index);
	bool KEY_IS_EXIST(int key); 
	void PRINT_TREE(PBTnode x);
	void B_TREE_INSERT(int k);
	void B_TREE_DELETE(int k); 
};

int main(){
	Btree tree1;
	tree1.B_TREE_INSERT(1);
	tree1.B_TREE_INSERT(2);
	tree1.B_TREE_INSERT(3);
	tree1.B_TREE_INSERT(4);
	tree1.B_TREE_INSERT(5);
	tree1.B_TREE_INSERT(6);
	tree1.B_TREE_INSERT(7);
	tree1.B_TREE_INSERT(8);
	tree1.B_TREE_INSERT(9);
	tree1.B_TREE_INSERT(10);
	std::cout << "build tree(1~10): " << std::endl;
	tree1.PRINT_TREE(tree1.getRoot());
	std::cout << "delete key 2(test case 2): " << std::endl;
	tree1.B_TREE_DELETE(2);
	tree1.PRINT_TREE(tree1.getRoot());
	std::cout << "delete key 4(test case 3): " << std::endl;
	tree1.B_TREE_DELETE(4);
	tree1.PRINT_TREE(tree1.getRoot());
	std::cout << "delete key 10(test case 1): " << std::endl;
	tree1.B_TREE_DELETE(10);
	tree1.PRINT_TREE(tree1.getRoot());
	
	return 0;
} 

void Btree::DELETE_TREE(PBTnode pNode){
	if(pNode == NULL) return;
	else{
		if(!pNode->leaf){
			for(int i=0; i<=pNode->keyNum; i++){
				DELETE_TREE(pNode->children[i]);
			}
		}
		delete pNode;
		pNode = NULL;
	}
}

PBTnode Btree::ALLOACT_NODE(){
	PBTnode newNode = new BTnode();
	newNode->keyValue = new int[2*T-1];
	newNode->children = new PBTnode[2*T];
	for(int i=0; i<2*T; i++)
		newNode->children[i] = NULL;
	
	return newNode;
}

/*
/* �ҵ���Ӧ�Ľڵ㷵�أ�����ͨ��index�����õõ��ڽڵ�x�е�λ�� 
*/
PBTnode Btree::B_TREE_SEARCH(PBTnode x, int k, int& index){
	if(x == NULL) return NULL;
	else{
		int i=0;
		while(i<x->keyNum && k>x->keyValue[i]){
			i++;
		}
		if(i<x->keyNum && k==x->keyValue[i]){
			index = i;
			return x;
		} 			
		else{
			if(x->leaf)
				return NULL;
			else
				return B_TREE_SEARCH(x->children[i], k, index);
		} 
	}
}

bool Btree::KEY_IS_EXIST(int key){
	int index;
	if(B_TREE_SEARCH(root, key, index)==NULL) return false;
	return true;
}

void Btree::PRINT_TREE(PBTnode x){
	if(NULL == x) return;
	
	// �����ǰ�ڵ�����йؼ��� 
	std::cout << "[";
	for(int i=0; i<x->keyNum; i++) 
		std::cout << " " << x->keyValue[i];
	std::cout << " ]";
	
	// �ݹ������������
	for(int i=0; i<=x->keyNum; i++)
		PRINT_TREE(x->children[i]); 
		
	std::cout << std::endl;
}


void Btree::B_TREE_SPLIT_CHILD(PBTnode x, int index){
	PBTnode z = ALLOACT_NODE();
	PBTnode y = x->children[index];
	z->leaf = y->leaf;
	z->keyNum = T-1;
	for(int i=0; i<T-1; i++){ // ��ȡ���ιؼ�����Ϊ���ӽڵ�Ĺؼ��� 
		z->keyValue[i] = y->keyValue[T+i];
	}
	if(!y->leaf){
		for(int i=0; i<T; i++){
			z->children[i] = y->children[T+i];
		}
	}
	
	y->keyNum = T-1; // ����ԭ�����Ĺؼ��ָ���
	// �����ڵ�x�У�λ��index������йؼ��ֺ���������һλ 
	for(int i=x->keyNum; i>index; i--){
		x->children[i+1] = x->children[i];
		x->keyValue[i] = x->keyValue[i-1]; 
	} 
	x->keyNum++;
	x->children[index+1] = z; // �洢������
	x->keyValue[index] = y->keyValue[T-1]; // ���ڵ��м�ֵ���������ڵ� 
}

void Btree::B_TREE_INSERT_NONFULL(PBTnode x, int k){
	int i=x->keyNum-1;
	if(x->leaf){
		for(; i>=0&&k<x->keyValue[i]; i--){
			x->keyValue[i+1] = x->keyValue[i];
		}
		i++;
		(x->keyNum)++;
		x->keyValue[i] = k;
	}
	else{ 
		while(i>=0&&k<x->keyValue[i])
			i--;
		i++;
		if(x->children[i]->keyNum == 2*T-1){
			B_TREE_SPLIT_CHILD(x, i);
			if(k>x->keyValue[i]) i++; 
		}
		B_TREE_INSERT_NONFULL(x->children[i], k);
	}
}

void Btree::B_TREE_INSERT(int k){
	if(!KEY_IS_EXIST(k)){
		if(root == NULL){ // ����Ϊ���� 
			root = ALLOACT_NODE();
		}
		if(root->keyNum == 2*T-1){ // ���ڵ����������¸������Ѹ��ڵ� 
			PBTnode newRoot = ALLOACT_NODE();
			newRoot->children[0] = root;
			newRoot->leaf = false;
			B_TREE_SPLIT_CHILD(newRoot, 0);
			root = newRoot; // ���¸��ڵ� 
		}
		B_TREE_INSERT_NONFULL(root, k);
	} 
}

void Btree::DELETE_NODE(PBTnode &node){
	if(node != NULL){
		delete node;
		node = NULL;
	}
}

void Btree::B_TREE_MERGE_CHILD(PBTnode x, int index){
	PBTnode xchild1 = x->children[index];
	PBTnode xchild2 = x->children[index+1];
	xchild1->keyValue[T-1] = x->keyValue[index]; 
	for(int j=0; j<T-1; j++)
		xchild1->keyValue[T+j] = xchild2->keyValue[j];
	if(!xchild1->leaf){ // ����ڵ㲻��Ҷ�ڵ㣬����Ҫ�ƶ����� 
		for(int j=0; j<T; j++){
			xchild1->children[j+T] = xchild2->children[j];
		} 
	}
	xchild1->keyNum = 2*T-1;
	
	// �ָ����ڵ㣺ɾ����һ���ؼ��֣�index֮��Ĺؼ��ּ�ָ����Ҫǰ�� 
	x->keyNum--;
	for(int j=index; j<=x->keyNum; j++){
		x->keyValue[j] = x->keyValue[j+1];
		x->children[j+1] = x->children[j+2];
	}
	DELETE_NODE(xchild2);
	if(x->keyNum == 0) DELETE_NODE(x);
}

int Btree::B_TREE_FIND_PREDECESSOR(PBTnode x){
	while(!x->leaf){
		x = x->children[x->keyNum];
	}
	return x->keyValue[x->keyNum-1];
} 

int Btree::B_TREE_FIND_SUCCESSOR(PBTnode x){
	while(!x->leaf){
		x = x->children[0];
	}
	return x->keyValue[0];
} 

void Btree::B_TREE_DELETE_RECURSIVE(PBTnode x, int k){
	int index=0;
	while(index<x->keyNum && k>x->keyValue[index])
		index++;
	if(k==x->keyValue[index]){ // �ؼ����ڽڵ�x 
		if(x->leaf){ // case 1
			for(int j=index; j<x->keyNum; j++)
				x->keyValue[j] = x->keyValue[j+1];
			x->keyNum--;
			std::cout << "aaa" << std::endl;
			return;
		} 
		else{ // �ڵ�xΪ�ڲ��ڵ� 
			PBTnode y = x->children[index]; // �ڵ�x��ǰ��k���ӽڵ� 
			PBTnode z = x->children[index+1]; // �ڵ�x�к���k���ӽڵ� 
			
			if(y->keyNum >= T){ // case 2a: �ڵ�y���ٰ���T���ؼ��� 
				int prevKey = B_TREE_FIND_PREDECESSOR(y); // ���key��ǰ���ؼ���
				 B_TREE_DELETE_RECURSIVE(y, prevKey);
				 x->keyValue[index] = prevKey;
				 return;
			} 
			else if(z->keyNum >= T){ // case 2b: �ڵ�z���ٰ���T���ؼ��� 
				int nextKey = B_TREE_FIND_SUCCESSOR(z); // ���key�ĺ����ؼ���
				B_TREE_DELETE_RECURSIVE(z, nextKey);
				x->keyValue[index] = nextKey;
				return; 
			}
			else{ // case 2c: �ڵ�y��z��ֻ����T-1���ؼ��� 
				B_TREE_MERGE_CHILD(x, index);
				B_TREE_DELETE_RECURSIVE(y, k);
			}
		}
	}
	else{ // �ؼ���k���ڽڵ�x�У���x->children[index]Ϊ����k�������ĸ��ڵ�
		PBTnode xchild = x->children[index]; // ����k���������ڵ�
		if(xchild->keyNum == T-1){ // ֻ��T-1���ؼ���
		 	PBTnode pLeft = index>0? x->children[index-1]:NULL; // ���ֵܽڵ�
			PBTnode pRight = index<x->keyNum? x->children[index+1]:NULL; // ���ֵܽڵ�  
			if(pLeft && pLeft->keyNum>=T){ // case 3a: ���ֵܽڵ��еĹؼ�����������T	
				// ���ڵ���i-1���ؼ����½����ϲ��ڵ�
				for(int j=xchild->keyNum; j>0; j--){
					xchild->keyValue[j] = xchild->keyValue[j-1];
				} 
				xchild->keyValue[0] = x->keyValue[index-1];
				if(!pLeft->leaf){
					// �����ֵܽڵ��к��ʵĺ���ָ����ֲ��xchild 
					for(int j=xchild->keyNum+1; j>0; j--){
						xchild->children[j] = xchild->children[j-1];
					}
					xchild->children[0] = pLeft->children[pLeft->keyNum];
				}
				xchild->keyNum++;
				x->keyValue[index] = pLeft->keyValue[pLeft->keyNum-1]; // ���ֵܽڵ��е����ؼ����������丸�ڵ���
				pLeft->keyNum--; 
			}
			else if(pRight && pRight->keyNum>=T){ // case 3a: ���ֵܽڵ��еĹؼ�����������T	
				// ���ڵ���i���ؼ����½����ϲ��ڵ� 
				xchild->keyValue[xchild->keyNum] = x->keyValue[index];
				xchild->keyNum++;
				x->keyValue[index] = pRight->keyValue[0]; // ���ֵܽڵ��е���С�ؼ������������ڵ�x
				pRight->keyNum--;
				for(int j=0; j<pRight->keyNum; j++){
					pRight->keyValue[j] = pRight->keyValue[j+1];
				} 
				if(!pRight->leaf){
					// �����ֵܽڵ��к��ʵĺ���ָ����ֲ��xchild 
					xchild->children[xchild->keyNum] = pRight->children[0];
					for(int j=0; j<=pRight->keyNum; j++){
						pRight->children[j] = pRight->children[j+1];
					} 
				}
			} 
			else if(pLeft){ // ���ֵܽڵ�ǿգ������ֵܺϲ� 
				B_TREE_MERGE_CHILD(x, index-1);
				xchild = pLeft;
			}
			else if(pRight){ // ���ֵܽڵ�ǿգ������ֵܺϲ� 
				B_TREE_MERGE_CHILD(x, index-1);
			}
		} 	
		B_TREE_DELETE_RECURSIVE(xchild, k); 
	} 
}	

void Btree::B_TREE_DELETE(int k){
	if(KEY_IS_EXIST(k)){
		if(root->keyNum == 1){
			if(root->leaf)
				DELETE_TREE(root);
			else{ // case 3b: ���ݲ�����򣬵����ڵ�ֻ��һ���ؼ���ʱ��ֻ������2������
			 	PBTnode rchild1 = root->children[0];
				PBTnode rchild2 = root->children[1];
				if(rchild1->keyNum == T-1 && rchild2->keyNum == T-1){
					B_TREE_MERGE_CHILD(root, 0);
					root = rchild1;
				} 	
			}
		}
		B_TREE_DELETE_RECURSIVE(root, k);
	}
}

