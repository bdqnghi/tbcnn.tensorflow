#ifndef SHELL_H
#define SHELL_H

#include<iostream>
#include<string>
#include<cmath>
#include <cstdlib>
#include "InsertionSort.cpp"
using namespace std;


namespace ShellSortNS{
  class ShellSort
  {
  public:
    static InsertionSortNS::LinkedList* sort(InsertionSortNS::LinkedList *inputList);
  private:
    static InsertionSortNS::LinkedList* insertionSort(InsertionSortNS::LinkedList *listToSort, int sorterSize);
    static InsertionSortNS::LinkedList* subList(InsertionSortNS::LinkedList *listToSort, int sorterSize, int start);
    static InsertionSortNS::LinkedList* columnSort(InsertionSortNS::LinkedList *listToSort, int sortSize, int start);
  };
}
#endif
