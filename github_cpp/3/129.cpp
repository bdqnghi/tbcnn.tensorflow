#include <iostream>

#include "tree_functions.cpp"

template <class T>
	class avl_tree {
		private:
			tree_functions::node<T>* root;

		public:

			avl_tree();
			avl_tree(T);

			bool empty();
			
			void clear();

			void insert(T);
			bool search(T);
			void remove(T);

			void print();

	};

template <class T>
	avl_tree<T>::avl_tree(){
		root=NULL;
	}	

template <class T>
	avl_tree<T>::avl_tree(T z){
		root=new tree_functions::node<T>(z);
	}	

template <class T>
	bool avl_tree<T>::empty(){
		return root==NULL;
	}

template <class T>
	void avl_tree<T>::clear(){
		root=NULL;
	}

template <class T>
	void avl_tree<T>::insert(T z) {
		root=tree_functions::insert(root,z);
	}

template <class T>
	bool avl_tree<T>::search(T z) {
		return tree_functions::search(root,z);
	}

template <class T>
	void avl_tree<T>::remove(T z) {
		root=tree_functions::remove(root,z);
	}

template <class T>
	void avl_tree<T>::print() {
		tree_functions::print(root);
		std::cout<<std::endl;
	}

int main() {
	avl_tree<int> x;

	x.insert(56);
	x.insert(79);
	x.insert(34);
	x.insert(61);
	x.insert(59);
	x.insert(55);
	x.insert(62);
	x.insert(34);
	x.insert(65);
	x.print();

	x.remove(34);

	x.print();

}