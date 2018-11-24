#include<iostream>
using namespace std;
const int MAX=50;
class node
{
    int data;
    node *next;
    friend class radixsort;
};
class radixsort
{
    int count;
    node **a;
    node **b;
    int *tmp;
    int pass;
    public:
	  void accept();
	  void sort();
	  radixsort();
	  void radix(int);
	  void predisplay();
	  void postdisplay();
	  void createb();
};
radixsort::radixsort()
{
     pass=1;
     count=0;
     tmp=new int[MAX];
     a=new node*[10];
     for(int i=0;i<10;i++)
	   a[i]=NULL;
}
void radixsort::createb()
{
     b=new node*[10];
     for(int i=0;i<10;i++)
	     b[i]=NULL;
}
void radixsort::accept()
{
     cout<<"\nEnter any character + ENTER to terminate!";
     cout<<"\nEnter the numbers:";
     while(cin>>tmp[count++]);
     count--;
}
void radixsort::predisplay()
{
     node *temp;
     int rem;
     for(int i=0;i<count;i++)
     {
	    cout<<tmp[i]<<"\t";
	    rem=tmp[i]%10;
	    temp=a[rem];
	    node *tt;
	    if(temp!=NULL)
	    {
		  while(temp->next!=NULL)
		    temp=temp->next;
		  tt=new node;
		  tt->data=tmp[i];
		  tt->next=NULL;
		  temp->next=tt;
	    }
	    else
	    {     tt=new node;
		  tt->data=tmp[i];
		  tt->next=NULL;
		  a[rem]=tt;
	    }
     }
}
void radixsort::sort()
{
       int inc=10;
       while(pass)
       {
	   inc*=10;
	   pass=0;
	   radix(inc);
       }
}
void radixsort::radix(int inc)
{
      node *tmp1;
      int rem;
      int pinc=inc/10;
      createb();
      int tempvar;
      node *tt;
      for(int i=0;i<10;i++)
      {
	     tmp1=a[i];
	     while(tmp1!=NULL)
	     {
		   tempvar=(tmp1->data)/pinc;
		   rem=tempvar%10;
		   if(rem!=0)
			pass=1;
		   tt=b[rem];
		   if(tt)
		   {
		     while(tt->next!=NULL)
			 tt=tt->next;
		     tt->next=new node;
		     tt->next->data=tmp1->data;
		     tt->next->next=NULL;
		   }
		   else
		   {
		     b[rem]=new node;
		     b[rem]->data=tmp1->data;
		     b[rem]->next=NULL;
		   }
		   tmp1=tmp1->next;
	     }
       }
       delete a;
       a=b;
}
void radixsort::postdisplay()
{
     node *t;
     t=a[0];
     while(t!=NULL)
     {
	   cout<<t->data<<"\t";
	   t=t->next;
     }
}
int main()
{
    radixsort x;
    x.accept();
    cout<<"\nElements before sorting are:";
    x.predisplay();
    x.sort();
    cout<<"\nElements after sorting are:";
    x.postdisplay();
    return 0;
}

