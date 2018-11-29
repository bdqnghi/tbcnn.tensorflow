/*
  Introduction to algorithms, CSLR
  Chapter:2, Getting Started.
  Solution for Exersice 2.3-4, Recursive Insertion Sort.
  Rakesh Kumar @ cpp.rakesh@gmail.com
  June 14th, 2016
 */

#ifndef DATA_STRUCTURE_CHAPTER_2_2_3_4_INSERTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_2_2_3_4_INSERTION_SORT_H_

#include <vector>

template <typename T>
class InsertionSort {
public:
	InsertionSort();
	~InsertionSort();
	void Sort(std::vector<T>& V);
	
private:
	void m_sort(std::vector<T>& V, const int& index, const int& size);
	void m_swap(T& A, T& B);
};

template <typename T>
InsertionSort<T>::InsertionSort() {}

template <typename T>
InsertionSort<T>::~InsertionSort() {}

template <typename T>
void InsertionSort<T>::Sort(std::vector<T>& V) {
	m_sort(V, 1, V.size());
}

template <typename T>
void InsertionSort<T>::m_sort(std::vector<T>& V, const int& index, const int& size) {
	if (index < size) {
		int i = index;
		while (i > 0 && V[i - 1] > V[i]) {
			m_swap(V[i - 1], V[i]);
			--i;
		}

		m_sort(V, index + 1, size);
	}
}

template <typename T>
void InsertionSort<T>::m_swap(T& A, T& B) {
	T t = A;
	A = B;
	B = t;
}

#endif // DATA_STRUCTURE_CHAPTER_2_2_3_4_INSERTION_SORT_H_
