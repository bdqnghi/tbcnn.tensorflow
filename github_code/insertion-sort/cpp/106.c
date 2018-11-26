/*
  Introduction to algorithms, CSLR
  Chapter:2, Getting Started.
  Solution for Exersice 2.3-4, Binary Search for Insertion Sort.
  Rakesh Kumar @ cpp.rakesh@gmail.com
  June 14th, 2016
 */

#ifndef DATA_STRUCTURE_CHAPTER_2_2_3_6_INSERTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_2_2_3_6_INSERTION_SORT_H_

#include <vector>

template <typename T>
class InsertionSort {
public:
	InsertionSort();
	~InsertionSort();

	void Sort(std::vector<T>& V);

private:
	void m_swap(T& A, T& B);
};

template <typename T>
InsertionSort<T>::InsertionSort() {}

template <typename T>
InsertionSort<T>::~InsertionSort() {}

template <typename T>
void InsertionSort<T>::Sort(std::vector<T>& V) {
	for (std::size_t i = 1; i < V.size(); ++i) {
		int p = 0;
		int q = i;

		while (p < q) {
			if (V[p] > V[p + 1])
				m_swap(V[p], V[p + 1]);

			if (V[q - 1] > V[q])
				m_swap(V[q - 1], V[q]);

			++p;
			--q;
		}
	}
}

template <typename T>
void InsertionSort<T>::m_swap(T& A, T& B) {
	T t = A;
	A = B;
	B = t;
}

#endif // DATA_STRUCTURE_CHAPTER_2_2_3_6_INSERTION_SORT_H_
