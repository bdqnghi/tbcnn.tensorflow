#include "../../shared/includes/helpers.cpp"

void insertion_sort(int *array, int size) {
  int key, sort_index;
  for (int index = 1; index < size; index++) {
    key        = array[index];
    sort_index = index - 1;
    while (sort_index >= 0 && array[sort_index] > key) {  
      array[sort_index + 1] = array[sort_index];
      sort_index--;
    }
    array[sort_index+1] = key;
  }
}

int main() {
  int ar[] = {5,1,4,3,2};
  int size = 5;

  cout << "Before sort:" << endl;
  printArray(ar, size);

  insertion_sort(ar, size);

  cout << "After sort:" << endl;
  printArray(ar, size);

}