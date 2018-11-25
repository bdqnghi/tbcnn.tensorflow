

#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

template<typename T>
class BubbleSort {
public:
	BubbleSort();
	virtual ~BubbleSort();

	static void sort(T data[], int n);

private:
	static void swap(T &a, T &b);
};

template<typename T>
void BubbleSort<T>::swap(T &a, T &b) {
	int temp = a;
	a = b;
	b = temp;
}

template<typename T>
void BubbleSort<T>::sort(T data[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = n - 1; j > i; j--) {
			if (data[j] < data[j - 1]) {
				swap(data[j], data[j - 1]);
			}
		}
	}
}


#endif 
