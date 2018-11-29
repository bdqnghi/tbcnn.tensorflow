#include <iostream>
#include <vector>
#include "Sort.h"

using namespace std;

Sort::Sort(vector<var_type> _data_array) {

	for (int i = 0; i < _data_array.size(); i++) {
		data_array.push_back(_data_array[i]);
	}

}

void Sort::selectSort() {

	for (int i = 0; i < DATA_SIZE - 1; i++) {
		var_type min = data_array[i];
		var_type temp_var = data_array[i];
		idx temp_idx = i;
		for (int j = i + 1; j < DATA_SIZE; j++) {
			if (less(data_array[j], temp_var)) {
				temp_var = data_array[j];
				temp_idx = j;
			}
		}
		exch(i, temp_idx);
	}

}

void Sort::insertSort() {

	for (int i = 1; i < DATA_SIZE; i++) {
		if (less(data_array[i - 1], data_array[i])) continue;
		idx a = i;
		while(a > 0) {
			if(less(data_array[a], data_array[a-1])) exch(a, a - 1);
			a--;
		}
	}

}

void Sort::shellSort() {

	int shell_param = 1;
	while (shell_param < DATA_SIZE / 3) shell_param = shell_param * 3 + 1;
	while (shell_param >= 1) {

		for (int i = shell_param; i < 2 * shell_param; i++) {
			for (int j = shell_param; j < DATA_SIZE; j += shell_param) {
				if (less(data_array[j - shell_param], data_array[j])) continue;
				idx a = j;
				while (a > i - shell_param) {
					if (less(data_array[a], data_array[a - shell_param])) exch(a, a - shell_param);
					a -= shell_param;
				}
			}
		}
		shell_param = shell_param / 3;
	}
	
}

void Sort::bubbleSort() {

	for (int i = 0; i < DATA_SIZE - 1; i++) {
		for (int j = i + 1; j < DATA_SIZE; j++) {
			if (less(data_array[j], data_array[i])) exch(i, j);
		}
	}

}

void Sort::mergeSort(idx low, idx high) {

	if (low < high) {
		int center = (low + high) / 2;
		mergeSort(low, center);
		mergeSort(center + 1, high);
		merge(low, high);
	}

}

void Sort::merge(idx low, idx high) {

	vector<var_type> merged_vec;
	merged_vec.resize(high - low + 1);

	idx mid = (low + high) / 2;
	idx i = low, j = mid + 1;

	for (int k = 0; k < high - low + 1; k++) {
		if (i > mid) merged_vec[k] = data_array[j++];
		else if (j > high) merged_vec[k] = data_array[i++];
		else if (less(data_array[i], data_array[j])) merged_vec[k] = data_array[i++];
		else merged_vec[k] = data_array[j++];
	}
	for (int k = 0; k < high - low + 1 ; k++) {
		data_array[k + low] = merged_vec[k];
	}

}

void Sort::quickSort(idx low, idx high) {

	if (low < high) {
		int privot = partition(low, high);
		quickSort(low, privot - 1);
		quickSort(privot + 1, high);
	}
}

int Sort::partition(idx low, idx high) {

	var_type temp = data_array[low];
	idx a = low, b = high;
	while (a < b) {
		while (a < b && data_array[b] >= temp) b--;
		exch(a, b);
		while (a < b && data_array[a] < temp) a++;
		exch(a, b);
	}
	return a;

}

bool Sort::isSorted() {

	for (int i = 0; i < sizeof(data_array) - 1; i++) {
		if (data_array[i + 1] > data_array[i]) {
			printf("The array is not sorted yet!");
			return false;	
		}
	}
	return true;

}

void Sort::exch(idx a, idx b) {

	var_type temp;
	temp = data_array[a];
	data_array[a] = data_array[b];
	data_array[b] = temp;

}

bool Sort::less(var_type a, var_type b) {

	return a < b;

}

void Sort::show() {

	for (int i = 0; i < data_array.size(); i++) {
		cout << data_array[i] << endl;
	}
	cout << endl;

}