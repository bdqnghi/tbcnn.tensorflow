

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

void mergeFloat (float *a, int n, int m) {
    int i, j, k;
    float *x = (float *)malloc(n * sizeof (float)); 
    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n      ? a[i++] 
             : i == m      ? a[j++] 
             : a[j] < a[i] ? a[j++] 
             :               a[i++]; 
    }
    for (i = 0; i < n; i++) {
        a[i] = x[i]; 
    }
    free(x);
}
 
void mergeSortFloat (float *a, int n) {
    if (n < 2)
        return;
    int m = n / 2; 
    mergeSortFloat(a, m); 
    mergeSortFloat(a + m, n - m); 
    mergeFloat(a, n, m);
}


void mergeInt (int *a, int n, int m) {
    int i, j, k;
    int *x = (int *)malloc(n * sizeof (int)); 
    for (i = 0, j = m, k = 0; k < n; k++) {
        x[k] = j == n      ? a[i++] 
             : i == m      ? a[j++] 
             : a[j] < a[i] ? a[j++] 
             :               a[i++]; 
    }
    for (i = 0; i < n; i++) {
        a[i] = x[i]; 
    }
    free(x);
}
 
void mergeSortInt (int *a, int n) {
    if (n < 2)
        return;
    int m = n / 2; 
    mergeSortInt(a, m); 
    mergeSortInt(a + m, n - m); 
    mergeInt(a, n, m);
}
    




int main( int argc, char *argv[] ) 

{
    
    float a[] = { 7.1, 7.0, 6.9, -7.1, -7.0, 12.1, 1.1, -2.1, 0.0, 15.0, 4.0, 11.0, 9.1, 100.0};
	printf("\n\nUnsorted array is:  ");
	for(int i = 0; i < 14; ++i)
		printf(" %4.1f ", a[i]);
	mergeSortFloat( a, 13);
	printf("\n\nSorted array is:  ");
	for(int i = 0; i < 14; ++i)
		printf(" %4.1f ", a[i]);
    printf("\n\n");
    
    
    int b[] = { 7, 7, 6, -7, -7, 12, 1, -2, 0, 15, 4, 11, 9, 100};
	printf("\n\nUnsorted array is:  ");
	for(int i = 0; i < 14; ++i)
		printf(" %d ", b[i]);
	mergeSortInt( b, 13);
	printf("\n\nSorted array is:  ");
	for(int i = 0; i < 14; ++i)
		printf(" %d ", b[i]);
    printf("\n\n");
    
}


