#ifndef CPP_UTILS_ALGORITHM_SORT_SELECTION_H
#define CPP_UTILS_ALGORITHM_SORT_SELECTION_H

#include <vector>
#include "base.h"

using namespace std;

template<typename Num>
class Selection : public SortBase<Num> {
 public:
  void Sort(vector<Num> &nums) {
    long minIndex = 0;
    long minValue = 0;

    for (long pos = 0; pos < nums.size(); pos++) {
      minValue = nums.back();
      for (long cur = nums.size() - 1; cur >= pos; cur--) {
        if (nums[cur] < minValue) {
          minValue = nums[cur];
          minIndex = cur;
        }
      }
      swap(nums[pos], nums[minIndex]);
    }
  }

};

#endif //CPP_UTILS_ALGORITHM_SORT_SELECTION_H
