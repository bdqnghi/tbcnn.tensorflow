// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Radix sort implementation

#include "book.h"

// Include comparator functions
#include "compare.h"

extern int THRESHOLD;

int POW2[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

#define pow2(X) POW2[X]

template <typename E, typename getKey>
void radix(E A[], E B[],
           int n, int k, int r, int cnt[]) {
  // cnt[i] stores number of records in bin[i]
  int j;

  for (int i=0, rtoi=1; i<k; i++, rtoi*=r) { // For k digits
    for (j=0; j<r; j++) cnt[j] = 0;        // Initialize cnt

    // Count the number of records for each bin on this pass
    for (j=0; j<n; j++) cnt[(getKey::key(A[j])/rtoi)%r]++;

    // Index B: cnt[j] will be index for last slot of bin j.
    for (j=1; j<r; j++) cnt[j] = cnt[j-1] + cnt[j];

    // Put records into bins, work from bottom of each bin.
    // Since bins fill from bottom, j counts downwards
    for (j=n-1; j>=0; j--)
      B[--cnt[(getKey::key(A[j])/rtoi)%r]] = A[j];

    for (j=0; j<n; j++) A[j] = B[j];    // Copy B back to A
  }
}

// Radix sort implementation. THRESHOLD is the number of bits done each pass
template <typename E, typename Comp>
void sort(E* array, int n) {
  static E* temp = NULL;
  static int* cnt = NULL;
  Assert(THRESHOLD > 0, "Need to set THRESHOLD");
  if (temp == NULL) temp = new E[n];  // Declare temp array
  if (cnt == NULL) cnt = new int[pow2(THRESHOLD)];  // Declare temp array
  radix<E,Comp>(array, temp, n, (sizeof(E) * 8)/THRESHOLD,
                   pow2(THRESHOLD), cnt);
}

#include "sortmain.cpp"

int main(int argc, char** argv) {
  return sortmain<getintKey>(argc, argv);
}
