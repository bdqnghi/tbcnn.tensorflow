#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <time.h>
using namespace std;

void FixHeap(int, int, int);			//MaxHeap�� partial order�� ������Ű�� ���� downheap�ϴ� �Լ�
void ConstructHeap(int, int);			//Tree�� �ؿ��� ���� left, right subtree�� ������ ��������� fixheap�Ͽ� heap�� ����� �Լ�
void Heapsort(int, int);				//Heapsort�� �ϴ� �Լ�
void AcceleratedHeapSort(int, int);		//AcceleratedHeapSort�ϴ� �Լ�
int Promote(int, int, int);				//���� Ʈ�� ������ h/2 ���� downheap�ϴ� �Լ�
void FixHeapFast(int, int, int, int);	//FixHeap���� �� �� ���� FixHeapFast �Լ�
void bubbleUpHeap(int, int, int);		//�� �����Դ��� �˻� ��, �߸� �������� �� �ٽ� upheap�ϴ� �Լ�

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
		scanf("%d", &N);	//���� ���� �Է¹ޱ�
		for (size = 1; size <= N; size++) {
			scanf("%d", &tree[size]);
		}
		scanf("%d %d", &HeapsortM1, &AccelHeapsortM2);	//M1. M2 �Է¹ޱ�

		ConstructHeap(1, N);			//Heap�� �����
		for (int i = 1; i <= N; i++) {	//AcceleratedHeapSort�� ���� �Ȱ��� Ʈ���� �ϳ� �� �����
			Acceltree[i] = tree[i];
		}

		start_time = clock();
		Heapsort(N, HeapsortM1);		//Heapsort �Լ� ȣ��		
		end_time = clock();
		Heapsort_Time = (double)(end_time - start_time) / CLOCKS_PER_SEC;	//�ð����� ���

		start_time = clock();
		AcceleratedHeapSort(N, AccelHeapsortM2);	//AcceleratedHeapSort �Լ� ȣ��
		end_time = clock();
		AccelHeapsort_Time = (double)(end_time - start_time) / CLOCKS_PER_SEC;		//�ð����� ���

		printf("%d %d\n", HeapsortANS, AccelHeapANS);						//���� ���
		printf("%0.3f %0.3f\n", AccelHeapsort_Time, Heapsort_Time);			//�ð� ���

	}
	return 0;
}


void ConstructHeap(int top, int bottom)
{
	if (2 * top > bottom) return;				//Leaf�̸� �̹� Heap�̹Ƿ� return
	else {
		ConstructHeap(2 * top, bottom);			//left child subtree	
		ConstructHeap(2 * top + 1, bottom);		//right child subtree
		int K = tree[top];
		FixHeap(bottom, top, K);				//Heap �籸���ϴ� �Լ� ȣ��
	}
}



void Heapsort(int size, int HeapsortM1)
{
	for (int i = size; i > size - HeapsortM1; i--) {	//M1��° ��ŭ heapsort����
		HeapsortANS = -1;
		int K = tree[i];			//��������� ����
		FixHeap(i - 1, 1, K);		//Heap �籸���ϴ� �Լ� ȣ��
	}
	return;
}

void FixHeap(int size, int root, int K)
{
	if (2 * root > size) 	//leaf��� �϶�
		tree[root] = K;
	else {
		//�� ū subheap�� ã�´�
		int largerSubHeap;
		if (tree[2 * root] == size) largerSubHeap = 2 * root;
		else if (tree[2 * root + 1] > tree[2 * root])
			largerSubHeap = 2 * root + 1;
		else
			largerSubHeap = 2 * root;

		//K���� ���Ͽ� �´� �ڸ��� ����
		if (K > tree[largerSubHeap])
			tree[root] = K;
		else {
			tree[root] = tree[largerSubHeap];
			HeapsortANS = log2(root);			//���������� fixheapȣ���� ����� ���� ���ϱ� ����
			FixHeap(size, largerSubHeap, K);	//FixHeap��� ȣ��
		}
	}
	return;
}




void AcceleratedHeapSort(int size, int AccelHeapsortM2)
{
	for (int i = size; i > size - AccelHeapsortM2; i--) {	//M2��° ��ŭ heapsort����
		int K = Acceltree[i];				//��������� ����	
		int Height = log2(i);				//Ʈ���� ���̸� ����

		if (i == size - AccelHeapsortM2 + 1) {		//M2��°�� �� flag�� true��
			flag = true;
		}
		FixHeapFast(i - 1, K, 1, Height);	//Heap �籸���ϴ� FixHeapFast�Լ� ȣ��
	}
}

void FixHeapFast(int size, int K, int vacant, int h)
{
	if (2 * vacant > size) {		//leaf��� �϶�
		Acceltree[vacant] = K;
		return;
	}

	if (h == 0) return;
	else {
		int hStop = h / 2;							//Ʈ�� ������ �ݸ�ŭ �������Ƿ� ���� ���̸� ����(Ȧ�� �� ��츦 ����� h + 1)

		int vacStop = Promote(hStop, vacant, h);	//Promote�� ���� vacant�� ���� ��带 �޾ƿ�
		int vacParent = vacStop / 2;				//�� �����Դ��� �񱳸� ���� ���� ����� �θ� ��带 ����

		if (Acceltree[vacParent] < K) {				//K�� �񱳰�� �߸��������� ���  

			if (flag == true) {
				AccelHeapANS = Acceltree[vacParent];		//M2��° ū ���� ã�� �� ó������ bubbleupheap�� �ϴ� ����� ���� �� ����
				flag = false;
			}

			Acceltree[vacStop] = Acceltree[vacParent];		//vacStop�� �θ��� ���� ���� �־���	
			bubbleUpHeap(vacant, K, vacParent);				//�ٽ� �ö󰡱� ���� bubbleupheap����
		}
		else                                                //�� �������� ���
			FixHeapFast(size, K, vacStop, hStop);			//�ٽ� promote ������ ���� FixHeapFasat ���ȣ��
	}
}

int Promote(int hStop, int vacant, int h)
{
	int vacStop;		//���� ���� ���(index)

	if (h <= hStop)
		vacStop = vacant;
	else if (Acceltree[vacant * 2] < Acceltree[vacant * 2 + 1]) {		//rightchild�� �� Ŭ ���
		Acceltree[vacant] = Acceltree[vacant * 2 + 1];
		vacStop = Promote(hStop, 2 * vacant + 1, h - 1);				//Promote��� ����
	}
	else {																//leftchild�� �� Ŭ ���
		Acceltree[vacant] = Acceltree[vacant * 2];
		vacStop = Promote(hStop, 2 * vacant, h - 1);					//Promote��� ����
	}

	return vacStop;
}

void bubbleUpHeap(int root, int K, int vacant)
{
	if (vacant == root)					//���� ������ �ݸ�ŭ ���� �� �� �̻� Ȯ���� �ʿ� �����Ƿ�
		Acceltree[vacant] = K;
	else {
		int parent = vacant / 2;
		if (K < Acceltree[parent])		//�θ� �� Ŭ ���
			Acceltree[vacant] = K;
		else {							//�θ� �� ���� ���	 
			Acceltree[vacant] = Acceltree[parent];
			bubbleUpHeap(root, K, parent);		//�� �ö󰡾��ϹǷ� bubbleUpHeap ���
		}
	}
}
