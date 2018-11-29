#include <vector>

using namespace std;

namespace cpp_sort {
inline vector<int> bubble_sort(vector<int> numbers_to_sort) {
  unsigned int size_of_array = numbers_to_sort.size() - 1;
  // Used to store int while switching array values
  unsigned int temp;
  // Keeps track of swaps, if none are made array is sorted
  unsigned int swaps;

  for (unsigned int i = 0; i < size_of_array; i++) {
    swaps = 0;
    for (unsigned int j = 0; j < size_of_array; j++) {
      if (numbers_to_sort[j] > numbers_to_sort[j + 1]) {
        temp = numbers_to_sort[j];
        numbers_to_sort[j] = numbers_to_sort[j + 1];
        numbers_to_sort[j + 1] = temp;
        swaps++;
      }
    }
    if (swaps == 0) {
      break;
    }
  }
  return numbers_to_sort;
}
}  // namespace cpp_sort
