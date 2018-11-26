#if !defined(AFX_SHELLSORT_H__1A6501A1_BA43_11D5_9B3B_004095418E0F__INCLUDED_)
#define AFX_SHELLSORT_H__1A6501A1_BA43_11D5_9B3B_004095418E0F__INCLUDED_

#ifndef __API_INTERN__
#include "ge_math.h"
#endif

template <class ShellsortItemType> class CShellSort
{
public:
	CShellSort();
	virtual ~CShellSort();

	void Sort(ShellsortItemType* pArray, Int32(*fnCompareItem)(const ShellsortItemType a, const ShellsortItemType b), Int32 lNumItems);
	void Sort(ShellsortItemType* pArray, Int32(*fnCompareItem)(const ShellsortItemType* a, const ShellsortItemType* b), Int32 lNumItems);
	void Sort(ShellsortItemType* pArray, Int32(*fnCompareItem)(const ShellsortItemType a, const ShellsortItemType b, const void* pData), Int32 lNumItems, const void* pData);
	void Sort(ShellsortItemType* pArray, Int32(*fnCompareItem)(const ShellsortItemType* a, const ShellsortItemType* b, const void* pData), Int32 lNumItems, const void* pData);

protected:
};


template<class T> CShellSort<T>::CShellSort()
{
}

template<class T> CShellSort<T>::~CShellSort()
{
}

template<class T> void CShellSort<T>::Sort(T* pArray, Int32(*fnCompareItem)(const T a, const T b), Int32 lNumItems)
{
	Int32 i, j, h;
	T v;

	for (h = 1; h <= lNumItems / 9; h = 3 * h + 1) { }
	for (; h > 0; h /= 3)
	{
		for (i = h; i < lNumItems; i++)
		{
			v = pArray[i];
			j = i;
			while (j > h - 1 && fnCompareItem(pArray[j - h], v) > 0)
			{
				pArray[j] = pArray[j - h]; j -= h;
			}
			pArray[j] = v;
		}
	}
}

template<class T> void CShellSort<T>::Sort(T* pArray, Int32(*fnCompareItem)(const T* a, const T* b), Int32 lNumItems)
{
	Int32 i, j, h;
	T v;

	for (h = 1; h <= lNumItems / 9; h = 3 * h + 1) { }
	for (; h > 0; h /= 3)
	{
		for (i = h; i < lNumItems; i++)
		{
			v = pArray[i];
			j = i;
			while (j > h - 1 && fnCompareItem(&(pArray[j - h]), &v) > 0)
			{
				pArray[j] = pArray[j - h]; j -= h;
			}
			pArray[j] = v;
		}
	}
}

template<class T> void CShellSort<T>::Sort(T* pArray, Int32(*fnCompareItem)(const T a, const T b, const void* pData), Int32 lNumItems, const void* pData)
{
	Int32 i, j, h;
	T v;

	for (h = 1; h <= lNumItems / 9; h = 3 * h + 1) { }
	for (; h > 0; h /= 3)
	{
		for (i = h; i < lNumItems; i++)
		{
			v = pArray[i];
			j = i;
			while (j > h - 1 && fnCompareItem(pArray[j - h], v, pData) > 0)
			{
				pArray[j] = pArray[j - h]; j -= h;
			}
			pArray[j] = v;
		}
	}
}

template<class T> void CShellSort<T>::Sort(T* pArray, Int32(*fnCompareItem)(const T* a, const T* b, const void* pData), Int32 lNumItems, const void* pData)
{
	Int32 i, j, h;
	T v;

	for (h = 1; h <= lNumItems / 9; h = 3 * h + 1) { }
	for (; h > 0; h /= 3)
	{
		for (i = h; i < lNumItems; i++)
		{
			v = pArray[i];
			j = i;
			while (j > h - 1 && fnCompareItem(&(pArray[j - h]), &v, pData) > 0)
			{
				pArray[j] = pArray[j - h]; j -= h;
			}
			pArray[j] = v;
		}
	}
}


#endif // !defined(AFX_SHELLSORT_H__1A6501A1_BA43_11D5_9B3B_004095418E0F__INCLUDED_)
