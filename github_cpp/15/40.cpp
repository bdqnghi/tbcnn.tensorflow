#include<iostream>
using namespace std;
void multiply(int a[4][4],int b[4][4],int c[4][4],int size)
{
  for(int i=0;i<size;i++)
  { for(int k=0;k<size;k++)
    for(int j=0;j<size;j++)
    {
      c[i][k]+=a[i][j]*b[j][k];
    }

  }
}
int main()
{
  int a[4][4],b[4][4],c[4][4]={0},i,j;
  cout<<"fill first matrix"<<endl;
  for(i=0;i<4;i++)
  for(j=0;j<4;j++)
  cin>>a[i][j];
  cout<<"fill second matrix"<<endl;
  for(i=0;i<4;i++)
  for(j=0;j<4;j++)
  cin>>b[i][j];
  multiply(a,b,c,4);
  cout<<"matrix multiplication"<<endl;
  for(i=0;i<4;i++)
  {for(j=0;j<4;j++)
  {cout<<c[i][j]<<" ";}
  cout<<endl;}

  return 0;
}
