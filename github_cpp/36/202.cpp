//Saeid Ghafouri
//610390139
#include "stdafx.h"
#include "b-tree.h"
#include<iostream>
using namespace std;

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
 
    keys = new mystring[2*t-1];
    C = new BTreeNode *[2*t];
 	n = 0;
}

void BTreeNode::traverse()
{

	int i;
    for (i = 0; i < n; i++)
    {
            if (leaf == false)
            C[i]->traverse();
		cout << " "<< keys[i].s;
    }
 
    
    if (leaf == false)
        C[i]->traverse();
}
 BTreeNode *BTreeNode::search(mystring k)
{
     int i = 0;
    while (i < n && k > keys[i])
        i++;
     if (keys[i] == k)
        return this;
     if (leaf == true)
        return NULL;
     return C[i]->search(k);
}

mystring BTreeNode::linearsearch(mystring s)
{
	for (int i=0;i<n;i++)
	{
		if(keys[i] == s)
			return keys[i];
	}
}
void BTree::insert(mystring k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k; 
        root->n = 1; 
    }
    else 
    {
                if (root->n == 2*t-1)
        {
                    BTreeNode *s = new BTreeNode(t, false);
 
        
            s->C[0] = root;
 
                    s->splitChild(0, root);
 
                    int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
             root = s;
        }
        else
			root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(mystring k)
{
    int i = n-1;
 
    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else 
    {
		while (i >= 0 && keys[i] > k)
            i--;
         if (C[i+1]->n == 2*t-1)
        {
             splitChild(i+1, C[i+1]);
 
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}
 void BTreeNode::splitChild(int i, BTreeNode *y)
{
     BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
 
    y->n = t - 1;
 
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    keys[i] = y->keys[t-1];
    n = n + 1;
}


mystring::mystring()
{}
mystring::mystring(string input)
{
	sz=input;
}

bool operator<(const mystring s1,const mystring s2)
{
	int i=0;
	while(i<s1.s.size() && i<s2.s.size())
	{
		if(s1.s[i]<s2.s[i]) return true;
		if(s1.s[i]>s2.s[i]) return false;
		if(s1.s[i]==s2.s[i]) i++;
	}
	return false;
}
bool operator>(const mystring s1,const mystring s2)
{
	int i=0;
	while(i<s1.s.size() && i<s2.s.size())
	{
		if(s1.s[i]>s2.s[i]) return true;
		if(s1.s[i]<s2.s[i]) return false;
		if(s1.s[i]==s2.s[i]) i++;
	}
	return false;
}
bool operator==(const mystring s1,const mystring s2)
{
	int i=0;
	if(s1.s.size()!=s2.s.size()) return false;
	else {
		for(int i=0;i<s1.s.size();i++)
		{
			if(s1.s[i]!=s2.s[i]) return false;
		}
		return true;
	}
	return true;
}