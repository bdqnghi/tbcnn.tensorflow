/*******************
Antonio Gonzalez csc330
file: bubble.cpp
This program creates a vector and fills it 
with randomly generated values according to the size
specified by the user. The vector is then sorted using
a bubble sort algorithm.
100% complete
data structure: vector
**************************/

#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;

/******* bubbleSort() ***********************
This function takes in a vector and sorts
it using a bubble sort algorithm.
time complexity: O(n^2)
storage complexity: O(1)
******************************/
void bubbleSort( vector<int> &v )
{
  int temp;
  int n = v.size();
  for( int i = n - 1; i > 0 ; i--){
    for( int j = 0; j < i; j++){
	  if( v[j] > v[j+1] ){
   	      temp = v[j];
	      v[j] = v[j+1];
	      v[j+1] = temp;
	  }
      }
  }
}

/******** main() **********
Creates a vector of size n ( specified by the user)
It then calls bubbleSort() to sort the vector
time complexity: O(n)
storage complexity: O(1)
 **********************/
int main()
{
  int n;  
  vector<int> v;
  cin >> n;    //prompt user for number of elements in the vector

  for( int i = 0; i < n ; i++ )
    v.push_back( (rand() % 1000000) );

  bubbleSort(v);

  for( int i = 0; i < n ; i++ )
    cout << v[i] << endl;

  return 0;
}
