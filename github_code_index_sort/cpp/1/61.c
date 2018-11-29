/*
Brian Faure
RUID:150003563
NetID:bdf39
Programming Methodology II
Homework #3
Problem #1
Insertion Sort
*/

/*
Main function as well as read_file function is the same as
Bubble.cpp, only difference is the Insertion_Sort function.
Insertion Sort implementation in textbook
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<int> read_file(std::string filename){
  std::vector<int> array;
  int temp;
  std::ifstream read(filename);
  while(read>>temp){
    array.push_back(temp);
  }
  return array;
}

void Insertion_Sort(std::vector<int> &input){
  int n = input.size();
  for(int unsorted=1; unsorted<n; unsorted++){
    int nextItem = input[unsorted];
    int loc = unsorted;
    while((loc>0) && (input[loc-1] > nextItem)){
      int temp = input[loc];
      input[loc] = input[loc-1];
      input[loc-1] = temp;
      loc--;
    }
  }
}

int main(){
  std::vector<int> data = read_file("test.txt");
  std::cout<<"\nOriginal Vector...\n";
  int size = data.size();
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\nSorted Vector...\n";
  Insertion_Sort(data);
  for(int i=0; i<size; i++){
    std::cout<<data[i]<<" ";
  }
  std::cout<<"\n\n";
}
