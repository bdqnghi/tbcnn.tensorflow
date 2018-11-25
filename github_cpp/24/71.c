
#include<iostream>
using namespace std;
int binary(int a[],int,int,int);
int main()
{
         int lb,ub,a[100],key;
         cout<<"Enter number of elements:";
         cin>>a[0];

          
          for(int i=1;i<=a[0];i++)
          {
                    cout<<"Enter element number "<<i<<" : ";
 	            cin>>a[i];
          }
          
         
          cout<<"Enter element that is to be found :";
          cin>>key;
          lb=1,ub=a[0];        
          int o=binary(a,lb,ub,key);
          
          if(o==-1)
          {
                 cout<<"Number not found"<<endl;
          }
          else
          {
                 cout<<"Number is present at location number :"<<o;
          }
             
          return 0;
}
int binary(int a[],int lb,int ub,int key)
{
         
          int mid;
           if(lb>ub)
           {
                             return -1;
           }
           else
           {
                      mid=(lb+ub)/2;
                         if(key==a[mid])
                         {
				return mid;
                          }
                          else if(key<a[mid])
                          {
                                   binary(a,lb,mid-1,key);
                          }
                          else if(key>a[mid])
                          {
                                     binary(a,mid+1,ub,key);
                           }
           }
}
