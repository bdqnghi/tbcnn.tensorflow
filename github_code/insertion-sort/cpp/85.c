/*
  Introduction to Algorithms
  Chapter 2: Getting Started
  Exersice, 2.1-2 implementation for decreasing Insrtion Sort
  Author: Rakesh Kumar @ cpp.rakesh@gmail.com
  Date: June 10th, 2016
 */

/*
  2.1-2
  Rewrite the INSERTION-SORT procedure to sort into nonincreasing instead of nondecreasing
  order.
 */

#ifndef DATA_STRUCTURE_CHAPTER_2_2_1_2_INSERTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_2_2_1_2_INSERTION_SORT_H_

#include <vector>


template <typename T>
void InsertionSort<T>::Sort(std::vector<T>& V) {
	for (std::size_t i = 1; i < V.size(); ++i) {
		int j = i;
		while (j > 0 && V[j - 1] < V[j]) {
			m_swap(V[j - 1], V[j]);
			--j;
		}			
	}
}

template <typename T>
void InsertionSort<T>::m_swap(T& A, T& B) {
	T t = A;
	A = B;
	B = t;
}

#endif // DATA_STRUCTURE_CHAPTER_2_2_1_2_INSERTION_SORT_H_
