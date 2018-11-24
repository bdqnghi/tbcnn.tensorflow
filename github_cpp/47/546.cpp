#include <iostream>
#include <vector>

int bsearch_iterative(const std::vector<int>&, int);
int bsearch_recursive(const std::vector<int>&, int);
int bsearch_recursive(const std::vector<int>&, int, int, int);

int bsearch_iterative(const std::vector<int>& v, int n) {
  int lo = 0, hi = v.size() - 1, mid;
  while (lo <= hi) {
    mid = (lo + hi) / 2;
    if (v[mid] == n)
      return mid;
    else if (v[mid] < n)
      lo = mid + 1;
    else
      hi = mid - 1;
  }
  return -1;
}

int bsearch_recursive(const std::vector<int>& v, int n) {
  return bsearch_recursive(v, 0, v.size() - 1, n);
}

int bsearch_recursive(const std::vector<int>& v, int lo, int hi, int n) {
  if (lo > hi) return -1;
  int mid = (lo + hi) / 2;
  if (v[mid] == n)
    return mid;
  else if (v[mid] < n)
    return bsearch_recursive(v, mid + 1, hi, n);

  return bsearch_recursive(v, lo, mid - 1, n);
}

int main() {
  std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::cout << "Iterative: " << bsearch_iterative(v, 12) << std::endl;
  std::cout << "Recursive: " << bsearch_recursive(v, -12) << std::endl;
}
