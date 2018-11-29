/*
 * sort.cpp
 *
 *  Created on: 2015?11?12?
 *      Author: xuqji
 */

#include "Sort.h"

namespace datastruct {
void swap(int &a, int &b)
{
	int temp;
	temp=a;
	a=b;
	b=temp;
}

void init_array(int *a, int n)
{
	for(int i=0; i<n; ++i){
		a[i] = 100-i;
	}

	for(int i=5; i<n-6; i++) {
		a[i] = i;
	}
}

void dump(int *a, int n)
{
	for(int i=0; i<n; ++i){
		cout<<" "<<a[i]<<" ";
	}
	cout<<endl;
}

void bubble_sort(int *a, int n)
{

	for(int i=0; i<n-1; ++i) {
		bool flag = false;
		for(int j=n-1; j>i; --j) {
			if(a[j-1] > a[j]) {
				swap(a[j-1], a[j]);
				flag = true;
			}
		}
		if(!flag) break;
	}
	return;
}

void insert_sort(int *a, int n)
{
	for(int i=1; i<n; ++i) {
		for(int j=i; (a[j] < a[j-1]) && j >0; --j) {
			swap(a[j], a[j-1]);
		}
	}
}

void select_sort(int *a, int n)
{
	int index;

	for(int i=0; i<n-1 ; ++i) {
		index=i;
		for(int j=i+1; j<n; ++j) {
			if(a[j] < a[index]) {
				index = j;
			}
		}
		if(i != index) {
			swap(a[i], a[index]);
		}
		assert(a[i]<a[i+1]);
	}
}
/*****
 *
 *
in shell sort need find the n(i)=f(n,step, i) to be express by (n, step, i),
**** **** **** **
n0 = 4
n1 = 4
n2 = 3
n3 = 3

n = 15, step = 4, imax=3

ni=f(n,step,i)

n(i) = (n-i-1)step + 1
 *
 *
 *
 *
 *
 */

void shell_sort(int *a, int n)
{
	int step = 0;

	while(step < n) step = step*3 + 1;

	do {
		step = (step -1)/3;

		for(int i=0; i<step; ++i) {
			int nsub = (n - i - 1)/step + 1;
			int *narr = new int[nsub];

			for(int j=0; j<nsub; ++j) {
				narr[j] = a[i + step*j];
			}

			bubble_sort(narr, nsub);

			for(int j=0; j<nsub; ++j) {
				a[i + step*j] = narr[j];
			}
			delete[] narr;
		}

	}while (step>1);

}

#define HEAP_MAX  20
void sift_up(int *a)
{
	int leaf, parent;

	for(leaf=a[0]; (leaf/2>0); ) {
		parent = leaf/2;
		if(a[leaf] < a[parent]){
			swap(a[leaf], a[parent]);
			leaf=parent;
		}
		else {
			break;
		}
	}
}

void insert_heap(int *a, int item)
{
	int index;
	if(a[0] >= HEAP_MAX)
		return;

	a[0] = a[0]+1;
	index = a[0];
	a[index] = item;
	sift_up(a);

}

void init_heap(int *heap, int *data, int len)
{
	if(len > HEAP_MAX) {
		cout<<"exceed max heap size: "<<len<<">"<<"HEAP_MAX(20)"<<endl;
	}
	for(int i=0; i<HEAP_MAX+1; ++i){
		heap[i]=0;
	}

	for(int i=0; i<len; ++i) {
		insert_heap(heap, data[i]);
	}
	//cout<<"heap size "<<heap[0]<<endl;
	//dump(heap+1, 20);
}


void sift_down(int *heap)
{
	int leaf, parent;
	//cout<<"before"<<endl;
	//dump(heap+1, 20);
	for(parent = 1, leaf = 2*parent;parent<=heap[0] && leaf<=heap[0];){
		if((leaf+1<=heap[0])&& (heap[leaf+1]<heap[leaf])){
			leaf ++;
		}

		if(heap[parent]>heap[leaf]){
			swap(heap[parent], heap[leaf]);
		}
		else {
			break;
		}
		parent=leaf;
		leaf=2*parent;
	}
	//cout<<"after"<<endl;
	//dump(heap+1, 20);
}

int get_min(int *heap)
{
	if(heap[0] <= 0) {
		cout<<"heap empty"<<endl;
		return 0xffff;
	}

	int index = heap[0];
	--heap[0];
	int ret = heap[1];
	swap(heap[1], heap[index]);

	sift_down(heap);
	return ret;
}

void heap_sort(int *heap, int *data, int n)
{
	init_heap(heap, data, n);

	for(int i=0; i<n; ++i) {
		data[i]=get_min(heap);
	}
}

void merge_sort(int *a, int n)
{
	if(n==1) {
		return;
	}

	if(n==2) {
		if(a[1]<a[0]) {
			swap(a[1], a[0]);
		}
		return;
	}

	merge_sort(a, n/2);
	merge_sort(a+n/2, n-n/2);

	int index1 = 0;
	int index2 = 0;
	int *data1 = a;
	int *data2 = a+n/2;
	int len1 = n/2;
	int len2 = n-n/2;
	int *temp = new int[n];
	int i=0;

	while(index1<len1 && index2<len2) {
		if(data1[index1] <= data2[index2]) {
			temp[i++] = data1[index1++];
		}
		else {
			temp[i++] = data2[index2++];
		}
	}

	if(index1<len1) {
		while(index1 <len1){
			temp[i++] = data1[index1++];
		}
	}

	if(index2<len2) {
		while(index2 <len2){
			temp[i++] = data2[index2++];
		}
	}

	for(int i=0; i<n; ++i) {
		a[i] = temp[i];
	}

	delete[] temp;
}

void quick_sort(int *a, int n)
{
	int mid = n/2;
	int mid_value=a[mid];
	int index = 1;

	if(n<=1) {
		return ;
	}

	if(n==2) {
		if(a[0] > a[1]) {
			swap(a[0], a[1]);
			return;
		}
	}

	swap(a[0], a[mid]);

	for(int i=1; i<n; ++i) {
		if(a[i] < mid_value) {
			swap(a[index], a[i]);
			index ++;
		}
	}

	swap(a[0], a[index-1]);

	quick_sort(a, index-1);
	quick_sort(a+index, n - (index));

	return;
}
void TestSort() {
	TestSort();
	//dump(a, 1000);
/*
	init(a, 20);
	dump(a, 20);
	insert_sort(a, 20);
	dump(a, 20);
*/
	/*
	init(a, 20);
	dump(a, 20);
	select_sort(a, 20);
	dump(a, 20);
*/
/*
	init(a, 20);
	dump(a, 20);
	shell_sort(a, 20);
	dump(a, 20);
*/
	/*
	int heap[21];

	init(a, 20);
	dump(a, 20);
	heap_sort(heap, a, 20);
	dump(a, 20);
	*/
/*
	init(a, 20);
	dump(a, 20);
	merge_sort(a, 20);
	dump(a, 20);
*/
	/*
	init(a, 20);
	dump(a, 20);
	quick_sort(a, 20);
	dump(a, 20);
	*/
}
} /* namespace datastruct */
