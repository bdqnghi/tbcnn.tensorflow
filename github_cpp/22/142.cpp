




#include<iostream>
#include<iomanip>
using namespace std;
void BucketSort(int arr[],int size){
	const int MAX_SIZE = 101;
	int bucket[MAX_SIZE];
	
	for (int i = 0; i < MAX_SIZE; ++i){
		bucket[i] = 0;
	}
	for (int i = 0; i <size; ++i)
		++bucket[arr[i]];

	for (int i = 0,j = 0; j < MAX_SIZE; ++j)
		for (int k = bucket[j]; k>0; --k)
			arr[i++] = j;
		
}
int main(){
	int arr[10] = { 10, 24, 22, 62, 1, 50, 100, 75, 2, 3 };
	BucketSort(arr, 10);
	for (int i = 0; i <10; ++i){
		cout << arr[i] << endl;
	}
	
}


