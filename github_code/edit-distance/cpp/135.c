#include<bits/stdc++.h>
using namespace std;
int minn(int x,int y,int z)
{
    return min(min(x,y),z);
  }
int countt=0;
int main()
{
cout<<"Enter the two string"<<endl;
string C,D;
cin>>C>>D;
int c=C.length(),d=D.length();
int A[c+1][d+1]={};
for(int i=0;i<=d;i++)
    A[0][i]=i;
for(int i=0;i<=c;i++)
    A[i][0]=i;
    for(int i=1;i<=c;i++)
    {
        for(int j=1;j<=d;j++)
        {
         if(C[i-1]==D[j-1])
         {
          A[i][j]=A[i-1][j-1];
          cout<<A[i][j]<<" ";
          countt++;
         }
         else
            {
            A[i][j]=1+minn(A[i-1][j-1],A[i-1][j],A[i][j-1]);
            cout<<A[i][j]<<" ";
            countt++;
         }
        }
        cout<<endl;

    }
cout<<A[c][d]<<endl;
cout<<countt;



return 0;
}
