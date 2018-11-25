#include<iostream>
using namespace std;
class node
{
public:
    int info;
    node *next;
};
main()
{
    node *x1=new node;
    
    
    
    int a;
    int count;
    cout<<"ENTER NUMBER OF ELEMENTS TO ENTER : ";
    cin>>count;
    cout<<"ENTER 1 ELEMENT = ";
    cin>>a;
    x1->info=a;

    
    node *container,*c2;
    node *t;
    t=x1;
    node *n;
    n=x1;
    for(int i=0;i<count-1;i++)
    {
        x1 = new node;
        int a;
        cout<<"Enter "<<i+2<<" ELEMENT : ";
        cin>>a;
        x1->info=a;
        t->next=x1;
        t=t->next;
        if(i==0)
        {
            c2=x1;
        }
    }
    t->next=NULL;
    container=n;
    
   if(container!=NULL)
    {
        while(container!=t)
        {
            c2=container;
            while(c2!=NULL)
            {
            if(container->info>c2->info)
            {
                int t=container->info;
                container->info=c2->info;
                c2->info=t;
            }
            c2=c2->next;
            }
            container=container->next;
        }
    }
   c2= container = n;
   cout<<"AFTER SORTING : \n";
    if(c2!=NULL)
    {
        while(c2!=NULL)
        {
            cout<<c2->info<<" ";
            c2=c2->next;
        }
    }
    cout<<"ENTER ITEM TO SEARCH";
    cin>>a;
    count=count/2;
    int f=0;
    int i=0;
    if(container!=NULL)
    {
        while(container!=NULL && i!=count)
        {
            if(container->info==a)
               {
                f=1;
                break;
               }
               i++;
            container=container->next;
        }
    }
    
    node *temp=container;
    if(temp->info>a)
    {
        temp=n;
            count=0;
         while(temp!=container)
        {
            if(temp->info==a)
               {
                f=1;
                break;
               }
            count++;
            temp=temp->next;
        }
    }
    else
    {
        count++;
         while(temp!=NULL)
        {
            if(temp->info==a)
               {
                f=1;
                break;
               }
            count++;
            temp=temp->next;
        }
        
    }
    if(f==1)
    {
        cout<<"FOUND AT POSITION : "<<count;
        
    }
    else
    {
        cout<<"NOT FOUND";
    }
}

