#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

vector<int> Merge(vector<int> a1, vector<int> a2, int len_a1, int len_a2) {
	int len_b = len_a1 + len_a2;
	vector<int> b;

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < len_b) {
		if ((j < len_a1) && (k < len_a2)) {
			if (a1[j] < a2[k]) {
				b.push_back(a1[j]);
				j++;
			}
			else {
				b.push_back(a2[k]);
				k++;
			}
		}
		else {
			if (j < len_a1) {
				b.push_back(a1[j]);
				j++;
			}
			else {
				b.push_back(a2[k]);
				k++;
			}
		}
		i++;
	}
	return b;
}

vector<int> MergeSort(vector<int> a, int len_a) {
	if (len_a == 1) return a;

	int len_a1 = len_a/2;
	int len_a2 = len_a - len_a1;

	vector<int> a1(a.begin(), a.begin() + len_a1);
	vector<int> a2(a.begin() + len_a1, a.end());

	a1 = MergeSort(a1, len_a1);
	a2 = MergeSort(a2, len_a2);

	return Merge(a1, a2, len_a1, len_a2);
}


int main() {
	int n;
	scanf("%d", &n);
	vector<int> a;

	for (int i = 0; i < n; i++) {
		int temp;
		scanf("%d", &temp);
		a.push_back(temp);
	}
	// vector<int> a = {3, 9, 1, 0, 5, 7, 2, 4, 8, 6};

	a = MergeSort(a, a.size());

	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}

	return 0;
}