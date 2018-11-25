#include <iostream>
#include <vector>

using std::cout;
using std::vector;

template <typename T>
void split(const vector<T>& list, vector<T>& first_list, vector<T>& second_list) {
  vector<T>* first = &first_list;
  vector<T>* second = &second_list;

  for (const T& element : list) {
    first->push_back(element);
    swap(first, second);
  }
}

template <typename T>
vector<T> merge(const vector<T>& first_list, const vector<T>& second_list) {
  vector<T> result;

  int i = 0, j = 0;
  while (i < first_list.size() && j < second_list.size()) {
    if (first_list[i] < second_list[j]) {
      result.push_back(first_list[i]);
      ++i;
    } else {
      result.push_back(second_list[j]);
      ++j;
    }
  }

  while (i < first_list.size()) {
    result.push_back(first_list[i]);
    ++i;
  }

  while (j < second_list.size()) {
    result.push_back(second_list[j]);
    ++j;
  }

  return result;
}

template <typename T>
vector<T> merge_sort(const vector<T>& list) {
  if (list.size() < 2) {
    return list;
  }

  vector<T> first_list, second_list;
  split(list, first_list, second_list);

  return merge(merge_sort(first_list), merge_sort(second_list));
}

template <typename T>
void print(const vector<T>& list) {
  for (const T& element : list) {
    cout << element << ' ';
  }
  cout << '\n';
}

int main() {
  vector<int> list = {42, 3, 21, 5, 1};

  print(merge_sort(list));

  return 0;
}
