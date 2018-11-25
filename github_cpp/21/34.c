

#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;


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
