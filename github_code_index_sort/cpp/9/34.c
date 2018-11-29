/***********************
Antonio Gonzalez csc330
File: selection.cpp
Problem: A vector of size n (specified by the user) needs
to be sorted using a selection sort algorithm.
100% complete
data structure: vector
************************/

#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;

/****** selectionSort() ************
Receives a vector as input and sorts it using
the selection sort algorithm.
Time complexity: O(n^2)
storage complexity: O(1)
**********************************/
void selectionSort( vector<int> &v )
{
  int temp;
  for( int i = 0; i < (v.size() - 1) ; i++ ){
      for( int j = i + 1; j < v.size(); j++){
	  if( v[i] > v[j] ){
   	      temp = v[i];
	      v[i] = v[j];
	      v[j] = temp;
	  }
      }
  }
}

/************* main() ******
Creates a vector with randomly generated numbers and calls
selectionSort() to sort the vector.
time complexity: O(n)
storage complexity: O(1)
**************************/
int main()
{
  int n;  
  vector<int> v;
  cin >> n;

  for( int i = 0; i < n ; i++ )
    v.push_back( (rand() % 1000000) );

  selectionSort(v);

  for( int i = 0; i < n ; i++ )
    cout << v[i] << endl;

  return 0;
}
