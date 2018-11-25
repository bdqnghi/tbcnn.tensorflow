


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

void insertionSort(int* array, const int len) {
  for(int index = 1; index < len; index++) {
    int value = array[index];
    int left = index - 1;
    for(int left = index - 1; left >= 0; left--) {
      if(array[left] < value) break;
      swap(array, left, left + 1);
    }
  }
}

void insertionSortTest() {
  {
    int len = 6;
    int wrong[] = {64, 25, 12, 22, 11, 8};
    int right[] = {8, 11, 12, 22, 25, 64};
    insertionSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }

  {
    int len = 5;
    int wrong[] = {67, 34, 17, 55, 6};
    int right[] = {6, 17, 34, 55, 67};
    insertionSort(wrong, len);
    assert(arrayEqual(wrong, right, len));
  }
}

int main() {
  insertionSortTest();
  return 0;
}

