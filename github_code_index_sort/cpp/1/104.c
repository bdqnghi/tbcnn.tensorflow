/*          Name:- Bakul Gupta
            e-mail:- bakulgupta11@gmail.com
*/

//Header-Files Inclusion
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b,c) for(i=a;i<b;i+=c) 

//Insertion-sort function definition
void Insertionsort(int A[],int n)
{
  int i,j,key;
   rep(i,1,n,1)
       {
       key=A[i];
       j=i-1;
           while (j >=0 and key< A[j])
               {
                 A[j+1]=A[j];
                 j--;
               }
       A[j+1]=key;
       }
              
}

//Main-fucntion
int main()
{
int A[]={34,23,1,5,8,9};
int n=sizeof(A)/sizeof(A[0]);
int i;
cout<<"The array elements before sorting are;- "<<endl;
rep(i,0,n,1)
cout<<A[i]<<"\t";
Insertionsort(A,n);
cout<<endl;
cout<<"The array elements after sorting are:- "<<endl;
rep(i,0,n,1)
cout<<A[i]<<"\t";
return 0;
}
