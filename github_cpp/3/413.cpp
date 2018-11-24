#include <iostream>
#include <map>
using namespace std;

class Node
{
	Node* prev;
	Node* next;
	int key,val;
public:
	Node(int key,int val)
	{
		this->key=key;
		this->val=val;	
		prev=NULL;
		next=NULL;
	}
};

class LRUCache
{
	Node* head;
	Node* tail;
	map<int,Node*> my_map;
	int MAX_SIZE;
	int size;
	void evict()
	{
		while(size>MAX_SIZE)
		{
			if (!tail)
			{
				return;
			}

			Node* prev=tail->prev;
			if (prev)
			{
				tail->prev->next=NULL;
			}

			map<int,Node*> iterator::it;
			for (int it =my_map.begin();it!=my_map.end(); ++it)
			{
				if (it->second==tail)
				{
					my_map.erase(it->first);
					break;
				}
			}

			delete tail;
			tail=prev;
			size--;

		}	

	}
	void moveToFront(Node* node)
	{
		//already in the beginning
		if (head==node || head==tail)
		{
			return;
		}
		//node at the end
		if (node==tail)
		{
			 tail=node->prev;
		}

		Node* prev=node->prev;
		if (prev)
		{
			prev->next=node->next;
		}

		if (node->next)
		{
			node->next->prev=prev;
		}

		node->prev=NULL;
		head->prev=node;
		node->next=head;
		head=node;
		tail->next=NULL;

	}
public:
	LRUCache(int MAX_SIZE)
	{
		this->MAX_SIZE=MAX_SIZE;
		size=0;
		head=NULL;
		tail=NULL;
	}

	void set(int key,int val)
	{
		if (my_map.count(key)!=0)
		{
			Node* node=my_map[key];
			node->val=val;
		}
		else
		{
			Node* node=new Node(key,val);
			if (head)
			{
				head->prev=node;
				node->prev=NULL;
				node->next=head;
				head=node;

			}
			else
			{
				head=node;
				tail=node;
			}

			size++;
			if (size>MAX_SIZE)
			{
				evict();
			}	
		}	
	}

	int get(int k)
	{
		if (my_map.count(k)==0)
		{
			return -1;
		}

		Node* node=my_map[k];
		moveToFront(node);
		return node->val;
	}
	
};