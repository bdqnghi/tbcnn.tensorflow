#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "btree.h"

using namespace std;

TNumber min(TNumber num1, TNumber num2) {
	if (num1 < num2) {
		return num1;
	} else {
		return num2;
	}
}
TNumber max(TNumber num1, TNumber num2) {
	if (num1 > num2) {
		return num1;
	} else {
		return num2;
	}
}

char ToLowerCase(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		letter += 'a' - 'A';
	}
	return letter;
}

int StringComparison(char *str1, char *str2) {
	for (size_t i = 0; true; i++) {
		if (str1[i] == '\0' && str2[i] != '\0') {
			return -1;
		}
		if (str1[i] != '\0' && str2[i] == '\0') {
			return 1;
		}
		if (str1[i] == '\0' && str2[i] == '\0') {
			return 0;
		}
		if (ToLowerCase(str1[i]) == ToLowerCase(str2[i])) {
			continue;
		}
		if (ToLowerCase(str1[i]) > ToLowerCase(str2[i])) {
			return 1;
		} else {
			return -1;
		}
	}
}


TNote::TNote() {
	this->Key[0] = '\0';
	this->Num = 0;
}



TBTreeNode::TBTreeNode(TBTreeNode *parent, bool is_leaf) {
	this->Parent = parent;

	this->Elements = NULL;
	this->ElementsNum = 0;

	this->Children = NULL;
	this->ChildrenNum = 0;

	this->IsLeaf = is_leaf;
}

TBTreeNode::~TBTreeNode() {
	delete [] this->Elements;
	delete [] this->Children;
}

void TBTreeNode::InsertElementToLeaf(TNote element) {
	if (!this->IsLeaf) {
		cout << "Node is not a leaf" << endl;
		return;
	}

	//Binnary search
	size_t left = 0;
	size_t right = this->ElementsNum - 1;
	if (this->ElementsNum == 0) {
		right = 0;
	}
	while (right > left) {
		size_t tmp_size = right - left + 1;
		size_t middle = tmp_size / 2 + left;
		if (StringComparison(element.Key, this->Elements[middle].Key) == -1) {
			right = middle - 1;
		} else {
			left = middle;
		}
	}

	//Insert element
	size_t insert_pos = left;
	if (this->ElementsNum != 0) {
		int cmp = StringComparison(element.Key, this->Elements[insert_pos].Key);
		if (insert_pos != 0 || cmp != -1) {
			insert_pos++;
		}
	}

	TNote *new_elements = new TNote[this->ElementsNum + 1];
	size_t pos = 0;
	for (size_t i = 0; i < this->ElementsNum; i++) {
		if (i == insert_pos) {
			pos++;
		}
		new_elements[pos] = this->Elements[i];
		pos++;
	}
	new_elements[insert_pos] = element;
	delete [] this->Elements;
	this->Elements = new_elements;
	this->ElementsNum++;
}

void TBTreeNode::DeleteElementFromLeaf(size_t pos) {
	size_t new_arr_len = this->ElementsNum - 1;
	TNote *new_arr = new TNote[new_arr_len];
	size_t tmp_pos = 0;
	for (size_t i = 0; i < new_arr_len; i++) {
		if (tmp_pos == pos) {
			tmp_pos++;
		}
		new_arr[i] = this->Elements[tmp_pos];
		tmp_pos++;
	}
	delete [] this->Elements;
	this->Elements = new_arr;
	this->ElementsNum = new_arr_len;
}

size_t TBTreeNode::GetInsertPosition(TBTreeNode *child) {
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		if (this->Children[i] == child) {
			return i;
		}
	}
	return 0;
}

void TBTreeNode::Print(size_t lvl) {
	for (size_t i = 0; i < this->ElementsNum; i++) {
		for (size_t j = 0; j < lvl; j++) {
			cout << "  ";
		}
		cout << this->Elements[i].Key << ":" << this->Elements[i].Num << endl;
	}
	cout << "----------" << endl;
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		this->Children[i]->Print(lvl + 1);
	}
}

