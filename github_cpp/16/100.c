

#include "shell.h"

shell::shell() {
	

}

shell::~shell() {
	
}

int shell::shellPass(int* s, int low, int high) {
	int i = low;
	int j = high;
	int key = s[low];
	while (i < j) {
		while (j > i && s[j] > key) {
			j--;
		}
		if (i < j) {
			s[i] = s[j];
			i++;
		}
		while (j > i && s[i] < key) {
			i++;
		}

		if (i < j) {
			s[j] = s[i];
			j--;
		}

	}
	s[i] = key;
	return i;

}

void shell::sort(int* s, int low, int high) {
	if (low < high) {
		int mid = shellPass(s, low, high);
		sort(s, low, mid - 1);
		sort(s, mid + 1, high);
	}
}

