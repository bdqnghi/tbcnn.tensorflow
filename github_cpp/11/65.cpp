#ifndef BINHEAPH
#define BINHEAPH



#include <iostream>

using namespace std ;

typedef int KeyType ;   

class BinHeap {
  
  void minHeapify( int i ) ;
  void buildMinHeap( ) ;     
	void exchange(int i, int j);
 public:
  
  KeyType* A ;  
  int heapSize ; 
  int length ;   

  
  BinHeap() ;
  BinHeap( int arrayLength ) ;
  ~BinHeap() ;

  
  void insert( KeyType key ) ;
  KeyType minimum( ) ;
  KeyType extractMin( ) ;
  void decreaseKey( int i, KeyType key ) ;

  
  inline bool empty() { return heapSize == 0 ; } 
  void ShowHeap( int i, int depth ) ;  
  void PrintHeap( ) ;                  
  int search( KeyType key ) ;          

  void minHeapSort( ) ;  
} ;

#endif
