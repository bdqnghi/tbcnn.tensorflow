
#include<stdio.h>
#include<stdlib.h>

void Rodcutting(int*, int);

int main(void) {
	int length = 0;
	int i = 0;
	int *rod = NULL;

	scanf("%d", &length);
	length++;
	rod = (int*)malloc(sizeof(int)*length);
	rod[0] = 0;
	for (i = 1; i < length; i++)
		scanf("%d", &rod[i]);

	Rodcutting(rod, length);

	return 0;
}

void Rodcutting(int* rod, int length) {
	int *revenue = (int*)malloc(sizeof(int)*length);
	int *cutted = (int*)malloc(sizeof(int)*length);
	int i = 0;
	int j = 0;
	int max = 0;

	revenue[0] = 0;
	cutted[0] = 0;
	for (i = 1; i < length; i++) {
		max = -1;
		for (j = 1; j <= i; j++) {
			if (max < rod[j] + revenue[i - j]) {
				max = rod[j] + revenue[i - j];
				cutted[i] = j;
			}
		}
		revenue[i] = max;
	}

	int profit = 0;
	for (i = 0; i < length; i++)
		if (profit < revenue[i])
			profit = revenue[i];
	
	printf("%d\n", profit);

	length--;
	while (length > 0) {
		printf("%d ", cutted[length]);
		length = length - cutted[length];
	}

}