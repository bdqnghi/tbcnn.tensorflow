


#include "stdafx.h"
#include "iostream"
#include "conio.h"
#include <iomanip>
#include <stack>
#include <string.h>
#include <stdlib.h>

using namespace std;

template<class T>
void quickSortR(T* a, long N);

int _tmain(int argc, _TCHAR* argv[])
{
	int *arr=new int[15]; 
	for (int i=0; i<15; i++) {
		arr[i]=rand()%100;
	}
	for (int i=0; i<15; i++) {
		cout<<arr[i]<<endl;
	}
	cout<<"quicksort"<<endl;
	quickSortR(arr,15);
	for (int i=0; i<15; i++) {
		cout<<arr[i]<<endl;
	}
	setlocale(LC_ALL, "Russian");
	_getch();
	 return 0;
}

template<class T>
void quickSortR(T* a, long N) {


  long i = 0, j = N-1; 		
  T temp, p;

  p = a[ N>>1 ];		

  
  do {
    while ( a[i] < p ) i++;
    while ( a[j] > p ) j--;

    if (i <= j) {
      temp = a[i]; a[i] = a[j]; a[j] = temp;
      i++; j--;
    }
  } while ( i<j );


  
  if ( j > 0 ) quickSortR(a, j);
  if ( N > i ) quickSortR(a+i, N-i);
}

