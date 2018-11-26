// Rod-Cutting Reccursive1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <memory.h>

#define MAX_INPUT 100

struct stuff{
	int length;
	int price;
};

void CalcValue(stuff * arr ,int * pos, int n, int * res, int *cutPos){
	int length = 0;
	int sumValue = 0;
	
	for (int i = 0; i < n - 1; ++i){
		if (pos[i]){
			sumValue += arr[i - length].price;
			length += arr[i-length].length;
		}
	}

	sumValue += arr[n - length - 1].price;
	
	if (*res < sumValue){
		*res = sumValue;
		for (int i = 0; i < n - 1; ++i){
			cutPos[i] = pos[i];
		}
	}
}

void RodCutting(int n,stuff * arr, int * pos, int current, int* res, int* cutPos){
	if (current == n - 1){
		CalcValue(arr, pos, n, res, cutPos);
		return;
	}

	pos[current] = 1;
	RodCutting(n, arr, pos, current + 1, res,cutPos);
	pos[current] = 0;
	RodCutting(n, arr, pos, current + 1, res,cutPos);
}

void PrintRodCutting(int * res, int * cutPos, int n){
	printf("%d\n", *res);

	int length = 0;

	for (int i = 0; i < n - 1; ++i){
		if (cutPos[i]){
			printf("%d ", i + 1 - length);
			length = i + 1 - length;
		}
	}
	printf("%d\n",n-length);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	stuff * arr = new stuff[MAX_INPUT];

	//�Է�
	errno_t err;
	FILE * filePtr;
	err = fopen_s(&filePtr,"input.txt", "r");

	fscanf_s(filePtr,"%d", &n);
	for (int i = 0; i < n; ++i){
		arr[i].length = i + 1;
		fscanf_s(filePtr, "%d", &arr[i].price);
	}
	fclose(filePtr);

	//RodCutting
	int * pos = new int[MAX_INPUT];
	int * res = new int;
	int * cutPos = new int[MAX_INPUT];

	memset(pos, 0, sizeof(int) * MAX_INPUT);
	memset(res, 0, sizeof(int));

	RodCutting(n,arr, pos, 0, res, cutPos);
	
	//RodCutting ���� ������ ����
	PrintRodCutting(res, cutPos, n);
	
	delete[] pos;
	delete res;
	delete[] cutPos;

	getchar();
	return 0;
}