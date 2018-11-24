#include <iostream>
#include <vector>
#include <queue>
#include <string>
struct Node {
	int idata;
	char cdata;
	Node *left, *right;
	Node(char, int);
};
Node::Node(char cval, int ival) {
	idata = ival;
	cdata = cval;
	left = right = nullptr;
}
struct compare {
	bool operator() (Node *p1, Node *p2) {
		return p1->idata > p2->idata;
	}
};

using std::priority_queue;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using freq_priority_queue
= priority_queue<Node *, vector<Node *>, compare >;

void encode(Node *root, string str) {
	if(!root->left && !root->right) {
		cout << root->cdata << " " << str << endl;
		return;
	}
	if(root->left) {
		str.push_back('0');
		encode(root->left, str);
		str.pop_back();
	}
	if(root->right) {
		str.push_back('1');
		encode(root->right, str);
		str.pop_back();
	}
}
void hoffman(freq_priority_queue freq) {
	while(freq.size() != 1) {
		Node *ptemp1 = freq.top();
		freq.pop();
		Node *ptemp2 = freq.top();
		freq.pop();
		Node *new_node = new Node('\0', ptemp1->idata + ptemp2->idata);
		new_node->left = ptemp1;
		new_node->right = ptemp2;
		freq.push(new_node);
	}
	Node *root = freq.top();
	string str("");
	encode(root, str);
}
int main() {
	int char_num;
	cin >> char_num;
	freq_priority_queue freq;
	for(int i = 0; i < char_num; ++i) {
		char cval;
		int ival;
		cin.ignore();
		cin >> cval >> ival;
		Node *new_node = new Node(cval, ival);
		freq.push(new_node);
	}
	hoffman(freq);
	return 0;
}
