/*
  Introduction to Algorithms, CLRS
  Chapter 2, Getting Started
  Implementation of Selection Sort
  Author : Rakesh Kumar @ cpp.rakesh@gmail.com
  Date : July 7th, 2016
*/

/*
  Time complexity of Merge Sort is O(n ^ 2).
*/

#ifndef DATA_STRUCTURE_CHAPTER_2_SELECTION_SORT_H_
#define DATA_STRUCTURE_CHAPTER_2_SELECTION_SORT_H_

#include <vector>

template <typename T>
class SelectionSort {
public:
    SelectionSort();
    ~SelectionSort();

    void Sort(std::vector<T>& V);

private:
    int m_find_min(const std::vector<T>& A, const int& start_index);
    void m_swap(T& A, T& B);
};

template <typename T>
SelectionSort<T>::SelectionSort() {}

template <typename T>
SelectionSort<T>::~SelectionSort() {}

template <typename T>
void SelectionSort<T>::Sort(std::vector<T>& V) {
    for (std::size_t i = 0; i < V.size(); ++i) {
        const int index = m_find_min(V, i);
        if (i != index)
            m_swap(V[i], V[index]);
    }
}

template <typename T>
int SelectionSort<T>::m_find_min(const std::vector<T>& V, const int& start_index) {
    int index = start_index;
    int min = V[start_index];
    for (int i = start_index + 1; i < V.size(); ++i) {
        if (V[i] < min) {
            min = V[i];
            index = i;
        }
    }

    return index;
}

template <typename T>
void SelectionSort<T>::m_swap(T& A, T& B) {
    T t = A;
    A = B;
    B = t;
}

#endif // DATA_STRUCTURE_CHAPTER_2_SELECTION_SORT_H_
