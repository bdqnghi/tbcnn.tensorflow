#pragma once

#include <string>
#include <sstream>

namespace tg
{
	enum colorType
	{
		RBTREE_RED,
		RBTREE_BLACK
	};

	enum traversalModel
	{
		PREORDER,
		INORDER,
		POSTORDER
	};

	typedef struct treeNode
	{
		size_t _key;
		colorType _nodeType;
		treeNode * _parent;
		treeNode * _lChild;
		treeNode * _rChild;

		treeNode(const int& value) :_key(value) 
		{
			_parent = nullptr;
			_lChild = nullptr;
			_rChild = nullptr;
		}

		~treeNode()
		{
			printf("destory.. %d\r\n", _key);
		}

		std::string to_string()
		{
			std::stringstream ss;
			ss << "key : " << _key << " -- clrtype : " << (_nodeType == RBTREE_BLACK ? "RBTREE_BLACK" : "RBTREE_RED") << "\r\n";
			return ss.str();
		}
	} Node;

	typedef void(*__process)(Node* node);
	
	class RBTree
	{
	public:
		RBTree();
		~RBTree();

		void insertNode(const int& value);			
		void findNode(const int& value);			
		void removeNode(const int& value);			
		std::string to_string();					
		size_t size() { return _Tree_Size; }		

	private:
		void init();								
		void color(Node * node, colorType type_c);	

		Node * makeHead();							
		Node * createNode(const int& value);		
		Node * parent(Node* node);					

		void leftMost(Node* node, Node* child);		
		void rightMost(Node* node, Node* child);	
		void parentMost(Node* node, Node* parent);	

		void treeLeftRotate(Node* node);			
		void treeRightRotate(Node* node);			
		void balanceRBTree(Node* node);				

		bool clrType(Node* node, colorType type);					
		void traversalTree(traversalModel type, __process func);	

		void preorderTraversal(Node * node);									
		void inorderTraversal(Node * node, __process func = nullptr);			
		void postorderTraversal(Node * node);									

		static void free_node(Node* node) { delete node; node = nullptr; }

	private:
		Node * _Head;
		Node * _Root;
		std::stringstream _SS;
		size_t _Tree_Size;
	};
}


