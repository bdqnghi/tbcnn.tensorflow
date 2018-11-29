#include <stdio.h>
#include "profiler.h"
#define MAX_SIZE 10000

Profiler profiler("Tema 1");

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void selectionSort(int *v, int n) {
	int a = 0, c = 0, poz_min, i, j;

	for (i = 0; i < n - 1; i++) {
		poz_min = i;

		for (j = i + 1; j < n; j++) {
			profiler.countOperation("Selection: Numar de comparatii", n);
			profiler.countOperation("Selection: Numar de comparatii si asignari", n);

			if (v[j] < v[poz_min]) {
				poz_min = j;
			}
		}

		if (i != poz_min) {
			profiler.countOperation("Selection: Numar de asignari", n, 3);
			profiler.countOperation("Selection: Numar de comparatii si asignari", n, 3);
			swap(&v[i], &v[poz_min]);
		}
	}
}

void insertionSort(int *v, int n) {
	int a = 0, c = 0, el, i, j;

	for (i = 2; i < n; i++) {
		el = v[i];
		j = i - 1;
		profiler.countOperation("Insertion: Numar de asignari", n);
		profiler.countOperation("Insertion: Numar de comparatii si asignari", n);

		while (j >= 0 and el < v[j]) {
			v[j + 1] = v[j];
			j--;
			profiler.countOperation("Insertion: Numar de asignari", n);
			profiler.countOperation("Insertion: Numar de comparatii si asignari", n, 2);
			profiler.countOperation("Insertion: Numar de comparatii", n);
		}
		v[j + 1] = el;
		profiler.countOperation("Insertion: Numar de asignari", n);
		profiler.countOperation("Insertion: Numar de comparatii si asignari", n);
	}
}

void bubbleSort(int *v, int n) {
	int a = 0, c = 0, i, j;
	bool swapped = true;

	for (i = 0; i < n - 1; i++)

		for (j = 0; j < n - i - 1; j++) {
			profiler.countOperation("Bubble: Numar de comparatii", n);
			profiler.countOperation("Bubble: Numar de comparatii si asignari", n);

			if (v[j] > v[j + 1]) {
				swap(&v[j], &v[j + 1]);
				profiler.countOperation("Bubble: Numar de asignari", n, 3);
				profiler.countOperation("Bubble: Numar de comparatii si asignari", n, 3);
			}
		}

}

void afiseaza(int *v, int n) {
	int i;

	for (i = 0; i < n; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

void verificareAlgoritm(int n) {
	int i;
	int a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE];

	for (i = 0; i < n; i++) {
		a[i] = rand() % 100 + 1;
		b[i] = a[i];
		c[i] = a[i];
	}
	bubbleSort(a, n);
	insertionSort(b, n);
	selectionSort(c, n);
	afiseaza(a, n);
	afiseaza(b, n);
	afiseaza(c, n);
}

int main() {
	int i, j;
	int v[MAX_SIZE], v1[MAX_SIZE], v2[MAX_SIZE];
	//verificareAlgoritm(10);

	for (i = 100; i < 800; i += 100) {
		FillRandomArray(v, i, 1, 10000, false, 0);

		for (j = 0; j < i; j++) {
			v1[j] = v[j];
			v2[j] = v[j];
		}
		bubbleSort(v, i);
		insertionSort(v1, i);
		selectionSort(v2, i);
	}
	profiler.createGroup("Comparatii AVG", "Bubble: Numar de comparatii", "Insertion: Numar de comparatii", "Selection: Numar de comparatii");
	profiler.createGroup("Asignari AVG", "Bubble: Numar de asignari", "Insertion: Numar de asignari", "Selection: Numar de asignari");
	profiler.createGroup("Comparatii si asignari AVG", "Bubble: Numar de comparatii si asignari", "Insertion: Numar de comparatii si asignari", "Selection: Numar de comparatii si asignari");
	//profiler.createGroup("Bubble Sort AVG", "Bubble: Numar de comparatii", "Bubble: Numar de asignari", "Bubble: Numar de comparatii si asignari");
	//profiler.createGroup("Insertion Sort AVG", "Insertion: Numar de comparatii", "Insertion: Numar de asignari", "Insertion: Numar de comparatii si asignari");
	//profiler.createGroup("Selection Sort AVG", "Selection: Numar de comparatii", "Selection: Numar de asignari", "Selection: Numar de comparatii si asignari");
	profiler.reset(" ");

	for (i = 100; i < 800; i += 100) {
		FillRandomArray(v, i, 1, 10000, false, 1);

		for (int j = 0; j < i; j++) {
			v1[j] = v[j];
			v2[j] = v[j];
		}
		bubbleSort(v, i);
		insertionSort(v1, i);
		selectionSort(v2, i);
	}
	profiler.createGroup("Comparatii BEST", "Bubble: Numar de comparatii", "Selection: Numar de comparatii");
	profiler.createGroup("Asignari BEST", "Insertion: Numar de asignari");
	profiler.createGroup("Comparatii si asignari BEST", "Bubble: Numar de comparatii si asignari", "Insertion: Numar de comparatii si asignari", "Selection: Numar de comparatii si asignari");
	//profiler.createGroup("Bubble Sort BEST", "Bubble: Numar de comparatii", "Bubble: Numar de comparatii si asignari");
	//profiler.createGroup("Insertion Sort BEST","Insertion: Numar de asignari", "Insertion: Numar de comparatii si asignari");
	//profiler.createGroup("Selection Sort BEST", "Selection: Numar de comparatii", "Selection: Numar de comparatii si asignari");
	profiler.reset(" ");

	for (i = 100; i < 800; i += 100) {
		FillRandomArray(v, i, 1, 10000, false, 2);

		for (int j = 0; j < i; j++) {
			v1[j] = v[j];
			v2[j] = v[j];
		}
		bubbleSort(v, i);
		insertionSort(v1, i);
		selectionSort(v2, i);
	}
	profiler.createGroup("Comparatii WORST", "Bubble: Numar de comparatii", "Insertion: Numar de comparatii", "Selection: Numar de comparatii");
	profiler.createGroup("Asignari WORST", "Bubble: Numar de asignari", "Insertion: Numar de asignari", "Selection: Numar de asignari");
	profiler.createGroup("Comparatii si asignari WORST", "Bubble: Numar de comparatii si asignari", "Insertion: Numar de comparatii si asignari", "Selection: Numar de comparatii si asignari");
	//profiler.createGroup("Bubble Sort WORST", "Bubble: Numar de comparatii", "Bubble: Numar de asignari", "Bubble: Numar de comparatii si asignari");
	//profiler.createGroup("Insertion Sort WORST", "Insertion: Numar de comparatii", "Insertion: Numar de asignari", "Insertion: Numar de comparatii si asignari");
	//profiler.createGroup("Selection Sort WORST", "Selection: Numar de comparatii", "Selection: Numar de asignari", "Selection: Numar de comparatii si asignari");
	profiler.showReport();

	return 0;


}