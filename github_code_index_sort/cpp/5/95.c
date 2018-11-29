#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void swap(int *a, int *b);
void bubblesort(int *a, int n);

int main(int argc, char *argv[]) {
	int a[] = {3,4,21,2,1,5,7,8,9};
	int n = 9;
	bubblesort(a,n);
	for (int i= 0; i< n; i++)
		cout<<a[i]<<" ";
}
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void bubblesort(int *a, int n){
	for (int i = 0; i< n-1; i++){
		for (int j =i+1; j<n ; j++)
			if (a[i] >= a[j]) swap(&a[i],&a[j]);
	}
}
