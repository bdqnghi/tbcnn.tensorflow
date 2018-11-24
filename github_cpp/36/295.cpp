#include<iostream>
#include<vector>
#include <queue>
using namespace std;

#define BTreeDegree 2
typedef enum
{
	BTreeErrorCodeKeyNotFound = -1  
}BTreeErrorCode;

/************** Helper **************/
struct BTreeData
{
	int key;
	int data;

	BTreeData(int k, int d)
	{
		key = k;
		data = d;
	}

	BTreeData()
	{
		key = -1;
		data = -1;
	}

	BTreeData clone()
	{
		return BTreeData(this->key, this->data);
	}

};

struct BTreeKeyRange
{
	int start;
	int end;

	BTreeKeyRange(int s, int e)
	{
		start = s;
		end = e;
	}

	bool contains(int key)
	{
		return key >= start && key <= end;
	}
};
/************** End of Helper **************/


struct BTreeNode
{
	int keyCount;
	bool isLeaf;

	BTreeData *indexes[2 * BTreeDegree - 1];
	BTreeNode *childs[2 * BTreeDegree];
	BTreeNode *parent;

	BTreeNode()
	{
		keyCount = 0;
		isLeaf = true;

		for (int i = 0; i < 2 * BTreeDegree - 1; i++)
		{
			indexes[i] = NULL;
		}

		for (int i = 0; i < 2 * BTreeDegree; i++)
		{
			childs[i] = NULL;
		}

		parent = NULL;
	}

	~BTreeNode()
	{
		for (int i = 0; i < keyCount; i++)
		{
			if (indexes[i] != NULL) delete indexes[i];
			indexes[i] = NULL;
		}

		for (int i = 0; i < keyCount + 1; i++)
		{
			if (childs[i] != NULL) delete childs[i];
			childs[i] = NULL;
		}
        
        keyCount = 0;
		parent = NULL;
	}

	void addChild(BTreeNode *child, int pos)
	{
		if (this == NULL || child == NULL) return;
		if (pos > 2 * BTreeDegree - 1 || pos < 0) return;
		if (this->keyCount >= 2 * BTreeDegree - 1) return;

		this->childs[pos] = child;
		child->parent = this;
		this->isLeaf = false;
	}

	int findDataOffset(int key, bool &isEqual)
	{
		for (int i = 0; i < keyCount; i++)
		{
			BTreeData *temp = indexes[i];
			if (temp->key == key)
			{
				isEqual = true;
				return i;
			}
			else if (key < temp->key)
			{
				return i;
			}
		}
		return keyCount;
	}

};

class BTree
{
public:
	BTree();
	~BTree();

	vector<BTreeData> getRange(BTreeKeyRange range);
	void put(int key ,int value);
	int get(int key);

	void printBTree(); // Just for debug
private:
	BTreeNode *root;

	void splitNode(BTreeNode *nodeToSplit);
	void insertNode(int key, int value);
	void recursiveInsertNode(BTreeNode *node, int key, int value);

	BTreeData *searchDataWithKey(BTreeNode *node, int key);
    void layerTraverse(vector<BTreeData> &result, BTreeKeyRange range);
};

/************** Public API **************/
BTree::BTree():root(new BTreeNode())
{}

BTree::~BTree()
{
	if (root == NULL) return;

	delete root; 
	root = NULL;
}

vector<BTreeData> BTree::getRange(BTreeKeyRange range)
{
	vector<BTreeData> result;
	layerTraverse(result, range);
	return result;
}

void BTree::put(int key, int value)
{
	BTreeData *existData = searchDataWithKey(root, key);
	if (existData != NULL) existData->data = value;
    else insertNode(key, value);
}

int BTree::get(int key)
{
	BTreeData *existData = searchDataWithKey(root, key);
	if (existData != NULL) return existData->data;

	return BTreeErrorCodeKeyNotFound;
}

void BTree::printBTree()
{
    if (root == NULL) return;
    
    int layer = 0;
    BTreeNode *nullNode = new BTreeNode();
    
    queue<BTreeNode *> nodeQueue;
    nodeQueue.push(root);
    nodeQueue.push(nullNode);
    
    cout << "Layer " << 0 << ":" << " ";
    
    while (!nodeQueue.empty()) {
        BTreeNode *head = nodeQueue.front();
        if (head == nullNode)
        {
            cout << endl;
            layer++;
            nodeQueue.pop();
            
            if (!nodeQueue.empty())
            {
                cout << "Layer " << layer << ":" << " ";
                nodeQueue.push(nullNode);
            }
            continue;
        }
        
        if (!head->isLeaf)
        {
            for (int i = 0; i < head->keyCount + 1; i++)
            {
                nodeQueue.push(head->childs[i]);
            }
        }
       
        for (int i = 0; i < head->keyCount; i++)
        {
            cout << head->indexes[i]->key << " ";
        }
        cout << "| ";
        
        nodeQueue.pop();
    }
    
    delete nullNode;
}
/************** End of Public API **************/


