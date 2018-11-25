#include "q6solution.hpp"



template<class T>
void merge_sort(T a[], int low, int high) {
  if (high - low < 1)               
    return;
  else {
    int mid = (low + high)/2;       
    merge_sort(a, low, mid);        
    merge_sort(a, mid+1, high);     
    merge(a, low,mid, mid+1,high);  
  }
}


template<class T>
void merge_sort(T a[], int length) {
  merge_sort(a, 0, length-1);
}





int main() {
  try {

    
    std::cout << "\nTesting selection sort" << std::endl;
    int test_selection_sort[10] = {1,2,3,4,5,6,7,8,9,10};
    for (int i=0; i<5; i++) {
      shuffle(test_selection_sort,10);
      LN<int>* t = build(test_selection_sort, 10, 0);
      print("\n  List before sort: ", t, false);
      selection_sort(t);
      print("  List after  sort: ", t, true);
    }



    
    std::cout << "\n\nTesting merge by itself" << std::endl;
    int test_merge[10] = {1,2,5,8,10,   3,4,6,7,9};
    print("\n  Array before merge: ", test_merge, 10, false);
    merge(test_merge,0,4, 5,9);
    print("  Array after  merge: ", test_merge, 10, true);

    std::cout << "\n\nTesting merge in merge sort" << std::endl;
    int test_merge_sort[10] = {1,2,3,4,5,6,7,8,9,10};
    for (int i=0; i<5; i++) {
      shuffle(test_merge_sort, 3);
      print("\n  Array before sort: ", test_merge_sort, 10, false);
      merge_sort(test_merge_sort, 10);
      print("  Array after  sort: ", test_merge_sort, 10, true);
    }



    
    std::cout << "\n\nTesting radix sort" << std::endl;
    int test_radix_sort [30];

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,1000000);   

    for (int i=0; i<30; ++i)
      test_radix_sort[i] = distribution(generator);

    for (int i=0; i<5; i++) {
      shuffle(test_radix_sort, 30);
      print("\n  Array before sort: ", test_radix_sort, 30, false);
      radix_sort(test_radix_sort, 30);
      print("  Array after  sort: ", test_radix_sort, 30, true);
    }



    
    std::cout << "\nTesting partition performance using last: "
              << test_partition(100,100000,last) << std::endl;
    std::cout << "\nTesting partition performance using median_3: "
              << test_partition(100,100000,median_3) << std::endl;

  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}




