void TBTreeNode::PrintElements() {
	cout << "NodeContent::";
	for (size_t i = 0; i < this->ElementsNum; i++) {
		cout << this->Elements[i].Key << " ";
	}
	cout << endl;
}



TBTree::TBTree(size_t factor) {
	this->Root = NULL;
	this->FactorT = factor;

	//Creating file prefix
	//this->FilePrefix = {'P', 'a', 's', 'W', 'D', 'd', 'a', '\0'};
	this->FilePrefix[0] = 'P';
	this->FilePrefix[1] = 'a';
	this->FilePrefix[2] = 's';
	this->FilePrefix[3] = 'W';
	this->FilePrefix[4] = 'D';
	this->FilePrefix[5] = 'd';
	this->FilePrefix[6] = 'a';
	this->FilePrefix[7] = '\0';

	//this->FilePrefixSize = 8;
}

TBTree::~TBTree() {
	if (this->Root != NULL) {
		this->TreeDestroy(this->Root);
	}
}

void TBTree::TreeDestroy(TBTreeNode *node) {
	for (size_t i = 0; i < node->ChildrenNum; i++) {
		this->TreeDestroy(node->Children[i]);
	}
	delete node;
}

size_t TBTree::Split(TBTreeNode *node) {
	//Separate arrays
	size_t middle = node->ElementsNum / 2;
	TNote middle_element = node->Elements[middle];

	size_t arr1_elements_len = middle;
	size_t arr2_elements_len = node->ElementsNum - middle - 1;

	TNote *arr1_elements = new TNote[arr1_elements_len];
	TNote *arr2_elements = new TNote[arr2_elements_len];
	size_t arr1_children_len = 0;
	size_t arr2_children_len = 0;

	TBTreeNode **arr1_children = NULL;
	TBTreeNode **arr2_children = NULL;
	if (!node->IsLeaf) {
		arr1_children_len = arr1_elements_len + 1;
		arr2_children_len = arr2_elements_len + 1;

		arr1_children = new TBTreeNode *[arr1_children_len];
		arr2_children = new TBTreeNode *[arr2_children_len];
	}

	for (size_t i = 0; i < node->ElementsNum; i++) {
		if (i == middle) {
			continue;
		}
		if (i < middle) {
			arr1_elements[i] = node->Elements[i];
		} else {
			arr2_elements[i - middle - 1] = node->Elements[i];
		}
	}
	if (!node->IsLeaf) {
		for (size_t i = 0; i < node->ChildrenNum; i++) {
			if (i <= middle) {
				arr1_children[i] = node->Children[i];
			} else {
				arr2_children[i - middle - 1] = node->Children[i];
			}
		}
	}

	if (node->Parent == NULL) {
		node->Parent = new TBTreeNode(NULL, false);
		node->Parent->ChildrenNum = 1;
		node->Parent->Children = new TBTreeNode *[node->Parent->ChildrenNum];
		node->Parent->Children[node->Parent->ChildrenNum - 1] = node;
		this->Root = node->Parent;
	}

	if (node->Parent->ElementsNum >= this->FactorT * 2 - 1) {
		this->Split(node->Parent);
	}

	size_t insert_pos_element = node->Parent->GetInsertPosition(node);
	size_t insert_pos_children = insert_pos_element + 1;

	//Space
	TNote *parent_elements_new = new TNote[node->Parent->ElementsNum + 1];
	size_t pos = 0;
	for (size_t i = 0; i < node->Parent->ElementsNum; i++) {
		if (pos == insert_pos_element) {
			pos++;
		}
		parent_elements_new[pos] = node->Parent->Elements[i];
		pos++;
	}
	node->Parent->ElementsNum++;
	delete [] node->Parent->Elements;
	node->Parent->Elements = parent_elements_new;

	TBTreeNode **parent_children_new = new TBTreeNode *[node->Parent->ChildrenNum + 1];
	pos = 0;
	for (size_t i = 0; i < node->Parent->ChildrenNum; i++) {
		if (pos == insert_pos_children) {
			pos++;
		}
		parent_children_new[pos] = node->Parent->Children[i];
		pos++;
	}
	node->Parent->ChildrenNum++;
	delete [] node->Parent->Children;
	node->Parent->Children = parent_children_new;

	
	//Inserting
	node->Parent->Elements[insert_pos_element] = middle_element;

	node->Parent->Children[insert_pos_children] = new TBTreeNode(node->Parent, node->IsLeaf);
	node->Parent->Children[insert_pos_children]->IsLeaf = node->IsLeaf;

	node->Parent->Children[insert_pos_children]->Elements = arr2_elements;
	node->Parent->Children[insert_pos_children]->ElementsNum = arr2_elements_len;
	if (!node->IsLeaf) {
		TBTreeNode *ths_tmp = node->Parent->Children[insert_pos_children];
		ths_tmp->Children = arr2_children;
		ths_tmp->ChildrenNum = arr2_children_len;
		for (size_t i = 0; i < ths_tmp->ChildrenNum; i++) {
			ths_tmp->Children[i]->Parent = ths_tmp;
		}
	}

	delete [] node->Elements;
	node->Elements = arr1_elements;
	node->ElementsNum = arr1_elements_len;

	if (!node->IsLeaf) {
		delete [] node->Children;
		node->Children = arr1_children;
		node->ChildrenNum = arr1_children_len;
	}

	return insert_pos_element;
}

