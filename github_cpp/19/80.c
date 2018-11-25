


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


void quickSort(int* array, const int low, const int high) {
  if(low >= high) return;
  int pivot = array[high];
  int index = low;
  for(int i = low; i < high; i++) {
    if(array[i] <= pivot) {
      swap(array, index, i);
      index++;
    }
  }
  swap(array, index, high);
  quickSort(array, low, index - 1);
  quickSort(array, index + 1, high);
}


void quickSort(int* array, const int len) {
  quickSort(array, 0, len - 1);
}

void quickSortTest() {
  {
    int len = 6;
    int wrong[] = {64, 25, 12, 22, 11, 8};
    int right[] = {8, 11, 12, 22, 25, 64};
    quickSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }

  {
    int len = 5;
    int wrong[] = {67, 34, 17, 55, 6};
    int right[] = {6, 17, 34, 55, 67};
    quickSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }
}

int main() {
  quickSortTest();
  return 0;
}


