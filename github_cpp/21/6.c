


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

void selectionSort(int* array, const int len) {
  int min;
  for(int offset = 0; offset < len - 1; offset++) {
    min = offset;
    for(int index = offset + 1; index < len; index++) {
      if(array[index] < array[min]) min = index;
    }
    
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

