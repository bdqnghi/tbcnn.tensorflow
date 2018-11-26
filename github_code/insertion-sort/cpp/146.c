/*
  Introduction to Algorithms, CLRS
  Chapter 2, Getting Started
  Insertion Sort implementation
  Author : Rakesh Kumar @ cpp.rakesh@gmail.com
  Date : June 10th, 2016
 */
  
#ifndef DATA_STRUCTURE_CHAPTER_1_INSERTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_1_INSERTION_SORT_H_

#include <vector>

template <typename T>
class InsertionSort {
public:
	InsertionSort();
	~InsertionSort();

	void Sort(std::vector<T>& V);
	void SortReverse(std::vector<T>& V);
};

template <typename T>
InsertionSort<T>::InsertionSort() {}

template <typename T>
InsertionSort<T>::~InsertionSort() {}

template <typename T>
void InsertionSort<T>::Sort(std::vector<T>& V) {
	for (std::size_t i = 1; i < V.size(); ++i) {
		int j = i;
		const T key = V[j];
		while (j > 0 && V[j - 1] > key) {
			V[j] = V[j - 1];
			--j;
		}
		V[j] = key;
	}
}

template <typename T>
void InsertionSort<T>::SortReverse(std::vector<T>& V) {
	for (std::size_t i = 1; i < V.size(); ++i) {
		int j = i;
		const T key = V[j];
		while (j > 0 && V[j - 1] < key) {
			V[j] = V[j - 1];
			--j;
		}
		V[j] = key;
	}
}

#endif // DATA_STRUCTURE_CHAPTER_1_INSERTION_SORT_H_
