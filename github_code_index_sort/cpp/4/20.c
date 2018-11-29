#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1024;

// @note: all the arrays' indices are 1-based

// Insertion-sort
void sort0(int n, int a[]) {
	for (int i = 2; i <= n; ++i) {
		int v = a[i], ii = i - 1;
		for (; ii >= 1 && a[ii] > v; --ii)
			a[ii + 1] = a[ii];
		a[ii + 1] = v;
	}
}

// Merge-sort
void merge(int l, int r, int a[], int buf[]) {
	int m = (l + r) >> 1;
	int i = l, j = m, n = 0;
	while (i < m && j < r)
		buf[n++] = (a[i] < a[j] ? a[i++] : a[j++]);
	while (i < m)
		buf[n++] = a[i++];
	while (j < r)
		buf[n++] = a[j++];
	memcpy(a + l, buf, sizeof(int) * n);
}

void sort1(int l, int r, int a[], int buf[]) {
	if (r - l <= 1)
		return;
	int m = (l + r) >> 1;
	sort1(l, m, a, buf);
	sort1(m, r, a, buf);
	merge(l, r, a, buf);
}

// Heap-sort
void pushDown(int i, int n, int a[]) {
	int m = i;
	if (i * 2 <= n && a[i * 2] > a[m])
		m = i * 2;
	if (i * 2 + 1 <= n && a[i * 2 + 1] > a[m])
		m = i * 2 + 1;
	if (m != i) {
		swap(a[i], a[m]);
		pushDown(m, n, a);
	}
}

void makeHeap(int n, int a[]) {
	for (int i = n / 2; i >= 1; --i)
		pushDown(i, n, a);
}

void sort2(int n, int a[]) {
	int hn = n;
	makeHeap(hn, a);
	for (int i = n; i >= 2; --i) {
		swap(a[1], a[i]);
		pushDown(1, --hn, a);
	}
}

// Quick-sort
inline int pivotIndex(int l, int r) {
	return l + rand() % (r - l);
}

void sort3(int l, int r, int a[]) {
	if (r - l <= 1)
		return;
	swap(a[l], a[pivotIndex(l, r)]);
	int pivot = a[l], i = l + 1, j = r - 1;
	while (1) {
		while (i <= j && a[i] <= pivot) ++i;
		while (i <= j && a[j] >= pivot) --j;
		if (i < j) {
			swap(a[i], a[j]);
		} else {
			break;
		}
	}
	swap(a[i - 1], a[l]);
	sort3(l, i - 1, a);
	sort3(i, r, a);
}

// Shell-sort
void sort4(int n, int a[]) {
	for (int inc = n / 2; inc >= 1; inc /= 2) {
		for (int i = inc + 1; i <= n; ++i) {
			int v = a[i], ii = i - inc;
			for (; ii >= 1 && a[ii] > v; ii -= inc)
				a[ii + inc] = a[ii];
			a[ii + inc] = v;
		}
	}
}

// Selection-sort
void sort5(int n, int a[]) {
	for (int i = 1; i <= n; ++i) {
		int m = i;
		for (int j = i + 1; j <= n; ++j) {
			if (a[j] < a[m])
				m = j;
		}
		swap(a[i], a[m]);
	}
}

// Bubble-sort
void sort6(int n, int a[]) {
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (a[i] > a[j])
				swap(a[i], a[j]);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Testing code

void show(int n, int a[]) {
	for (int i = 1; i <= n; ++i)
		printf("%d ", a[i]);
	puts("");
}

void test(int cas, int m) {
	int n, a[MAXN], v[MAXN], buf[MAXN];
	
	srand((unsigned)time(NULL));
	for (int ca = 1; ca <= cas; ++ca) {
		n = rand() % m + 1;
		for (int i = 1; i <= n; ++i)
			v[i] = rand() % 1024;
		printf("\ninput %d\t : ", ca);
		for (int i = 1; i <= n; ++i)
			printf("%d ", v[i]);
		puts("");
		
		// insertion-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort0(n, a);
		printf("insert\t : ");
		show(n, a);
		
		// merge-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort1(1, n + 1, a, buf);
		printf("merge\t : ");
		show(n, a);
		
		// heap-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort2(n, a);
		printf("heap\t : ");
		show(n, a);
		
		// quick-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort3(1, n + 1, a);
		printf("quick\t : ");
		show(n, a);

		// shell-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort4(n, a);
		printf("shell\t : ");
		show(n, a);
		
		// selection-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort5(n, a);
		printf("select\t : ");
		show(n, a);

		// bubble-sort
		memcpy(a + 1, v + 1, sizeof(v[0]) * n);
		sort6(n, a);
		printf("bubble\t : ");
		show(n, a);
	}
}

int main() {
	test(8, 10);
	return 0;
}
