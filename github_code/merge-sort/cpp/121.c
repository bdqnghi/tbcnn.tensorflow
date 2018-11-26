#include "zSelectSort.hpp"
#include "zTestSort.hpp"
#include "zInsertSort.hpp"
#include "zBubbleSort.hpp"
#include "zShellSort.hpp"
#include "zMergeSort.hpp"
#include "zQuickSort.hpp"
#include "zHeapSort.hpp"

using namespace zLimbo;

void testSelect() {
	zTestInt(&zSelectSort<long>, "selectSort long: ");
//	zTestInt(&zSelectSort2<long>, "selectSort2 long: ");
	zTestReal(&zSelectSort<double>, "selectSort double: ");
//	zTestReal(&zSelectSort2<double>, "selectSort2 double: ");
}

void testInsert() {
	zTestInt(&zInsertSort<long>, "insertSort long: ");
//	zTestInt(&zInsertSort2<long>, "insertSort2 long: ");
	zTestReal(&zInsertSort<double>, "insertSort double: ");
//	zTestReal(&zInsertSort2<double>, "insertSort2 double: ");
//	zTestInt(&zInsertSort3<long>, "insertSort3 long: ");
//	zTestReal(&zInsertSort3<double>, "insertSort3 double: ");
}

void testBubble() {
	zTestInt(&zBubbleSort<long>, "bubbleSort long: ");
	zTestReal(&zBubbleSort<double>, "bubbleSort double: ");
}

void testShell() {
	long f = 2;
	long N = 1000000;
	zTestInt(&zShellSort<long>, 
			"shellSort long: ", f, N);
	zTestReal(&zShellSort<double>, 
			"shellSort double: ", f, N);
}

void testMerge() {
	long f = 2;
	long N = 1000000;
/*	zTestInt(&zMergeSort<long>, 
			"mergeSort long: ", f, N);
	zTestReal(&zMergeSort<double>, 
			"mergeSort double: ", f, N);
	zTestInt(&zMergeSort2<long>,
			"mergeSort2 long: ", f, N);
	zTestReal(&zMergeSort2<double>,
			"mergeSort2 double: ", f, N);
	zTestInt(&zMergeSort3<long>,
			"mergeSort3 long: ", f, N);
	zTestReal(&zMergeSort3<double>,
			"mergeSort3 double: ", f, N);
*/	zTestInt(&zMergeSort4<long>,
			"mergeSort4 long: ", f, N);
	zTestReal(&zMergeSort4<double>,
			"mergeSort4 double: ", f, N);
}

void testQuick() {
	long f = 2;
	long N = 1000000;
	zTestInt(&zQuickSort<long>,
			"quickSort long: ", f, N);
	zTestReal(&zQuickSort<double>,
			"quickSort double: ", f, N);
	zTestInt(&zQuickSort2<long>,
			"quickSort long2: ", f, N);
	zTestReal(&zQuickSort2<double>,
			"quickSort double2: ", f, N);
}

void testHeap() {
	long f = 2;
	long N = 1000000;
	zTestInt(&zHeapSort<long>,
			"heapSort long: ", f, N);
	zTestReal(&zHeapSort<double>,
			"heapSort doubel: ", f, N);
}

int main() {
//	testSelect();
//	testInsert();
//	testBubble();	
	testShell();
	testMerge();
	testQuick();
	testHeap();
	return 0;
}

