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

	zTestReal(&zSelectSort<double>, "selectSort double: ");

}

void testInsert() {
	zTestInt(&zInsertSort<long>, "insertSort long: ");

	zTestReal(&zInsertSort<double>, "insertSort double: ");



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
	zTestInt(&zMergeSort4<long>,
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



	testShell();
	testMerge();
	testQuick();
	testHeap();
	return 0;
}

