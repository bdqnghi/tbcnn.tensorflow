# include <iostream>
using namespace std;
void bubblesort(int n,int arr[30])
{int j,i,temp;
 for(i=0;i<n-1;i++)
 for(j=0;j<n-i-1;j++)
 if(arr[j]>arr[j+1])
 {temp=arr[j];
  arr[j]=arr[j+1];
  arr[j+1]=temp;
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
 cout<<"  \n The Sorted Array"<<endl;
  bubblesort(n,a);
  for(int i=0;i<n;i++)
cout<<"\t"<<a[i];
return 0;
}
