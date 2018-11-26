#include<iostream>
#include<conio.h>

using namespace std;

int main(void)
{
  int arr[30],n;
  cout<<"\nEnter the number of elements required: ";
  cin>>n;
  cout<<"\nEnter the elements: ";
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
  }
  int key,i;
  for(int j=1;j<n;j++)
  {
    key=arr[j];
    i=j-1;
    while(i>=0 && arr[i]>key)
    {
      arr[i+1]=arr[i];
      i--;
    }
    arr[i+1]=key;
  }
  cout<<"\nSorted list is: \n";
  for(int i=0;i<n;i++)
  {
    cout<<arr[i]<<" ";
  }
  return 0;
}
