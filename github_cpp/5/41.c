
#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;


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