void TBTree::Unite(TBTreeNode *node, size_t pos) {
	if (node->IsLeaf) {
		cout << "Unite error: Node is leaf" << endl;
		return;
	}
	if (pos >= node->ElementsNum) {
		cout << "Unite error: Unable position" << endl;
		return;
	}

	node->Children[pos]->PrintElements();
	node->Children[pos + 1]->PrintElements();

	//Creating united arrays
	size_t new_arr_elements_len = 1;
	new_arr_elements_len += node->Children[pos]->ElementsNum;
	new_arr_elements_len += node->Children[pos + 1]->ElementsNum;
	TNote *new_arr_elements = new TNote[new_arr_elements_len];

	for (size_t i = 0; i < new_arr_elements_len; i++) {
		if (i < node->Children[pos]->ElementsNum) {
			new_arr_elements[i] = node->Children[pos]->Elements[i];
			continue;
		}
		if (i > node->Children[pos]->ElementsNum) {
			size_t tmp_pos = i - node->Children[pos]->ElementsNum - 1;
			new_arr_elements[i] = node->Children[pos + 1]->Elements[tmp_pos];
			continue;
		}
		new_arr_elements[i] = node->Elements[pos];
	}

	size_t new_arr_children_len = 0;
	TBTreeNode **new_arr_children = NULL;
	if (!node->Children[pos]->IsLeaf) {
		new_arr_children_len = node->Children[pos]->ChildrenNum;
		new_arr_children_len += node->Children[pos + 1]->ChildrenNum;
		new_arr_children = new TBTreeNode *[new_arr_children_len];
		for (size_t i = 0; i < new_arr_children_len; i++) {
			if (i < node->Children[pos]->ChildrenNum) {
				new_arr_children[i] = node->Children[pos]->Children[i];
			} else {
				size_t tmp_pos = node->Children[pos]->ChildrenNum;
				new_arr_children[i] = node->Children[pos + 1]->Children[i - tmp_pos];
			}
		}
	}

	//Deleting second branch and creating united child in first branch
	delete node->Children[pos + 1];
	delete [] node->Children[pos]->Elements;
	if (!node->Children[pos]->IsLeaf) {
		delete [] node->Children[pos]->Children;
	}

	node->Children[pos]->Elements = new_arr_elements;
	node->Children[pos]->ElementsNum = new_arr_elements_len;
	node->Children[pos]->Children = new_arr_children;
	node->Children[pos]->ChildrenNum = new_arr_children_len;

	//Creating new parent arrays
	size_t new_parent_arr_elements_len = node->ElementsNum - 1;
	size_t new_parent_arr_children_len = node->ChildrenNum - 1;
	TNote *new_parent_arr_elements = new TNote[new_parent_arr_elements_len];
	TBTreeNode **new_parent_arr_children = new TBTreeNode *[new_parent_arr_children_len];

	size_t tmp_pos = 0;
	for (size_t i = 0; i < new_parent_arr_elements_len; i++) {
		if (tmp_pos == pos) {
			tmp_pos++;
		}
		new_parent_arr_elements[i] = node->Elements[tmp_pos];
		tmp_pos++;
	}

	tmp_pos = 0;
	for (size_t i = 0; i < new_parent_arr_children_len; i++) {
		if (tmp_pos == pos + 1) {
			tmp_pos++;
		}
		new_parent_arr_children[i] = node->Children[tmp_pos];
		tmp_pos++;
	}

	//Refreshing arrays
	delete [] node->Elements;
	delete [] node->Children;
	node->Elements = new_parent_arr_elements;
	node->ElementsNum = new_parent_arr_elements_len;
	node->Children = new_parent_arr_children;
	node->ChildrenNum = new_parent_arr_children_len;

	for (size_t i = 0; i < node->Children[pos]->ChildrenNum; i++) {
		node->Children[pos]->Children[i]->Parent = node->Children[pos];
	}

	tmp_pos = 0;
	if (node->Parent != NULL) {
		for (size_t i = 0; i < node->Parent->ChildrenNum; i++) {
			if (node == node->Parent->Children[i]) {
				tmp_pos = i;
				break;
			}
		}
	}

	this->Balance(node, tmp_pos);
}

