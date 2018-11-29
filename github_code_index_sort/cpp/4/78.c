/*
PARENT(i)
	return floor(i)
LEFT(i)
	return 2i
RIGHT
	return 2i + 1

1. MAX-HEAPIFY
2. BUILD-MAX-HEAP
3. HEAPSORT
*/

/*
MAX-HEAPIFY(A, i)
1.		l = LEFT(i)
2.		r = RIGHT(i)
3.		if l <= A.heap-size and A[l] > A[i]
4.			largest = l;
5.		else largest = i
6.		if r <= A.heap-size and A[r] > A[largest]
7.			largest = r;
8.		if largest != i
9.			exchange A[i] with A[largest]
10.		MAX-HEAPIFY(A, largest)
*/

/*
BUILD-MAX-HEAP(A)
1.		A.heap-size = A.length
2.		for i = floor(A.length / 2) down to 1
3.			MAX-HEAPIFY(A, i)
*/

/*
HEAPSORT(A)
1.		BUILD-MAX-HEAP(A)
2.		for i = A.length down to 2
3.			exchange A[1] with A[i]
4.			A.heap-size  = A.heap-size - 1
5.			MAX-HEAPIFY(A, 1)
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class HEAPSORT{
private:
	vector<T> m_pArray;
private:
	void MAX_HEAPIFY(int i);
	void BUILD_MAX_HEAP();

	int PARENT(int i) { return i /2 ; }
	int LEFT(int i) { return 2*i + 1; }
	int RIGHT(int i) { return 2*i + 2; }

	void PRINT(const vector<T>& array);
public:
	HEAPSORT(const vector<T>& array);
	~HEAPSORT();

	void HEAP_SORT();
};

template<class T>
HEAPSORT<T>::HEAPSORT(const vector<T>& array){
	m_pArray.assign(array.begin(), array.end());
}

template <class T>
HEAPSORT<T>::~HEAPSORT(){

}

template <class T>
void HEAPSORT<T>::PRINT(const vector<T>& array){
	for(size_t i = 0; i < array.size(); ++i){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

template <class T>
void HEAPSORT<T>::MAX_HEAPIFY(int i){
	size_t l = LEFT(i);
	size_t r = RIGHT(i);
	int largest = i;
	if(l < m_pArray.size() && m_pArray[l] > m_pArray[i]){
		largest = l;
	}else largest = i;

	if(r < m_pArray.size() && m_pArray[r] > m_pArray[largest])
		largest = r;

	if(largest != i){
		swap(m_pArray[i], m_pArray[largest]);
		MAX_HEAPIFY(largest);
	}
}

template <class T>
void HEAPSORT<T>::BUILD_MAX_HEAP(){
	size_t start = m_pArray.size()/ 2 - 1;
	for(int i = start; i >=0; --i)
		MAX_HEAPIFY(i);
}

template <class T>
void HEAPSORT<T>::HEAP_SORT(){
	vector<T> temp;
	BUILD_MAX_HEAP();
	PRINT(m_pArray);
	for(int i = m_pArray.size() -1; i >= 0; --i){
		temp.push_back(m_pArray[0]);
		swap(m_pArray[0], m_pArray[i]);
		m_pArray.pop_back();
		MAX_HEAPIFY(0);
	}
	PRINT(temp);
}

int main(){
	vector<int> A;
	for(int i = 0; i< 10; ++i)
		A.push_back(i);
	random_shuffle(A.begin(), A.end());

	HEAPSORT<int> heap(A);
	heap.HEAP_SORT();

	return 1;
}

