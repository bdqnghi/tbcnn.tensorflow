/*
Heapsort template class in C++.
Michael Seyfert <michael@codesand.org>

Copyright GNU GPL 2
 */
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

// Bubble Sort.
// O(n^2) worst case / best case.
template<typename T>
void BubbleSort(T a[], size_t n)
{
	for(size_t k = 0;k < n-1; ++k)
		for(size_t j = n-1; j > k; --j)
			if(a[j] < a[j-1]) std::swap(a[j],a[j-1]);
}

//==============================================================================
// HeapSort
//
// Floyd's Heap Sort
// We assume operator<() and operator<=() supported for type T.
//==============================================================================
template<typename T>
class HeapSort
{
public:
	HeapSort(T *a, size_t n);
	HeapSort(std::vector<T> &a);
	~HeapSort();
	void Sort();

private:
	int _N;
	T *_a;
	// The heap is just a vector of indexes into input 'a'
	std::vector<size_t> _heap;

	void FixHeap(int q);
};
//==============================================================================

// Quick Sort. // TODO.
// Merge Sort. // TODO.

int main()
{
	using namespace std;

	// hash: (int)(Math.sqrt(97)*(13*i + 1)*(19*i + 2)+i - 17) % 1000;
//	int a[] = {8,8*2,8*2,8*4,9*5};
//	static const int N = sizeof(a) / sizeof(a[0]);
	vector<int> a(8);
	a[0] = -2;
	a[1] = -1;
	a[2] = 0;
	a[3] = 20;
	a[4] = 20;
	a[5] = 120;
	a[6] = 1200;
	a[7] = 12003;
	static const int N = a.size();

	int count = 0;
	do{
		++count;
		for(int k = 0;k < N;++k)
			cout << ' ' << a[k];

		cout << " -> ";

		vector<int> b(a);
		HeapSort<int>(b).Sort();

		for(int k = 0;k < N;++k)
			cout << ' ' << b[k];

		cout << endl;

	}while(next_permutation(&a[0],&a[N]));

	cout << count << endl;
}

//==============================================================================
// HeapSort
//==============================================================================
template<typename T>
HeapSort<T>::HeapSort(T *a, size_t n)
	:
	// The heap is a binary tree stored as a linear array.
	// This is Floyd's heapsort algorithm, so we do not use the 0 index
	//  in the heap.
	_N(n),
	_a(a-1), // This makes indexing by 1 easier.
	_heap(n+1)
{
	// Start with the elements of the heap in the order given.
	for(size_t k = 1;k < n+1;++k)
		_heap[k] = k;
}

template<typename T>
HeapSort<T>::HeapSort(std::vector<T> &a)
	:
	_N(a.size()),
	_a(reinterpret_cast<T*>(&a[0])-1),
	_heap(a.size()+1)
{
	for(size_t k = 1;k < _heap.size();++k)
		_heap[k] = k;
}

template<typename T>
void HeapSort<T>::FixHeap(int q)
{
	// Fix the heap for index q.
	size_t x = _heap[q];

	int child_idx = 2 * q;
	while(child_idx <= _N) {

		if(child_idx < _N)
			// A second child exists.
			if(_a[_heap[child_idx]] < _a[_heap[child_idx+1]])
				++child_idx; // make it the index of the larger child.

		if(_a[_heap[child_idx]] <= _a[x]) {
			// x is not lesser than any of its children.
			// so, x belongs at index q, and the heap is fixed up to q.
			_heap[q] = x;
			break;
		}

		_heap[q] = _heap[child_idx]; // Promote the larger child of x.
		q = child_idx;
		child_idx *= 2;
	}
	_heap[q] = x; // x has been demoted all the way to an index of a leaf.
}

template<typename T>
void HeapSort<T>::Sort()
{
	// Fix the heap.
	// This makes the root the largest element, and
	// a parent is larger than its children.
	for(size_t q = _N/2; q > 0; --q) // Start at the parent of the last element.
		FixHeap(q);

	// Now we remove all values from the heap.
	for(size_t idx = _N; idx > 1; --idx) {
		//std::swap(_a[_heap[1]], _a[idx]); // Put a[idx] = max element
		std::swap(_heap[1],_heap[idx]); // fill the vacancy with the last element.
		--_N; // We got the max, scale down the tree size.
		FixHeap(1);
	}

	// The heap is now sorted. We modify the input array here.
	// By sorted we mean an array of indices smallest to largest.
	// This will take at most input size N swaps.

	// setup reverse heap (index->heap index)
	std::vector<size_t> reverse_heap(_heap.size());
	for(size_t k = 1;k < _heap.size();++k)
		reverse_heap[_heap[k]] = k;

	for(size_t idx = _heap.size()-1;idx > 0; --idx) {
		if(idx != _heap[idx]){
			// Put the largest element at the end.
			std::swap(_a[idx], _a[_heap[idx]]);
			_heap[reverse_heap[idx]] = _heap[idx];
			reverse_heap[_heap[idx]] = reverse_heap[idx];
		}
	}
}

template<typename T>
HeapSort<T>::~HeapSort()
{}
//==============================================================================
