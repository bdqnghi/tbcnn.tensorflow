
/*
  Selection Sort

  Worst Case Performance: O(n^2)
    Scanning for the min of a n-long list takes (n - 1),
    the next scan takes (n - 2), next scan is (n - 3),
    So: (n - 1) + (n - 2) + ...
    So: Arithmetic progression for finite series states:
      ( number-of-terms * (first-value + last-value)) / 2
    So: n(n - 1) / 2 = (n^2 - n) / 2 => O(n^2)
  Best Case Performance: O(n^2)
    Performance is the same as the worst case because the
    scans are performed to find the min even if the array
    is already completely sorted, which is the ideal.
  Average Case Performance: O(n^2)
  Worst Case Space Complexity: O(1); sorting is in-place

  Comparision to other sorts:
    - Better than Bubble and other O(n^2) sorts
    - Non-adaptive, i.e. constant performance no matter how
      much of the data is already sorted.
    - Slower than Insert Sort, but wins on swap operations.
      If swap operations are a factor consider Cycle Sort.
    - Best suited to small arrays, use divide-and-conquer
      for larger arrays e.g. Merge Sort.
*/

#include <assert.h>
/* #include <iostream> */
/* using namespace std; */

void swap(int* &array, const int a, const int b) {
  int c = array[a];
  array[a] = array[b];
  array[b] = c;
}

bool arrayEqual(const int* uno, const int* dos, const int len) {
  for(int i = 0; i < len; i++) {
    /* cout << uno[i] << " == " << dos[i] << endl; */
    if(uno[i] != dos[i]) return false;
  }
  return true;
}

void selectionSort(int* array, const int len) {
  int min;
  for(int offset = 0; offset < len - 1; offset++) {
    min = offset;
    for(int index = offset + 1; index < len; index++) {
      if(array[index] < array[min]) min = index;
    }
    // if min == offset, the value is already in the right order
    if(min != offset) swap(array, offset, min);
  }
}

void selectionSortTest() {
  {
    int len = 6;
    int wrong[] = {64, 25, 12, 22, 11, 8};
    int right[] = {8, 11, 12, 22, 25, 64};
    selectionSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }

  {
    int len = 5;
    int wrong[] = {67, 34, 17, 55, 6};
    int right[] = {6, 17, 34, 55, 67};
    selectionSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }
}

int main() {
  selectionSortTest();
  return 0;
}

