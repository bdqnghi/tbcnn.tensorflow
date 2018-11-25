#include<bits/stdc++.h>
using namespace std;
int binary(int low,int high,int key,int a[])
{
    while(low<=high)
    { int mid=(low+high)/2;
        if(key<a[mid]){
        
        high=mid-1; }
        else if(key>a[mid])
        { 
        low=mid+1;
        }else
        {
        return mid; }
    } return -1;
}
int main()
{
    int t;
    cin>>t;
   int a[t];
   for(int i=0;i<t;i++)
   cin>>a[i];
   sort(a,a+t);
   int q;
   cin>>q;
   while(q--)
   {
       int m;
       cin>>m;
    int y= binary(0,t-1,m,a);
   
    cout<<y+1<<endl;   
   }
}
