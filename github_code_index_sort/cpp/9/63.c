#include <vector>

using namespace std;

namespace cpp_sort {
vector<int> selection_sort(vector<int>& numbers_to_sort) {
  int i, j;
  int numbers_to_sort_length = numbers_to_sort.size();

  for (j = 0; j < numbers_to_sort_length - 1; j++) {
    int iMin = j;

    for (i = j + 1; i < numbers_to_sort_length; i++) {
      if (numbers_to_sort[i] < numbers_to_sort[iMin]) {
        iMin = i;
      }
    }

    if (iMin != j) {
      int temp = numbers_to_sort[j];
      numbers_to_sort[j] = numbers_to_sort[iMin];
      numbers_to_sort[iMin] = temp;
    }
  }
  return numbers_to_sort;
}
};  // namespace cpp_sort
