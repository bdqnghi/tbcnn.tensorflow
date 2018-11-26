#include <stdio.h>
#include <vector>

struct TreeNode {
	char data;
	std::vector<TreeNode*> children;
	TreeNode *parent = nullptr;

	TreeNode* AddChild(char new_data);
	void PrintBreadthFirst();
	void PrintBreadthFirstRecurse();
	void PrintDepthFirst();
	TreeNode *SearchDepthFirst(char needle);
	TreeNode *SearchBreadthFirst(char needle);
};

TreeNode* TreeNode::AddChild(char new_data) {
	TreeNode *node = new TreeNode;
	node->data = new_data;
	node->parent = this;
	children.push_back(node);
	return node;
}

void TreeNode::PrintBreadthFirst() {
	printf("%c\n", data);
	PrintBreadthFirstRecurse();
}

void TreeNode::PrintBreadthFirstRecurse() {
	for (auto it = children.begin(); it != children.end(); it++) {
		printf("%c\n", (*it)->data);
	}
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->PrintBreadthFirstRecurse();
	}
}

void TreeNode::PrintDepthFirst() {
	printf("%c\n", data);
	for (auto it = children.begin(); it != children.end(); it++) {
		(*it)->PrintDepthFirst();
	}
}

TreeNode *TreeNode::SearchDepthFirst(char needle) {
	if (data == needle) {
		return this;
	}
	for (auto &el : children) {
		TreeNode *result = el->SearchBreadthFirst(needle);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

TreeNode *TreeNode::SearchBreadthFirst(char needle) {
	if (data == needle) {
		return this;
	}
	for (auto &el : children) {
		if (el->data == needle) {
			return el;
		}
	}
	for (auto &el : children) {
		TreeNode *result = el->SearchBreadthFirst(needle);
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

void PrintTreeNode(TreeNode *node) {
	if (node == nullptr) {
		printf("No node\n");
		return;
	}
	printf("Node: %c\n", node->data);
}


void TreesMain() {
	printf("===============================================\n");
	printf("TREES\n");
	printf("===============================================\n");

	TreeNode root;
	root.data = 'A';
	TreeNode *b = root.AddChild('B');
	TreeNode *f = root.AddChild('F');
	TreeNode *j = root.AddChild('J');
	b->AddChild('C');
	b->AddChild('D');
	b->AddChild('E');
	f->AddChild('G');
	f->AddChild('H');
	f->AddChild('I');
	j->AddChild('K');
	j->AddChild('L');
	j->AddChild('M');

	printf("-----------------------------------------------\n");
	printf("Breadth First\n");
	printf("-----------------------------------------------\n");
	root.PrintBreadthFirst();

	printf("-----------------------------------------------\n");
	printf("Depth First\n");
	printf("-----------------------------------------------\n");
	root.PrintDepthFirst();

	printf("-----------------------------------------------\n");
	printf("Search Depth First\n");
	printf("-----------------------------------------------\n");
	PrintTreeNode(root.SearchDepthFirst('A'));
	PrintTreeNode(root.SearchDepthFirst('D'));
	PrintTreeNode(root.SearchDepthFirst('J'));
	PrintTreeNode(root.SearchDepthFirst('X'));


	printf("-----------------------------------------------\n");
	printf("Search Breadth First\n");
	printf("-----------------------------------------------\n");
	PrintTreeNode(root.SearchBreadthFirst('A'));
	PrintTreeNode(root.SearchBreadthFirst('D'));
	PrintTreeNode(root.SearchBreadthFirst('J'));
	PrintTreeNode(root.SearchBreadthFirst('X'));
}