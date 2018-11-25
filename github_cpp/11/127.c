
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>



template<typename T>
void BubbleSort(T a[], size_t n)
{
	for(size_t k = 0;k < n-1; ++k)
		for(size_t j = n-1; j > k; --j)
			if(a[j] < a[j-1]) std::swap(a[j],a[j-1]);
}







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
	
	std::vector<size_t> _heap;

	void FixHeap(int q);
};





int main()
{
	using namespace std;

	


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




template<typename T>
HeapSort<T>::HeapSort(T *a, size_t n)
	:
	
	
	
	_N(n),
	_a(a-1), 
	_heap(n+1)
{
	
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
	
	size_t x = _heap[q];

	int child_idx = 2 * q;
	while(child_idx <= _N) {

		if(child_idx < _N)
			
			if(_a[_heap[child_idx]] < _a[_heap[child_idx+1]])
				++child_idx; 

		if(_a[_heap[child_idx]] <= _a[x]) {
			
			
			_heap[q] = x;
			break;
		}

		_heap[q] = _heap[child_idx]; 
		q = child_idx;
		child_idx *= 2;
	}
	_heap[q] = x; 
}

template<typename T>
void HeapSort<T>::Sort()
{
	
	
	
	for(size_t q = _N/2; q > 0; --q) 
		FixHeap(q);

	
	for(size_t idx = _N; idx > 1; --idx) {
		
		std::swap(_heap[1],_heap[idx]); 
		--_N; 
		FixHeap(1);
	}

	
	
	

	
	std::vector<size_t> reverse_heap(_heap.size());
	for(size_t k = 1;k < _heap.size();++k)
		reverse_heap[_heap[k]] = k;

	for(size_t idx = _heap.size()-1;idx > 0; --idx) {
		if(idx != _heap[idx]){
			
			std::swap(_a[idx], _a[_heap[idx]]);
			_heap[reverse_heap[idx]] = _heap[idx];
			reverse_heap[_heap[idx]] = reverse_heap[idx];
		}
	}
}

template<typename T>
HeapSort<T>::~HeapSort()
{}

