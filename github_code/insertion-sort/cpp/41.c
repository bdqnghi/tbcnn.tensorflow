/************************
Antonio Gonzalez
csc330
file: insertion.cpp
Problem: We need to create a vector filled with randomly generated
numbers and get it sorted using an insertion sort algorithm.
100% complete
data structure: vector
**********************/
#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;

/****** insertionSort() ************
Receives a vector as input and sorts it using
the insertion sort algorithm.
Time complexity: O(n^2)
storage complexity: O(1)
**********************************/
void insertionSort( vector<int> &v )
{
  int temp;
  int n = v.size();
  int elem;
  int j;
  for( int i = 1; i < n ; i++ ){
      for( elem = v[i], j = i - 1; j >= 0 && elem < v[j]; j--){
	  v[j+1] = v[j];
      }
      v[j+1] = elem;
  }
}


/******* main *******
Fills the vector and calls insertionSort()
Time complexity: O(n)
Storage complexity: O(1)
******************/
int main()
{
  int n;  
  vector<int> v;
  cin >> n;

  for( int i = 0; i < n ; i++ )
      v.push_back( (rand() % 1000000) );

  insertionSort(v);

  for( int i = 0; i < n ; i++ )
      cout << v[i] << endl;

  return 0;
}
