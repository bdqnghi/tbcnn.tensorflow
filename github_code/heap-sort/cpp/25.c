#pragma once
#include "include\HeapTemplate.h"

template <typename T>
class HeapSort
{
public:
	HeapSort();
	~HeapSort();

	void SortAscending();
	void SortDescending();
	void Sort(bool Ascend);
	void SetArray(const int *arr, size_t len);
	inline const int *GetArray() { return heapArray; }
	inline size_t GetArraySize() { return arraySize; }
	void TestAllSort() const;

private:
	HeapTemplate<T> *heapArray;

	size_t arraySize;
};

template <typename T>
HeapSort<T>::HeapSort()
{
}

template <typename T>
HeapSort<T>::~HeapSort()
{
	if (heapArray != NULL)
		delete[] heapArray;
}

template <typename T>
void HeapSort<T>::SortAscending()
{
	Sort(true);
}

template <typename T>
void HeapSort<T>::SortDescending()
{
	Sort(false);
}

template <typename T>
void HeapSort<T>::Sort(bool Ascend)
{
	heapArray->Insert()
}

template <typename T>
void HeapSort<T>::SetArray(const int * arr, size_t len)
{
	if (heapArray != NULL)
		delete[] heapArray;

	heapArray = new HeapTemplate<T>[len];
	arraySize = len;

	for (int i = 0; i < len; i++)
	{
		heapArray->Insert()
	}
}

template <typename T>
void HeapSort<T>::TestAllSort() const
{
}

// sort �Լ�ȣ�� �ϳ��� inline�� ������ ���ΰ