#pragma once
using namespace std;

template <class T>
struct TreeNode
{
	T info;
	TreeNode<T>* left;
	TreeNode<T>* right;
};

template <class T>
class TreeType
{
public:
	TreeType();
	~TreeType();
	//  TreeType(const TreeType<T>& originalTree);

	void operator=(const TreeType<T>& originalTree);
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int NumberOfNodes();				////
	void RetrieveItem(T& item, bool& found);  //
	void InsertItem(T item);
	void DeleteItem(T item);
	void ResetTree();
	void GetNextItem(T& item, bool& finished);
	void PrintTree(ofstream& outfile);
	void Display();
	void HasA(string surname, vector<T>& list);

private:
	TreeNode<T>* root;

	//helper methods
	int CountNodes(TreeNode<T>* tree);
	void Retrieve(TreeNode<T>* tree, T& item, bool& found);
	void Insert(TreeNode<T>*& tree, T item);
	void Delete(TreeNode<T>*& tree, T item);
	void DeleteNode(TreeNode<T>*& tree);
	void GetPredecessor(TreeNode<T>* tree, T& data);
	void Print(TreeNode<T>* tree, ofstream& outfile);
	void Destroy(TreeNode<T>* tree);
	void Search(TreeNode<T>* tree, vector<T>& list, string substr);
	void Show(TreeNode<T>* tree);
};

template <class T>
void TreeType<T>::Search(TreeNode<T>* tree, vector<T>& list, string subs)
{
	if (tree != nullptr)
	{
		Search(tree->left, list, subs);
		if (tree->info == subs)
			list.push_back(tree->info);
		Search(tree->right, list, subs);
	}
	

}
template <class T>
void TreeType<T>::HasA(string surname, vector<T>& list)
{
	list.clear();
	Search(root, list, surname);
	//return list;
	
}

template <class T>
TreeType<T>::TreeType()
{
	root = nullptr;
}

template <class T>
void TreeType<T>::Display()
{
	Show(root);
}
template <class T>
void TreeType<T>::Show(TreeNode<T>* tree)
{
	if (tree != nullptr)
	{
		Show(tree->left);
		cout << tree->info;
		Show(tree->right);
	}
}
template <class T>
TreeType<T>::~TreeType()
{
	Destroy(root);
}

template <class T>
void TreeType<T>::MakeEmpty()
{
	Destroy(root);
	root = nullptr;
}
template <class T>
void TreeType<T>::Destroy(TreeNode<T>* tree)
{
	if (tree != nullptr)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

template <class T>
bool TreeType<T>::IsFull() const
{
	TreeNode<T>* temp;
	try
	{
		temp = new TreeNode<T>();
		delete temp;
		return false;
	}
}
template <class T>
bool TreeType<T>::IsEmpty() const
{
	return root == nullptr;
}

template <class T>
void TreeType<T>::PrintTree(ofstream& outfile)
{
	Print(root, outfile);
}

template <class T>
void TreeType<T>::Print(TreeNode<T>* tree, ofstream& outfile)
{
	if (tree != NULL)
	{
		Print(tree->left, outfile);
		outfile << tree->info;
		Print(tree->right, outfile);
	}

}











template <class T>
void TreeType<T>::Delete(TreeNode<T>*& tree, T item)
{
	if (tree == nullptr)
		return;
	if (item < tree->info)
		Delete(tree->left, item);
	else if (item > tree->info)
		Delete(tree->right, item);
	else
		DeleteNode(tree);

}
template <class T>
void TreeType<T>::DeleteNode(TreeNode<T>*& tree)
{
	T data;
	TreeNode<T>* temp;
	temp = tree;
	if (tree->left == nullptr)
	{
		tree = tree->right;
		delete temp;
	}
		
	else if (tree->right == nullptr)
	{
		tree = tree->left;
		delete temp;
	}
	else
	{
		GetPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);
	}
	

}
template <class T>
void TreeType<T>::DeleteItem(T item)
{
	Delete(root, item);
}
template <class T>
void TreeType<T>::GetPredecessor(TreeNode<T>* tree, T& data)
{
	while (tree->right != nullptr)
	{
		tree = tree->right;
	}
	data = tree->info;
}
















template <class T>
void TreeType<T>::InsertItem(T item)
{
	Insert(root, item);
}
template <class T>
void TreeType<T>::Insert(TreeNode<T>*& tree, T item)
{
	if (tree == nullptr)
	{
		tree = new TreeNode<T>();
		tree->right = nullptr;
		tree->left = nullptr;
		tree->info = item;
	}
	else if (item < tree->info)
		Insert(tree->left, item);
	else
		Insert(tree->right, item);
}







template <class T>
int TreeType<T>::NumberOfNodes() 
{
	return CountNodes(root);
}
template <class T>
int TreeType<T>::CountNodes(TreeNode<T>* tree)
{
	if (tree == nullptr)
		return 0;
	else
		return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}



template <class T>
void TreeType<T>::RetrieveItem(T& item, bool& found)
{
	Retrieve(root, item, found);
}
template <class T>
void TreeType<T>::Retrieve(TreeNode<T>* tree, T& item, bool& found)
{
	if (tree == nullptr)
		found = false;
	else if (item < tree->info)
		Retrieve(tree->left, item, found);
	else if (item > tree->info)
		Retrieve(tree->right, item, found);
	else
	{
		found = true;
		item = tree->info;
	}
}