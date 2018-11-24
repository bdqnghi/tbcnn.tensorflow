/*
    HUFFMAN coding Problem.
    
    Author: Kunaal Jain
    Email: kunaalus@gmail.com

*/

#include<bits/stdc++.h>
using namespace std;

struct node{
	string value;
	int probabilty;
	node *leftchild;
	node *rightchild;
	node *parent;
};

struct DereferenceCompareNode
{
    bool operator()(const node* lhs, const node* rhs) const
    {
        return lhs->probabilty > rhs->probabilty;
    }
};


void traversal(node *a,string x)
{
	if((a->leftchild)==NULL) { cout<<a->value<<" "<<x<<endl; }
	else { traversal(a->leftchild,x+"0"); traversal(a->rightchild,x+"1"); }
	return;
}

int main()
{
	node *x;
	node *y,*z;
	string value;
	priority_queue<node*,vector<node*>,DereferenceCompareNode> q1;
	int i,n,temp;
	cin>>n;
	for(i=0;i<n;i++) 
	{		
		cin>>temp;
		cin>>value;
		x = new node;
		x->probabilty=temp;
		x->leftchild=NULL;
		x->rightchild=NULL;
		x->parent=NULL;
		x->value=value;
		q1.push(x);
	}
	while(q1.size()>1)
	{
		y=q1.top();
		q1.pop();
		z=q1.top();
		q1.pop();
		x=new node;
		x->probabilty=y->probabilty+z->probabilty;
		x->leftchild=y;
		x->rightchild=z;
		x->parent=NULL;
		q1.push(x);
	}
	string a="";

	traversal(x,a);
	return 0;
}
