#include <iostream>

int binary_search_iter(int element, int array[], int length) {
  int begin = 0;
  int end = length - 1;
  int mid = (begin + end) / 2;

  while (array[mid] != element && begin <= end) {
    if (element < array[mid]) {
      end = mid - 1;
    } else {
      begin = mid + 1;
    }

    mid = (begin + end) / 2;
  }

  return element == array[mid] ? mid : -1;
}

int binary_search(int element, int array[], int begin, int end) {
  if (begin > end) {
    return -1;
  }

  int mid = (begin + end) / 2;
  if (array[mid] == element) {
    return mid;
  }
  if (element < array[mid]) {
    return binary_search(element, array, begin, mid - 1);
  }
  return binary_search(element, array, mid + 1, end);
}

int binary_search(int element, int array[], int length) {
  return binary_search(element, array, 0, length - 1);
}

int main() {
  int array[] = {3, 5, 10, 21, 42};
  std::cout << binary_search(42, array, 5) << '\n';

  return 0;
}