#include <iostream>
#include "node.h"
#include "helper.h"
using namespace std;

node * bubble(node * head, int n){
	for(int i = 0; i < n; ++i){
		node * prev = NULL;
		node * cur = head;
		node * next = cur->link;
		while(cur != NULL && next != NULL){
			if (cur->data > next->data){
				//swapping when first 2 nodes
				if (cur == head){
					cur->link = next->link;
					next->link = cur;
					head = next;
					prev = head;
					next = cur->link;
				}
				else {
					prev->link = next;
					cur->link = next->link;
					next->link = cur;
					prev = next;
					next = cur->link;
				}
			}
			else {
				prev = cur;
				cur = next;
				next = cur->link;
			}
		}
	}
	return head;
}

int main(){
	int n; 	cin >> n;
	node * list = createList(n);
	printList(list);
	list = bubble(list, n);
	printList(list);
	return 0;
}