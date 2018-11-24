#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void show(std::vector<int> &v) {
  for (auto &x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

/*
  第一个被覆盖的元素:已经被povit保存;
  中间被覆盖的元素:已经被上次移动保存到其他位置;
  最后一个被移动的元素:保存povit值,代表povit到位;
*/
int participant(vector<int> &vec, int begin, int end) {
  auto povit = vec[begin];
  while (begin < end) {
    while (povit <= vec[end] && begin < end) {
      --end;
    }
    vec[begin] = vec[end];
    while (povit >= vec[begin] && begin < end) {
      ++begin;
    }
    vec[end] = vec[begin];
  }
  vec[begin] = povit;
  return begin;
}

void quick_sort(vector<int> &vec, int begin, int end) {
  if (begin >= end)
    return;
  auto index = participant(vec, begin, end);
  quick_sort(vec, begin, index - 1);
  quick_sort(vec, index + 1, end);
}

int main(int argc, char const *argv[]) {
  std::vector<int> v = {1, 3, 6, 5, 4, 7, 8, 3, 9, 10, -10};
  show(v);
  quick_sort(v, 0, v.size() - 1);
  show(v);
  return 0;
}
