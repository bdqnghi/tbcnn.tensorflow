

#include "utilities.hpp"

vector <int> heap; 

void maxHeapify(int i, int size)
{
	

	int largest, left, right;
	left = i*2 + 1; 
	right = i*2 + 2; 
	
	
	if (left < size && heap[left] > heap[i])
		largest = left;
	else largest = i;
	if (right < size && heap[right] > heap[largest])
		largest = right;

	if (largest != i)
	{
		
		int temp = heap[largest];
		heap[largest] = heap[i];
		heap[i] = temp;

		
		maxHeapify(largest, size);
	}
}

void buildMaxHeap(int n)
{
	
	int nonLeafLast = (n-1)/2;
	for (int i = nonLeafLast; i >= 0; i--)
		maxHeapify(i, n);
}

void heapSort(int n)
{
	

	buildMaxHeap(n);
	int end = n-1;
	for (int i = end; i > 0; i--)
	{
		
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		
		maxHeapify(0, --n);
	}
}

int main()
{
	int n;
	cout << "Enter the number of elements in the list: ";
	cin >> n;

	cout << "Enter " << n << " elements:\n";
	int temp;
	for(int i = 0; i < n; i++)
	{
		cin >> temp;
		heap.push_back(temp);
	}

	heapSort(n);

	cout << "The sorted elements are: ";
	printV(heap);

	return 0;
}
