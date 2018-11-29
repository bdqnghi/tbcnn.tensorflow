/*
 * SelectionSort.h
 *
 *  Created on: Oct 18, 2015
 *      Author: lakshay
 */

#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_
#include <vector>

namespace std {

class SelectionSort {
public:
	SelectionSort();
	virtual ~SelectionSort();
	//iterative sorts for vectors and arrays
	void SelectionSortIterative(vector<int>& v, int order);
	void SelectionSortIterative(int v[], int order );

	//Recursive sorts for vectors and arrays
	void SelectionSortRecursive(vector<int>& v,int size, int order);
	void SelectionSortRecursive(int v[], int size, int order );


};




} /* namespace std */
#endif /* SELECTIONSORT_H_ */
