


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


