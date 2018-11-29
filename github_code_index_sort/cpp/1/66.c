#include <iostream>
#include <iomanip>
using namespace std;

void insertionsort(long long a[],long long n)
{
	long long key,i,j;
	for(i=1;i<n;i++)
	{
		key = a[i];
		j = i-1;

		while(j>=0 && a[j]>key)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = key;
	}
}
int main(){
	long long *a,n,i,num;
	cin>>n;
	a = new long long[n];
	for(i=0;i<n;i++)
	{
		cin>>num;
		a[i] = num;
		insertionsort(a,i+1);
		if((i+1)%2==0)
		{
			cout<<fixed<<setprecision(1)<<(float)(a[i/2]+a[(i/2)+1])/2<<"\n";
		}
		else
		{
			cout<<fixed<<setprecision(1)<<(float)a[i/2]<<"\n";
		}

	}
}