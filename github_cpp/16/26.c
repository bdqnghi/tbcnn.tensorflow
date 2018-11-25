#include <vector>

using namespace std;

namespace cpp_sort {
vector<int> shell_sort(vector<int>& numbers_to_sort) {
  int j;
  int size = numbers_to_sort.size();

  for (int gap = size / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < size; ++i) {
      int temp = numbers_to_sort[i];
      for (j = i; j >= gap && temp < numbers_to_sort[j - gap]; j -= gap) {
        numbers_to_sort[j] = numbers_to_sort[j - gap];
      }
      numbers_to_sort[j] = temp;
    }
  }

  return numbers_to_sort;
}
};  