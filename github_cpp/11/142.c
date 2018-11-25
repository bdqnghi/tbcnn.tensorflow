#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
#define N 300000

void slink(int* a, int i, int len);
void heapsort(int* a, int len);

void heapsort(int* a, int len) {
    
	
	for (int k = len/2; k > -1; k--) {
	    slink(a, k, len);
	}
	
	
	
	
	
	
	
	int i = len;
	while ( i > 1) {
	    int tmp = a[0];
		a[0] = a[i - 1];
		a[i - 1] = tmp;
		slink(a, 0, i - 1);
		i--;
	}
}

void slink(int* a, int i, int len) {
    
    while (2*i + 1 < len) {
	    int j = 2*i + 1;
		if (j < len - 1 && a[j] < a[j+1] ) {
		    j++;
		}
		if (a[i] > a[j]) break;
		else {
		    int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
		i = j;
	}
    
}


int main() {
    int a[N];
    srand(50000);
	for (int i = 0; i < N; i++) {
	    a[i] = rand() % N;
		
	}
	
	heapsort(a, N);
	
	
	
	
    return EXIT_SUCCESS;
}
