#include <cstdio>
using namespace std;

typedef struct {
	int *arr, val, sz;
}num;

void convtobase(int n, int b, int m, num *p) {
	int i;
	p->val = n;
	p->sz = m;
	p->arr = new int[m];
	i = 0;
	while(n > 0) {
		p->arr[i] = n % b;
		n /= b;
		i++;
	}
	while(i < m) {
		p->arr[i] = 0;
		i++;
	}
}

void printnum(num n) {
	int i, m;
	printf("val: %d | ", n.val);
	printf("sz: %d | ", n.sz);
	m = n.sz;
	for(i = 0 ; i < m ; i++) {
		printf("%d ", n.arr[i]);
	}
	printf("\n");
}

int getlen(int n, int b) {
	int i;
	i = 0;
	while(n > 0) {
		n /= b;
		i++;
	}
	return i;
}

void numcopy(num *a, num *b) {
	int i, n;
	a->sz = b->sz;
	a->val = b->val;
	n = b->sz;
	for(i = 0 ; i < n ; i++) {
		a->arr[i] = b->arr[i];
	}
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void count_sort(num *a, int n, int d) {
	int i, k, *c;
	num *b;
	b = new num[n];
	c = new int[n];
	k = a[0].sz;
	for(i = 0 ; i < n ; i++) {
		b[i].arr = new int[k];
		c[i] = 0;
	}
	for(i = 0 ; i < n ; i++) {
		c[a[i].arr[d]]++;
	}
	for(i = 1 ; i < n ; i++) {
		c[i] += c[i-1];
	}
	for(i = n-1 ; i >= 0 ; i--) {
		k = a[i].arr[d];
		numcopy(b+c[k]-1, a+i);
		c[k]--;
	}
	for(i = 0 ; i < n ; i++) {
		numcopy(a+i, b+i);
	}
	for(i = 0 ; i < n ; i++) {
		delete(b[i].arr);
	}
	delete(b);
	delete(c);
}

void radix_sort(int *a, int n) {
	int i, m, j;
	num *b;
	b = new num[n];
	m = 0;
	for(i = 0 ; i < n ; i++) {
		m = max(m, getlen(a[i], n));
	}
	for(i = 0 ; i < n ; i++) {
		convtobase(a[i], n, m, b+i);
	}
	for(i = 0 ; i < m ; i++) {
		count_sort(b, n, i);
	}
	for(i = 0 ; i < n ; i++) {
		a[i] = b[i].val;
	}
	for(i = 0 ; i < n ; i++) {
		delete(b[i].arr);
	}
	delete(b);
}

void array_add(int *a, int n, int k) {
	int i;
	for(i = 0 ; i < n ; i++) {
		a[i] += k;
	}
}

int main() {
	int n, i, *a, m, k;
	scanf("%d", &n);
	a = new int[n];
	for(i = 0 ; i < n ; i++) {
		scanf("%d", &a[i]);
	}
	m = 0;
	for(i = 1 ; i < n ; i++) {
		if(a[m] > a[i]) {
			m = i;
		}
	}
	k = a[m];
	if(k < 0) {
		array_add(a, n, -k);
	}
	radix_sort(a, n);
	if(k < 0) {
		array_add(a, n, k);
	}
	for(i = 0 ; i < n ; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	delete(a);
	return 0;
}