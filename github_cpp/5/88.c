#include <vector>

using namespace std;

namespace cpp_sort {
vector<int> insertion_sort(vector<int>& numbers_to_sort) {
  int numbers_to_sort_length = numbers_to_sort.size();

  for (int i = 0; i < numbers_to_sort_length; i++) {
    int j = i;
    while (j > 0 && numbers_to_sort[j - 1] > numbers_to_sort[j]) {
      int temp = numbers_to_sort[j];
      numbers_to_sort[j] = numbers_to_sort[j - 1];
      numbers_to_sort[j - 1] = temp;
      j--;
    }
  }

  return numbers_to_sort;
}
}; 
