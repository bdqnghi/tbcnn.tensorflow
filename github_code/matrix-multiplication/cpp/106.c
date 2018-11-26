#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include<climits>
using namespace std;


int minoperation(int a[],int si,int ei)
{
    if(ei-si<=1)
{
    return 0;
}

int minoper=INT_MAX;

    for(int i=si+1;i<=ei-1;i++)
    {
        int leftoper=minoperation(a,si,i);
        int rightoper=minoperation(a,i,ei);

        int finalmultiply=a[si]*a[ei]*a[i];

        int oper=leftoper+rightoper+finalmultiply;

        if(oper<minoper)
        {
            minoper=oper;
        }


    }
        return minoper;

}

int minBhelper(int a[],int si,int ei,int ** arr)
{
     if(ei-si<=1)
     {
         return 0;
     }


    if(arr[si][ei]>-1)
    {
        return arr[si][ei];
    }

   int minoper=INT_MAX;
   for(int i=si+1;i<=ei-1;i++)
   {
       int leftoper=minBhelper(a,si,i,arr);
       int rightoper=minBhelper(a,i,ei,arr);

       int finalmultiply=a[si]*a[ei]*a[i];
       int  oper=leftoper+rightoper+finalmultiply;
       if(oper<minoper)
       {
           minoper=oper;
       }

   }

    arr[si][ei]=minoper;
    return minoper;

}

int minoperationB(int a[],int Size)
{
    int **arr=new int*[Size+1];

    for(int i=0;i<=Size;i++)
    {
        arr[i]=new int[Size+1];


    for(int j=0;j<=Size;j++)
    {
        arr[i][j]=-1;
    }
}

int ans= minBhelper(a,0,Size-1,arr);

for(int i=0;i<=Size;i++)
{
    delete []arr[i];
}
    delete[]arr;
    return ans;
}




int main()
{
    int a[]={2,6,4,1};
    cout<<minoperation(a,0,3)<<endl;
    cout<<minoperationB(a,4)<<endl;

    return 0;
}



