



#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b,c) for(i=a;i<b;i+=c)


void selection_sort(int A[],int n)
{
 int i,j,k,min;
       rep(i,0,n,1)
       {
       	 k=i;
       	 min=A[i];
       	 rep(j,i+1,n,1)
       	  {
       	  	if(min>A[j])
       	  	  {
       	  		min=A[j];
       	  		k=j;
       	  	  }
       	  }
       swap(A[i],A[k]);
       }
}

int main()
{
	int i;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
int A[]={67,45,23,11,5};
int n=sizeof(A)/sizeof(A[0]);
cout<<"The array elements before sorting are:-";
rep(i,0,n,1)
  cout<<A[i]<<"\t";  
selection_sort(A,n);
cout<<endl;
cout<<"The array elements after sorting are:-";
rep(i,0,n,1)
  cout<<A[i]<<"\t";
return 0;
}











