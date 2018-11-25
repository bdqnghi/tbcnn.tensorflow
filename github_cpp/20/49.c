#ifndef B
#define B

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>


namespace RBTree{
	
	template<class T>
	class Node {
	public:
		T data; 
		char color;  
		Node *left, *right, *parent; 
		bool isBlack;

		
		Node(T x) {
			data = x;
			left = NULL;
			right = NULL;
			parent = NULL;
			color = 'X';
			isBlack = true;
		}

		
		Node() {
		
			color = 'X';
			left = NULL;
			right = NULL;
			parent = NULL;
			isBlack = true;
		}
	};


	
	template<class T>
	class RedBlackTree {
	public:
		
		RedBlackTree(); 
		RedBlackTree(const RedBlackTree& old);
		RedBlackTree& operator=(const RedBlackTree& old);
		~RedBlackTree();
		void load(T* arr, int size);
		bool insert(T value);
		bool remove(T value);
		bool search(T value);
		T* search(T valueMin, T valueMax,int &iCount);
		void deleteAll();
		T* dump(int& n) const; 
		

		
		int size() const;
		int height() const;
		int b_height() const;

		
		void redProperty(Node<T>* nd, bool & ok) const; 
		bool redCheck() const; 
		
		
		
		void dump_help(Node<T> *node, int& n) const;
		void insertfixup(Node<T> *node);
		void removefixup(Node<T> *node);
		Node<T>* deleteNode(Node<T>* node);
		void deletefixup(Node<T>* node,Node<T>* nodeParent, bool nodeIsLeft);
		

		
		Node<T>* TreeSuccessor(Node<T>* target);
		void delete_all(Node<T>* p);
		void LeftRotate(Node<T>* x);
		void RightRotate(Node<T>* x);
		bool RedBlackTree<T>::isEmpty() const;

		
		void deleteNode(Node<T>* target, Node<T>* parent, bool isLeft);




		
    
		
		
		
		

		
		
		
		
		
		
		
		
		
		

		
		
		
		

	private:
		Node<T>* root;
		int n; 
		T* arr;

		
	};
}
#endif