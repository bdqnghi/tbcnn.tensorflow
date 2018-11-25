# include <iostream>
using namespace std;
void insertionsort(int n,int a[30])
{int j,i,temp;
 for(i=1;i<n;i++)
 {temp=a[i];
  j=i-1;
  while((temp<a[j])&&(j>=0))
  {
   a[j+1]=a[j];
   j=j-1;
  }
  a[j+1]=temp;
 }
}

int main()
{int n,a[30],o, i=0,j;
 cout<<"Enter the no. of elements: ";
 cin>>n;
 
  cout<<"Enter the element else press!  ";
  for(int i=0;i<n;i++)
  cin>>a[i];
  cout<<endl;
 cout<<" \n unsorted array is"<<endl;
 for(j=0;j<n;j++)
 cout<<"\t"<<a[j];
  cout<<"           \n  The Sorted Array"<<endl;
insertionsort(n,a);
       
for(int i=0;i<n;i++)
cout<<"\t"<<a[i];
return 0;
    }
