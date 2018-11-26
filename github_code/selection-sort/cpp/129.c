#include <iostream>
#include <iterator>
#include <array>

using namespace std;

int arr[] = {2,1,7,4,3,8,66,11};
int len = sizeof(arr)/sizeof(arr[0]);

void selectionsort(int arr[]);


int main(){

	selectionsort(arr);

	for(int i = 0; i < len; i++){

		cout << arr[i] << " " ;

	}

	cout << endl;

}

void selectionsort(int arr[]){

	int min;
	for(int i = 0 ; i < len ; i++){

		min = i;

		for(int j = min ; j < len ; j++){

			if(arr[j] < arr[min]){

				arr[j] = arr[min] + arr[j];
				arr[min] = arr[j] - arr[min];
				arr[j] = arr[j] - arr[min];	

			}

		}

	}

}
