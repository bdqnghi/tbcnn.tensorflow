#include <iostream>
#include "AVLTree.h"

#define T int

using namespace std;

T g_stopFlag = 0;
T g_data = 0;

void setStopFlag() {
	cout << "Set your stop flag to exit the program: ";
	cin >> g_stopFlag;
	cout << endl;
}

void addNodePrompt(AVLTree<T> &htObj) {
	cout << endl << "--- ADDING NODES INTO AVL-TREE (" << g_stopFlag << " TO STOP) ---" << endl;
	do {
		cout << endl << "Enter data into the AVLTree: ";
		cin >> g_data;
		if (g_data != g_stopFlag) {
			if (htObj.insert(g_data)) {
				cout << "[ " << g_data << " ] inserted into the AVLTree." << endl;
				htObj.printAsTree();
				cout << endl;
			} else {
				cout << "[ " << g_data << " ] already exists in the AVLTree." << endl;
			}
		}
	} while (g_data != g_stopFlag);
}

void searchNodePrompt(AVLTree<T> &htObj) {
	cout << endl << "--- SEARCHING NODES FROM AVL-TREE (" << g_stopFlag << " TO STOP) ---" << endl;
	do {
		cout << endl << "Enter a data to search in the tree: ";
		cin >> g_data;
		if (g_data != g_stopFlag) {
			if (htObj.searchTree(g_data))
				cout << "[ " << g_data << " ] exists in the AVLTree." << endl;
			else
				cout << "[ " << g_data << " ] does not exist in the AVLTree." << endl;
		}
	} while (g_data != g_stopFlag);
}

void removeNodePrompt(AVLTree<T> &htObj) {
	cout << endl << "--- REMOVING NODES FROM AVL-TREE (" << g_stopFlag << " TO STOP) ---" << endl;
	do {
		cout << endl << "Enter a data to remove from the AVLTree: ";
		cin >> g_data;
		if (g_data != g_stopFlag) {
			if (htObj.remove(g_data)) {
				cout << "[ " << g_data << " ] removed from the AVLTree." << endl;
				htObj.printAsTree();
				cout << endl;
			} else {
				cout << "[ " << g_data << " ] does not exist in AVLTree." << endl;
			}
		}
	} while (g_data != g_stopFlag);
}

void printTree(AVLTree<T> &htObj) {
	cout << endl << "--- PRINTING ALL THE NODES FROM AVL-TREE IN TREE FORMAT ---" << endl;
	htObj.printAsTree();
	cout << endl;
}

void printList(AVLTree<T> &htObj) {
	cout << endl << "--- PRINTING ALL THE NODES FROM AVL-TREE IN LIST FORMAT ---" << endl;
	htObj.printAsList();
	cout << endl;
}

int main() {
	AVLTree<T> htObj;
	setStopFlag();
	addNodePrompt(htObj);
	searchNodePrompt(htObj);
	removeNodePrompt(htObj);
	printTree(htObj);
	printList(htObj);
	htObj.clearTree();
	cout << endl << "All nodes removed." << endl;
	cout << endl << "Press any key to exit...";
	cin >> g_data;
	return 0;
}