void TBTree::Balance(TBTreeNode *CurrentNode, size_t pos) {
	if (CurrentNode == NULL) {
		return;
	}
	
	/*if (CurrentNode->Parent->ElementsNum == 0 && CurrentNode->Parent->Parent == NULL) {
		delete this->Root;
		this->Root = CurrentNode;
		this->Root->Parent = NULL;
		return;
	}*/
	if (CurrentNode->ElementsNum == 0 && CurrentNode->Parent == NULL) {
		CurrentNode = CurrentNode->Children[0];
		delete this->Root;
		this->Root = CurrentNode;
		this->Root->Parent = NULL;
		return;
	}
	if (CurrentNode->ElementsNum >= this->FactorT - 1 || CurrentNode->Parent == NULL) {
		return;
	}

	bool is_left_larger = false;
	bool is_right_larger = false;

	if (pos > 0) {
		if (CurrentNode->Parent->Children[pos - 1]->ElementsNum > this->FactorT - 1) {
			is_left_larger = true;
		}
	}
	if (pos < CurrentNode->Parent->ChildrenNum - 1) {
		if (CurrentNode->Parent->Children[pos + 1]->ElementsNum > this->FactorT - 1) {
			is_right_larger = true;
		}
	}

	//this->Print();
	if (!is_left_larger && !is_right_larger) {
		//CurrentNode->DeleteElementFromLeaf(pos);
		if (pos > 0) {
			this->Unite(CurrentNode->Parent, pos - 1);
		} else {
			this->Unite(CurrentNode->Parent, pos);
		}
		return;
	}
	if (is_left_larger) {
		this->RotateRight(CurrentNode);
	} else {
		this->RotateLeft(CurrentNode);
	}
}

