#include <iostream>
#include <string>
#include "Student.h"
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "MergeSortBU.h"
#include "QuickSort2.h"
#include "QuickSortThreeWays.h"
#include "HeapSort.h"
using namespace std;

template<typename Item>
class IndexMaxHeap{
	
private:
	Item* data;  // ����������е�����
	int* indexes; // ����������е�����
	int count;
	int capacity;

	// ��������, ����֮��ıȽϸ���data�Ĵ�С���бȽ�, ��ʵ�ʲ�����������
	void shiftUp(int k){
		while( k>1 && data[indexes[k/2]] < data[indexes[k]]){
			swap( indexes[k/2], indexes[k]);
			k = k/2;
		}
	}

	// ��������, ����֮��ıȽϸ���data�Ĵ�С���бȽ�, ��ʵ�ʲ�����������
	void shiftDown(int k){
		// �жϽڵ��Ƿ�������
		while( 2*k <= count){
			
			int j = 2 * k;
			if( j+1 <= count && data[indexes[j+1]] > data[indexes[j]])
				j++;
			// data[j] �� data[2*k]��data[2*k+1]�е����ֵ

			if(data[indexes[k]] >= data[indexes[j]])
				break;
			swap(indexes[k], indexes[j]);
			k = j;
		}
	
	}

public:
	
	// ���캯��, ����һ���յ�������, ������capacity��Ԫ��
	IndexMaxHeap(int capacity){
		data = new Item[capacity + 1];
		indexes = new int[capacity + 1];
		this->count = 0;
		this->capacity = capacity;
	}


	~IndexMaxHeap(){
		delete[] data;
		delete[] indexes;
	}

	// ���ض��е�Ԫ�ظ���
	int size(){
		return count;
	}

	// �ж϶����Ƿ�Ϊ��
	int isEmpty(){
		return count == 0;
	}

	// ������������в���һ����Ԫ��item
	// ��ָ������
	// �����i���û����ԣ��Ǵ�0��ʼ������
	void insert(int i, Item item){

		assert( count+1 <= capacity);
		assert( i+1 <= capacity && i+1 >= 1);

		i++;
		data[i] = item;
		indexes[count+1] = i;

		count++;
		shiftUp( count );
	}

	// �������������ȡ���Ѷ�Ԫ��, �������������洢���������
	Item extractMax(){

		assert(count > 0);

		Item ret = data[indexes[1]];

		swap( indexes[count], indexes[1]);
		count--;
		shiftDown(1);

		return ret;
	}

	// �������������ȡ���Ѷ�Ԫ�ص�����
	Item extractMaxIndex(){

		assert(count > 0);

		// ���û����صģ���Ҫ��1
		int ret = indexes[1] - 1;

		swap( indexes[count], indexes[1]);
		count--;
		shiftDown(1);

		return ret;
	}

	Item getItem(int i){
		return data[i+1];
	}

	// change�������ʱ�临�Ӷ���O(n)+O(logn) = O(n)
	// �ò������Ż�
	void change(int i, Item newItem){
		
		i++;
		data[i] = newItem;

		// ��Ҫ�ҵ�j,����indexes[j]=i, j��ʾdata[i]�ڶ��е�λ��
		// Ȼ��������Ųһ�� shiftUp(j),��shiftDown(j);
		for(int j=1; j<=count; j++){
			if(indexes[j] == i){
				shiftUp(j);
				shiftDown(j);
				return;
			}
		}
	}


};


// ʹ����������ѽ��ж�����, ����֤���ǵ���������ѵ���ȷ��
// ��������ѵ���Ҫ���ò�����������, ����������ʹ������ֻ��Ϊ����֤���ǵ����������ʵ�ֵ���ȷ��
// �ں�����ͼ����, ��������С�������㷨, �������·���㷨, ���Ƕ���Ҫʹ�������ѽ����Ż�:)
template<typename T>
void heapSortUsingIndexMaxHeap(T arr[], int n){

    IndexMaxHeap<T> indexMaxHeap = IndexMaxHeap<T>(n);
    for( int i = 0 ; i < n ; i ++ )
        indexMaxHeap.insert( i , arr[i] );

    for( int i = n-1 ; i >= 0 ; i -- )
        arr[i] = indexMaxHeap.extractMax();
}



