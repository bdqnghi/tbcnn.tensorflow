#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

void FixHeap(int, int, int);			
void ConstructHeap(int, int);			
void Heapsort(int, int);				
void AcceleratedHeapSort(int, int);		
int Promote(int, int, int);				
void FixHeapFast(int, int, int, int);	
void bubbleUpHeap(int, int, int);		

int tree[10000001], Acceltree[10000001];
int HeapsortANS, AccelHeapANS = 0;
bool flag;

int main()
{
	int caseNum, N, size, HeapsortM1, AccelHeapsortM2;
	clock_t start_time, end_time;
	double Heapsort_Time, AccelHeapsort_Time;

	scanf("%d", &caseNum);
	while (caseNum--) {
		flag = false;
		AccelHeapANS = 0;
		scanf("%d", &N);	
		for (size = 1; size <= N; size++) {
			scanf("%d", &tree[size]);
		}
		scanf("%d %d", &HeapsortM1, &AccelHeapsortM2);	

		ConstructHeap(1, N);			
		for (int i = 1; i <= N; i++) {	
			Acceltree[i] = tree[i];
		}

		start_time = clock();
		Heapsort(N, HeapsortM1);		
		end_time = clock();
		Heapsort_Time = (double)(end_time - start_time) / CLOCKS_PER_SEC;	

		start_time = clock();
		AcceleratedHeapSort(N, AccelHeapsortM2);	
		end_time = clock();
		AccelHeapsort_Time = (double)(end_time - start_time) / CLOCKS_PER_SEC;		

		printf("%d %d\n", HeapsortANS, AccelHeapANS);						
		printf("%0.3f %0.3f\n", AccelHeapsort_Time, Heapsort_Time);			

	}
	return 0;
}


void ConstructHeap(int top, int bottom)
{
	if (2 * top > bottom) return;				
	else {
		ConstructHeap(2 * top, bottom);			
		ConstructHeap(2 * top + 1, bottom);		
		int K = tree[top];
		FixHeap(bottom, top, K);				
	}
}



void Heapsort(int size, int HeapsortM1)
{
	for (int i = size; i > size - HeapsortM1; i--) {	
		HeapsortANS = -1;
		int K = tree[i];			
		FixHeap(i - 1, 1, K);		
	}
	return;
}

void FixHeap(int size, int root, int K)
{
	if (2 * root > size) 	
		tree[root] = K;
	else {
		
		int largerSubHeap;
		if (tree[2 * root] == size) largerSubHeap = 2 * root;
		else if (tree[2 * root + 1] > tree[2 * root])
			largerSubHeap = 2 * root + 1;
		else
			largerSubHeap = 2 * root;

		
		if (K > tree[largerSubHeap])
			tree[root] = K;
		else {
			tree[root] = tree[largerSubHeap];
			HeapsortANS = log2(root);			
			FixHeap(size, largerSubHeap, K);	
		}
	}
	return;
}




void AcceleratedHeapSort(int size, int AccelHeapsortM2)
{
	for (int i = size; i > size - AccelHeapsortM2; i--) {	
		int K = Acceltree[i];				
		int Height = log2(i);				

		if (i == size - AccelHeapsortM2 + 1) {		
			flag = true;
		}
		FixHeapFast(i - 1, K, 1, Height);	
	}
}

void FixHeapFast(int size, int K, int vacant, int h)
{
	if (2 * vacant > size) {		
		Acceltree[vacant] = K;
		return;
	}

	if (h == 0) return;
	else {
		int hStop = h / 2;							

		int vacStop = Promote(hStop, vacant, h);	
		int vacParent = vacStop / 2;				

		if (Acceltree[vacParent] < K) {				

			if (flag == true) {
				AccelHeapANS = Acceltree[vacParent];		
				flag = false;
			}

			Acceltree[vacStop] = Acceltree[vacParent];		
			bubbleUpHeap(vacant, K, vacParent);				
		}
		else                                                
			FixHeapFast(size, K, vacStop, hStop);			
	}
}

int Promote(int hStop, int vacant, int h)
{
	int vacStop;		

	if (h <= hStop)
		vacStop = vacant;
	else if (Acceltree[vacant * 2] < Acceltree[vacant * 2 + 1]) {		
		Acceltree[vacant] = Acceltree[vacant * 2 + 1];
		vacStop = Promote(hStop, 2 * vacant + 1, h - 1);				
	}
	else {																
		Acceltree[vacant] = Acceltree[vacant * 2];
		vacStop = Promote(hStop, 2 * vacant, h - 1);					
	}

	return vacStop;
}

void bubbleUpHeap(int root, int K, int vacant)
{
	if (vacant == root)					
		Acceltree[vacant] = K;
	else {
		int parent = vacant / 2;
		if (K < Acceltree[parent])		
			Acceltree[vacant] = K;
		else {							
			Acceltree[vacant] = Acceltree[parent];
			bubbleUpHeap(root, K, parent);		
		}
	}
}
