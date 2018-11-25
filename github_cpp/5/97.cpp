#include <iostream>  
using namespace std;
struct node
{
	int data;
	node *next;
};
node* sorting(node **head,node *ptr);
node* push(node **head,int val)
{
	node *ptr=new node;
	ptr->data=val;
	ptr->next=*head;
	*head=ptr;
	return *head;
}
void insertsort(node **head)
{
	node *ptr1=NULL;
	node *ptr2=*head;
	while(ptr2!=NULL)
	{
		node *ptr3=ptr2->next;
		sorting(&ptr1,ptr2);
		ptr2=ptr3;
	}
	*head=ptr1;
}
node* sorting(node **head,node *ptr)
{
	node *ptr1=new node;
	if(*head!=NULL && (*head)->data!=ptr->data)
	{
		ptr->next=*head;
		(*head)->next=ptr;
	}
	else 
	{
		ptr=*head;
		while(ptr1->next!=NULL && ptr1->next->data < ptr->data)
		{
			ptr1=ptr1->next;
		}
		ptr->next=ptr1->next;
		ptr1->next=ptr;
	}
	return ptr;
}
void display(node *n)
{
	while(n!=NULL)
	{
		cout<<n->data<<" ";
		n=n->next;
	}
	cout<<endl;
}
int main()
{
	struct node* head=NULL;
	push(&head,20);
	push(&head,2);
	push(&head,10);
	push(&head,3);
	push(&head,1);
	insertsort(&head);
	display(head);
	return 0;
}