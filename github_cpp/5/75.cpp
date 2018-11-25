






#include <vector>
#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
void InsertionSort(vector<int>& arr) {
	for(int i=1; i<arr.size(); i++) {
		int cur = arr[i];
		int j = i -1;
		while(j >= 0 && arr[j] > cur) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = cur;
	}
}
int main() {
	std::vector<int> v = {5, 1, 3, 2, 0};
	InsertionSort(v);
	for(const int elem: v) {
		cout << elem << " ";
	}
	cout << endl;
	return 0;
}