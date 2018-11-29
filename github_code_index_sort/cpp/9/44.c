# include <iostream>
using namespace std;
void selectionsort(int n,int arr[30])
{int j,i,temp,min,pos;
 for(i=0;i<n-1;i++)
 {min=arr[i];
  pos=i;
  for(j=i+1;j<n;j++)
  if(min>arr[j])
    {min=arr[j];
     pos=j;
    }
  temp=arr[pos];
  arr[pos]=arr[i];
  arr[i]=temp;
 }
}

int main()
{ int n,a[30],o, i=0,j;
 cout<<"Enter the no. of elements: ";
 cin>>n;
 
  cout<<"Enter the element else press!  ";
  for(int i=0;i<n;i++)
  cin>>a[i];
  cout<<endl;
 cout<<" \n unsorted array is"<<endl;
 for(j=0;j<n;j++)
 cout<<"\t"<<a[j];
 
 cout<<" \n The Sorted Array"<<endl;
  selectionsort(n,a);
   for(int i=0;i<n;i++)
cout<<"\t"<<a[i];
 return 0;
}
