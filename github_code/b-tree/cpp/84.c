#include "btree.h"
#include <iostream>

//implementation of class InternalTreeNode-----------------------------
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
        //结点未满
        this->addChild(i + 1,tmp);
        return this;
    }
    
    //结点已满,当前结点分裂
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

/**
 * 删除key
 * 说明:本质是删除叶子结点中的键值对，所以存在以下情况:
 * 	1) 叶子结点被清空，释放叶子结点，同时删除其在父结点中的引用，并引出以下两个问题
 * 	    1))父结点的子树数不满足B树的要求，需要进行合并操作
 *	    2))父结点的子树数满足B树的要求 
 * 	2) 叶子结点未被清空，不作任何处理
 * 返回值:
 * 	非NULL: 该子结点不满足B树结点要求，需要进行合并操作
 * 	NULL: 子结点満足B树结点要求
 **/
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
    
    //试图从兄弟结点中获取一个
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
	//可以了从兄弟结点中获取一个子结点
	int l = i + 1;
	
	InternalTreeNode* t = (InternalTreeNode*)p;
	do
	{
	    q = (InternalTreeNode*)child[l];
	    InternalTreeNode* s = (InternalTreeNode*)q->child[0];
	    t->addChild(t->childCount,s);
	    //调整兄弟结点
	    q->delChild(0);
	    if(l > 0)
		keys[l - 1] = child[l]->getMinKey();
	    t = q;
	    ++l;
	    
	}while(q->childCount < minChildCount);
	
	return NULL;
    }
    
    //未找到有效的兄弟结点，进行结点合并
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
/**
 * 返回值: 返回合并后的结点
 */
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
    
    //std::cout << "max: " << max << " min: " << min << std::endl;
    
    InternalTreeNode *s = (InternalTreeNode*) child[max];
    InternalTreeNode *t = (InternalTreeNode*) child[min];
    
    for(int i = 0; i < s->childCount; i++)
    {
	t->addChild(t->childCount,s->child[i]);
    }
    
    delChild(max);
    //std::cout << "delete: " << s->keys[0] << std::endl;
    delete s;
    
    //std::cout << "merge finished -------------- " << std::endl;
    
    return t;
}

/**
 * 删除子结点
 */
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

/**
 * 在位置p处分割结点
 * */
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
/**
 * 返回子树的最小键值
 * 
 */
int InternalTreeNode::getMinKey()
{
    if(isLeaf())
	return keys[0];
    else
	return child[0]->getMinKey();
}
/**
 * 返回子树的最大键值
 * 
 */
int InternalTreeNode::getMaxKey()
{
    if(isLeaf())
	return keys[keyCount - 1];
    else
	return child[childCount - 1]->getMaxKey();
}
/**
 *遍历结点
 */
void InternalTreeNode::visit()
{
    for(int i = 0; i < keyCount; i++)
	std::cout << keys[i] << " ";
    std::cout << std::endl;
    for(int i = 0;  i < childCount; i++)
	child[i]->visit();
}

////////////////////////////////////////////////////////////////////
//the implementation of class LeafTreeNode
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
	return this;  //the record already exists
    if(keyCount < (order - 1))
    {
	//the current leaf node is still not full
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
    
    //the current leaf node is full, a new leaf node must be created
    LeafTreeNode *p = new LeafTreeNode(order);
    p->keys[p->keyCount] = key;
    p->values[p->keyCount++] = value;
    
    return p;
}
/**
 * 从叶子结点中删除(K,V)
 * 返回值
 * 	NULL: 结点非空
 * 	this: 结点为空
 */
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
//////////////////////////////////////////////////////////////////////////////
//the implemetation of class BTree
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