void TBTree::RotateLeft(TBTreeNode *CurrentNode) {
	size_t pos = 0;
	for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
		if (CurrentNode == CurrentNode->Parent->Children[i]) {
			pos = i;
			break;
		}
	}

	size_t right_first = 0;
	TNote k1 = CurrentNode->Parent->Children[pos + 1]->Elements[right_first];
	TNote k2 = CurrentNode->Parent->Elements[pos];
	CurrentNode->Parent->Children[pos + 1]->DeleteElementFromLeaf(right_first);
	CurrentNode->Parent->Elements[pos] = k1;

	TNote *new_arr_elements = new TNote[CurrentNode->ElementsNum + 1];
	for (size_t i = 0; i < CurrentNode->ElementsNum; i++) {
		new_arr_elements[i] = CurrentNode->Elements[i];
	}
	new_arr_elements[CurrentNode->ElementsNum] = k2;
	delete [] CurrentNode->Elements;
	CurrentNode->Elements = new_arr_elements;
	CurrentNode->ElementsNum++;

	if (!CurrentNode->IsLeaf) {
		TBTreeNode *t_right = CurrentNode->Parent->Children[pos + 1];
		TBTreeNode *tmp = t_right->Children[right_first];
		TBTreeNode **new_arr_children = new TBTreeNode *[t_right->ChildrenNum - 1];

		for (size_t i = 1; i < t_right->ChildrenNum; i++) {
			new_arr_children[i - 1] = t_right->Children[i];
		}
		delete [] t_right->Children;
		t_right->Children = new_arr_children;
		t_right->ChildrenNum--;

		new_arr_children = new TBTreeNode *[CurrentNode->ChildrenNum + 1];
		for (size_t i = 0; i < CurrentNode->ChildrenNum; i++) {
			new_arr_children[i] = CurrentNode->Children[i];
		}
		tmp->Parent = CurrentNode;
		new_arr_children[CurrentNode->ChildrenNum] = tmp;
		delete [] CurrentNode->Children;
		CurrentNode->Children = new_arr_children;
		CurrentNode->ChildrenNum++;
	}
}

void TBTree::RotateRight(TBTreeNode *CurrentNode) {
	CurrentNode->PrintElements();
	this->Print();
	size_t pos = 0;
	CurrentNode->Parent->PrintElements();
	for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
		if (CurrentNode == CurrentNode->Parent->Children[i]) {
			pos = i;
			break;
		}
	}
	size_t left_last = CurrentNode->Parent->Children[pos - 1]->ElementsNum - 1;
	TNote k1 = CurrentNode->Parent->Children[pos - 1]->Elements[left_last];
	TNote k2 = CurrentNode->Parent->Elements[pos - 1];
	CurrentNode->Parent->Children[pos - 1]->DeleteElementFromLeaf(left_last);
	CurrentNode->Parent->Elements[pos - 1] = k1;

	TNote *new_arr_elements = new TNote[CurrentNode->ElementsNum + 1];
	//
	for (size_t i = 0; i < CurrentNode->ElementsNum; i++) {
		new_arr_elements[i + 1] = CurrentNode->Elements[i];
	}
	new_arr_elements[0] = k2;
	delete [] CurrentNode->Elements;
	CurrentNode->Elements = new_arr_elements;
	CurrentNode->ElementsNum++;

	if (!CurrentNode->IsLeaf) {
		TBTreeNode *t_left = CurrentNode->Parent->Children[pos - 1];
		TBTreeNode *tmp = t_left->Children[left_last + 1];
		TBTreeNode **new_arr_children = new TBTreeNode *[t_left->ChildrenNum - 1];

		for (size_t i = 0; i < t_left->ChildrenNum - 1; i++) {
			new_arr_children[i] = t_left->Children[i];
		}
		delete [] t_left->Children;
		t_left->Children = new_arr_children;
		t_left->ChildrenNum--;

		new_arr_children = new TBTreeNode *[CurrentNode->ChildrenNum + 1];
		for (size_t i = 0; i < CurrentNode->ChildrenNum; i++) {
			new_arr_children[i + 1] = CurrentNode->Children[i];
		}
		tmp->Parent = CurrentNode;
		new_arr_children[0] = tmp;
		delete [] CurrentNode->Children;
		CurrentNode->Children = new_arr_children;
		CurrentNode->ChildrenNum++;
	}
}

