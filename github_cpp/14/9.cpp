





#include <iostream>
#include <vector>
#include <algorithm> 
#include <iterator>  
#include <queue>     
#include "get_input.h"
using namespace std;


template <typename InputIterator, typename OutputIterator>
void radixSort(InputIterator start, InputIterator end, OutputIterator output) {
  const int BASE = 10; 
  std::queue<typename std::iterator_traits<OutputIterator>::value_type>
      bucket[BASE]; 

  unsigned size = end - start;
  
  typename std::iterator_traits<InputIterator>::value_type max =
      *std::max_element(start, end); 

  
  std::copy(start, end, output); 

  
  
  for (unsigned power = 1; max != 0;
       max /= BASE, power *=
                    BASE) { 
                            

    
    for (OutputIterator it = output; it != output + size; it++) {
      unsigned bucketNumber = (unsigned)((*it / power) % BASE);
      bucket[bucketNumber].push(*it); 
    }

    
    OutputIterator it = output;
    for (int i = 0; i < BASE; i++) {
      int bucketSize = bucket[i].size();
      for (int j = 0; j < bucketSize; j++) {
        *it = bucket[i].front();
        bucket[i].pop();
        it++;
      }
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Need 1 input file name";
  }
  
  std::vector<int> input = getInput(argv[1]);
  vector<unsigned> output(input.size());

  radixSort(input.begin(), input.end(), output.begin());

  
  
  for (unsigned it : output) {
    cout << it << endl;
  }

  return 0;
}
