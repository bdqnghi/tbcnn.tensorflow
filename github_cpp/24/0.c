#include <iostream>

using namespace std;

int main() {
	int *array;
	int n, low, high, mid, key, found = 0;
	
	cout << "Enter number of elements" << endl;
	cin >> n;
	
	array = new int[n];
	
	cout << "Enter the elements" << endl;
	for(int i = 0; i < n; i++){
		cin >> array[i];
	}
	
	cout << "Enter a number to search" << endl;
	cin >> key;
	
	low = 0;
	high = n - 1;
	
	while(low <= high) {
		mid = (low + high) / 2;
		
		if(array[mid] == key) {
			cout << "Element found at index = " << mid << endl;
			found = 1;
			break;
		}
		
		else if(array[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	
	if(!found)
		cout << "Element not found" << endl;
		
	return 0;
}