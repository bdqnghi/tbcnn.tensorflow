//������_508 

#include <stdio.h>
#include <stdlib.h>

void CutRod(int p[], int n){
	int i, j, q;
	int *r = (int *)malloc(sizeof(int)* (n + 1));
	int *s = (int *)malloc(sizeof(int)* (n + 1));
	r[0] = 0;

	for (j = 1; j <= n; j++){
		q = -1;
		for (i = 1; i <= j; i++){
			if (q < p[i] + r[j - i]){
				q = p[i] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	printf("%d\n", r[n]);

	while (n > 0){
		printf("%d ", s[n]);
		n -= s[n];
	}

	free(r);
	free(s);

}

int main(){
	int N, i;
	int *arr;

	scanf("%d", &N);

	arr = (int *) malloc(sizeof(int) * (N + 1));

	for (i = 1; i <= N; i++){
		scanf("%d", &arr[i]);
	}

	CutRod(arr, N);

	free(arr);

	return 0;
}
