//stuednt Name: Meng Zhao
//student ID: 301173271

#ifndef _RedBlackTree_

#define _RedBlackTree_


#include <string>
using namespace std;
#include"Node.h"

template <class T>
class RedBlackTree
{
public:
	RedBlackTree(void);
	~RedBlackTree(void);
	RedBlackTree(const RedBlackTree &rb);//copy constructor
    
	// Overloaded assignment operator
	RedBlackTree & operator= (const RedBlackTree & rb);
	void load(T arr[],int size);
	bool insert(T);
	bool remove(T);
	bool search(T) const;
	T* search(T,T,int&) const;
	void deleteAll();
	T* dump(int&) const;
	int size() const;
	int height() const;
	int b_height() const;
	bool redCheck()const;
	void print()const;
	
	void debugPrint()const;
	
private:

	Node<T>* root;
	int n;
	bool recursiveSearch(T d,Node<T>* nd) const;
	void bstInsert(Node<T>* x);
	void preorderTraversal(Node<T>* nd) const;
	void left_rotate(Node<T>* x);
	void right_rotate(Node<T>* x);
	void destroy(Node<T>* x);
	void deepcopy(Node<T>* nd,Node<T>* rb);
	void inorderheper(Node<T>* nd,int& a, T* arr) const;
	void inordersreachindex(Node<T>* nd,int& a,T d1,T d2) const;
    void inordersreach(Node<T>* nd,int& a, T* arr,T d1,T d2) const;
	void debugPrint(Node<T> * node) const;
	int rbtheight(Node<T>* nd) const;
	Node<T>* GetSuccessorOf(Node<T> * x) const;
	Node<T>* bstremove(T x) const;
	void rbDeleteFixUp(Node<T>* x);
	void redProperty(Node<T>* nd, bool & ok) const; //should be private
};

#include "RedBlackTree.cpp"

#endif