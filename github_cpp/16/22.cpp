#include <iostream>

using namespace std;

#define pa(a, n) do { \
	for (int i = 0; i < n; ++i) \
		cout << a[i] << " "; \
	cout << endl; \
} while(0)

void shell_sort(int* a, int n) {
	for (int gap = n; gap > 0; gap >>= 1) {
		for (int i = gap; i < n; ++i) {
			int tmp = a[i];
			int j;
			for (j = i - gap; j >= 0 && a[j] > tmp; j -= gap) {
				a[j+gap] = a[j];
			}
			a[j+gap] = tmp;
		}
	}
}

int main() {
    int a[] = {321, 32, 32, 43, 4, 65, 87, 32, 4342, 43, 5454, 6776, 564};
	const int n = sizeof(a)/sizeof(a[0]);
	pa(a, n);
    shell_sort(a, n);
	pa(a, n);

    return 0;
}
