//
// Created by hoshino on 18-9-15.
//

#ifndef CPP_QUICK_SORT_HPP
#define CPP_QUICK_SORT_HPP

#include <iostream>

auto partition(int arr[], int low, int high) -> int {
	int pivotKey = arr[low];
	while (low != high) {        //结束条件是 low 和 high 指向 pivotKey (原材料中是 low < high
		while (low < high && arr[high] >= pivotKey)        //从 high 开始搜索, 找到第一个比 pivotKey 小的元素, 并将 high 指向它
			high --;
		std::swap(arr[low], arr[high]);        //交换元素
		//此时 high 指向 pivotKey
		while (low < high && arr[low] <= pivotKey)        //从 low 开始搜索, 找到第一个比 pivotKet 大的元素, 并将 low 指向它
			low ++;
		std::swap(arr[low], arr[high]);        //交换元素
		//此时 low 又指回了 pivotKey
	}


	return low;
}

auto q_sort(int *arr, const int &low, const int &high) -> void {
	if (low != high) {        //当排序区间只有 1 个元素的时候, 执行结束, 否则进行排序
		int pivot = partition(arr, low, high);        //将 arr 变为枢轴左边均比枢轴右边小, 并返回枢轴
		q_sort(arr, low, pivot - 1);        //对左边排序
		q_sort(arr, pivot + 1, high);        //对右边排序
	}
}

auto quick_sort(int arr[], const int &begin, const int &end) -> void {
	q_sort(arr, begin, end - 1);
}

auto main(int, char **) -> int {
	int v[]{4, 2, 4, 5, 1};
	quick_sort(v, 0, 5);

	for (int i : v) {
		std::cout << i << std::endl;
	}

	return 0;
}

#endif //CPP_QUICK_SORT_HPP
