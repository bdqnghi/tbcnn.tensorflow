
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "heap_helper.cc" 
using namespace std;


int partition(vector<int>& A, int p, int r) {
  int i = p-1;
  for ( int j=p; j<=r-1; ++j) {
    if( A[j] <= A[r] ) {
      ++i;
      swap(A[i],A[j]);
    }
  }
  swap(A[i+1],A[r]);
  return i+1;
}


void quicksort(vector<int>& A,int p, int r) {
  if ( p<r ) {
    int q = partition(A,p,r);
    quicksort(A,p,q-1);
    quicksort(A,q+1,r);
  }
}


void quicksort(vector<int>& A) {
  quicksort(A,0,A.size()-1);
}


int randomized_partition(vector<int>& A,int p, int r) {
  int i = p + rand()%(r-p+1);
  swap(A[i],A[r]);
  return partition(A,p,r);
}


void randomized_quicksort(vector<int>& A,int p, int r) {
  if ( p<r ) {
    int q = randomized_partition(A,p,r);
    randomized_quicksort(A,p,q-1);
    randomized_quicksort(A,q+1,r);
  }
}


void randomized_quicksort(vector<int>& A) {
  randomized_quicksort(A,0,A.size()-1);
}


int main() {
  
  srand(time(NULL));
  vector<int> vec;
  for ( int i=0; i<10; ++i ) {
    vec.push_back(i+1);
  }
  shuffle(vec);
  vector<int> copy = vec;

  
  cout<<"---Original---"<<endl;
  print_vec(vec);

  
  cout<<"---Quicksort---"<<endl;
  quicksort(vec);
  print_vec(vec);

  
  cout<<"---Randomized Quicksort---"<<endl;
  randomized_quicksort(vec);
  print_vec(vec);

  return 0;
}
