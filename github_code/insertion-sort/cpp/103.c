/*
 * InsertionSort.cpp
 *
 *  Created on: Sep 12, 2015
 *      Author: ericwadkins
 */

#include "InsertionSort.h"

template<typename T>
std::vector<T> InsertionSort::sort(std::vector<T> x) {
	T temp;
	for (int i = 1; i < x.size(); i++) {
		for (int j = i; j > 0; j--) {
			if (x[j - 1] > x[j]) {
				temp = x[j - 1];
				x[j - 1] = x[j];
				x[j] = temp;
			}
		}
	}

	return x;
}
