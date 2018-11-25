#include "btree.h"
#include <iostream>


InternalTreeNode::InternalTreeNode(int order)
{
    this->order = order;
    this->keyCount = 0;
    this->childCount = 0;
    this->keys = new int[order - 1];
    this->child = new TreeNode*[order];
    
    for(int i = 0; i < order; i++)
	    this->child[i] = (TreeNode*)NULL;
    for(int i = 0; i < order - 1; i++)
	    this->keys[i] = -1;
}
InternalTreeNode::~InternalTreeNode()
{
    this->order = 0;
    this->keyCount = 0;
    if(this->keys)
        delete[] this->keys;
    this->keys = NULL;
    
    if(this->child)
        delete[] this->child;
    this->child = NULL;
}
int InternalTreeNode::search(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] > key)
    	    break;
    }
    return child[i]->search(key);
}

TreeNode* InternalTreeNode::insert(int key, int value)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] == value)
            return NULL;
        if(keys[i] > key)
            break;
    }
    TreeNode* tmp = child[i]->insert(key,value);
    
    if(tmp == child[i])
	return this;
    
    if(childCount < order)
    {
        
        this->addChild(i + 1,tmp);
        return this;
    }
    
    
    int half = (order >> 1);
    if(order % 2)
	half = half + 1;
    int cut_point = half;
    if((i + 1) < half)
	--cut_point;
    TreeNode* tmp_2 = split(cut_point);
    if(cut_point < half)
	addChild(i + 1,tmp);
    else
	tmp_2->addChild((i + 1) - cut_point,tmp);
    if(((InternalTreeNode*)tmp_2)->childCount == 1)
    {
	tmp_2->addChild(child[childCount - 1]);
	child[childCount - 1] = NULL;
	--childCount;
	keys[keyCount - 1] = -1;
	--keyCount;
    }
    return tmp_2;
}
void InternalTreeNode::addChild(int p,TreeNode* t)
{
    int min = t->getMinKey();
    
    if(childCount > 0)
    {
	for(int j = keyCount - 1; j >= p - 1 && j >= 0; j--)
	{
	    keys[j + 1] = keys[j];
	}
	if(keyCount > 0)
	    keys[p - 1] = min;
	else
	    keys[0] = min;
	++keyCount;
    }
    
    for(int j = childCount - 1; j >= p; j--)
    {
	child[j + 1] = child[j];
    }
    child[p] = t;
    ++childCount;
}
void InternalTreeNode::addChild(TreeNode *p)
{
    int min = p->getMinKey();
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(keys[i] >= min)
	    break;
    }
    addChild(i,p);
}


TreeNode* InternalTreeNode::del(int key)
{
    int half = (order >> 1);
    if(order % 2)
	half = half + 1;
    int minChildCount = half;
    
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(keys[i] == key)
	{
	    i++;
	    break;
	}
	else if(keys[i] > key)
	{
	    break;
	}
    }
    
    TreeNode* p = child[i]->del(key);
    if(p && p->isLeaf())
    {
	delete p;
	delChild(i);
	if(childCount < minChildCount)
	    return this;
	else
	{
	    return NULL;
	}
    }
    else if(!p)
    {
	if(i > 0)
	    keys[i - 1] = child[i]->getMinKey();
	return NULL;
    }
    
    
    InternalTreeNode *q = NULL;
    int j = 0;
    for(j = i + 1; j < childCount; j++)
    {
	q = (InternalTreeNode *)child[j];
	if(q->childCount > minChildCount)
	    break;
    }
    
    if(j < childCount)
    {
	
	int l = i + 1;
	
	InternalTreeNode* t = (InternalTreeNode*)p;
	do
	{
	    q = (InternalTreeNode*)child[l];
	    InternalTreeNode* s = (InternalTreeNode*)q->child[0];
	    t->addChild(t->childCount,s);
	    
	    q->delChild(0);
	    if(l > 0)
		keys[l - 1] = child[l]->getMinKey();
	    t = q;
	    ++l;
	    
	}while(q->childCount < minChildCount);
	
	return NULL;
    }
    
    
    j = 0;
    if(i == 0)
	j = 1;
    else if(i == (childCount - 1))
	j = i - 1;
    else
	j = i + 1;
    
    merge(i,j);
    
    if(childCount < minChildCount)
	return this;
    keys[i - 1] = p->getMinKey();
    return NULL;
}

TreeNode *InternalTreeNode::merge(int p,int q)
{
    int min = 0,max = 0;
    if(p == q)
	return NULL;
    
    if(p > q)
    {
	max = p;
	min = q;
    }
    else
    {
	max = q;
	min = p;
    }
    
    
    
    InternalTreeNode *s = (InternalTreeNode*) child[max];
    InternalTreeNode *t = (InternalTreeNode*) child[min];
    
    for(int i = 0; i < s->childCount; i++)
    {
	t->addChild(t->childCount,s->child[i]);
    }
    
    delChild(max);
    
    delete s;
    
    
    
    return t;
}


