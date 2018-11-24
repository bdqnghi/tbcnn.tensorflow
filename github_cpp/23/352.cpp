#include "stdafx.h"
#include "iostream"
#include "vector"
#include "string"
#include "map"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <sstream>
#include <iomanip>

using namespace std;
//http://www.cs.umd.edu/~meesh/420/Notes/MountNotes/lecture11-skiplist.pdf

class SkipListNode{
public:
	int data;
	SkipListNode *backward;
	vector<SkipListNode*> forward;

	SkipListNode(){}

	SkipListNode(int d, int level){
		data=d;
		forward=vector<SkipListNode*>(level+1, NULL);
	}
};

class SkipList{
public:
	int maxLevel;
	SkipListNode* header;

	SkipList(int maxLev){
		maxLevel=maxLev;
		header=new SkipListNode(NULL, maxLevel);

		SkipListNode *sentinel =new SkipListNode(INT_MAX, maxLevel);
		for(int i=0;i<=maxLevel;i++)
		{
			header->forward[i]=sentinel;
		}
		sentinel->backward=header;
	}

	int find(int key)
	{
		SkipListNode* current=header;

		for(int i=maxLevel;i>=0;i--)
		{
			SkipListNode *next=current->forward[i];
			while(next->data<key)
			{
				current=next;
				next=current->forward[i];
			}
		}

		current=current->forward[0];

		if(current->data==key)return current->data;
		else return NULL;
	}

	void insert(int key)
	{
		SkipListNode* current=header;
		for(int i=maxLevel;i>=0;i--)
		{
			SkipListNode *next=current->forward[i];
			while(next->data<key)
			{
				current=next;
				next=current->forward[i];
			}
		}

		SkipListNode* forwardNode=current->forward[0];
		if(forwardNode->data==key)return;

		SkipListNode* newNode=new SkipListNode(key, 0);
		current->forward[0]=newNode;
		newNode->forward[0]=forwardNode;
		forwardNode->backward=newNode;
		newNode->backward=current;

		SkipListNode* backwardNode=current;

		srand(time(NULL));
		for(int i=1;i<=maxLevel;i++)
		{
			if(rand()%10<5)
			{
				while(forwardNode->forward.size()<i+1)
					forwardNode=forwardNode->forward[forwardNode->forward.size()-1];
				newNode->forward.push_back(forwardNode);
				while(backwardNode&&backwardNode->forward.size()<i+1)
				{
					backwardNode=backwardNode->backward;
				}
				backwardNode->forward[i]=newNode;
			}
			else
			{
				break;
			}
		}
	}

	void erase(int key)
	{
		SkipListNode* current=header;
		for(int i=maxLevel;i>=0;i--)
		{
			SkipListNode *next=current->forward[i];
			while(next->data<key)
			{
				current=next;
				next=current->forward[i];
			}
		}

		SkipListNode* eraseNode=current->forward[0];
		if(eraseNode->data!=key)return;
		SkipListNode* backwardNode=current;
		SkipListNode* forwardNode=eraseNode->forward[0];
		forwardNode->backward=backwardNode;

		while(true)
		{
			for(int i=min(backwardNode->forward.size()-1, eraseNode->forward.size()-1);i>=0;i--)
			{
				if(backwardNode->forward[i]==eraseNode)
					backwardNode->forward[i]=eraseNode->forward[i];
			}
			if(backwardNode->forward.size()>=eraseNode->forward.size())break;
			backwardNode=backwardNode->backward;
		}
		delete eraseNode;
	}

	void print()
	{
		for(int i=maxLevel;i>=0;i--)
		{
			SkipListNode *current=header;
			while(current->forward[0])
			{
				if(current->forward.size()>=i+1)
					cout<<setw(4)<<setfill('-')<<current->data<<"-->";
				else
					cout<<"-------";
				current=current->forward[0];
			}
			cout<<endl;
		}
		cout<<endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	SkipList *skl=new SkipList(4);
	srand(time(NULL));
	for(int i=0;i<10;i++)
	{
		int tmp=(i+rand()%31)%17;
		skl->insert(tmp);
		cout<<skl->find(tmp)<<endl;
		skl->print();
		if(tmp%7<=2)
		{
			skl->erase(tmp);
			skl->print();
		}
	}
	return 0;
}


