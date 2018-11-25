

#include <iostream>
#include <vector>
#include "cstdlib"
using namespace std;


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


int main()
{
  int n;  
  vector<int> v;
  cin >> n;    

  for( int i = 0; i < n ; i++ )
    v.push_back( (rand() % 1000000) );

  bubbleSort(v);

  for( int i = 0; i < n ; i++ )
    cout << v[i] << endl;

  return 0;
}
