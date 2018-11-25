

#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

template<typename T>
class SelectionSort {
public:
	SelectionSort() {}
	virtual ~SelectionSort() {}

	static void sort(T data[], int n);

private:
	static void swap(T &a, T &b);
};

template<typename T>
void SelectionSort<T>::swap(T &a, T &b) {
	int temp = a;
	a = b;
	b = temp;
}

template<typename T>
void SelectionSort<T>::sort(T data[], int n) {
	for (int i = 0; i < n - 1; i ++) {
		int p = i;
		for (int j = 1; j < n; j++) {
			if (data[j] < data[p]) {
				p = j;
			}
		}

		if (p != i) {
			swap(data[i], data[p]);
		}
	}
}

#endif 