void InternalTreeNode::delChild(int p)
{
    for(int i = p; i < childCount - 1; i++)
	child[i] = child[i + 1];
    --childCount;
    child[childCount] = NULL;
    
    for(int i = p - 1; i < keyCount - 1; i++)
	keys[i] = keys[i + 1];
    --keyCount;
    keys[keyCount] = -1;
}
void InternalTreeNode::delChild(TreeNode *p)
{
    int i = 0;
    for(i = 0; i < childCount; i++)
	if(child[i] == p)
	    break;
    if(i < childCount)
	delChild(i);
}


TreeNode* InternalTreeNode::split(int p)
{
    InternalTreeNode* q = new InternalTreeNode(order);
    int cc = childCount;
    int kc = keyCount;
    for(int i = p; i < cc; i++)
    {
	q->child[q->childCount++] = child[i];
	child[i] = NULL;
	--childCount;
	
	if(i < kc)
	{
	    q->keys[q->keyCount++] = keys[i];
	    keys[i] = -1;
	    --keyCount;
	}
    }
    keys[p - 1] = -1;
    --keyCount;
    return q;
}

int InternalTreeNode::getMinKey()
{
    if(isLeaf())
	return keys[0];
    else
	return child[0]->getMinKey();
}

int InternalTreeNode::getMaxKey()
{
    if(isLeaf())
	return keys[keyCount - 1];
    else
	return child[childCount - 1]->getMaxKey();
}

void InternalTreeNode::visit()
{
    for(int i = 0; i < keyCount; i++)
	std::cout << keys[i] << " ";
    std::cout << std::endl;
    for(int i = 0;  i < childCount; i++)
	child[i]->visit();
}



LeafTreeNode::LeafTreeNode(int order)
{
    this->order = order;
    keys = new int[order - 1];
    keyCount = 0;
    for(int i = 0; i < order - 1;i++)
    {
        keys[i] = -1;
    }
    
    values = new int[order - 1];
    for(int i = 0; i < order - 1; i++)
    {
	values[i] = -1;
    }
}
LeafTreeNode::~LeafTreeNode()
{
    if(keys)
	delete[] keys;
    keys = NULL;
    
    if(values)
	delete[] values;
    values = NULL;
}
int LeafTreeNode::search(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
        if(keys[i] == key)
	    return values[i];
        if(keys[i] > key)
	    return -1;
    }
    return -1;
}
TreeNode* LeafTreeNode::insert(int key,int value)
{
    int v = search(key);
    if(v >= 0)
	return this;  
    if(keyCount < (order - 1))
    {
	
	int j = 0;
	for(j = 0;j < keyCount; j++)
	    if(keys[j] > key)
		break;
	for(int i = keyCount; i > j; i--)
	{
	    keys[i] = keys[i - 1];
	    values[i] = values[i - 1];
	}
	keys[j] = key;
	values[j] = value;
	keyCount++;
	
	return this;
    }
    
    
    LeafTreeNode *p = new LeafTreeNode(order);
    p->keys[p->keyCount] = key;
    p->values[p->keyCount++] = value;
    
    return p;
}

TreeNode* LeafTreeNode::del(int key)
{
    int i = 0;
    for(i = 0; i < keyCount; i++)
    {
	if(key == keys[i])
	    break;
    }
    if(i == keyCount)
	return NULL;
    
    for(int j = i; j < keyCount - 1; j++)
    {
	keys[j] = keys[j + 1];
	values[j] = keys[j + 1];
    }
    keyCount--;
    
    if(keyCount == 0)
	return this;
    return NULL;
}
void LeafTreeNode::visit()
{
    for(int i = 0; i < keyCount; i++)
	std::cout << "(" << keys[i] << ":" << values[i] << ")" << " ";

    std::cout << std::endl;
}
int LeafTreeNode::getMaxKey()
{
    return keys[keyCount - 1];
}
int LeafTreeNode::getMinKey()
{
    return keys[0];
}


BTree::BTree(int order)
{
    this->order = order;
    root = NULL;
}
BTree::~BTree()
{
    
}
int BTree::search(int key)
{
    if(root)
	return root->search(key);
    return -1;
}
bool BTree::insert(int key,int value)
{
    if(!root)
	root = new LeafTreeNode(order);
    TreeNode *p = root->insert(key,value);
    if(p != root)
    {
	TreeNode *q = new InternalTreeNode(order);
	q->addChild(0,root);
	q->addChild(1,p);
	root = q;
    }
    return true;
}
bool BTree::del(int key)
{
    if(root == NULL)
	return false;
    TreeNode *p = root->del(key);
    if(p && !p->isLeaf())
    {
	if(((InternalTreeNode*)p)->getChildCount() == 1)
	{
	    root = ((InternalTreeNode*)p)->getChild()[0];
	}
    }
    else if(p  && p->isLeaf())
    {
	delete p;
	root = NULL;
    }
    return true;
}
void BTree::visit()
{
    root->visit();
}