// �Ƚ� Merge Sort, ���� Quick Sort �ͱ��ڽ��ܵ����� Heap Sort ������Ч��
// ע��, �⼸�������㷨���� O(nlogn) ����������㷨
int main(){
	
	int n = 1000000;

	// һ���Բ���
	cout<<"general test"<<" ("<<n<<" numbers)"<<endl;
	int *arr1 = SortTestHelper::generateRandomArray(n,0,n);
	int *arr2 = SortTestHelper::copyIntArray(arr1, n);
	int *arr3 = SortTestHelper::copyIntArray(arr1, n);
	int *arr4 = SortTestHelper::copyIntArray(arr1, n);
	int *arr5 = SortTestHelper::copyIntArray(arr1, n);
	int *arr6 = SortTestHelper::copyIntArray(arr1, n);
	int *arr7 = SortTestHelper::copyIntArray(arr1, n);


	SortTestHelper::testSort("Merge Sort", mergeSort<int>, arr1, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2<int>, arr2, n);
	SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways<int>, arr3, n);
	SortTestHelper::testSort("Heap Sort 1", heapSort1<int>, arr4, n);
	SortTestHelper::testSort("Heap Sort 2", heapSort2<int>, arr5, n);
	SortTestHelper::testSort("Heap Sort Inplace", heapSortInplace<int>, arr6, n);
	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap<int>, arr7, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;

	cout<<endl;

	// ���Խ�����������
	// ���������ѡ��궨��Ĳ����, ���ǵĿ�������������ɴ���������������
	// ��Ϊÿ��patition�����Ǽ��Ȳ�ƽ��ķֽ�
	cout<<"nealy ordered data test"<<" ("<<n<<" numbers)"<<endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n,100);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);
	arr4 = SortTestHelper::copyIntArray(arr1, n);
	arr5 = SortTestHelper::copyIntArray(arr1, n);
	arr6 = SortTestHelper::copyIntArray(arr1, n);
	arr7 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort<int>, arr1, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2<int>, arr2, n);
	SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways<int>, arr3, n);
	SortTestHelper::testSort("Heap Sort 1", heapSort1<int>, arr4, n);
	SortTestHelper::testSort("Heap Sort 2", heapSort2<int>, arr5, n);
	SortTestHelper::testSort("Heap Sort Inplace", heapSortInplace<int>, arr6, n);
	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap<int>, arr7, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;

	cout<<endl;

	// ������ȫ��������
	cout<<"fully ordered data test"<<" ("<<n<<" numbers)"<<endl;
	arr1 = SortTestHelper::generateNearlyOrderedArray(n,0);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);
	arr4 = SortTestHelper::copyIntArray(arr1, n);
	arr5 = SortTestHelper::copyIntArray(arr1, n);
	arr6 = SortTestHelper::copyIntArray(arr1, n);
	arr7 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort<int>, arr1, n);
	SortTestHelper::testSort("Quick Sort2", quickSort2<int>, arr2, n);
	SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways<int>, arr3, n);
	SortTestHelper::testSort("Heap Sort 1", heapSort1<int>, arr4, n);
	SortTestHelper::testSort("Heap Sort 2", heapSort2<int>, arr5, n);
	SortTestHelper::testSort("Heap Sort Inplace", heapSortInplace<int>, arr6, n);
	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap<int>, arr7, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;

	cout<<endl;


	// ���԰���������ͬԪ�ص�����
	// ����ʱ, ���ں��д�����ͬԪ�ص�����, ���������㷨�ٴ��˻�����O(n^2)������㷨
	cout<<"many same elements test"<<" ("<<n<<" numbers)"<<endl;
	arr1 = SortTestHelper::generateRandomArray(n,0,10);
	arr2 = SortTestHelper::copyIntArray(arr1, n);
	arr3 = SortTestHelper::copyIntArray(arr1, n);
	arr4 = SortTestHelper::copyIntArray(arr1, n);
	arr5 = SortTestHelper::copyIntArray(arr1, n);
	arr6 = SortTestHelper::copyIntArray(arr1, n);
	arr7 = SortTestHelper::copyIntArray(arr1, n);

	SortTestHelper::testSort("Merge Sort", mergeSort<int>, arr1, n);
	SortTestHelper::testSort("Quick Sort", quickSort2<int>, arr2, n);
	SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways<int>, arr3, n);
	SortTestHelper::testSort("Heap Sort 1", heapSort1<int>, arr4, n);
	SortTestHelper::testSort("Heap Sort 2", heapSort2<int>, arr5, n);
	SortTestHelper::testSort("Heap Sort Inplace", heapSortInplace<int>, arr6, n);
	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap<int>, arr7, n);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
	delete[] arr4;
	delete[] arr5;
	delete[] arr6;
	delete[] arr7;

	cout<<endl;

	return 0;

}



