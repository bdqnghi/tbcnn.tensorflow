#include <stdio>

#include "heap-struct.hpp"
#include "heap-sort.hpp"

int HEAP_MAXIMUM(std::vector A)
{
	return A[1];
}

int HEAP_EXTRACT_MAX(std::vector A)
{
	if(A.empty())
	{
		return -1;
	}

	int max = A.pop();
	MAX_HEAPIFY(A, 1);

	return max;
}

std::vector HEAP_INCREASE_KAY(std::vector A, int i, int key)
{
	if(key < A[i])
	{
		return A;
	}

	A[i] = key;
	for(; i > 0 && A[PARENT(i)] < A[i]; i = PARENT(i))
	{
		int tmp = A[i];
		A[i] = A[PARENT(i)];
		A[PARENT(i)] = tmp;
	}

	return A;
}

std::vector MAX_HEAP_INSERT(std::vector A, int key)
{
	A.push_back(0xFFFFFFFF);
	HEAP_INCREASE_KEY(A, A.size()-1, key);

	return A;
}