/************** Private API **************/
void BTree::splitNode(BTreeNode *nodeToSplit)
{
	BTreeNode *newNode = new BTreeNode();
	newNode->isLeaf = nodeToSplit->isLeaf;
	newNode->keyCount = BTreeDegree - 1;

	// Copy Indexed Data from right half of NodeToSplit
	for (int i = 0; i < newNode->keyCount; i++)
	{
		newNode->indexes[i] = nodeToSplit->indexes[i + BTreeDegree];
	}

	if (nodeToSplit->isLeaf == false)
	{
		for (int i = 0; i < newNode->keyCount + 1; i++)
		{
            newNode->addChild(nodeToSplit->childs[i + BTreeDegree], i);
		}
	}

	BTreeData *dataToLift = nodeToSplit->indexes[BTreeDegree - 1];
	nodeToSplit->keyCount = BTreeDegree - 1;
	BTreeNode *parentNode = nodeToSplit->parent;

	int insertPos = 0;
	for (int i = 0; i < parentNode->keyCount; i++)
	{
		int key = parentNode->indexes[i]->key;
		if (dataToLift->key < key) break;

		insertPos++;
	}

	// Move Data after pos by 1 offset
	for (int i = parentNode->keyCount - 1; i >= insertPos; i--)
	{
		parentNode->indexes[i + 1] = parentNode->indexes[i];
	}

	// Move Pointer after post by 1 offset
	for (int i = parentNode->keyCount; i > insertPos; i--)
	{
		parentNode->childs[i + 1] = parentNode->childs[i];
	}

	parentNode->indexes[insertPos] = dataToLift;
	parentNode->addChild(newNode, insertPos + 1);
	parentNode->keyCount += 1;
}

BTreeData* BTree::searchDataWithKey(BTreeNode *start, int key)
{
	if (start == NULL) return NULL;

	bool isEqual = false;
	int offset = start->findDataOffset(key, isEqual);

	if (isEqual)
	{
		return start->indexes[offset];
	} 
	else if (start->isLeaf)
	{
		return NULL;
	}
	else
	{
		return searchDataWithKey(start->childs[offset], key);
	}
}

void BTree::layerTraverse(vector<BTreeData> &result, BTreeKeyRange range)
{
    if (root == NULL) return;
    
    queue<BTreeNode *> nodeQueue;
    
    nodeQueue.push(root);
    
    while (!nodeQueue.empty())
    {
        BTreeNode *head = nodeQueue.front();
        
        for (int i = 0; i < head->keyCount; i++) {
            int key = head->indexes[i]->key;
            if (range.contains(key))
            {
                result.push_back(head->indexes[i]->clone());
            }
        }
        
        if (head->isLeaf == false)
        {
            for (int i = 0; i < head->keyCount + 1; i++)
            {
                nodeQueue.push(head->childs[i]);
            }
        }
        
        nodeQueue.pop();
    }
}

void BTree::insertNode(int key, int value)
{
	if (root == NULL) return;

	if (root && root->keyCount >= 2 * BTreeDegree - 1)
	{
		BTreeNode *newRoot = new BTreeNode();
		newRoot->keyCount = 0;
		newRoot->addChild(root, 0);
		splitNode(root);
		root = newRoot;
	}

	recursiveInsertNode(root, key, value);
}

void BTree::recursiveInsertNode(BTreeNode *node ,int key, int value)
{
    // We can assure that the node for insert must be not full with key
	if (node->isLeaf == true)
	{
		int insertPos = 0;
		for (int i = 0; i < node->keyCount; i++)
		{
			int k = node->indexes[i]->key;
			if (key < k) break;
			insertPos ++;
		}

		// Move Data after pos by 1 offset
		for (int i = node->keyCount - 1; i >= insertPos; i--)
		{
			node->indexes[i + 1] = node->indexes[i];
		}

		BTreeData *newData = new BTreeData(key, value);
		node->indexes[insertPos] = newData;
		node->keyCount += 1;
	}
	else
	{
		int lookPos = 0;
		for (int i = 0; i < node->keyCount; i++)
		{
			int k = node->indexes[i]->key;
			if (key < k) break;
			lookPos ++;
		}

		BTreeNode *nextLookUpNode = node->childs[lookPos];
		if (nextLookUpNode->keyCount == 2 * BTreeDegree - 1)
		{
			splitNode(nextLookUpNode);
			if (key > node->indexes[lookPos]->key)
			{
				nextLookUpNode = node->childs[lookPos + 1];
			}
		}

		recursiveInsertNode(nextLookUpNode, key, value);
	}
}
/************** End of Private API **************/

int main()
{
    BTree *tree = new BTree();
    tree->put(3, 7);
    tree->put(1, 4);
    tree->put(5, 2);
    tree->put(4, 2);
    tree->put(0, 8);
    tree->put(9, 4);
    tree->put(10, 4);
    tree->put(11, 2);
    tree->put(12, 2);
    tree->put(13, 6);
    tree->put(14, 20);
    tree->put(18, 4);
    tree->put(17, 3);
    tree->printBTree();
    
    cout << "Get is " << tree->get(9) << endl;
    
    
    tree->put(9, 5);
    vector<BTreeData> result = tree->getRange(BTreeKeyRange(0, 9));
    
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i].key << " " << result[i].data << endl;
    }
    
    delete tree;
    return 0;
}