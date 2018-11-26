#include "HeapSort.h"

template <typename T> 
HeapSort<T>::HeapSort(const Heap <T> *heap_) {
	try{
		this->heap = new Heap<T>(*heap_);
	}
	catch (std::runtime_error run_err){
		throw std::runtime_error(run_err.what());
	}
}

template <class T>
HeapSort<T>::~HeapSort()
{
	delete heap;
}

template <class T>
void HeapSort<T>::sort() {
	//heap->build_heap(a);
	for (uint i = heap->get_lenght(); i >= heap->INDEX_ROOT + 1; --i) {
		uint index_root = heap->INDEX_ROOT;
		//std::swap(heap->store[heap->INDEX_ROOT], heap->store[i]);
		heap->swap(index_root, i);
		heap->decrease_size();

		heap->heapify(index_root);
	}
}

template <class T>
const T *HeapSort<T>::get_data() {
	return this->heap->get_data();
}

template HeapSort < int > ;
template HeapSort < float >;
template HeapSort < double >;
template HeapSort < char >;
// ... add own data type
