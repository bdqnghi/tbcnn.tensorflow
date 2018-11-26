/* heap.cpp */
// STL push_heap, pop_heap, make_heap and sort_heap
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

#include <vector>

int main() {
  const int SIZE = 10;
  int a[SIZE] = { 3, 100, 52, 77, 22, 31, 1, 98, 13, 40 };
  int i;
  std:: vector<int> v(a, a + SIZE),
    v2;
  std::ostream_iterator<int> output(cout, " ");

  cout << "v: ";
  std::copy(v.begin(), v.end(), output);

  std::make_heap(v.begin(), v.end());
  cout << "\nv after make_heap():\n";
  std::copy(v.begin(), v.end(), output);

  std::sort_heap(v.begin(), v.end());
  cout << "\nv after sort_heap():\n";
  std::copy(v.begin(), v.end(), output);

  // Perform heapsort with push_heap and pop_heap
  cout << "a: ";
  std::copy(a, a + SIZE, output);

  for (i = 0; i < SIZE; ++i) {
    v2.push_back(a[i]);
    std::push_heap(v2.begin(), v2.end());

    cout << "\nv2 after push_heap)a[" << i << "]): ";
    std::copy(v2.begin(), v2.end(), output);
  }

  for (i = 0; i < v2.size(); ++i) {
    cout << "\nv2 after " << v2[0] << " popped from heap\n";
    std::pop_heap(v2.begin(), v2.end() - i);
    std::copy(v2.begin(), v2.end(), output);
  }

  cout << endl;
  
  return 0;
}
