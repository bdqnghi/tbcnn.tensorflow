/*                             Begin LinkedList.h                                           */
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <functional>

typedef unsigned long ulong;

template<class T>
struct node {
	T data;
	node *next;

	node(T value) : data(value), next(nullptr) {}
};

template<class T>
class LinkedList {
private:
	node<T> *root;
	node<T> *cursor;
	int listLength;
	enum linkInfo { prevNodeA, nextNodeA, prevNodeB, nextNodeB };
	void PrintList(node<T> *printer, bool reversed) const;
	void SetRoot(node<T> **newRoot, node<T> *n);
	void DoDeleteAll(node<T> *dltr);
	bool IterativeReverse(node<T> *head);
	bool RecurseReverse(node<T> *currNode, node<T> *prevNode, node<T> *newNext);


public:
	LinkedList();            ~LinkedList();

	bool InsertNode(T val);
	void PrintList(bool reversed) const;
	node<T> *Search(T val);
	T RemoveNode(T val);
	void DeleteEntireList(void);
	bool SwapNodes(T nodeOne, T nodeTwo);
	bool SortList(std::string sortForm);
	bool ReverseList(char toggle);
	bool MakeUnique(void);
	bool ModifyNode(T nodeVal, T toVal);
	void GetCursor(void) const;
	void AdvanceCursor(int places);
	int GetLength(void) const;

};
/*                             End LinkedList.h                                           */

/*                             Begin LinkedList.cpp                                           */
/* Idea is to implement basic functions first, in order from non-destructive to destructive
* Hence: Insert -> PrintList -> Search -> Remove etc; before moving on to the more involved functionality.
*/

template<class T>
LinkedList<T>::LinkedList() : root(nullptr), cursor(nullptr), listLength(0) {}

template<class T>
LinkedList<T>::~LinkedList() {}

template<class T>
bool LinkedList<T>::InsertNode(T val) {
	if (!root) {
		root = new node<T>(val);
		cursor = root;
	}
	else {
		node<T> *n = new node<T>(val);
		cursor->next = n;
		cursor = n;
	}
	++listLength;
	return true;
}


template<class T>
void LinkedList<T>::PrintList(bool reversed) const {
	if (root == nullptr) { std::cout << "The list's empty ... "; return; }
	std::cout << std::endl;
	PrintList(root, reversed);
}

template<class T>
void LinkedList<T>::PrintList(node<T> *printer, bool reversed) const {
	if (printer == nullptr) { return; }

	if (reversed) {
		PrintList(printer->next, reversed);
		std::cout << printer->data << "\t";
	}
	if (!reversed) {
		std::cout << printer->data << "\t";
		PrintList(printer->next, reversed);
	}
}

template<class T>
bool LinkedList<T>::ReverseList(char toggle) {
	if (root == nullptr) { return false; }

	/* Come back to this later */
	if (toggle == 1) { //iterative
		IterativeReverse(root);
	}

	if (toggle == 2) {
		RecurseReverse(root->next, root, nullptr);
	}
	return false;
}


/* The iterative version is just unoptimal puzzle to play around with pointers-to-pointers.
 It's _not_ meant to be efficient, or pretty, or remotely 'good'. This is _bad_.*/
 /* Currently putting into statis, will return to it later */
template<class T>
bool LinkedList<T>::IterativeReverse(node<T> *head) {
	/*	node<T> **reverseArr[listLength];      // ISSUE: Trying to create a dynamic array from static conventions -->listLength is volatile, need a dynamic array for this approach
	node<T> *parser = root;

	for (auto i : reverseArr) {				// ISSUE: Since the array declaration is illegal, this doesn't work either
	i = &parser;
	parser = parser->next;
	}

	for (int ppi = listLength - 1; ppi >= 0; --ppi) {
	if (ppi == 0)
	(*reverseArr[ppi])->next = nullptr;
	else
	(*reverseArr[ppi])->next = (*reverseArr[ppi - 1]);
	}*/
	return true;
}

template<class T>
bool LinkedList<T>::RecurseReverse(node<T> *currNode, node<T> *prevNode, node<T> *newNext) {

	if (prevNode == nullptr) { return true; }
	if (currNode == nullptr && prevNode != nullptr) { root = prevNode; return true; }
	else {
		prevNode->next = newNext;
		RecurseReverse(currNode->next, currNode, prevNode);
		currNode->next = prevNode;
		return true;
	}
}

template<class T>
node<T> *LinkedList<T>::Search(T val) {
	if (root == nullptr) {
		std::cout << "List's empty! Found gobs of nothing!";
		return nullptr;
	}
	else {
		node<T> *parser = root;
		while (parser != nullptr) {
			if (parser->data != val) { parser = parser->next; }
			else { break; }
		}

		if (parser == nullptr) {
			std::cout << "Couldn't find your query! Sorry.";
			return nullptr;
		}
		return parser;
	}
}


// Modify the root
template<class T>
void LinkedList<T>::SetRoot(node<T> **newRoot, node<T> *n) {
	if (n == nullptr) { (*newRoot)->next = nullptr; }
	else { (*newRoot)->next = n->next; }

	(*newRoot) = n;
	return;
}

template<class T>
bool LinkedList<T>::ModifyNode(T nodeVal, T toVal) {
	if (root == nullptr) { return false; }

	node<T> *targetN = Search(nodeVal);
	if (targetN) {
		targetN->data = toVal;
		return true;
	}
	else { return false; }
}


