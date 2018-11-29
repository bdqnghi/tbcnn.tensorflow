// cmdint.cpp - command interpreter program to test Binary Heap module

#include "binheap.h"
#include <iostream>
#include <string>
#include <time.h>  // For use in timing heap-sort in Assignment # 5

using namespace std ;

int main()
{
  string comment ;
  char choice ;
  KeyType key ;
	int size;
  BinHeap H ;            // This actually constructs the heap
  int i, j, n ;
  KeyType origA[1005] ;  // May be useful in timing heap-sort

  bool interact = false;
  bool printExtract = true ;

  if ( interact )  cout << "Choose: (c)onstruct, (i)nsert, (m)inimum, "
			<< "(e)xtractmin, decrease (k)ey, S(how), P(rint), (s)earch, "
			<< "+/- turns extract print on/off, or # (to comment): " ;
  cin >> choice ;
  while ( !cin.eof() ) {
    switch ( choice ) {
    case 'c':
      // This has already been done above
      // Doing it within the switch causes problems
      break ;
    case 'i':
      if ( interact ) cout << "Enter key value to insert: " ;
      cin >> key ;
      H.insert( key ) ;
      break ;
    case 'm':
      key = H.minimum() ;
      cout << "Minimum = " << key << "\n" ;
      break ;
    case 'e':
      if ( H.empty() ) {
	cout << "Heap empty, can't extract minimum.\n\n" ;
      } else {
	key = H.extractMin( ) ;
	if ( printExtract )
	  cout << "Minimum extracted = " << key << "\n" ;
      }
      break ;
    case 'k':
      if ( interact ) cout << "Enter index & new key to decrease: " ;
      cin >> i >> key ;
      H.decreaseKey( i, key ) ;
      break ;
    case 'S':
      cout << "Structure of heap (rotated 90 degrees to left):\n\n" ;
      H.ShowHeap( 1, 0 ) ;
      cout << "\n\n" ;
      break ;
    case 'P':
      H.PrintHeap( ) ;
      break ;
    case '+':
      printExtract = true ;
      break ;
    case '-':
      printExtract = false ;
      break ;
    case '#':
      cout << '#' ; getline(cin, comment) ;
      cout << comment << "\n\n" ;
      break ;
    case 's':
      if ( interact ) cout << "Enter key value to search for: " ;
      cin >> key ;
      i = H.search( key ) ;
      cout << "key, " << key << ", found at index " << i << "\n" ;
      break ;
     case 'T':
      cout<<"This will time the heapSort for array of 1000 elements 10000 times" <<endl;
      H.minHeapSort();
	break;
    default:
      cout << "Illegal choice: " << choice << endl ;
    }
    if ( interact )  cout << "Choose: (c)onstruct, (i)nsert, (m)inimum, "
			  << "(e)xtractmin, decrease (k)ey, S(how), P(rint), (s)earch, "
			  << "+/- turns extract print on/off, or # (to comment): " ;
    cin >> choice ;
  }
  cout << endl ;


  return 0;
}
