/*
 * BubbleSort.h
 *
 *	可以将要排序的数组想象成一个垂直的柱体， 其中最小的元素在顶部， 最大的元素在底部。数组从底部往上扫描，
 *	如果相邻的两个元素逆序，则交互两者。首先，比较数据项data[n-1]和data[n-2], 如果逆序，则互换，
 *	接着比较data[n-2]和data[n-3], 有需要时就改变他们的顺序，一直比较到data[1]和data[0].
 *	这样最小的元素就移动到了数组的顶部。
 *	然后，以上只是第一次遍历数组。再次对数组扫描，比较剩下来的数据项，当有需要时交换他们。但是这一次，最后
 *	比较的数据项是data[2]和data[1],因为最小的元素已经在合适的位置上，也就是位置0. 第二次冒泡会将
 *	第二个最小的元素放在数组的第二个位置，即位置1,。这一过程继续下去，直到最后一次，此时只比较一次，即比
 *	较data[n-1]与data[n-2]，这时可能会执行一次交换。
 *
 *	缺点：元素需要一步步地向上冒泡直到数组的顶部，这时非常费时的，
 *	在平均情况下，冒泡排序的比较次数近似为插入排序的两倍，移动次数与插入排序相同。而冒泡排序与选择排序的比较
 *	次数是一样的，移动次数比选择排序多出n次。
 *	可以说，插入排序要比冒泡排序快两倍，而实际上也是这样。
 *
 *	算法复杂度 ：O（n2）
 *
 *  Created on: 2017-3-20
 *      Author: Davi
 */

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


#endif /* BUBBLESORT_H_ */
