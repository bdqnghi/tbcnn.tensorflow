/*
  Introduction to Algorithms, CLRS
  Chapter 2, Getting Started
  Implementation of Bubble Sort
  Author : Rakesh Kumar @ cpp.rakesh@gmail.com
  Date : July 7th, 2016
*/

#ifndef DATA_STRUCTURE_CHAPTER_2_BUBBLE_H_
#define DATA_STRUCTURE_CHAPTER_2_BUBBLE_H_

#include <vector>

template <typename T>
class BubbleSort {
public:
    BubbleSort();
    ~BubbleSort();

    void Sort(std::vector<T>& V);
	
private:
    void m_swap(T& A, T& B);
};

template <typename T>
BubbleSort<T>::BubbleSort() {}

template <typename T>
BubbleSort<T>::~BubbleSort() {}

template <typename T>
void BubbleSort<T>::Sort(std::vector<T>& V) {
    for (std::size_t i = 0; i < V.size() - 2; ++i) {
        for (int j = V.size() - 1; j > i; --j) {
            if (V[j - 1] > V[j])
                m_swap(V[j - 1], V[j]);
        }
    }
}

template <typename T>
void BubbleSort<T>::m_swap(T& A, T& B) {
    T t = A;
    A = B;
    B = t;
}

#endif // DATA_STRUCTURE_CHAPTER_2_BUBBLE_H_
