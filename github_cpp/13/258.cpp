
/*
  Merge Sort

  Worst Case Performance: O(nlog n)
  Best Case Performance: O(nlog n)
  Average Case Performance: O(nlog n)
  Worst Case Space Complexity: O(n)

  Comparision to other sorts:
    - Needs an auxillary array the same size of the input.
    - Unlike Quick Sort, most Merge Sorts are stable.
    - Best used with sequential memory, such as linked lists.
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

void copySegment(
    const int* src, int* &dest,
    const int start, const int end) {
  for(int i = start; i < end; i++) {
    dest[i] = src[i];
  }
}

/*
  This method is called to sort two given close sublists
  into one sorted list recursively until the original big
  list is completely sorted.
*/
void mergeSortMerge(
    int* array, int* working,
    const int start, const int middle, const int end) {
  int lowStart = start;
  int lowEnd = middle;
  for(int index = start; index < end; index++) {
    if(
        lowStart < middle &&
        (lowEnd >= end || array[lowStart] <= array[lowEnd])) {
      working[index] = array[lowStart];
      lowStart++;
    } else {
      working[index] = array[lowEnd];
      lowEnd++;
    }
  }
}

/*
  This is the method called recursively to break the list
  into smalled sublist, the smallest list being size = 1.
*/
void mergeSortSplit(int* array, int* working, int start, int end) {
  if(end - start < 2) return;
  int middle = (end + start) / 2;
  mergeSortSplit(array, working, start, middle);
  mergeSortSplit(array, working, middle, end);
  mergeSortMerge(array, working, start, middle, end);
  copySegment(working, array, start, end);
}

/*
  This is the method called by regular arrays.
*/
void mergeSort(int* array, const int len) {
  int working[len];
  mergeSortSplit(array, working, 0, len);
}

void mergeSortTest() {
  {
    int len = 6;
    int wrong[] = {64, 25, 12, 22, 11, 8};
    int right[] = {8, 11, 12, 22, 25, 64};
    mergeSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }

  {
    int len = 5;
    int wrong[] = {67, 34, 17, 55, 6};
    int right[] = {6, 17, 34, 55, 67};
    mergeSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }
}

int main() {
  mergeSortTest();
  return 0;
}


