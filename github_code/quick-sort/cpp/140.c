/*
   Author : Rick Liu
    Date  : 20150207
   Source : ItA P171
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "heap_helper.cc" // print_vec(...)
using namespace std;

// partition
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

// quicksort
void quicksort(vector<int>& A,int p, int r) {
  if ( p<r ) {
    int q = partition(A,p,r);
    quicksort(A,p,q-1);
    quicksort(A,q+1,r);
  }
}

// quicksort
void quicksort(vector<int>& A) {
  quicksort(A,0,A.size()-1);
}

// randomized partition
int randomized_partition(vector<int>& A,int p, int r) {
  int i = p + rand()%(r-p+1);
  swap(A[i],A[r]);
  return partition(A,p,r);
}

// randomized quicksort
void randomized_quicksort(vector<int>& A,int p, int r) {
  if ( p<r ) {
    int q = randomized_partition(A,p,r);
    randomized_quicksort(A,p,q-1);
    randomized_quicksort(A,q+1,r);
  }
}

// randomized quicksort
void randomized_quicksort(vector<int>& A) {
  randomized_quicksort(A,0,A.size()-1);
}


int main() {
  // initialize and shuffle
  srand(time(NULL));
  vector<int> vec;
  for ( int i=0; i<10; ++i ) {
    vec.push_back(i+1);
  }
  shuffle(vec);
  vector<int> copy = vec;

  // print result before heapify
  cout<<"---Original---"<<endl;
  print_vec(vec);

  // quicksort and print result
  cout<<"---Quicksort---"<<endl;
  quicksort(vec);
  print_vec(vec);

  // randomized quicksort and print result
  cout<<"---Randomized Quicksort---"<<endl;
  randomized_quicksort(vec);
  print_vec(vec);

  return 0;
}
