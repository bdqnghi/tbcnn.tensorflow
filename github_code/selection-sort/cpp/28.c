

#include <iostream>
#include "Profiler_linux.h"

using namespace std;
int comparisons, assignments;
Profiler profiler("HW1");

void bubble_sort(int n, int x[10000]) {
    bool t;
    int i, aux;
    do {
        t = false;
        for(i = 0; i < n-1; i++) {
            comparisons ++;
            if(x[i] > x[i + 1]) {
                aux = x[i];
                x[i] = x[i + 1];
                x[i+1] = aux;
                assignments = assignments + 3;
                t = true;
            }
        }
    }while(t == true);
}

void insertion_sort (int n, int x[10000]) {
    for (int i = 0; i < n; i++) {
        int j;
        j = i;
        comparisons ++;
        while (j != 0 && x[j] < x[j - 1]) {
            comparisons++;
            assignments = assignments + 3;
            int aux;
            aux = x[j];
            x[j] = x[j - 1];
            x[j - 1] = aux;
            j--;
        }
    }
}

void selection_sort(int n, int x[10000]) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (x[j] < x[min]) {
                min = j;
            }
        }
        if (min != i) {
            assignments = assignments + 3;
            int aux;
            aux = x[i];
            x[i] = x[i+1];
            x[i+1] = aux;
        }
    }
}

int main() {
    int i;
    int n, x[10000];
    comparisons = assignments = 0;
    for (n = 100; n <= 10000; n = n + 100) { // we compute the number of operations in the best case scenario, the one that implies having
        //the arrays already sorted in ascending order
        for (i = 0; i < n; i++) {
            x[i] = i;
        }
        comparisons = assignments = 0;
        insertion_sort(n, x);
        profiler.countOperation("InsertionSortAssignments", n, assignments);
        profiler.countOperation("InsertionSortComparisons", n, comparisons);
        profiler.countOperation("InsertionSortTotal", n, assignments + comparisons);

        comparisons = assignments = 0;
        for (i = 0; i < n; i++) {
            x[i] = i;
        }
        bubble_sort(n, x);
        profiler.countOperation("BubbleSortComparisons", n, comparisons);
        profiler.countOperation("BubbleSortAssignments", n, assignments);
        profiler.countOperation("BubbleSortTotal", n, comparisons + assignments);

        comparisons = assignments = 0;
        for (i = 0; i < n; i++) {
            x[i] = i;
        }
        selection_sort(n, x);
        profiler.countOperation("SelectionSortComparisons", n, comparisons);
        profiler.countOperation("SelectionSortAssignments", n, assignments);
        profiler.countOperation("SelectionSortTotal", n, comparisons + assignments);

        profiler.createGroup("Assignments in best case scenario", "InsertionSortAssignments", "BubbleSortAssignments", "SelectionSortAssignments");
        profiler.createGroup("Comparisons in best case scenario", "InsertionSortComparisons", "BubbleSortComparisons", "SelectionSortComparisons");
        profiler.createGroup("Total operations in best case scenario", "InsertionSortTotal", "BubbleSortTotal", "SelectionSortTotal");
    }

    for (n = 100; n <= 10000; n = n + 100) { // we compute the number of operations in the worst case scenario, which are:
        //elements sorted in descending order for BubbleSort and InsertionSort, and for SelectionSort, the first half descending,
        //and the second half, ascending

        FillRandomArray (x, n, 0, 10000, false, 2);
        comparisons = assignments = 0;
        bubble_sort(n, x);
        profiler.countOperation("BubbleSortComparisonsWorst", n, comparisons);
        profiler.countOperation("BubbleSortAssignmentsWorst", n, assignments);
        profiler.countOperation("BubbleSortTotalWorst", n, comparisons + assignments);

        FillRandomArray (x, n, 0, 10000, false, 2);
        comparisons = assignments = 0;
        insertion_sort(n, x);
        profiler.countOperation("InsertionSortComparisonsWorst", n, comparisons);
        profiler.countOperation("InsertionSortAssignmentsWorst", n, assignments);
        profiler.countOperation("InsertionSortTotalWorst", n, comparisons + assignments);

        for (i = 0; i <= n/2; i++) {
            x[i] = n - i;
        }
        for (i = n/2 + 1; i < n; i++) {
            x[i] = i - n/2;
        }
        comparisons = assignments = 0;
        selection_sort(n, x);
        profiler.countOperation("SelectionSortComparisonsWorst", n, comparisons);
        profiler.countOperation("SelectionSortAssignmentsWorst", n, assignments);
        profiler.countOperation("SelectionSortTotalWorst", n, comparisons + assignments);

        profiler.createGroup("Assignments in worst case scenario", "InsertionSortAssignmentsWorst", "BubbleSortAssignmentsWorst", "SelectionSortAssignmentsWorst");
        profiler.createGroup("Comparisons in worst case scenario", "InsertionSortComparisonsWorst", "BubbleSortComparisonsWorst", "SelectionSortComparisonsWorst");
        profiler.createGroup("Total operations in worst case scenario", "InsertionSortTotalWorst", "BubbleSortTotalWorst", "SelectionSortTotalWorst");
    }

    for (n = 100; n <= 10000; n = n + 100) {//we compute the number of operations when we generate random arrays
        comparisons = assignments = 0;
        for (int j = 1; j <= 5; j++)
        {
            FillRandomArray(x, n);
            bubble_sort(n, x);
        }
        profiler.countOperation("BubbleSortComparisonsRandom", n, comparisons);
        profiler.countOperation("BubbleSortAssignmentsRandom", n, assignments);
        profiler.countOperation("BubbleSortTotalRandom", n, comparisons + assignments);

        comparisons = assignments = 0;
        for (int j = 1; j <= 5; j++)
        {
            FillRandomArray(x, n);
            insertion_sort(n, x);
        }
        profiler.countOperation("InsertionSortComparisonsRandom", n, comparisons);
        profiler.countOperation("InsertionSortAssignmentsRandom", n, assignments);
        profiler.countOperation("InsertionSortTotalRandom", n, assignments + comparisons);

        comparisons = assignments = 0;
        for (int j = 1; j <= 5; j++)
        {
            FillRandomArray(x, n);
            selection_sort(n, x);
        }
        profiler.countOperation("SelectionSortComparisonsRandom", n, comparisons);
        profiler.countOperation("SelectionSortAssignmentsRandom", n, assignments);
        profiler.countOperation("SelectionSortTotalRandom", n, comparisons + assignments);

        profiler.createGroup("Assignments when random numbers", "BubbleSortAssignmentsRandom", "InsertionSortAssignmentsRandom", "SelectionSortAssignmentsRandom");
        profiler.createGroup("Comparisons when random numbers", "BubbleSortComparisonsRandom", "InsertionSortComparisonsRandom", "SelectionSortComparisonsRandom");
        profiler.createGroup("Total operations when random numbers", "BubbleSortTotalRandom", "InsertionSortTotalRandom", "SelectionSortTotalRandom");
    }
    profiler.showReport();
    return 0;
}
