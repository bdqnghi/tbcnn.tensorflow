#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#define  _IDCOLUMN 0

using namespace std;

typedef string KeyType;
typedef vector<string> CSVRow;
typedef vector<CSVRow> CSVDatabase;

class Node{

	public:
		vector<KeyType> _keys;
		vector<Node*> _pointers;
		vector<KeyType> _paths;
		Node* _nextList;
		Node* _lastList;
		bool _isLeaf;
		int _numberKeys;
		Node* _dad;
	
		Node(int order, bool leaf){
			
			_keys.resize(order-1);
			_numberKeys = 0;
			_nextList = NULL;
			_lastList = NULL;
			_isLeaf = leaf ? true : false;
			_keys.clear();
			_numberKeys = 0;
			if(_isLeaf){
				_paths.resize(order-1);
				_paths.clear();
			}
			else{
				_pointers.resize(order);
				_pointers.clear();
			}
		}

		Node(int order){

			_keys.resize(order-1);
			_pointers.resize(order);
			_nextList = NULL;
			_lastList = NULL;
			_numberKeys = 0;
			_isLeaf = false;
			_keys.clear();
			_pointers.clear();
		}

		void _sortKeys(){

			sort(this->_keys.begin(), this->_keys.begin()+this->_numberKeys);
		}
};

void BppInsert(Node* &tree, KeyType value, int n_Order);
Node* getNodeToAdd(Node* node, KeyType value);
bool SplitVector(Node* &base, KeyType &upper, Node* &left, Node* &right);
void printTree(Node* &tree, int tabs);
void UpFirsts(vector<string> &_Keys, vector<Node*> &_Pointers, int n_Order, Node* &tree);
void BulkLoadingInsert(Node* &tree, CSVDatabase &_Table, int n_Order, int _Column);
bool searchPathByKey(Node* &tree, KeyType key, KeyType &path);
void RemoveNode(KeyType id, Node* &tree, CSVDatabase &_Table, int n_Order, int _Column);
void RemoveNodeOfVector(Node* &_node, KeyType _searchKey, int _index, int n_Order);

#include "../hpp/B.cpp"
