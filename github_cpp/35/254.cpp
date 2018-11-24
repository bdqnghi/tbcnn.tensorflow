#include<iostream>

using namespace std;

class node
{
    int data;
    node* next;

public:

    node()
    {
        data=0;
        next=NULL;
    }

    node(int d)
    {
        data=d;
        next=NULL;
    }

    int get_data()
    {
        return data;
    }
    void set_data(int d)
    {
        data=d;
    }

    node* get_next()
    {
        return next;
    }

    void set_next(node* p)
    {
        next=p;
    }
};

class Linked_List
{
    node* head;
    node* tail;
    int size;

public:
    Linked_List()
    {
        head=NULL;
        tail=NULL;
    }
    void push_back(int d);
    void push_front(int d);
    void pop_back();
    void pop_front();
    void deletepos(int d);
    void print();
    void deleteel(int d);
    void pushpos(int d, int pos);
};

void Linked_List::push_back(int d)
{
    node* NODE = new node(d);
    size++;

    if(head==NULL && tail==NULL)
    {
     head=tail=NODE;
    }
    else
    {
        tail->set_next(NODE);
        tail=NODE;
    }
}

void Linked_List::push_front(int d)
{
 node* NODE= new node(d);
  size++;
 if(head==NULL && tail==NULL)
 {
     head=tail=NODE;
 }
 else
 {
     NODE->set_next(head);
     head=NODE;

}
}

void Linked_List::print()
{
    node* NODE = head;
    while(NODE)
    {
        cout<<NODE->get_data();
        NODE=NODE->get_next();
        if(NODE)
            cout<<"->";
    }
    cout<<"\n";
}

void Linked_List::pop_back()
{

  if(head== NULL && tail==NULL)
  {
      cout<<"Empty";
  }

  else
  {
      node* temp=head;
      int flag=0;

      while(!flag)
      {
          if(temp->get_next()== tail)
          {
              temp->set_next(NULL);
              tail=temp;
              flag=1;
              size--;
          }
          temp=temp->get_next();
      }
  }
}

void Linked_List::pop_front()
{
    if(head==NULL && tail==NULL)
    {
         cout<<"Empty";
    }

    else
    {
        node* temp=head->get_next();
        delete(head);
        head=temp;
        size--;
    }
}

void Linked_List::deletepos(int d)
{
    node* temp= head;
    for(int i=0;i<d-1;i++)
    {
        temp=temp->get_next();
    }
    node* temp1=temp->get_next();
    temp->set_next(temp1->get_next());
    delete(temp1);
}

void Linked_List::deleteel(int d)
{
    node* temp=head;
    int i=0;
    while(temp)
    {
      if(temp->get_data()==d)
      {
          temp=temp->get_next();
          deletepos(i);


      }
      i++;
      temp=temp->get_next();
    }
}

void Linked_List::pushpos(int d, int pos)
{
    node* temp=head;
    while(temp)
    {
        temp=temp->get_next();
        pos--;
        if(pos==0)
        {
            node* temp1 = new node(d);
            node* temp2 = temp->get_next();
            temp->set_next(temp1);
            temp1->set_next(temp2);
        }
    }
}
