#include <iostream>
using namespace std;

class node{
public:
	int info;
	node *next;
};

class LinkedList{
	node *head;
public:
	LinkedList(){
		head=NULL;
	}

	int isEmpty();
	void addBeg(int);
	void addEnd(int);
	void addAfter(int, int);
	void delBeg();
	void delEnd();
	void delGiven(int);
	void delList();
	node* searchElement(int);
	void traverse();
	void traverseReverseOrder();
    void traverseReverse(node *);
    int lengthList();
    void swapNodes(int, int);
    int getNthNode(int);
    int getNthNodeFromEnd(int);
    int getMiddle();
    void reverseList();
};

int LinkedList::isEmpty(){
	if(head==NULL)
		return 1;
	else 
		return 0;
}

void LinkedList::addBeg(int item){
	node *ptr;
	ptr=new node;
	ptr->info=item;
	if(isEmpty())
		ptr->next=NULL;
	else
		ptr->next=head;
	head=ptr;
}

void LinkedList::addEnd(int item){
	node *ptr,*loc;
	ptr=new node;
	ptr->info=item;
	loc=head;
	while(loc->next!=NULL){
		loc=loc->next;
	}
	ptr->next=NULL;
	loc->next=ptr;
}

void LinkedList::addAfter(int item, int after){
	node *ptr,*loc;
	ptr=new node;
	while(loc!=NULL){
		if(after==loc->info)
			break;
		loc=loc->next;
	} 

	if(loc==NULL)
		return; 
	ptr->info=item;
	ptr->next=loc->next;
	loc->next=ptr;
}

void LinkedList::delBeg(){
	node *ptr;
	if(isEmpty()) //list initially empty 
		return;
	ptr=head;
	head=head->next;
	delete ptr;

}

void LinkedList::delEnd(){
	node *ptr,*loc;
	if(isEmpty()) //list initially empty
		return;
	loc=head;
	while((loc->next)->next!=NULL)
		loc=loc->next;
	ptr=loc->next;
	loc->next=NULL;
	delete ptr;
}

void LinkedList::delGiven(int item){
	node *ptr,*loc;
	if(isEmpty())
		return;
	loc=head;
	while((loc->next)->info !=item){
		loc=loc->next;
	}
	ptr=loc->next;
	loc->next=ptr->next;
	delete ptr;
}

void LinkedList::delList(){
	if(isEmpty())
		return;
	node *ptr;
	while(head!=NULL){
		ptr=head;
		head=head->next;
		delete ptr; 
	}
}

node* LinkedList::searchElement(int item){
	cout << "SEARCHING STARTED" << endl;
	node *ptr,*loc;
	ptr=head;
	while(ptr->next!=NULL) {
		if(item==ptr->info) {
			loc=ptr;
			cout << "SEARCHING COMPLETED" << endl;
			return loc;
		}
	
		ptr=ptr->next;
		
	}
	
	cout << "SEARCHING COMPLETED" << endl;
	return NULL;
}


void LinkedList::traverse(){
	node *ptr;
	ptr=head;
	while(ptr!=NULL){
		cout<<ptr->info<<"->";
		ptr=ptr->next;
	}
	cout<<"\n";
}

void LinkedList::traverseReverseOrder(){
	traverseReverse(head);
}

void LinkedList::traverseReverse(node *ptr){
	if(ptr->next!=NULL)
		traverseReverse(ptr->next);
	cout<<ptr->info<<"->";
}

int LinkedList::lengthList(){
	node *ptr;
	int count=0;
	if(isEmpty())
		return count;
	ptr=head;
	while(ptr!=NULL){
		ptr=ptr->next;
		count++;
	}
	return count;
}

void LinkedList::swapNodes(int item1, int item2){
	node *prev1,*prev2,*curr1,*curr2,*temp;
	prev1=prev2=NULL;
	curr1=curr2=head;
	while(curr1->info != item1){
		prev1=curr1;
		curr1=curr1->next;
	}
	while(curr2->info != item2){
		prev2=curr2;
		curr2=curr2->next;
	}
	//if either of the items are not found
	if(curr1==NULL || curr2==NULL)
		return;

	// If x is not head of linked list
	if (prev1 != NULL)
       prev1->next = curr2;
    else  //make x as the head 
       head = curr2;  

   // If y is not head of linked list
	if (prev2 != NULL)
       prev2->next = curr1;
    else //make y as the head
       head = curr1;

	temp=curr1->next;
	curr1->next=curr2->next;
	curr2->next=temp;
}

int LinkedList::getNthNode(int index){
	node *ptr;
	if(isEmpty())
		return -1;
	ptr=head;
	int count=0;
	while(ptr!=NULL){
		if(count==index)
			return ptr->info;
		ptr=ptr->next;
		count++;
	}
	return -1;
}

int LinkedList::getNthNodeFromEnd(int index){
	node *ptr;
	if(isEmpty())
		return -1;
	ptr=head;
	int len=lengthList();
	int count=0;
	while(ptr!=NULL){
		if(count==len-index-1)
			return ptr->info;
		ptr=ptr->next;
		count++;
	}
	return -1;
}

int LinkedList::getMiddle(){
	node *ptr,*dbptr;
	ptr=head;
	dbptr=head;
	while(dbptr != NULL && dbptr->next != NULL){
		dbptr=(dbptr->next)->next;
		ptr=ptr->next;
	}
	return ptr->info;
}

void LinkedList::reverseList(){
	node *prev=NULL;
	node *current=head;
	node *next;
	while(current!=NULL){
		next=current->next;
		current->next=prev;
		prev=current;
		current=next;
	}
	head=prev;
}

//End of function definitions

int main(int argc, char const *argv[])
{
	LinkedList l;
	l.addBeg(1);
	l.addBeg(2);
	l.addBeg(3);
	l.traverse();
	l.addEnd(4);
	l.addEnd(5);
	l.traverse();
	l.traverseReverseOrder();
	cout<<"\n";
	l.addAfter(10,4);
	l.traverse();
	cout<<l.lengthList()<<"\n";
	l.swapNodes(2,10);
	l.traverse();
	cout<<l.getNthNode(2)<<"\n";
	cout<<l.getNthNode(4)<<"\n";
	cout<<l.getNthNodeFromEnd(4)<<"\n";
	cout<<l.getNthNodeFromEnd(6)<<"\n";
	l.traverse();
	l.reverseList();
	l.traverse();

	cout<<"Middle element is : "<<l.getMiddle()<<"\n";

	node *n = l.searchElement(4);
	cout << n->info << endl;

	l.delBeg();
	l.delEnd();
	l.traverse();
	l.delGiven(4);
	l.traverse();
	l.delList();
	l.traverse();
	cout<<l.lengthList()<<"\n";

	return 0;
}