#include<iostream>
using namespace std;
void Merge(int r[],int rl[],int s,int m,int t)
{
  int i=s,j=m+1,k=s;
  while(i<=m && j<=t)
    {
      if(r[i]<=r[j]) rl[k++]=r[i++];
      else rl[k++]=r[j++];
    }
  if(i<=m)while(i<=m)
	    rl[k++]=r[i++];
  else while(j<=t)
	 rl[k++]=r[j++];
  for(int m=s;m<=t;m++)   //增加了写回r[]的一步
    {
      r[m]=rl[m];
    }

}
void MergeSort(int r[],int rl[],int s,int t)
{
  if(s==t) 
    rl[s]=r[s];
  else{
    int m=(s+t)/2;
    MergeSort(r,rl,s,m);
    MergeSort(r,rl,m+1,t);
    Merge(r,rl,s,m,t); // 我改了下,书上是Merge(rl,r,s,m,t);
  }
}

int main()
{
  int r[]={23,13,49,6,31,19,28};
  cout<<"Waiting to be sorted: ";
  for(int k=0;k<=6;k++)  //输出未排序前的序列
    {
      cout<<r[k]<<" ";
    }
  cout<<endl;
  int rl[7];
  MergeSort(r,rl,0,6);
  cout<<"Sorted:";
  for(int i=0;i<=6;i++) //输出排序后的序列
    {
      cout<<r[i]<<" ";
    }

  return 0;
}
