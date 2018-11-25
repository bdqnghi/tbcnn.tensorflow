



#ifndef DATA_STRUCTURE_CHAPTER_2_2_1_2_INSERTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_2_2_1_2_INSERTION_SORT_H_

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

#endif 
