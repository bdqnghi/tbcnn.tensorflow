/*
  Name: kriti
  Copyright: 
  Author: 
  Date: 12/08/13 19:07
  Description: rod-cutting problem 
*/

#include<stdio.h>
#include<conio.h>
#include<iostream>
using namespace std;
//-----------------------------------------------------------------------------

int max(int i,int j)
{
   if(i>j)
   return i;
   else
   return j;
}
//-----------------------------------------------------------------------------

int main()
{
   int length,n;
   cin>>n;
   int len[n+1],val[n+1];
   for(int i=0;i<n;i++)
   {
      cin>>len[i]>>val[i];
   }
   
   cin>>length;
   int a[n+1][length+1];
   for(int i=0;i<n;i++)
   {
      a[i][0]=0;
      a[0][i]=0;
   }
   
   for(int j=1;j<=n;j++)
   {
      for(int i=1;i<=length;i++)
      {
         a[j][i]=max(a[j-1][i],a[j-1][i-len[j]]+val[j]);
      }
   }
   
   printf("%d\n",a[n][length]);
   getch();
   return 0;
}
         
   
