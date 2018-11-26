#include "HeapSort.h"
#include <algorithm>

HeapSort::HeapSort()
{}

void HeapSort::sort(int *array, int length)
{
	heapSort(array, length);
}

int HeapSort::rightSon(int vertex) const
{
	return vertex * 2 + 1;
}

int HeapSort::leftSon(int vertex) const
{
	return vertex * 2;
}

void HeapSort::heapify(int vertex, int *heap, int size)
{
	while (vertex > 0)
	{
		int maxVertex = vertex;
		if (leftSon(vertex) <= size && heap[leftSon(vertex) - 1] > heap[maxVertex - 1])
		{
			maxVertex = leftSon(vertex);
		}
		if (rightSon(vertex) <= size && heap[rightSon(vertex) - 1] > heap[maxVertex - 1])
		{
			maxVertex = rightSon(vertex);
		}
		if (maxVertex != vertex)
		{
			std::swap(heap[maxVertex - 1], heap[vertex - 1]);
			vertex = maxVertex;
		}
		else
		{
			vertex /= 2;
		}
	}
}

void HeapSort::buildHeap(int size, int *heap)
{
	for (int i = size; i > 0; i--)
	{
		heapify(i, heap, size);
	}
}

void HeapSort::heapSort(int *inputArray, int size)
{
	buildHeap(size, inputArray);
	for (int i = size; i > 0; i--)
	{
		std::swap(inputArray[0], inputArray[size - 1]);
		size--;
		heapify(1, inputArray, size);
	}
}