


#include <assert.h>



void swap(int* &array, const int a, const int b) {
  int c = array[a];
  array[a] = array[b];
  array[b] = c;
}

bool arrayEqual(const int* uno, const int* dos, const int len) {
  for(int i = 0; i < len; i++) {
    
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


void mergeSortSplit(int* array, int* working, int start, int end) {
  if(end - start < 2) return;
  int middle = (end + start) / 2;
  mergeSortSplit(array, working, start, middle);
  mergeSortSplit(array, working, middle, end);
  mergeSortMerge(array, working, start, middle, end);
  copySegment(working, array, start, end);
}


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


