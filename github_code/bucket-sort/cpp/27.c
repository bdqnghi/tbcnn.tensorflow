#include <iostream>
#include <stdlib.h>

using namespace std;

struct node{
	float data;
	node *next;
};

node *list[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
float arr[]={0.2,0.3,0.4,0.12,0.22};



void insert(int pos,float data){
	cout<<"in insert"<<endl;
		node *temp=new node;
		temp->data=data;
		temp->next=NULL;
		
		if(list[pos] == NULL){
			list[pos]=temp;
			cout<<"inserted"<<data<<endl;
			return;
		}
		
		node *ptr=list[pos];
		while(ptr->next != NULL)
			ptr=ptr->next;
		ptr->next=temp;	
		cout<<"inserted"<<data<<endl;		
		return;
}




void sort(int i){
	node *ptr=list[i];	
	node *ptrpar=ptr;
	
	while(ptr != NULL){
		node *inloop=root;
		node *inpar=inloop;
		while(inloop->data != ptr->data)
		{
			if(inloop->data > ptr->data)
			{
				node *temp=ptr;
				inpar->next=ptr;
				ptrpar->next=inloop;
				ptr->next=inloop->next;
				inloop->next=temp->next;
				
			}
			inpar=inloop;
			inloop=inloop->next;
		}
		ptrpar=ptr;
		ptr=ptr->next;
	}
}

void display(){
	cout<<"in ddisplay"<<endl;
	//node *temp;
	for(int i=0;i<10;i++){
	node *temp=list[i];
		//cout<<i<<endl;
		if(temp == NULL){
			cout<<"no element"<<endl;
		}
		else{
		while(temp != NULL){
			cout<<temp->data<<" ";
			temp=temp->next;
		}
	
		}
				cout<<"\n";
	}
	return;
}


int bucketsort(int size){
	
	//cout<<"1 hello"<<endl;
	
	/*for(int i=0;i<10;i++){
	list[i]=new node;	
	}*/
	//cout<<"2 hello"<<endl;
	
	for(int i=0;i<size;i++)
	{
		int f_digit=(arr[i])*10;
		cout<<f_digit<<endl;
		insert(f_digit,arr[i]);
		cout<<"ok bahar"<<endl;
	}
	
	/*for(int i=0;i<10;i++){
		sort(list[i]);
	}*/
	//cout<<"3 hello"<<endl;
	display();
	return 0;
}


int main(){
	int size=sizeof(arr)/sizeof(arr[0]);
	cout<<"hello";
	bucketsort(size);
}
