#include "bits/stdc++.h"
#define MIN(a,b,res) ((a)>(b))? (res)=(b):(res)=(a)
#define MAX(a,b,res) ((a)<(b))? (res)=(b):(res)=(a)
#define repeat(x) while(x--)
#define printArray(a,l,n) for(int(i)=(l);(i)<int(n);i++) { cout<<(a[i])<<' ';}
using namespace std;
int findLargest (int a[],int l,int n) 
{ 
	int largest=INT_MIN; 
	for(int i= l; i <n;i++) 
	{ 
		if(a[i]>largest) 
			largest=a[i]; 
	} 
	return largest; 
}
void sortByDigit(int a[], int n, int exp)
{
	int output[n]; //to hold the sorted array when sorted by the current place(unit's, hundreds, thoudands etc)
	int *freq= new int[10]; //make a new array with size = 10
	for (int i = 0; i < n; ++i) //loop through the input and increment the frequency of each element when it is encountered
		freq[(a[i]/exp)%10]++;
	for (int i = 1; i < 10; ++i) //loop through the freq count and change it so that it is the actual pos of this digit in output array.
		freq[i] = freq[i]+ freq[i-1];
	for (int i = n-1; i >= 0; i--) //building the sorted by digit array
	{
		output[ freq[(a[i]/exp)%10]-1 ] =  a[i];
		freq[(a[i]/exp)%10]--;
	}
	for (int i = 0; i < n; ++i) //copy it back to the input array. this array is the input for the next sortByDigit call (if any).
		a[i]=output[i];
}
void radixSort(int a[],int n)
{
	int largest= findLargest(a,0,n);
	for(int exp=1; largest/exp > 0; exp*=10) //call sort by digit for unit's place, hundred's place etc. exp= 1,10,100..etc
		sortByDigit(a,n,exp);
}
int main()
{
	int input[10];
	for (int i = 0; i < 10; ++i)
		input[i]=rand()%1000;
	cout<<"Unsorted: ";
	printArray(input,0,10);
	cout<<endl<<"Sorted : ";
	radixSort(input,10);
	printArray(input,0,10);
	return 0;
}