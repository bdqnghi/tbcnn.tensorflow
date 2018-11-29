/*
 * Homework 2 - CIT225
 * Matthew Noel
 */

#include<cstdlib>
#include<iostream>
#include<ctime>
#include<math.h>

using namespace std;

struct Counter {
        long long swaps = 0;
        long long comparisons = 0;
};

void revertArrays(long[], long[], long[], long[], long[], long[]);
void insertionSort(long[], long, Counter&);
void selectionSort(long[], long, Counter&);
void quickSort(long[], long, long, Counter&);
long partition(long[], long, long, Counter&);
void shellSort(long[], long, long[], long, Counter&);
void insertionSortInterleaved(long[], long, long, long, Counter&);
void generateGaps(long[], long&, long);
void generateGapsAlt(long[], long&, long);

int main() {
        Counter insertionCounter;
        Counter selectionCounter;
        Counter quickCounter;
        Counter shellCounter;
        Counter shellOneCounter;

        long fiveThousandMaster[5000];
        long tenThousandMaster[10000];
        long hundredThousandMaster[100000];

        long fiveThousand[5000];
        long tenThousand[10000];
        long hundredThousand[100000];

        long gapValues[20];
        long numGaps;

        double start;
        double stop;

        for (int i = 0; i < 3; i++) {
                // Fill master arrays randomly
                for (int i = 0; i < 5000; i++) {
                        fiveThousandMaster[i] = rand();
                }

                for (int i = 0; i < 10000; i++) {
                        tenThousandMaster[i] = rand();
                }

                for (int i = 0; i < 100000; i++) {
                        hundredThousandMaster[i] = rand();
                }
                
                // Fill duplicate arrays
                revertArrays(fiveThousand, fiveThousandMaster, tenThousand, tenThousandMaster, hundredThousand, hundredThousandMaster);

                // Insertion sort all three
                insertionCounter.swaps = 0;
                insertionCounter.comparisons = 0;
                start = clock();
                insertionSort(fiveThousand, 5000, insertionCounter);
                stop = clock();
                cout << "5000   - Insertion Sort - Swaps: " << insertionCounter.swaps << " Comparisons: " << insertionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                insertionCounter.swaps = 0;
                insertionCounter.comparisons = 0;
                start = clock();
                insertionSort(tenThousand, 10000, insertionCounter);
                stop = clock();
                cout << "10000  - Insertion Sort - Swaps: " << insertionCounter.swaps << " Comparisons: " << insertionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                insertionCounter.swaps = 0;
                insertionCounter.comparisons = 0;
                start = clock();
                insertionSort(hundredThousand, 100000, insertionCounter);
                stop = clock();
                cout << "100000 - Insertion Sort - Swaps: " << insertionCounter.swaps << " Comparisons: " << insertionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl << endl;
                
                revertArrays(fiveThousand, fiveThousandMaster, tenThousand, tenThousandMaster, hundredThousand, hundredThousandMaster);

                // Selection sort all three
                selectionCounter.swaps = 0;
                selectionCounter.comparisons = 0;
                start = clock();
                selectionSort(fiveThousand, 5000, selectionCounter);
                stop = clock();
                cout << "5000   - Selection Sort - Swaps: " << selectionCounter.swaps << " Comparisons: " << selectionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                selectionCounter.swaps = 0;
                selectionCounter.comparisons = 0;
                start = clock();
                selectionSort(tenThousand, 10000, selectionCounter);
                stop = clock();
                cout << "10000  - Selection Sort - Swaps: " << selectionCounter.swaps << " Comparisons: " << selectionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                selectionCounter.swaps = 0;
                selectionCounter.comparisons = 0;
                start = clock();
                selectionSort(hundredThousand, 100000, selectionCounter);
                stop = clock();
                cout << "100000 - Selection Sort - Swaps: " << selectionCounter.swaps << " Comparisons: " << selectionCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl << endl;
        
                revertArrays(fiveThousand, fiveThousandMaster, tenThousand, tenThousandMaster, hundredThousand, hundredThousandMaster);

                // Quicksort all three
                quickCounter.swaps = 0;
                quickCounter.comparisons = 0;
                start = clock();
                quickSort(fiveThousand, 0, 4999, quickCounter);
                stop = clock();
                cout << "5000   - Quicksort - Swaps: " << quickCounter.swaps << " Comparisons: " << quickCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                quickCounter.swaps = 0;
                quickCounter.comparisons = 0;
                start = clock();
                quickSort(tenThousand, 0, 9999, quickCounter);
                stop = clock();
                cout << "10000  - Quicksort - Swaps: " << quickCounter.swaps << " Comparisons: " << quickCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                quickCounter.swaps = 0;
                quickCounter.comparisons = 0;
                start = clock();
                quickSort(hundredThousand, 0, 99999, quickCounter);
                stop = clock();
                cout << "100000 - Quicksort - Swaps: " << quickCounter.swaps << " Comparisons: " << quickCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl << endl;
        
                revertArrays(fiveThousand, fiveThousandMaster, tenThousand, tenThousandMaster, hundredThousand, hundredThousandMaster);

                // Shell Sort all three
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGaps(gapValues, numGaps, 5000);
                start = clock();
                shellSort(fiveThousand, 5000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "5000   - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGaps(gapValues, numGaps, 10000);
                start = clock();
                shellSort(tenThousand, 10000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "10000  - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGaps(gapValues, numGaps, 100000);
                start = clock();
                shellSort(hundredThousand, 100000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "100000 - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl << endl;
        
                revertArrays(fiveThousand, fiveThousandMaster, tenThousand, tenThousandMaster, hundredThousand, hundredThousandMaster);

                // Shell Sort all three
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGapsAlt(gapValues, numGaps, 5000);
                start = clock();
                shellSort(fiveThousand, 5000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "5000   - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGapsAlt(gapValues, numGaps, 10000);
                start = clock();
                shellSort(tenThousand, 10000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "10000  - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl;
                shellCounter.swaps = 0;
                shellCounter.comparisons = 0;
                generateGapsAlt(gapValues, numGaps, 100000);
                start = clock();
                shellSort(hundredThousand, 100000, gapValues, numGaps, shellCounter);
                stop = clock();
                cout << "100000 - Shell Sort - Swaps: " << shellCounter.swaps << " Comparisons: " << shellCounter.comparisons << " Time: " << (stop - start) / CLOCKS_PER_SEC << endl << endl;
        }

        return 0;
}

void revertArrays(long fiveThousand[], long fiveThousandMaster[], long tenThousand[], long tenThousandMaster[], long hundredThousand[], long hundredThousandMaster[]) {

        for (int i = 0; i < 5000; i++) {
                fiveThousand[i] = fiveThousandMaster[i];
        }

        for (int i = 0; i < 10000; i++) {
                tenThousand[i] = tenThousandMaster[i];
        }

        for (int i = 0; i < 100000; i++) {
                hundredThousand[i] = hundredThousandMaster[i];
        }
        return;
}

// [Y] Works
// Smallest to largest
void insertionSort(long numbers[], long numbersSize, Counter& insertionCounts) {
        int i = 0;
        int j = 0;
        int temp = 0;

        for (int i = 1; i < numbersSize; i++) {
                j = i;
                insertionCounts.comparisons += 1;
                while (j > 0 && numbers[j] < numbers[j - 1]) {

                        temp = numbers[j];
                        numbers[j] = numbers[j - 1];
                        numbers[j - 1] = temp;

                        insertionCounts.swaps += 3;

                        j--;
                }
        }
}

// [Y] Works
// Smallest to largest
void selectionSort(long numbers[], long numbersSize, Counter& selectionCounts) {
        int i = 0;
        int j = 0;
        int indexSmallest = 0;
        int temp = 0;

        for (int i = 0; i < numbersSize - 1; i++) {
                indexSmallest = i;
                for (int j = i + 1; j < numbersSize; j++) {
                        selectionCounts.comparisons += 1;
                        if (numbers[j] < numbers[indexSmallest]) {
                                indexSmallest = j;
                        }
                }

                temp = numbers[i];
                numbers[i] = numbers[indexSmallest];
                numbers[indexSmallest] = temp;
                selectionCounts.swaps += 3;
        }
}

// [Y] Works
// Smallest to largest
// i is first element
// k is last element
void quickSort(long numbers[], long i, long k, Counter& quickCounts) {
        int j = 0;

        if (i >= k) {
                return;
        }

        j = partition(numbers, i, k, quickCounts);

        quickSort(numbers, i, j, quickCounts);
        quickSort(numbers, j + 1, k, quickCounts);
}

long partition(long numbers[], long i, long k, Counter& quickCounts) {
        int l = 0;
        int h = 0;
        int midpoint = 0;
        int pivot = 0;
        int temp = 0;
        bool done = false;

        midpoint = i + (k - i) / 2;
        pivot = numbers[midpoint];

        l = i;
        h = k;

        while (!done) {
                quickCounts.comparisons += 1;
                while (numbers[l] < pivot) {
                        l++;
                }
                quickCounts.comparisons += 1;
                while (pivot < numbers[h]) {
                        h--;
                }

                if (l >= h) {
                        quickCounts.comparisons += 1;
                        done = true;
                } else {
                        temp = numbers[l];
                        numbers[l] = numbers[h];
                        numbers[h] = temp;
                        quickCounts.swaps += 3;

                        l++;
                        h--;
                }
        }

        return h;
}

// [Y] Works
// Smallest to largest
void shellSort(long numbers[], long numbersSize, long gapValues[], long numGaps, Counter& shellCounts) {
        for (int j = 0; j < numGaps; j++) {
                for (int i = 0; i < gapValues[j]; i++) {
                        insertionSortInterleaved(numbers, numbersSize, i, gapValues[j], shellCounts);
                }
        }
}

void insertionSortInterleaved(long numbers[], long numbersSize, long startIndex, long gap, Counter& shellCounts) {

        int temp = 0;

        for (int i = startIndex + gap; i < numbersSize; i = i + gap) {
                int j = i;
                shellCounts.comparisons += 1;
                while (j - gap >= startIndex && numbers[j] < numbers[j - gap]) {
                        temp = numbers[j];
                        numbers[j] = numbers[j - gap];
                        numbers[j - gap] = temp;
                        shellCounts.swaps += 3;
                        j = j - gap;
                }
        }
}

void generateGaps(long gapValues[], long& numGaps, long numElements) {
        numGaps = 0;
        int divisor = 2;
        for (int i = 0; i < 20; i++) {
                if ((numElements / divisor) != 1) {
                        gapValues[i] = (numElements / divisor);
                        numGaps += 1;
                        divisor = divisor * 2;
                }
                else {
                        gapValues[i] = 0;
                }
        }
}

void generateGapsAlt(long gapValues[], long& numGaps, long numElements) {
        numGaps = 1;
        int exponent = 1;
        long reversed[20];
        reversed[0] = 1;

        for (int i = 1; i < 20; i++) {
                if (pow(2, exponent) + 1 < numElements) {
                        reversed[i] = pow(2, exponent) + 1;
                        numGaps++;
                        exponent++;
                } else {
                        reversed[i] = 0;
                }
        }
        int index = 0;
        for (int i = 0; i < 20; i++) {
                if (index < numElements) {
                        gapValues[i] = reversed[19 - (20 - numElements) - index];
                        index++;
                } else {
                        gapValues[i] = 0;
                }
        }
}