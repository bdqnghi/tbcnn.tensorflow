#include <iostream>
using namespace std;

int binarysearch (int *a,int min,int max,int find)
{
	int mid = (min+max)/2;

	if (a[mid] == find) return mid;

	else if (a[mid] < find) return binarysearch(a,mid,max,find);

	else if (a[mid]>find) return binarysearch(a,min,mid,find); 
    
    else {cout<<"element not found!"<<endl;}
    return 1;

}



int main()
{
	int a[5];
	int n;

	for (int i=0 ; i<5 ; i++)
	{
			cout << "Please enter values for array!" <<endl;

		cin >> a[i] ;
	}

	cout << "the first element in the array is:" << a[0] << endl ;

	cout << "please enter the element to be searched!" << endl;
	cin >> n ;
	int b = binarysearch(a,0,4,n) ; 
	cout<< "the number that u searched is at index " <<b << endl ;
}

