#include<bits/stdc++.h>
using namespace std;

// linked list is a data structure
// the main diffrence between an array and a linked list is that in an array elements are stored continuously 
// in a linked list elements are stored using pointers ; they need not be alloted memory continously
// insertion and deletion are very expenive operations in arrays but not in linked list

// linked list -> if we have to access any element then we have to move sequentially, Cant do binary search etc etc
// each node in a linked list consists of 1)data and 2)pointer(to the next element)

//self implemented linked list


class Node{
    public:
        //value of current
        int data;
        //address of next node
        Node *next;
        //constructor to store values of data and address in node at the time of declaration itself
        Node(int data){
            this->data=data;
            //initialise the adress with null
            this->next=NULL;
        }

};

void print_linked(Node *head){
    //last elemnet next will have NULL
    while(head!=NULL){
        cout<<head->data<<" ";
        head=head->next;
    }
}


int main(){
    //dynamically initialised the nodes
    Node *node1 = new Node(10);
    Node *node2=new Node(20);
    //stored address of 2 in 1
    node1->next=node2;
    //statically initialised
    Node n3(30);
    node2->next=&n3;
    //printing the linked list
    print_linked(node1);


    return 0;
}