TSearchRes TBTree::Search(char *key) {
	TSearchRes result;
	TBTreeNode *node = this->Root;
	result.Node = node;
	result.Pos = 0;
	result.IsFound = false;

	while (node != NULL) {
		bool is_maximal = true;
		bool is_leaf = node->IsLeaf;
		for (size_t i = 0; i < node->ElementsNum; i++) {
			int cmp = StringComparison(key, node->Elements[i].Key);
			/*cout << "SearchLog:: ";
			cout << key;
			switch (cmp) {
				case -1:
					cout << " < ";
					break;
				case 0:
					cout << " = ";
					break;
				case 1:
					cout << " > ";
					break;
			}
			cout << node->Elements[i].Key << endl;*/
			if (cmp == 0) {
				result.Pos = i;
				result.IsFound = true;
				result.Element = node->Elements[i];
				return result;
			}
			
			if (cmp < 0) {
				is_maximal = false;
				if (!node->IsLeaf) {
					node = node->Children[i];
				}
				break;
			}
		}
		if (is_leaf) {
			result.Node = node;
			result.IsFound = false;
			return result;
		}
		if (is_maximal) {
			node = node->Children[node->ChildrenNum - 1];
		}
		if (node != NULL) {
			result.Node = node;
		}
	}
	result.IsFound = false;
	return result;
}

void TBTree::Push(TNote element) {
	//cout << "Push::Element " << element.Key << ":" << element.Num << endl;
	
	TSearchRes search_res = this->Search(element.Key);
	TBTreeNode *CurrentNode = search_res.Node;

	if (search_res.IsFound) {
		cout << "Exist" << endl;
		return;
	}

	if (CurrentNode == NULL) {
		CurrentNode = new TBTreeNode(NULL, true);
		this->Root = CurrentNode;
	}

	if (CurrentNode->ElementsNum >= this->FactorT * 2 - 1) { 
		size_t insert_pos = this->Split(CurrentNode);
		if (StringComparison(element.Key, CurrentNode->Parent->Elements[insert_pos].Key) != -1) {
			CurrentNode = CurrentNode->Parent->Children[insert_pos + 1];
		}
	}

	CurrentNode->InsertElementToLeaf(element);
	cout << "OK" << endl;
}

TNote TBTree::Pop(char *key) {
	TNote res;
	res.Num = 0;
	res.Key[0] = '\0';
	//cout << "Searching..." << endl;
	TSearchRes search_res = this->Search(key);
	//cout << "OK" << endl;
	if (!search_res.IsFound) {
		cout << "NoSuchWord" << endl;
		return res;
	}
	//cout << "Pop::In" << endl;
	TBTreeNode *CurrentNode = search_res.Node;
	size_t pos = search_res.Pos;

	res = CurrentNode->Elements[pos];
	//cout << "Pop::Point1" << endl;
	while (!CurrentNode->IsLeaf) {
		TBTreeNode *left = CurrentNode->Children[pos];
		TBTreeNode *right = CurrentNode->Children[pos + 1];

		bool is_left_larger = false;
		bool is_right_larger = false;

		if (left->ElementsNum > this->FactorT - 1) {
			is_left_larger = true;
		}

		if (right->ElementsNum > this->FactorT - 1) {
			is_right_larger = true;
		}

		if (!is_left_larger && !is_right_larger) {
			this->Unite(CurrentNode, pos);
			CurrentNode = left;
			pos = CurrentNode->ElementsNum / 2;
			continue;
		}

		if (is_left_larger) {
			this->RotateRight(right);
			CurrentNode = right;
			pos = 0;
		} else {
			this->RotateLeft(left);
			CurrentNode = left;
			pos = CurrentNode->ElementsNum - 1;

		}
	}
	//cout << "Pop::Point2" << endl;

	if (CurrentNode == this->Root && CurrentNode->ElementsNum == 1) {
		//delete [] this->Root->Elements;
		//this->Root->ElementsNum = 0;
		TreeDestroy(this->Root);
		this->Root = NULL;
		cout << "OK" << endl;
		return res;
	}
	//cout << "Pop::Point3" << endl;
	
	CurrentNode->DeleteElementFromLeaf(pos);
	//cout << "Pop::Point4" << endl;
	
	size_t parent_pos = 0;
	if (CurrentNode->Parent != NULL) {
		for (size_t i = 0; i < CurrentNode->Parent->ChildrenNum; i++) {
			if (CurrentNode == CurrentNode->Parent->Children[i]) {
				parent_pos = i;
				break;
			}
		}
	}
	//cout << "Pop::Point5" << endl;

	this->Balance(CurrentNode, parent_pos);

	cout << "OK" << endl;
	return res;
}

