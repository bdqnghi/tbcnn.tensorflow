#include <iostream>

using namespace std;

typedef struct Node {

        int info;
        struct Node *next; 
} Node;

struct Node *start=NULL, *end=NULL;

//function prototypes
void create(struct Node*&, struct Node*&, int);
void display(struct Node*);
void insert_after(struct Node *&, struct Node *&,int,int);
void insert_before(struct Node *& ,int , int);
void remove(struct Node *& ,struct Node *& ,int);


int main() {

    int node, 
         which, //which node
             what,//what value of node to do 
                i;//for iteration

     //for insert keybord   
    /*do {
       cout<<"Node=";
       cin>>node; 
       create(start,end,(int)node);
    }while(node != 0);
    */

    for(i = 1; i <= 9; i++) create(start,end,i);
    display(start);

    cout<<"remove node=";
    cin>>which;
    remove(start,end,which);
    display(start);
 
    /*cout<<endl;
    cout<<"insert after which one=";
    cin>>which;
    cout<<"what value = ";
    cin>>what;
    insert_after(start,end,which,what); 
    display(start);

    cout<<endl;
    cout<<"insert before which one node=";
    cin>>which;
    cout<<"what value = ";
    cin>>what;
    insert_before(start,which,what); 
    display(start);
    */

    return(0);
}

void create(struct Node *&start, struct Node *&end, int info) {

     struct Node *c;

     if(start == NULL) {

        start = new Node;
        start->info = info;
        start->next = NULL;
        end = start;  

     } else {

        c = new Node; 
        c->info = info;
        c->next = NULL;
        end->next = c;
        end = c;
     }  
}

void insert_after(struct Node *&start, struct Node *&end, int which, int what) {

     struct Node *c = start, *newNode;

     while(c->info != which) 
           c = c->next;

     newNode = new Node;
     newNode->info = what;
     newNode->next = c->next;
     c->next = newNode;

     if(c == end) end = newNode;    
}


void insert_before(struct Node *&start, int whichnode, int whatvalue) {

     struct Node *newNode, *c;

     if(start->info == whichnode) {

        newNode = new Node;
        newNode->info = whatvalue; 
        newNode->next = start;
        start = newNode;

     } else {

        c = start;  

        while(c->next->info != whichnode)
              c = c->next;

        newNode = new Node;
        newNode->info = whatvalue;
        newNode->next = c->next;
        c->next = newNode;

     }
}

void remove(struct Node *& start,struct Node *&end ,int which) {
     struct Node *temp, *c;

     if(start->info == which) {

        temp = start;
        start = start->next;

        delete temp;  

     } else {

        c = start;

        while(c->next->info != which) c = c->next;

        temp = c->next;
        c->next = temp->next;

        if(c->next == end) end = c;
 
        delete temp;
     }
}

void display(struct Node* start) {

     struct Node* c = start;
 
     while( c && c->info != 0) {

            cout<<c->info<<" ";
            c = c->next;
     }
}