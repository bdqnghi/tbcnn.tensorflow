#include<iostream>
using namespace std;
const int MAX=50;
class shellsort
{
       int a[MAX];
       int count;
    public:
       void accept();
       void display();
       void sort();
       shellsort();
};
shellsort::shellsort()
{
   count=0;
}
void shellsort::accept()
{
    cout<<"\nPress any character and ENTER to terminate!";
    cout<<"\nEnter The numbers:";
    while((cin>>a[count++])>0);
    count--;
}
void shellsort::sort()
{
    int tmp;
    for(int gap=count/2;gap>0;gap/=2)
	 for(int i=gap;i<(count);i++)
	 {
	  
	     tmp=a[i];
	    for(int j=i;j>=gap && tmp<a[j-gap];j-=gap)
		  a[j]=a[j-gap];
	     a[j]=tmp;
	 }
}
void shellsort::display()
{
    for(int i=0;i<count;i++)
       cout<<a[i]<<"\t";
}
void main()
{
    shellsort x;
    x.accept();
    cout<<"\nThe elements before sorting are:\n";
    x.display();
    x.sort();
    cout<<"\nThe elements after shell sort are:\n";
    x.display();
}
