

#include "selectionSort.h"
#include <iostream>
using namespace std;


void SelectionSort::recursiveSort(int a[], const int size){
  int input;
  bool valid = false;
  while (!valid){ 
    cout << "Press 1 for ascending, 2 for descending: " << endl;
    cin >> input;
    switch (input){
    case 1:
      valid = true;
      recursiveSortAscending(a,size,0);
      break;
    case 2:
      valid = true;
      recursiveSortDescending(a,size,0);
      break;
    default:
      cout << "Invalid input." << endl;
      break;
    }
  }

}

void SelectionSort::recursiveSortAscending(int a[], const int size, int place){
  int smallest = place;
  for (int j = place + 1; j < size; j++){
    if (a[j] < a[smallest]){
      smallest = j;
    }
  }
  swap(&a[place], &a[smallest]);
  if (place < (size-1)){
    place++;
    recursiveSortAscending(a,size,place);
  }
}


void SelectionSort::recursiveSortDescending(int a[], const int size, int place){
  int largest = place;
  for (int j = place + 1; j < size; j++){
    if (a[j] > a[largest]){
      largest = j;
    }
  }
  swap(&a[place], &a[largest]);
  if (place < (size-1)){
    place++;
    recursiveSortDescending(a,size,place);
  }
}


void SelectionSort::iterativeSort(int a[], const int size){
  int input;
  bool valid = false;
  while (!valid){
    cout << "Press 1 for ascending, 2 for descending: " << endl;
    cin >> input;
    switch (input){
    case 1:
      valid = true;
      iterativeSortAscending(a, size);
      break;
    case 2:
      valid = true;
      iterativeSortDescending(a, size);
      break;
    default:
      cout << "Invalid input." << endl;
      break;
  }
  }
}


void SelectionSort::iterativeSortAscending(int a[], const int size){
  int smallest;
  for (int i = 0; i < size - 1; i++){
    smallest = i;
    for (int j = i + 1; j < size; j++){
      if (a[j] < a[smallest]){
	smallest = j;
      }
    }
    swap(&a[i], &a[smallest]);
  }
}


void SelectionSort::iterativeSortDescending(int a[], const int size){
  int largest;
  for (int i = 0; i < size - 1; i++){
    largest = i;
    for (int j = i + 1; j < size; j++){
      if (a[j] > a[largest]){
        largest = j;
      }
    }
    swap(&a[i], &a[largest]);
  }

}


void SelectionSort::recursiveSort(vector<int> &a, const int size){
  int input;
  bool valid = false;
  while (!valid){
    cout << "Press 1 for ascending, 2 for descending: " << endl;
    cin >> input;
    switch (input){
    case 1:
      valid = true;
      recursiveSortAscending(a,size,0);
      break;
    case 2:
      valid = true;
      recursiveSortDescending(a,size,0);
      break;
    default:
      cout << "Invalid input." << endl;
      break;
    }
  }
}


void SelectionSort::recursiveSortAscending(vector<int> &a, const int size, int place){
  int smallest = place;
  for (int j = place + 1; j < size; j++){
    if (a[j] < a[smallest]){
      smallest = j;
    }
  }
  swap(&a[place], &a[smallest]);
  if (place < (size-1)){
    place++;
    recursiveSortAscending(a,size,place);
  }
}


void SelectionSort::recursiveSortDescending(vector<int> &a, const int size, int place){
  int largest = place;
  for (int j = place + 1; j < size; j++){
    if (a[j] > a[largest]){
      largest = j;
    }
  }
  swap(&a[place], &a[largest]);
  if (place < (size-1)){
    place++;
    recursiveSortDescending(a,size,place);
  }
}


void SelectionSort::iterativeSort(vector<int> &a, const int size){
  int input;
  bool valid = false;
  while (!valid){
    cout << "Press 1 for ascending, 2 for descending: " << endl;
    cin >> input;
    switch (input){
    case 1:
      valid = true;
      iterativeSortAscending(a, size);
      break;
    case 2:
      valid = true;
      iterativeSortDescending(a, size);
      break;
    default:
      cout << "Invalid input." << endl;
      break;
    }
  }
}


void SelectionSort::iterativeSortAscending(vector<int> &a, const int size){
  int smallest;
  for (int i = 0; i < size - 1; i++){
    smallest = i;
    for (int j = i + 1; j < size; j++){
      if (a[j] < a[smallest]){
        smallest = j;
      }
    }
    swap(&a[i], &a[smallest]);
  }
}


void SelectionSort::iterativeSortDescending(vector<int> &a, const int size){
  int largest;
  for (int i = 0; i < size - 1; i++){
    largest = i;
    for (int j = i + 1; j < size; j++){
      if (a[j] > a[largest]){
        largest = j;
      }
    }
    swap(&a[i], &a[largest]);
  }
}


void SelectionSort::swap(int * const a1, int * const a2){
  int holder = *a1;
  *a1 = *a2;
  *a2 = holder;
}
