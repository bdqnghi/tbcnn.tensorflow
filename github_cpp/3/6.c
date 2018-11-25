


#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>
#include <chrono>

using namespace std;
using tp = chrono::time_point<chrono::system_clock>; 
std::string cr, cl, cp;      





typedef struct AVL_node{
	int key;
	unsigned char height;
	struct AVL_node* left;
	struct AVL_node* right;
	struct AVL_node* parent;
	AVL_node(int k, AVL_node* up = NULL){ key = k; left = right = NULL; height = 1; parent = up; }
} AVL_node;

AVL_node* createTreeAVL(int* array, int start, int end, AVL_node* up = NULL);
AVL_node* findMaxAVL(AVL_node* root);
void removeNodesAVL(AVL_node* root, int* valueList, int n);
void printInOrderAVL(AVL_node* root);
void printPreOrderAVL(AVL_node* root);
void deletePostOrderAVL(AVL_node* root);
void printSubtreeAVL(AVL_node* root);
AVL_node* searchAVL(AVL_node* root, int key);


unsigned char height(AVL_node* p);
int bfactor(AVL_node* p);
void fixheight(AVL_node* p);
AVL_node* rotateright(AVL_node* p);
AVL_node* balance(AVL_node* p);





typedef struct BST_node{
	int key;
	struct BST_node* left;
	struct BST_node* right;
	struct BST_node* parent;
	BST_node(int k, BST_node* p = NULL){ key = k; left = right = NULL; parent = p; }
} BST_node;

BST_node* createTreeBST(int* array, int n);
BST_node* findMaxBST(BST_node* root);
void removeNodesBST(BST_node* root, int* valueList, int n);
void printInOrderBST(BST_node* root);
void printPreOrderBST(BST_node* root);
void deletePostOrderBST(BST_node* root);
void printSubtreeBST(BST_node* root); 
BST_node* searchBST(BST_node* root, int key); 
void rotateLeftBST(BST_node* & root, BST_node* node);
void rotateRightBST(BST_node* & root, BST_node* node);
BST_node* balanceBST(BST_node* root);


void RandDescending(int tab[], int tabEnd, int start, int end);
void shellSort(int* array, int n);


void printBST(std::string sp, std::string sn, BST_node* v);
void printAVL(std::string sp, std::string sn, AVL_node* v);





