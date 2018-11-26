#include <vector>
#include <cstdlib>
/*
Christopher Puglia
pug-3b
10/18/2015
Compiled on Visual Studio

g++ -o list pug-3b.cpp Hash.h Heap.h WordList.cpp WordList.h Grid.cpp Grid.h -std=c++0x
*/
template <class T> 
class Heap
{
public:
	Heap();
	int parent(int n);
	int left(int n);
	int right(int n);
	T getItem(int n);
	void initalizeHeap(std::vector<T> copy);
	void buildMaxHeap();
	void maxHeapify(int i);
	void heapSort();
	void buildMinHeap();
	void minHeapify(int i);
	void printHeap();
	int heapSize();
	std::vector<T> getHeap();


private:
	std::vector<T> daHeap;
	int size;
};

template <class T>
Heap<T>::Heap()
{
	daHeap.clear();
}
template <class T>
int Heap<T>::parent(int n)
{
	return (n / 2);
}
template <class T>
int Heap<T>::left(int n)
{
	return (2*n);
}
template <class T>
int Heap<T>::right(int n)
{
	return (2*n + 1);
}

template <class T>
T Heap<T>::getItem(int n)
{
	return daHeap.at(n);
}

template <class T>
void Heap<T>::initalizeHeap(std::vector<T> copy)
{
	daHeap.resize(copy.size() + 1);
	for (int i = 0; i < copy.size(); i++)
	{
		daHeap.at(i+1) = (copy.at(i));
	}
}

template<class T>
void Heap<T>::buildMaxHeap()
{
	size = daHeap.size();
	for (int i = daHeap.size()/2; i >= 1; i--) //try1
	{

		maxHeapify(i);
	}
}
template<class T>
void Heap<T>::buildMinHeap()
{
	size = daHeap.size();
	for (int i = daHeap.size() / 2; i >= 1; i--) //try1
	{

		minHeapify(i);
	}
}

template <class T>
void Heap<T>::maxHeapify(int i)
{
	int l;
	int r;
	int largest=i;

	l = left(i);
	r = right(i);

	if (l < size && daHeap[l] > daHeap[i]) {
		largest = l;
	}
	if (r < size && daHeap[r] > daHeap[i] && daHeap[r] > daHeap[l]) {
		largest = r;
	}


	

	if (largest != i) {
		
		
		T temp = daHeap[largest];
		daHeap[largest] = daHeap[i];
		daHeap[i] = temp;

		maxHeapify(largest);
	}
}

template <class T>
void Heap<T>::minHeapify(int i)
{
	int l;
	int r;
	int smallest = i;

	l = left(i);
	r = right(i);

	if (l < size && daHeap[l] < daHeap[i]) {
		smallest = l;
	}
	if (r < size && daHeap[r] < daHeap[i] && daHeap[r] < daHeap[l]) {
		smallest = r;
	}


	if (smallest != i) {


		T temp = daHeap[smallest];
		daHeap[smallest] = daHeap[i];
		daHeap[i] = temp;

		minHeapify(smallest);
	}
}


template<class T>
int Heap<T>::heapSize()
{
	return daHeap.size();
}

template<class T>
std::vector<T> Heap<T>::getHeap()
{
	return daHeap;
}
template <class T>
void Heap<T>::heapSort()
{
	buildMaxHeap();
	for (int i = daHeap.size() - 1; i > 0; i--) {
		T temp = daHeap[1];
		daHeap[1] = daHeap[i];
		daHeap[i] = temp;
		size--;
		
		maxHeapify(1);
	}
}