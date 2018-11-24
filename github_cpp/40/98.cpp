#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& data, int l, int r) {
	int left = l, right = r;

	int p = data[(left + right) / 2];

	while (left <= right) {
		while (p > data[left]) left++;
		while (p < data[right]) right--;

		if (left <= right) {
			int tmp = data[left];
			data[left] = data[right];
			data[right] = tmp;
			left++;
			right--;
		}
	}

	return left;
}

int partition2(vector<int>& arr, int left, int right)

{

	int i = left, j = right;

	int tmp;

	int pivot = arr[(left + right) / 2];



	while (i <= j) {

		while (arr[i] < pivot)

			i++;

		while (arr[j] > pivot)

			j--;

		if (i <= j) {

			tmp = arr[i];

			arr[i] = arr[j];

			arr[j] = tmp;

			i++;

			j--;

		}

	};



	return i;

}



void quickSort(vector<int>& arr, int left, int right) {

	int index = partition(arr, left, right);

	if (left < index - 1)

		quickSort(arr, left, index - 1);

	if (index < right)

		quickSort(arr, index, right);

}
// void quickSort(vector<int>& data, int left, int right) {
// 	int index = partition(data, left, right);
//
// 	if (left < index - 1) {
// 		quickSort(data, left, index - 1);
// 	}
// 	if (right > index) {
// 		quickSort(data, index, right);
// 	}
// }
void quickSort2(vector<int>& arr, int left, int right) {

	int i = left, j = right;

	int tmp;

	int pivot = arr[(left + right) / 2];



	/* partition */

	while (i <= j) {

		while (arr[i] < pivot)

			i++;

		while (arr[j] > pivot)

			j--;

		if (i <= j) {

			tmp = arr[i];

			arr[i] = arr[j];

			arr[j] = tmp;

			i++;

			j--;

		}

	};



	/* recursion */

	if (left < j)

		quickSort(arr, left, j);

	if (i < right)

		quickSort(arr, i, right);

}
int main() {
	vector<int> arr = {9,2,6,1,2,3,4};
	quickSort(arr, 0, arr.size() - 1);

	for (int i=0; i< arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}