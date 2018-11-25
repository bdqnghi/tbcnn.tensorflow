


#include <vector>
#include <assert.h>
using namespace std;


int binarySearch(const int* array, const int len, const int query) {
  int lowerBound = 0;
  int upperBound = len;

  while(upperBound - lowerBound > 1) {
    int index = ((upperBound - lowerBound) / 2) + lowerBound;
    int value = array[index];
    if(value == query) return index;
    if(value > query) {
      upperBound = index;
    } else {
      lowerBound = index;
    }
  }
  return -1;
}


template<class T, class V>
int binarySearch(const T &container, const V query) {
  int lowerBound = 0;
  int upperBound = container.size();

  while(upperBound - lowerBound > 1) {
    int index = ((upperBound - lowerBound) / 2) + lowerBound;
    int value = container[index];
    if(value == query) return index;
    if(value > query) {
      upperBound = index;
    } else {
      lowerBound = index;
    }
  }
  return -1;
}

void binarySearchTest() {
  {
    int set[] = {1, 3, 4, 6, 8, 10};
    int len = 6;
    int query = 4;
    int pos = binarySearch(set, len, query);
    assert(pos == 2);
  }

  {
    int set[] = {1, 3, 5, 7, 9};
    int len = 5;
    int pos1 = binarySearch(set, len, 4);
    assert(pos1 == -1);

    int pos2 = binarySearch(set, len, 5);
    assert(pos2 == 2);
  }

  {
    
    static const int elems[] = {1,2,4,6,8,10};
    vector<int> vec (elems, elems + 6);

    int pos = binarySearch<vector<int>, int>(vec, 4);
    assert(pos == 2);
  }

  {
    
    static const int elems[] = {1,3,5,7,9};
    vector<int> vec (elems, elems + 5);

    int pos1 = binarySearch<vector<int>, int>(vec, 4);
    assert(pos1 == -1);

    int pos2 = binarySearch<vector<int>, int>(vec, 5);
    assert(pos2 == 2);
  }
}

int main() {
  binarySearchTest();
  return 0;
}

