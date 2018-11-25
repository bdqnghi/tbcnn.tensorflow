

#include<iostream>

using namespace std;

void mergesort(int*, int);
void merge(int*, int*, int*, int, int);
void display(int* , int);

void mergesort(int *arr, int size){
	
	int n = size;
	
	if(n < 2)
		return;
		
	int mid = n/2;
	
	
	
	
	int left[mid], right[n-mid];
		
	
	for (int i = 0; i < mid; i++)
		left[i] = arr[i];
	
	
	for (int j = mid; j < n; j++)
		right[j-mid] = arr[j];
			
	
	mergesort(left, mid);
	
	
	mergesort(right, n-mid);
	
	
	merge(left, right, arr, mid, n-mid);
	
}

void merge(int* l, int* r, int* a, int sizeleft, int sizeright){
	
	int nl, nr; 
	int i, j, k;
	
	nl = sizeleft;
	nr = sizeright;
	
	i = 0; 
	j = 0; 
	k = 0; 
	
	
	while ((i < nl) && (j < nr)){
		
		if (l[i] <= r[j]){
			
			a[k] = l[i];
			i++;
			
		}
		else {
			
			a[k] = r[j];
			j++;
			
		}
		
		k++;
	}
	
	
	while (i < nl){
		
		a[k] = l[i];
		i++;
		k++;
		
	}
	
	
	while (j < nr){
		
		a[k] = r[j];
		j++;
		k++;
		
	}

}

void display(int *arr, int size){
	
	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

}

int main()
{
	
	int b[] = {12,10,43,23,78,45,123,56,98,41,90,24};
	
	int size = sizeof(b)/sizeof(int);
	
	cout << "\nOriginal array :\n";
	display(b, size);
	mergesort(b,size);
	cout << "\nArray after merge sort :\n";
	display(b, size);

}
