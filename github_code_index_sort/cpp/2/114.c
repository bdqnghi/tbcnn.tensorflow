/***********************************************************************
   PROGRAM:    CSCI 241 Assignment 8 - mergesort.h
   PROGRAMMER: Kevin Kang
   LOGON ID:   z1837081
   SECTION:    4
   TA: Abdul   Subhan Moin Syed
   DUE DATE:   Wednesday, 11/29/2017 by 11:59 pm

   FUNCTION:   header file for mergesort, contains function to implement
               a merge sort

************************************************************************/
#ifndef MERGESORT_H
#define MERGESORT_H

//********************************************************************
// merge sort function prototypes
//********************************************************************
template <class T>
void mergeSort(vector<T>& set, bool (*compare)(const T&, const T&));

template <class T>
void mergeSort(vector<T>& set, int low, int high, bool (*compare)(const T&, const T&));

template <class T>
void merge(vector<T>& set, int low, int mid, int high, bool (*compare)(const T&, const T&));

//********************************************************************
// mergesort function definition
//********************************************************************

//mergeSort - initial calling function
template <class T>
void mergeSort(vector<T>& set, bool (*compare)(const T&, const T&)) {
  mergeSort(set, 0, set.size()-1, compare);
}

//mergeSort - recursive function for sorting
template <class T>
void mergeSort(vector<T>& set, int low, int high, bool (*compare)(const T&, const T&)) {
  int mid;
   
  if (low < high) {
    mid = (low + high) / 2;
      
    // Divide and conquer
    mergeSort(set, low, mid, compare);
    mergeSort(set, mid+1, high, compare);
      
    // Combine
    merge(set, low, mid, high, compare);
  }
}

//merge - main function that does the bulk of the sorting
template <class T>
void merge(vector<T>& set, int low, int mid, int high, bool (*compare)(const T&, const T&)){
  // Create temporary vector to hold merged subvectors
  vector<T> temp(high - low + 1);

  int i = low;      // Subscript for start of left sorted subvector
  int j = mid+1;    // Subscript for start of right sorted subvector
  int k = 0;        // Subscript for start of merged vector

  // While not at the end of either subvector
  while (i <= mid && j <= high) {
    if (compare(set[j], set[i])) {
      temp[k] = set[j];
      j++; 
      k++;
    }
    else {
      temp[k] = set[i];
      i++;
      k++;
    }
  }

  // Copy over any remaining elements of left subvector
  while (i <= mid) {
    temp[k] = set[i];
    i++;
    k++; 
  }

  // Copy over any remaining elements of right subvector
  while (j <= high) {
    temp[k] = set[j];
    j++;
    k++;  
  }

  // Copy merged elements back into original vector
  for (i = 0, j = low; j <= high; i++, j++)
    set[j] = temp[i];
}
#endif