template<class T>
bool LinkedList<T>::MakeUnique() {
	if (!root) { return false; }

	node<T> *parserSymbol = root,
		*comparer = nullptr,
		*del = nullptr;

	std::vector<node<T>*> nodesToRemove;

	while (parserSymbol != nullptr) {
		comparer = root;
		while (comparer != nullptr) {
			if (parserSymbol->data == comparer->data && parserSymbol != comparer) {
				if (nodesToRemove.size() > 0) {
					for (auto node : nodesToRemove) {
						if (node != comparer) {
							nodesToRemove.push_back(comparer);
						}
					}
				}
				else {
					nodesToRemove.push_back(comparer);
				}
			}
			comparer = comparer->next;
		}
		parserSymbol = parserSymbol->next;
	}

	std::cout << "Deleted nodes: \n";
	for (auto &i : nodesToRemove) {
		std::cout << i->data << "\t";
	}

	std::cout << "\nRemoved " << nodesToRemove.size() << " duplicate nodes.\n";
	return true;
}



template<class T>
T LinkedList<T>::RemoveNode(T val) {
	if (!root) {
		std::cout << "The list's empty, hey! It's maddening but /you/ might be doing something wrong!";
		return val;
	}

	node<T> *del = Search(val);
	T dataBuffer;

	if (del == root) {
		dataBuffer = root->data;

		SetRoot(&root, del->next);

		delete del;        --listLength;
		return dataBuffer;
	}
	else {
		dataBuffer = del->data;
		cursor = root;
		while (cursor->next != del) { cursor = cursor->next; }
		cursor->next = (cursor->next)->next;
		delete del;        
		--listLength;
		return dataBuffer;
	}
}

template<class T>
void LinkedList<T>::DeleteEntireList() {
	DoDeleteAll(root);
}

template<class T>
void LinkedList<T>::DoDeleteAll(node<T> *dltr) {
	if (dltr == nullptr) { listLength = 0; return; }

	DoDeleteAll(dltr->next);

	dltr->next = nullptr;
	delete dltr;
	dltr->data = -1;
	dltr = nullptr;

}

template<class T>
void LinkedList<T>::GetCursor() const {
	std::cout << "cursor: " << cursor->data << "\n";
}

template<class T>
void LinkedList<T>::AdvanceCursor(int places) {
	while (places != 0 && cursor->next != nullptr) {
		cursor = cursor->next;
		--places;
	}
	if (cursor->next == nullptr) {
		std::cout << "Reached the end of the list!" << std::endl;
		return;
	}
}


template<class T>
int LinkedList<T>::GetLength() const {
	return listLength;
}

// For now, non-unique linked-lists are out of scope.
template<class T>
bool LinkedList<T>::SwapNodes(T nodeOne, T nodeTwo) {
	if (!root || !nodeOne || !nodeTwo) { return false; }

	node<T> *A = Search(nodeOne);
	node<T> *B = Search(nodeTwo);

	node<T> **root_links[] = { nullptr, nullptr, nullptr, nullptr };

	// Data switching
	T temp = B->data;					B->data = A->data;					A->data = temp;

#pragma region pointer_addr_switching
	// NOTE: This does _not_ work; consider it a frozen thought experiement
	/*node<T> *parser = root;
	while (parser->next != nullptr) {
	if (parser->next == A) { root_links[linkInfo::prevNodeA] = &(parser); }
	if (parser->next == B) { root_links[linkInfo::prevNodeB] = &(parser); }
	parser = parser->next;
	}
	root_links[linkInfo::nextNodeA] = &(A->next);
	root_links[linkInfo::nextNodeB] = &(B->next);

	// > Commence swap <

	(*root_links[linkInfo::prevNodeA])->next = B;
	(*root_links[linkInfo::prevNodeB])->next = A;

	node<T> *tempVar = B;			B = A;			A = tempVar;

	node<T> *temp = *(root_links[linkInfo::nextNodeB]);
	*(root_links[linkInfo::nextNodeB]) = *(root_links[linkInfo::nextNodeA]);
	*(root_links[linkInfo::nextNodeA]) = temp;*/

#pragma endregion
	
	return true;
}
template<class T>
bool LinkedList<T>::SortList(std::string sortForm) {
	if (!root) { return  false; }
	
	std::vector<T> data_array;
	node<T> *parser = root;

	while (parser != nullptr) {
		data_array.push_back(parser->data);
		parser = parser->next;
	}
		
	if (sortForm == "asc") {
		std::sort(data_array.begin(), data_array.end(), std::less<T>());
	}
	if (sortForm == "dsc") {
		std::sort(data_array.begin(), data_array.end(), std::greater<T>());
	}

	parser = root;
	for (auto &i : data_array) {
		if (parser != nullptr) {
			parser->data = i;
			parser = parser->next;
		}
	}
}

int main(void) {
	// your code goes here

	LinkedList<int> slist;
	slist.PrintList(false);
	std::cout << "list length: " << slist.GetLength() << std::endl;

	slist.InsertNode(9);
	slist.PrintList(false);
	std::cout << "list length: " << slist.GetLength() << std::endl;

	slist.InsertNode(2);
	slist.InsertNode(5);
	slist.InsertNode(3);
	slist.InsertNode(5);
	slist.InsertNode(3);
	slist.InsertNode(5);
	slist.InsertNode(3);
	slist.InsertNode(2);
	slist.InsertNode(3);
	slist.InsertNode(7);
	slist.InsertNode(3);
	slist.InsertNode(5);
	slist.PrintList(false);

	std::cout << std::endl;

	//slist.SwapNodes(2, 7);
	//slist.ReverseList(2);
	//slist.ModifyNode(2, 23);

	//slist.MakeUnique();

	slist.SortList("asc");
	slist.PrintList(false);

	slist.SortList("dsc");
	slist.PrintList(false);

	std::cout << std::endl << "list length: " << slist.GetLength() << std::endl;

	return 0;
}

// End LinkedList.cpp //
