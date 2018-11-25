
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "get_input.h"






template <typename InputIterator, typename OutputIterator>
void mergesort(InputIterator start, InputIterator end, OutputIterator output) {
  int size = end - start;

  if (size == 1) {
    
    *output = *start;
    return;
  }

  
  int split = size / 2;

  
  mergesort(start, start + split, output);
  
  mergesort(start + split, end, output + split);

  
  inplace_merge (output, output+split, output+size);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Need 1 input file name";
  }
  
  std::vector<int> input = getInput(argv[1]);
  std::vector<int> output(input.size());

  mergesort(input.begin(), input.end(), output.begin());

  for (auto number : output) {
    std::cout << number << "\n";
  }
  return 0;
}
