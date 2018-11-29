/*
Program to perform heap-sort on an input array.
*/
#include <iostream>
#include <fstream>
using namespace std;

void heapify(int *a, int i, int n) {
	if (i > n / 2)
		return;

	int	l = 2 * i, r = 2 * i + 1;
	int s;
	if (a[l] > a[r] && r<=n) {
		s = r;
	}
	else {
		s = l;
	}
	if (a[i] > a[s]) {
		swap(a[i], a[s]);
		heapify(a, s, n);
	}
}


void heapsort(int *a, int n) {
	for (int i = n / 2; i > 0; i--) {
		heapify(a, i, n);
	}
	for (int i = n; i > 1; i--) {
		swap(a[i], a[1]);
		n--;
		heapify(a, 1, n);
	}
}

int main() {
	ifstream in;
	in.open("heap_in.txt");
	int n;
	in >> n;
	int *a = new int[n+2];
	for (int i = 1; i <= n; i++)
		in >> a[i];

	heapsort(a, n);

	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
}