#include <iostream>
#include <cstdlib>
#include <vector>

std::vector<int> QSortMerge(std::vector<int> &l, std::vector<int> &r);

void Swap (int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

std::vector<int> QSort(std::vector<int> &v) {
	
	if(v.size() <= 1) {return v;}

	std::vector<int> left, right;
	int pivot = v.size() / 2,
		l_index = 0,
		r_index = v.size() - 1;

	do {
		if (v[l_index] <= v[pivot]) { ++l_index; left.push_back(v[l_index]); }
		if (v[r_index] > v[pivot]) { --r_index; right.push_back(v[r_index]); }
		if (v[l_index] > v[pivot] && v[r_index] < v[pivot]) {
			Swap(v[l_index], v[r_index]);
		}
	} while (l_index < r_index);
	
	Swap(v[l_index], v[pivot]);

	left = QSort(left);
	right = QSort(right);

	return QSortMerge(left, right);

}

std::vector<int> QSortMerge(std::vector<int> &l, std::vector<int> &r) {

	std::vector<int> result;
	for (auto &i : l) {
		result.push_back(i);
	}
	for (auto &i : r) {
		result.push_back(i);
	}
	return result;
}

int main() {
	std::vector<int> arr = { 2, 1, 32, 7, 5, 3 };

	auto out = QSort(arr);

	for (auto i : out) {
		std::cout << i << "\t";
	}

	return 0;
}