int main(){

	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

	srand(time(NULL));

	int k = 1000000;
	unsigned n;
	int tree;
	int *array;
	bool isCorrectAnswer = false;
	AVL_node* testA = NULL;
	BST_node* testB = NULL;
	int answer;

	int nodes = 0;
	int * nodes_array;

	while(!isCorrectAnswer){
		puts("Enter number of data: ");
		if(!scanf_s("%u", &n) || n < 1)
			puts("Incorrect answer. Try again.");
		else	break;
	}
	
	array = (int*)malloc(n * sizeof(int));
	RandDescending(array, n, 1, k);
	tp start, end;
	while(true){
		isCorrectAnswer = false;
		while(!isCorrectAnswer){
			puts("Choose tree to build:");
			puts("   '1' - AVL-tree;");
			puts("   '2' - BST-tree;");
			scanf_s("%d", &tree);
			switch(tree){
				case 1:
					start = chrono::system_clock::now();
					testA = createTreeAVL(array, 0, n - 1);
					end = chrono::system_clock::now();
					cout <<"Time in microseconds(creating AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
					puts("AVL-tree builded succesfully.");
					isCorrectAnswer = true;
			
					break;
				case 2:
					start = chrono::system_clock::now();
					testB = createTreeBST(array, n);
					end = chrono::system_clock::now();
					cout << "Time in microseconds(creating BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
					puts("BST-tree builded succesfully.");
					isCorrectAnswer = true;
		
					break;
				default:
					puts("Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;
		while(!isCorrectAnswer){
			puts("\nWhat do you want to do with a tree:");
			puts("  1  Find way to max value;");
			puts("  2  Delete few elements;");
			puts("  3  Print tree in-order;");
			puts("  4  Print tree pre-order;");
			puts("  5  Delete tree post-order;");
			puts("  6  Print subtree from given key;");
			puts("  7  Balance tree using rotation;");
			puts("  8  Change tree type;");
			puts("  9  Exit;");
			puts("Give your answer:");
			scanf_s("%d", &answer);
			if(tree == 1){
				switch(answer){
					case 1:
						start = chrono::system_clock::now();
						findMaxAVL(testA);
						end = chrono::system_clock::now();
						cout << "Time in microseconds(Max Value AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 2:
						while(true){
							puts("Enter number of data to delete: ");
							if(!scanf_s("%d", &nodes) || nodes < 1)
								puts("Incorrect answer. Try again.");
							else	break;
						}
						nodes_array = (int*)malloc(nodes * sizeof(int));
						for(int i = 0; i < nodes; i++){
							while(true){
								puts("Enter key of node to delete: ");
								if(!scanf_s("%d", &nodes_array[i]))
									puts("Incorrect answer. Try again.");
								else	break;
							}
						}

						removeNodesAVL(testA, nodes_array, nodes);
						break;
					case 3:
						puts("In-order:");
						start = chrono::system_clock::now();
						printInOrderAVL(testA);
						end = chrono::system_clock::now();
						cout << "Time in microseconds(in-order AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 4:
						puts("Pre-order:");
						printPreOrderAVL(testA);
						break;
					case 5:
						puts("Deleting AVL-tree in post-order...");
						deletePostOrderAVL(testA);
						puts("AVL-tree deleted.");
						isCorrectAnswer = true;
						break;
					case 6:
						puts("Print subtree:");
						printSubtreeAVL(testA);
						break;
					case 7:
						puts("Balancing AVL-tree...");
						balance(testA);
						puts("AVL-tree balanced.");
						break;
					case 8:
						isCorrectAnswer = true;
						break;
					case 9:
						puts("Exited");
						return 0;
					default:
						puts("Incorrect answer. Try again.");
						break;
				}
			} else{
				switch(answer){
					case 1:
						start = chrono::system_clock::now();
						findMaxBST(testB);
						end = chrono::system_clock::now();
						cout << "Time in microseconds(Max Value BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 2:
						while(true){
							puts("Enter number of data to delete: ");
							if(!scanf_s("%d", &nodes) || nodes < 1)
								puts("Incorrect answer. Try again.");
							else	break;
						}
						nodes_array = (int*)malloc(nodes * sizeof(int));
						for(int i = 0; i < nodes; i++){
							while(true){
								puts("Enter key of node to delete: ");
								if(!scanf_s("%d", &nodes_array[i]))
									puts("Incorrect answer. Try again.");
								else	break;
							}
						}

						removeNodesBST(testB, nodes_array, nodes);
						break;
					case 3:
						puts("In-order:");
						start = chrono::system_clock::now();
						printInOrderBST(testB);
						end = chrono::system_clock::now();
						cout << "Timein microseconds(in-order BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 4:
						puts("Pre-order:");
						printPreOrderBST(testB);
						break;
					case 5:
						puts("Deleting BST-tree in post-order...");
						deletePostOrderBST(testB);
						puts("BST-tree deleted.");
						isCorrectAnswer = true;
						break;
					case 6:
						puts("Print subtree:");
						printSubtreeBST(testB);
						break;
					case 7:
						puts("Balancing BST-tree...");
						start = chrono::system_clock::now();
						testB = balanceBST(testB);
						end = chrono::system_clock::now();
						puts("BST-tree balanced.");
						printBST("", "", testB);
						cout << "Time in microseconds(balancing BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 8:
						isCorrectAnswer = true;
						break;
					case 9:
						puts("Exited");
						return 0;
					default:
						puts("Incorrect answer. Try again.");
						break;
				}
				puts("");
			}
		}

	}


	system("pause");
	return 0;
}





AVL_node* createTreeAVL(int* array, int start, int end, AVL_node* up){

	if(start > end)
		return NULL;

	int middle = (start + end + 1) / 2;
	AVL_node* root = new AVL_node(array[middle], up);

	root->left = createTreeAVL(array, middle + 1, end, root);
	root->right =  createTreeAVL(array, start, middle - 1, root);

	return root;
}

AVL_node* findMaxAVL(AVL_node* root){
	if(!root){
		puts("AVL-tree is empty.");
		return root;
	}

	while(root->right){
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}


AVL_node* findMinAVL(AVL_node* root){
	return root->left ? findMinAVL(root->left) : root;
}

AVL_node* removeMinAVL(AVL_node* root){
	if(root->left == NULL)
		return root->right;
	root->left = removeMinAVL(root->left);
	return root; 
}

AVL_node* deleteNodeAVL(AVL_node* root, int key){
	if(root == NULL) return root;
	if(root->left == NULL && root->right == NULL){ 
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = NULL;
			} else{
				root->parent->left = NULL;
			}
		}
		delete root;
		return NULL;
	}else if(root->left == NULL){
		AVL_node* temp = root->right;
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = temp;
			} else{
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	} else if(root->right == NULL){
		AVL_node* temp = root->left;
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = temp;
			} else{
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	} else{

		AVL_node* temp = findMinAVL(root->right);
		root->key = temp->key;
		deleteNodeAVL(temp, temp->key);
		
	}
	return root;
}

void removeNodesAVL(AVL_node* root, int* valueList, int n){
	for(int i = 0; i < n; i++){
		AVL_node* beDeleted = searchAVL(root, valueList[i]);
		if(!beDeleted){
			printf("\nNode with key %d didn\'t found.", valueList[i]);
		} else{
			deleteNodeAVL(beDeleted, beDeleted->key);
			printf("\nNode with key %d deleted.", valueList[i]);
		}
	}
}


void printInOrderAVL(AVL_node* root){
	if(!root){
		puts("AVL-tree is empty.");
		return;
	}
	if(root->left) printInOrderAVL(root->left);
	printf("%d ", root->key);
	if(root->right) printInOrderAVL(root->right);
}

void printPreOrderAVL(AVL_node* root){
	if(!root){
		puts("AVL-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if(root->left) printPreOrderAVL(root->left);
	if(root->right) printPreOrderAVL(root->right);
}

void deletePostOrderAVL(AVL_node* root){
	if(!root){
		puts("AVL-tree is empty.");
		return;
	}

	if(root->left) deletePostOrderAVL(root->left);
	if(root->right) deletePostOrderAVL(root->right);
	delete root;
}

void printSubtreeAVL(AVL_node* root){
	int key;
	AVL_node* result;
	do{
		printf("\nType root key of subtree:");
		scanf_s("%d", &key);
	} while(!key);

	result = searchAVL(root, key);

	if(!result){
		puts("No such element.");
	} else{
		printf("Printing subtree with root key %d:\n", result->key);
		printAVL("", "", result);
		
	}
}

AVL_node* searchAVL(AVL_node* root, int key){
	if(!root || root->key == key){
		return root;
	}

	if(root->key > key)
		return searchAVL(root->left, key);

	return searchAVL(root->right, key);
}


unsigned char height(AVL_node* p){
	return p ? p->height : 0;
}

int bfactor(AVL_node* p){
	return height(p->right) - height(p->left);
}

void fixheight(AVL_node* p){
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

AVL_node* rotateright(AVL_node* p){
	AVL_node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

AVL_node* rotateleft(AVL_node* q){
	AVL_node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

AVL_node* balance(AVL_node* p) 
{
	fixheight(p);
	if(bfactor(p) == 2){
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) == -2){
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}



void shellSort(int* array, int n){
	int gap = 1;
	while(gap < n / 3){
		gap = 3 * gap + 1;
	}

	while(gap > 0){
		for(int i = gap; i < n; i += gap){
			for(int j = i; j > 0 && array[j] < array[j - gap]; j -= gap){
				int temp = array[j];
				array[j] = array[j - gap];
				array[j - gap] = temp;
				
			}
		}
		gap = --gap / 3;
	}
}


BST_node* createTreeBST(int* array, int n){
	BST_node* root = new BST_node(array[0]);
	BST_node* node = root;
	for(int i = 1; i < n; i++){
		while(node){
			if(array[i] < node->key){ 
				if(node->left)	node = node->left; 
				else{ 
					node->left = new BST_node(array[i], node);
					break;
				}
			}else{
				if(node->right) node = node->right;
				else{
					node->right = new BST_node(array[i], node); 
					break;
				}
			}
		}
		
	}
	return root;
}

BST_node* findMaxBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return root;
	}

	while(root->right){
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}



BST_node* findMinBST(BST_node* root){
	return root->left ? findMinBST(root->left) : root;
}

BST_node* deleteNodeBST(BST_node* root, int key){
	if(root == NULL) return root;
	if(root->left == NULL && root->right == NULL){ 
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = NULL;
			} else{
				root->parent->left = NULL;
			}
		}
		delete root;
		return NULL;
	} else if(root->left == NULL){
		BST_node* temp = root->right;
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = temp;
			} else{
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	} else if(root->right == NULL){
		BST_node* temp = root->left;
		if(root->parent){
			if(root->parent->right == root){
				root->parent->right = temp;
			} else{
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	} else{

		BST_node* temp = findMinBST(root->right);
		root->key = temp->key;
		deleteNodeBST(temp, temp->key);
	}
	return root;
}

void removeNodesBST(BST_node* root, int* valueList, int n){
	for(int i = 0; i < n; i++){
		BST_node* beDeleted = searchBST(root, valueList[i]);
		if(!beDeleted){
			printf("\nNode with key %d didn\'t found.", valueList[i]);
		} else{
			deleteNodeBST(beDeleted, beDeleted->key);
			printf("\nNode with key %d deleted.", valueList[i]);
		}
	}
}

void printInOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}
	if(root->left) printInOrderBST(root->left);
	printf("%d ", root->key);
	if(root->right) printInOrderBST(root->right);
}

void printPreOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if(root->left) printPreOrderBST(root->left);
	if(root->right) printPreOrderBST(root->right);
}

void deletePostOrderBST(BST_node* root){
	if(!root){
		puts("BST-tree is empty.");
		return;
	}

	if(root->left) deletePostOrderBST(root->left);
	if(root->right) deletePostOrderBST(root->right);
	delete root;
}

void printSubtreeBST(BST_node* root){
	int key;
	BST_node* result;

	puts("Type root key of subtree:");
	scanf_s("%d", &key);

	result = searchBST(root, key);

	if(!result){
		puts("No such element.");
	} else{
		printBST("", "", result);
	}
}

BST_node* searchBST(BST_node* root, int key){
	if(!root || root->key == key){
		return root;
	}

	if(root->key > key)
		return searchBST(root->left, key);

	return searchBST(root->right, key);
}


void rotateRightBST(BST_node* & root, BST_node* node){
	BST_node* q = node->left;
	node->left = q->right;
	if(node->left) node->left->parent = node;
	q->right = node;
	q->parent = node->parent;
	node->parent = q;
	if(q->parent){
		if(q->parent->left == node)
			q->parent->left = q;
		else q->parent->right = q;
	} else root = q;
}

void rotateLeftBST(BST_node* & root, BST_node* node){
	BST_node* p = node->right;
	if(p){
		node->right = p->left;
		if(node->right) node->right->parent = node;
		p->left = node;
		p->parent = node->parent;
		node->parent = p;
		if(p->parent){
			if(p->parent->left == node)
				p->parent->left = p;
			else	p->parent->right = p;
		} else root = p;
	}
}

unsigned log2(unsigned x){
	unsigned y = 1;

	while((x >>= 1) > 0)
		y <<= 1;

	return y;
}

BST_node* balanceBST(BST_node* root){
	unsigned s, n = 0;
	BST_node* node = root;
	
	while(node){
		if(node->left){
			rotateRightBST(root, node);
			node = node->parent;
		}
		else{
			if(node->right)	node = node->right;
			else break;
			n++;
		}
	}
	
	s = n + 1 - log2(n + 1); 
	cout << s << endl;
	node = root;
	for(unsigned int i = 0; i < s; i++){
		rotateLeftBST(root, node);
		node = node->parent->right;
	}
	n = n - s;
	node = root;
	while(n > 1){
		n >>= 1;
		for(unsigned int i = 0; i < n; i++){
			rotateLeftBST(root, node);
			node = node->parent->right;
		}
		node = root;
	
	}
	return root;
}

void RandDescending(int tab[], int tabEnd, int start, int end){
	int prz = end  / tabEnd ;
	for(int x = 0; x < tabEnd ; x++)
		tab[x] = (rand() % prz) + (end - (x + 1) * prz);
}


							 
							 
void printBST(std::string sp, std::string sn, BST_node* v){
	std::string s;

	if(v){
		s = sp;
		if(sn == cr) s[s.length() - 2] = ' ';
		printBST(s + cp, cr, v->right);

		s = s.substr(0, sp.length() - 2);
		std::cerr << s << sn << v->key << std::endl;

		s = sp;
		if(sn == cl) s[s.length() - 2] = ' ';
		printBST(s + cp, cl, v->left);
	}
}
void printAVL(std::string sp, std::string sn, AVL_node* v){
	std::string s;

	if(v){
		s = sp;
		if(sn == cr) s[s.length() - 2] = ' ';
		if(v->right)printAVL(s + cp, cr, v->right);

		s = s.substr(0, sp.length() - 2);
		std::cerr << s << sn << v->key << std::endl;

		s = sp;
		if(sn == cl) s[s.length() - 2] = ' ';
		if(v->left)printAVL(s + cp, cl, v->left);
	}
}
