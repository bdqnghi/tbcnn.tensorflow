


#include "stdafx.h"
#include <memory.h>

#define MAX_INPUT 100

struct stuff{
	int length;
	int price;
};

int RodCutting(int n, stuff * arr, int cutLength, int * res, int * resArr, int * pos){
	if (resArr[cutLength] != -1)
		return resArr[cutLength];

	if (cutLength == 0){
		return 0;
	}

	int max = -1;

	for (int i = 1; i <= cutLength ; ++i){
		int temp = arr[i].price + RodCutting(n, arr, cutLength - i, res, resArr, pos);
		
		if (max < temp){
			max = temp;
			pos[cutLength] = i;
		}
	}

	resArr[cutLength] = max;
	
	return max;
}

void PrintRodCutting(int n, int * resArr, int * pos){
	
	printf("%d\n", resArr[n]);
	int position = n;

	while (position > 0){
		printf("%d ", pos[position]);
		position -= pos[position];
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

	memset(resArr, -1, sizeof(int) * MAX_INPUT);
	memset(pos, 0, sizeof(int) * MAX_INPUT);
	memset(res, 0, sizeof(int));
	
	RodCutting(n, arr, n, res, resArr, pos);
	PrintRodCutting(n, resArr, pos);
	
	delete[] pos;
	delete	 res;
	delete[] cutPos;
	delete[] resArr;

	
	
	

	getchar(); 
	return 0;
}