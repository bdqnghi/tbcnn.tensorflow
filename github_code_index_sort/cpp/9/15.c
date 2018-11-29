/*
 * SelectionSort.h
 *
 * 基本思想是：先找出数组中的最小元素，将其与第一个位置上的元素进行交互。然后在剩余元素data[1], ..., data[n-1]中找到
 * 最小的元素，把它放到第二个位置上
 *
 * 优点：赋值次数少，这一点是其他算法无法比拟的
 * 缺点：如果数据项已经在其合适的位置还是会交换（本程序通过条件判断已经避免了这种问题）
 *
 * 算法复杂度 ：O（n2）
 *
 *  Created on: 2017-3-20
 *      Author: Davi
 */

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

#endif /* SELECTIONSORT_H_ */
