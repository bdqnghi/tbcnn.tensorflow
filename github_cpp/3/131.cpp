#include <iostream>
#include "AVL-Tree.h"

int main(){
	
	AVL_Tree<int> avl;
	avl.insert(5);
	avl.insert(10);
	avl.insert(10);
	avl.insert(10);
	avl.insert(1);
	avl.insert(4);
	avl.insert(6);
	avl.insert(7);
	avl.insert(8);
	avl.insert(99);
	avl.insert(5);
	avl.insert(5);
	avl.insert(0);
	avl.insert(6);
	std::cout << "AVL-TREE!" << std::endl;
	avl.print();
	if(avl.search(99)) std::cout << 99 << " in tree!\n";
	if(avl.search(6)) std::cout << 6 << " in tree!\n";
	else std::cout << 6 << " not in the tree!\n";
	if(avl.search(0)) std::cout << 0 << " in tree!\n";
	if(avl.search(98)) std::cout << 98 << " in tree!\n";
	else std::cout << 98 << " not in the tree!\n";
	if(avl.search(99)) std::cout << 99 << " in tree!\n";
	return 0;
}
