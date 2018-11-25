#include <iostream>

using namespace std;

void counting_sort(int ia[], int size, int base) {
	int count[size];
	int result[size];
	for (int i = 0; i < size; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		count[(ia[i]/base)%size]++;
	}
	for (int i = 1; i < size; i++) {
		count[i] += count[i-1];
	}
	for (int i = size-1; i >= 0; i--) {
		result[--count[(ia[i]/base)%size]] = ia[i];
	}
	for (int i = 0; i < size; i++) {
		ia[i] = result[i];
	}
}

void print(int ia[], int size) {
	for (int i = 0; i < size; i++) {
		cout << ia[i] << ' ';
	}
	cout << endl;
}


int main() {
	int ia[] = {40, 12, 45, 32, 33, 1, 22};
	int size = sizeof(ia) / sizeof(ia[0]);
	
	print(ia, size);
	counting_sort(ia, size, 1);
	counting_sort(ia, size, size);
	print(ia, size);
}
