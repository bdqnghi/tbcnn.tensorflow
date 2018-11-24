#include <stdio.h>

struct Node{
    int value;
    Node* next;
};

Node* head;

void printList(Node* h){
    Node* p = h;
    while(p != NULL){
        printf("%d ",p->value);
        p = p->next;
    }
}

Node* makeNode(int x){
    Node* q = new Node ;
    q->value = x;
    q->next = NULL;
    return q;

}

Node* insertLast(Node* h, int x){
    Node* q = makeNode(x);
    if(h == NULL) return q;// tinh huong ngoai le (dac biet)

    // time phan tu cuoi cung cua danh sach
    Node* p = h;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = q;
    return h;
}
Node* insertLastRecursive(Node* h, int x){
    if(h == NULL){
        return makeNode(x);
    }
    h->next = insertLastRecursive(h->next,x);
    return h;
}
int count(Node* h){
    int k = 0;
    for(Node* p = h; p != NULL; p = p->next){
        k = k + 1;
    }
    return k;
}
int countRecursive(Node* h){
    if(h == NULL) return 0;
    return 1 + countRecursive(h->next);
}
Node* find(Node*h, int x){
    if(h == NULL) return NULL;
    for(Node* p = h; p != NULL; p = p->next){
        if(p->value == x) return p;
    }
    return NULL;
}

Node* removeRecursive(Node* h, Node* p){
    if(h == NULL) return NULL;
    if(p == NULL) return h;
    if(h == p){
        h = h->next;
        delete p;
        return h;
    }else{
        h->next = removeRecursive(h->next,p);
    }
    return h;
}

Node* remove(Node* h, Node* p){
    if(h == NULL || p == NULL) return h;
    if(h == p){
        h = h->next;
        delete p;
        return h;
    }
    Node* q = h;
    while(q->next != p){
        q = q->next;
        if(q == NULL) break;
    }
    if(q != NULL){
        q->next = p->next;
        delete p;
    }
    return h;
}

Node* concat(Node* h1, Node* h2){
    Node* q = h1;
    if(h1 == NULL){return h2;}
    if(h2 == NULL) return h1;
    while(q->next != NULL)
        q = q->next;
    q->next = h2;
    return h1;
}
int main(){

    for(int i = 0; i < 10; i++)
        head = insertLastRecursive(head,i+1);
    printList(head);

    printf("So phan tu cua danh sach la %d\n",countRecursive(head));

 Node* p = find(head,8);
    head = remove(head,p);
    printList(head);
 /*   printList(head);
    Node* h1 = NULL;
    Node* h2 = NULL;
    //for(int i = 1; i <= 10; i++)
    //    h1 = insertLast(h1,i);

    for(int i = 1; i <= 10; i++)
        h2 = insertLast(h2,i*100);

    h1 = concat(h1,h2);

    printList(h1);
*/

}

