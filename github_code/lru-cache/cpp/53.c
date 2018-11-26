#include"leetcode.h"
int LRUCache::get(int key)
{
	lruIterator = lruMap.find(key);
	if (lruIterator != lruMap.end())
	{
		ValueNode* firstNode = lruIterator->second;
		if (head != firstNode)
		{
			if (firstNode == tail)
			{
				ValueNode * q = tail;
				q->pre->next = NULL;
				tail = q->pre;
				firstNode->next = head;
				head->pre = firstNode;
				firstNode->pre = NULL;
				head = firstNode;
			}
			else
			{
				firstNode->pre->next = firstNode->next;
				firstNode->next->pre = firstNode->pre;
				firstNode->next = head;
				head->pre = firstNode;
				firstNode->pre = NULL;
				head = firstNode;


			}
		}
		return firstNode->value;
	}
	return -1;
}
LRUCache::ValueNode* LRUCache::addNode(int key,int value)
{
	ValueNode* node = (ValueNode*)malloc(sizeof(ValueNode));
	node->key = key;
	node->value = value;
	node->pre = NULL;
	node->next = NULL;
	return node;
}
void LRUCache::set(int key, int value)
{
	if (get(key) != -1)
	{
		head->value = value;
	}
	else
	{
		ValueNode* insertNode = addNode(key,value);
		if (lruMap.size() < size)
		{
			if (head == NULL)
			{
				head = insertNode;
				tail = insertNode;
			}
			else
			{
				insertNode->next = head;
				head->pre = insertNode;
				head = insertNode;
			}
		}
		else
		{
			ValueNode* q = tail;
			lruMap.erase(tail->key);
			tail = q->pre;
			delete q;
			if (tail == NULL)  //size==1
			{
				tail = head;
			}
			insertNode->next = head;
			head->pre = insertNode;
			head = insertNode;
		}
		lruMap.insert(make_pair(key, insertNode));
	}

}