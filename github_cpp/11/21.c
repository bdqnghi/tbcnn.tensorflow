#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 25

void Heapify(int iArray[], int index, int iSize)
{
	int iLargest = 0;
	
	int iLeft = 2 * index + 1;
	int iRight = iLeft + 1;
	
	if(iLeft >= iSize || index < 0 || iSize <= 0)
		return;
	
	iLargest = iArray[index] > iArray[iLeft] ? index : iLeft;
	if(iRight < iSize) 
		iLargest = iArray[iLargest]  > iArray[iRight] ? iLargest : iRight;

	
	if(iLargest != index)
	{
		int iTemp = iArray[index];
		iArray[index] = iArray[iLargest];
		iArray[iLargest] = iTemp;
		
		
		Heapify(iArray, iLargest, iSize);
	}
}


void BuildHeap(int iArray[], int iSize)
{
	
	int iStart = iSize / 2 - 1;
	for (; iStart >= 0; --iStart)
	{
		Heapify(iArray, iStart, iSize);
	}
}

void HeapSort(int iArray[], int iSize)
{
	BuildHeap(iArray, iSize);
	
	for (int i = iSize - 1; i > 0; --i)
	{
		int iTemp = iArray[i];
		iArray[i] = iArray[0];
		iArray[0] = iTemp;
		
		Heapify(iArray, 0, i);
	}
}

int main(int argc, char *argv[])
{
	
	int iArray[ARRAY_SIZE] = {0};
	srand(time(NULL));
	for (int i = 0; i < ARRAY_SIZE; ++i)
	{
		iArray[i] = rand() % 100;
		printf("%d ", iArray[i]);
	}
	printf("\n");

	
	HeapSort(iArray, ARRAY_SIZE);

	for(int i = 0; i<ARRAY_SIZE; ++i)
		printf("%d ", iArray[i]);
	printf("\n");
	return 0;
}