void TBTree::Print() {
	//cout << "Tree printing..." << endl;
	if (this->Root != NULL) {
		this->Root->Print(0);
	} else {
		cout << "Tree is empty" << endl;
	}
	//cout << "Finish printing" << endl;
}


//FILES

bool TBTree::Save(char *path) {
	FILE *out = fopen(path, "wb");
	if (out == NULL) {
		cout << "ERROR: Couldn't create file" << endl;
		return false;
	}

	//Writing prefix
	fwrite(this->FilePrefix, sizeof(char), FILE_PREFIX_SIZE, out);
	this->Root->Save(out);
	fclose(out);
	cout << "OK" << endl;
	return true;
}
bool TBTree::Load(char *path) {
	FILE *in = fopen(path, "rb");

	if (in == NULL) {
		cout << "ERROR: Couldn't open file" << endl;
		return false;
	}

	char out_prefix[FILE_PREFIX_SIZE];

	fread(out_prefix, sizeof(char), FILE_PREFIX_SIZE, in);

	if (StringComparison(this->FilePrefix, out_prefix) != 0) {
		cout << this->FilePrefix << " != " << out_prefix << endl;
		cout << "ERROR: Incorrect file" << endl;
		return false;
	}

	if (this->Root != NULL) {
		this->TreeDestroy(this->Root);
	}
	this->Root = NULL;

	//TBTreeNode *this_node = NULL;
	//TBTreeNode *prev_node = NULL;

	/*while (!feof(in)) {
		this_node = new TBTreeNode();
	}*/
	this->Root = this->LoadNodes(in, NULL);
	fclose(in);

	cout << "OK" << endl;
	return true;
}

void TBTreeNode::Save(FILE *out) {
	char is_leaf = (char) this->IsLeaf;
	fwrite(&is_leaf, 1, 1, out);
	fwrite(&this->ElementsNum, sizeof(size_t), 1, out);
	for (size_t i = 0; i < this->ElementsNum; i++) {
		fwrite(this->Elements[i].Key, sizeof(char), KEY_STR_LEN, out);
		fwrite(&this->Elements[i].Num, sizeof(TNumber), 1, out);
	}
	for (size_t i = 0; i < this->ChildrenNum; i++) {
		this->Children[i]->Save(out);
	}
}
TBTreeNode *TBTree::LoadNodes(FILE *in, TBTreeNode *parent) {
	if (feof(in)) {
		return NULL;
	}
	char is_leaf;
	fread(&is_leaf, 1, 1, in);
	TBTreeNode *node = new TBTreeNode(parent, (bool) is_leaf);

	fread(&node->ElementsNum, sizeof(size_t), 1, in);
	node->Elements = new TNote[node->ElementsNum];
	for (size_t i = 0; i < node->ElementsNum; i++) {
		fread(node->Elements[i].Key, sizeof(char), KEY_STR_LEN, in);
		fread(&node->Elements[i].Num, sizeof(TNumber), 1, in);
	}
	if (!node->IsLeaf) {
		node->ChildrenNum = node->ElementsNum + 1;
		node->Children = new TBTreeNode *[node->ChildrenNum];
		for (size_t i = 0; i < node->ChildrenNum; i++) {
			node->Children[i] = this->LoadNodes(in, node);
		}
	}
	return node;
}
