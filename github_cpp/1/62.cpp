#include<iostream>
using namespace std;
struct treenode{
	int data;
	treenode* left;
	treenode* right;
};
struct node{
	treenode* address;
	node* link;
};
node* createnode(){
	node* temp=new node;
	temp->link=NULL;
	return temp;
}
node* front=NULL;
node* rear=NULL;
void enqueue(treenode* address){
	if(front==NULL&&rear==NULL){
		node* temp=createnode();
		temp->address=address;
		front=temp;
		rear=temp;
	}
	else{
		node* temp=createnode();
		temp->address=address;
		rear->link=temp;
		rear=temp;
	}
}
void dequeue(){
	if(front==NULL)
		cout<<"Queue Is Empty"<<endl;
	else
		front=front->link;
}
treenode* frontvalue(){
	if(front==NULL){
		cout<<"Queue Is Empty"<<endl;
	}
	else
		return front->address;
}
bool IsqueueEmpty(){
	if(front==NULL)
		return true;
	else
		return false;
}
treenode* root=NULL;
treenode* getnewnode(){
	treenode* currentnode=new treenode;
	currentnode->left=NULL;
	currentnode->right=NULL;
	return currentnode;
}
void insert(int data){
	if(root==NULL){
		root=getnewnode();
		root->data=data;
	}
	else{
		treenode* currentnode=root;
		treenode* prev=NULL;
		int x=0;
		while(currentnode!=NULL){
			if(currentnode->data>=data){
				prev=currentnode;
				currentnode=currentnode->left;
				x=0;
			}
			else{
				prev=currentnode;
				currentnode=currentnode->right;
				x=1;
			}
		}
		if(x==1){
			currentnode=getnewnode();
			currentnode->data=data;
			prev->right=currentnode;
		}
		else if(x==0){
			currentnode=getnewnode();
			currentnode->data=data;
			prev->left=currentnode;
		}
	}
}
void bfs(){
	treenode* temp=root;
	cout<<temp->data<<" ";
	if(temp->left!=NULL)
		enqueue(temp->left);
	if(temp->right!=NULL)
		enqueue(temp->right);
	bool check;
	while(1){
		check=IsqueueEmpty();
		if(check==true)
			break;
		else{
			temp=frontvalue();
			dequeue();
			cout<<temp->data<<" ";
			if(temp->left!=NULL)
				enqueue(temp->left);
			if(temp->right!=NULL)
				enqueue(temp->right);
		}
	}
}
int main(){
	int test; 
	cout<<"Enter Test Case: "<<endl;
	cin>>test;
	while(test--){
		cout<<"Enter Number: "<<endl;
		int x;
		cin>>x;
		insert(x);
	}
	bfs();
	return 0;
}