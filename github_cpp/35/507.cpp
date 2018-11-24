/*
 * linked-list.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: viral
 */

#include "iostream"
using namespace std;
struct node
{
	int data;
	struct node* link;
};

struct node* head;
int getnode(int x)
{
	node* mynode=new node();
	mynode->data=x;
	mynode->link=NULL;
	mynode->link=head;
	head=mynode;
	return 0;
}
int print()
{
	node* temp;
	while(temp!=NULL)
	{
		cout<<temp->data;
		temp=temp->link;
	}
	return 0;
}
int main()
{
	int x,n;
	head= NULL;
	cout<<"how many numbers";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"enter the number";
		cin>>x;
		getnode(x);
		print();
	}
}
