#include <iostream>
struct Node {
    int num;
    Node* next;
    Node(int);
};

Node:: Node(int n): num(n), next(0){}

class List{
    public:
    List();
    ~List();
    void insert_at_front(int);
    void print() const;
    
private:
    Node* list;
};

void List::insert_at_front (int n)
{
    Node insert(n);
    insert.next=list;
    list=&insert;
    
}

void List::print() const
{
    for(Node* i=list; i!=0; i=i->next)
    {
        std::cout << i->num << std::endl;
    }

}


/*int main()
{
    Node first(20), second(-15), third(17);
    Node* List;
    List=&first;
    first.next=&second;
    second.next=&third;
    
    for(Node* i=List; i!=0; i=i->next)
    {
        std::cout << i->num << std::endl;
    }
}*/

int main()
{
    List L;
    L.insert_at_front(1);
    L.insert_at_front(2);
    L.insert_at_front(3);
    L.print();
}

