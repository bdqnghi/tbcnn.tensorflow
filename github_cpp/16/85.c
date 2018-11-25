# include <iostream>
using namespace std;
const int MAX=50;

void shellsort( int a[], int count)
{
    int tmp,j;
    for(int g=count/2;g>0;g/=2)
	 for(int i=g;i<(count);i++)
	 {
	     tmp=a[i];
	     for( j=i;j>=g && tmp<a[j-g];j-=g)
		  a[j]=a[j-g];
	     a[j]=tmp;
	 }
}
void display(int a[],int count)
{
    for(int i=0;i<count;i++)
       cout<<a[i]<<"\t";
}
int  main()
{    int a[50], count=0;
     cout<<"\nEnter The numbers else press ! \n";
    while((cin>>a[count++])>0);
    count--;

    cout<<"\nThe elements before sorting are:\n";
   display(a,count);
    shellsort(a,count);
    cout<<"\nThe elements after shell sort are:\n";
    display(a,count);
    return 0;
}
