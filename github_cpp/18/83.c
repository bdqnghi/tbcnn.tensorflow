


#include "stdafx.h"

#define MAX_ARR 100

#include <memory.h>

#define MAX_INPUT 100

struct stuff{
	int length;
	int price;
};

void RodCutting(int n, stuff * arr, int * resArr, int * cutPos){
	resArr[0] = 0;
	for (int i = 1; i <= n; ++i){
		resArr[i] = arr[i].price;
		cutPos[i] = i;
		for (int j = 1; j <= n; ++j){
			if (i - j >= 0){
				
				if (resArr[i] < resArr[i - j] + arr[j].price){
					resArr[i] =resArr[i - j] + arr[j].price;
					cutPos[i] = j;
				}
			}
		}
	}
}

void PrintRes(int n, int * resArr, int * cutPos){
	printf("%d\n", resArr[n]);
	int position = n;
	while (position > 0){
		printf("%d ", cutPos[position]);
		position -= cutPos[position];
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	stuff * arr = new stuff[MAX_INPUT];

	
	errno_t err;
	FILE * filePtr;
	err = fopen_s(&filePtr, "input.txt", "r");

	fscanf_s(filePtr, "%d", &n);
	for (int i = 1; i <= n; ++i){
		arr[i].length = i;
		fscanf_s(filePtr, "%d", &arr[i].price);
	}
	fclose(filePtr);

	
	int * pos = new int[MAX_INPUT];
	int * res = new int;
	int * cutPos = new int[MAX_INPUT];
	int * resArr = new int[MAX_INPUT];
	memset(pos, 0, sizeof(int) * MAX_INPUT);
	memset(resArr, -1, sizeof(int) * MAX_INPUT);
	memset(res, 0, sizeof(int));
	
	RodCutting(n, arr, resArr, cutPos);
	PrintRes(n, resArr, cutPos);
	delete[] pos;
	delete res;
	delete[] cutPos;
	delete[] resArr;

	getchar();
	return 0;
}

