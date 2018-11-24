#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node{
	
	public:
	int height;
	int data;
	Node **ptr;
	bool is_head;

	Node(int d){
		is_head = false;
		height = 1;
		data = d;
		while((rand()%2)!=1){
			++height;
		}
		//if(height>max) height = max;
		ptr = new Node*[height];
	}
	Node(int h, bool head){
		is_head = true;
		height = h;
		ptr = new Node*[height];
	}
};

class SkipList{
	int height;
	Node *head;
	public:
	bool insert(int x){
		Node **curr;
		curr = new Node*[height];
		curr[height-1] = head;
		int h = height-1;
		while(h>=0){
			if(!curr[h]->is_head && x==curr[h]->data) return false;
			if(curr[h]->ptr[h]==NULL || x<curr[h]->ptr[h]->data ){ 
				--h;
				if(h!=-1) curr[h] = curr[h+1];
			}
			else curr[h] = curr[h]->ptr[h];
		}
		Node *new_elt = new Node(x);
		int old_height = height;
		if(new_elt->height > height){
			Node *new_head = new Node(new_elt->height, true);
			for(int i=0; i<height; ++i){ 
				new_head->ptr[i] = head->ptr[i];
				if(curr[i]==head) curr[i] = new_head;
			}
			for(int i=height; i<new_head->height; ++i) new_head->ptr[i] = new_elt;
			// delete head;
			head = new_head;
			height = head->height;
		}
		cout<<"head height "<<head->height<<" element height "<<new_elt->height<<"\n";
		//for(int i=0;i<head->height;++i)cout<<"Head "<<i<<" pointing to"<<head->ptr[i]<<"\n";
		for(int i=0; i<(new_elt->height < old_height ? new_elt->height : old_height); ++i){
			Node *temp = curr[i]->ptr[i];
			curr[i]->ptr[i] = new_elt;
			//if(curr[i]->is_head) head->ptr[i] = new_elt;
			new_elt->ptr[i] = temp;
		}
		for(int i=0;i<head->height;++i)cout<<"Head "<<i<<" pointing to "<<head->ptr[i]<<"\n";
		return true;
	}

	bool delete_element(int x){
		Node **curr;
		curr = new Node*[height];
		curr[height-1] = head;
		//for(int i=0; i<max; ++i) curr[i] = head[i];
		int h = height-1;
		while(h>=0){
			if(curr[h]->ptr[h]==NULL || x<=curr[h]->ptr[h]->data){ 
				--h;
				if(h!=-1) curr[h] = curr[h+1];
			}
			else curr[h] = curr[h]->ptr[h];
		}
		if(curr[0]->ptr[0]==NULL || curr[0]->ptr[0]->data!=x) return false;
		Node *to_delete = curr[0]->ptr[0];
		for(int i=0; i<to_delete->height; ++i){
			curr[i]->ptr[i] = curr[i]->ptr[i]->ptr[i];
		}
		// delete to_delete;
		return true;
	}

	bool find(int x){
		Node *curr;
		//curr = new Node*[max];
		//curr[max-1] = head[max-1];
		//for(int i=0; i<max; ++i) curr[i] = head[i];
		curr = head;
		int h = height-1;
		while(h>=0){
			if(!curr->is_head && x==curr->data) return true;
			if(curr->ptr[h]==NULL || x<curr->ptr[h]->data){ 
				--h;
			}
			else curr = curr->ptr[h];
		}
		return false;
	}

	void print(){
		Node *curr;
		for(int i=height-1; i>=0; --i){
			//curr = head->ptr[i];
			curr = head;
			cout<<"Level "<<i<<" ";
			while(curr!=NULL){
				cout<<curr->data<<"\n";
				curr = curr->ptr[i];
			}
			cout<<"\n";
		}
	}

	SkipList(){
		height = 1;
		head = new Node(1,true);
		head->ptr[0] = NULL;
	}
};

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	SkipList s;
	// s.print();
	// for(int i=1;i<5;++i){ 
	// 	s.insert(2*i);
	// 	s.insert(11-2*i);
	// }
	s.insert(11);
	s.insert(10);
	cout<<"inserted\n";
	// cout<<s.insert(2);
	// s.print();
	// cout<<s.delete_element(100);
	s.print();
	return 0;
}