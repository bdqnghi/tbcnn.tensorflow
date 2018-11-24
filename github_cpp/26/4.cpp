
/*
  Bubble Sort

  Worst Case Performance: O(n^2)
    Given a list in the reverse order, each node in
    the list must be swapped with all other nodes to
    get to the correct side of the list. Graphically:

    S *           *
    w *           *   Looking like the graph of
    a * *       * *   y = x ^ 2 to me.
    p * *       * *
    s * * *   * * *
      * * *   * * *
    @ 7 6 5 4 3 2 1
  Best Case Performance: O(n)
    Given a list already sorted, no swap operations
    are needed but a linear pass is still need to be
    sure the list is sorted.
  Average Case Performance: O(n^2); O(n) < O(n^2)
  Worst Case Space Complexity: O(n); in-place

  Comparision to other sorts:

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

void bubbleSort(int* array, const int len) {
  bool swapped = true;
  while(swapped) {
    swapped = false;
    for(int index = 1; index < len; index++) {
      if(array[index - 1] > array[index]) {
        swap(array, index - 1, index);
        swapped = true;
      }
    }
  }
}

void bubbleSortTest() {
  {
    int len = 6;
    int wrong[] = {64, 25, 12, 22, 11, 8};
    int right[] = {8, 11, 12, 22, 25, 64};
    bubbleSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }

  {
    int len = 5;
    int wrong[] = {67, 34, 17, 55, 6};
    int right[] = {6, 17, 34, 55, 67};
    bubbleSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }
}

int main() {
  bubbleSortTest();
  return 0;
}


