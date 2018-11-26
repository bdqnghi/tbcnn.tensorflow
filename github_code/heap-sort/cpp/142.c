#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
#define N 300000

void slink(int* a, int i, int len);
void heapsort(int* a, int len);

void heapsort(int* a, int len) {
    // construct the heap
	// int k = len / 2;
	for (int k = len/2; k > -1; k--) {
	    slink(a, k, len);
	}
	
	// cout<<"heap constructed" <<endl;
	// for (int i = 0; i < N; i++) {
	//     cout<<a[i]<<" ";
	// }
	// cout<<endl;
	// sort
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
    // cout<<"slink in"<<endl;
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
    // cout<<"slink out"<<endl;
}


int main() {
    int a[N];
    srand(50000);
	for (int i = 0; i < N; i++) {
	    a[i] = rand() % N;
		// cout<<a[i]<<" ";
	}
	// cout<<endl;
	heapsort(a, N);
	// for (int i = 0; i < N; i++) {
	//     cout<<a[i]<<" ";
	// }
	// cout<<endl;
    return EXIT_SUCCESS;
}
