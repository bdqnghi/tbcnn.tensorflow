#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 25

void Heapify(int iArray[], int index, int iSize)
{
	int iLargest = 0;
	// 左右孩子节点
	int iLeft = 2 * index + 1;
	int iRight = iLeft + 1;
	// 边界check
	if(iLeft >= iSize || index < 0 || iSize <= 0)
		return;
	// 取出父，左右孩子节点中值最大的索引
	iLargest = iArray[index] > iArray[iLeft] ? index : iLeft;
	if(iRight < iSize) // 防止数组越界
		iLargest = iArray[iLargest]  > iArray[iRight] ? iLargest : iRight;

	// 三者最大的不是父节点，与父节点交换
	if(iLargest != index)
	{
		int iTemp = iArray[index];
		iArray[index] = iArray[iLargest];
		iArray[iLargest] = iTemp;
		// 递归，调整子节点
		// 因为交换后，子树有可能违反大根堆性质
		Heapify(iArray, iLargest, iSize);
	}
}

// 建立堆
void BuildHeap(int iArray[], int iSize)
{
	// 最后一个非叶子节点
	int iStart = iSize / 2 - 1;
	for (; iStart >= 0; --iStart)
	{
		Heapify(iArray, iStart, iSize);
	}
}

void HeapSort(int iArray[], int iSize)
{
	BuildHeap(iArray, iSize);
	// 下标从0开始
	for (int i = iSize - 1; i > 0; --i)
	{
		int iTemp = iArray[i];
		iArray[i] = iArray[0];
		iArray[0] = iTemp;
		// 重建堆
		Heapify(iArray, 0, i);
	}
}

int main(int argc, char *argv[])
{
	// 初始化乱序数组
	int iArray[ARRAY_SIZE] = {0};
	srand(time(NULL));
	for (int i = 0; i < ARRAY_SIZE; ++i)
	{
		iArray[i] = rand() % 100;
		printf("%d ", iArray[i]);
	}
	printf("\n");

	// 堆排序
	HeapSort(iArray, ARRAY_SIZE);

	for(int i = 0; i<ARRAY_SIZE; ++i)
		printf("%d ", iArray[i]);
	printf("\n");
	return 0;
}