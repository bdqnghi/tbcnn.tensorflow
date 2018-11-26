#include <ctime>
#include <iostream>
using namespace std;

/* Bubble Sort */
void bubble_sort (int array[], int size){
  for (int i = 0; i < size; i++){
    bool didSwap=false;
      for (int j = 0; j < size; j++){
        if (array[j] > array[j + 1]){
          didSwap=true;
          int temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
        }
      }
    if(!didSwap) break;
  }
}

/* Shaker Sort */
void shaker_sort(int array[], int size) {
    for (int i = 0; i < size/2; i++) {
        bool didSwap = false;
        for (int j = i; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                didSwap = true;
            }
        }
        for (int j = size - 2 - i; j > i; j--) {
            if (array[j] < array[j-1]) {
                int tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
                didSwap = true;
            }
        }
        if(!didSwap) break;
    }
}

/* Shell Sort Version 1
	Gap 1/2 of array size */
void shell_sort1(int array[], int size) {
    int gap = size/2;
    while (gap > 0) {
        for (int i = 0; i < size - gap; i++) {
            int j = i + gap;
            int tmp = array[j];
            while (j >= gap && tmp < array[j - gap]) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = tmp;
        }
        if (gap == 2) {
            gap = 1;
        } else {
            gap /= 2;
        }
    }
}

/* Shell Sort Version 2
	Gap 1/10 array size */
void shell_sort2(int array[], int size) {
    int gap = size / 10;
    while (gap > 0) {
        for (int i = 0; i < size - gap; i++) {
            int j = i + gap;
            int tmp = array[j];
            while (j >= gap && tmp < array[j - gap]) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = tmp;
        }
        if (gap == 2) {
            gap = 1;
        } else {
            gap /= 10;
        }
    }
}

/* 	Array fill function */
int fill(int *array, int size){
  srand(time(NULL));
  for(int i=0; i<size; i++){
        array[i] = (rand()%1000000); // limit random numbers to 0 MIN - 1,000,000 MAX
  }
  return *array;
}

/* Main Function */
int main(){
/* 10 of each of the array sizes */
  int array[500],array2[500],array3[500],array4[500],array5[500],
  array6[500],array7[500],array8[500],array9[500],array0[500];                           		//500 element array
  int sarray[1000],sarray2[1000],sarray3[1000],sarray4[1000],sarray5[1000],
  sarray6[1000],sarray7[1000],sarray8[1000],sarray9[1000],sarray0[1000];                        //1000 element array
  int marray[2500],marray2[2500],marray3[2500],marray4[2500],marray5[2500],
  marray6[2500],marray7[2500],marray8[2500],marray9[2500],marray0[2500];                        //2500 element array
  int larray[5000],larray2[5000],larray3[5000],larray4[5000],larray5[5000],
  larray6[5000],larray7[5000],larray8[5000],larray9[5000],larray0[5000];                        //5000 element array



  int n = sizeof(array)/sizeof(array[0]);   	//number of elements in 500 element array
  int o = sizeof(sarray)/sizeof(sarray[0]);   	//number of elements in 1000 element array
  int p = sizeof(marray)/sizeof(marray[0]);   	//number of elements in 2500 element array
  int q = sizeof(larray)/sizeof(larray[0]);   	//number of elements in 5000 element array

  clock_t t1,t2;                            	//clock variables to measure execution time
  float diff;
  float time;
  float c;
  float avg;

/* Bubble Sort
	Fill, sort and measure execution time
	and display sorting time */

/* Fill the arrays */
  fill(array, n);  fill(array2, n);  fill(array3, n);  fill(array4, n);  fill(array5, n);
  fill(array6, n);  fill(array7, n);  fill(array8, n);  fill(array9, n);  fill(array0, n);
  fill(sarray, o);  fill(sarray2, o);  fill(sarray3, o);  fill(sarray4, o);  fill(sarray5, o);
  fill(sarray6, o);  fill(sarray7, o);  fill(sarray8, o);  fill(sarray9, o);  fill(sarray0, o);
  fill(marray, p);  fill(marray2, p);  fill(marray3, p);  fill(marray4, p);  fill(marray5, p);
  fill(marray6, p);  fill(marray7, p);  fill(marray8, p);  fill(marray9, p);  fill(marray0, p);
  fill(larray, q);  fill(larray2, q);  fill(larray3, q);  fill(larray4, q);  fill(larray5, q);
  fill(larray6, q);  fill(larray7, q);  fill(larray8, q);  fill(larray9, q);  fill(larray0, q);


  printf("\nBubble sort on 500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  bubble_sort (array, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array2, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array3, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array4, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array5, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array6, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array7, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array8, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array9, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (array0, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nBubble sort average sort time for 500 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");

  printf("\nBubble sort on 1000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  bubble_sort (sarray, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray2, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray3, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray4, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray5, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray6, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray7, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray8, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray9, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (sarray0, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nBubble sort average sort time for 1000 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nBubble sort on 2500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  bubble_sort (marray, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray2, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray3, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray4, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray5, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray6, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray7, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray8, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray9, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (marray0, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nBubble sort average sort time for 2500 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nBubble sort on 5000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  bubble_sort (larray, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray2, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray3, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray4, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray5, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray6, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray7, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray8, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray9, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  bubble_sort (larray0, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nBubble sort average sort time for 5000 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");
  printf("\n-----------------------------------------------------------------------\n");


/* Shaker Sort
	Fill, sort and measure execution time
	and display sorting time */

/* Fill the arrays */
  fill(array, n);  fill(array2, n);  fill(array3, n);  fill(array4, n);  fill(array5, n);
  fill(array6, n);  fill(array7, n);  fill(array8, n);  fill(array9, n);  fill(array0, n);
  fill(sarray, o);  fill(sarray2, o);  fill(sarray3, o);  fill(sarray4, o);  fill(sarray5, o);
  fill(sarray6, o);  fill(sarray7, o);  fill(sarray8, o);  fill(sarray9, o);  fill(sarray0, o);
  fill(marray, p);  fill(marray2, p);  fill(marray3, p);  fill(marray4, p);  fill(marray5, p);
  fill(marray6, p);  fill(marray7, p);  fill(marray8, p);  fill(marray9, p);  fill(marray0, p);
  fill(larray, q);  fill(larray2, q);  fill(larray3, q);  fill(larray4, q);  fill(larray5, q);
  fill(larray6, q);  fill(larray7, q);  fill(larray8, q);  fill(larray9, q);  fill(larray0, q);


  printf("\nShaker sort on 500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shaker_sort (array, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array2, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array3, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array4, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array5, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array6, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array7, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array8, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array9, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (array0, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShaker sort average sort time for 500 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShaker sort on 1000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shaker_sort (sarray, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray2, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray3, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray4, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray5, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray6, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray7, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray8, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray9, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (sarray0, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShaker sort average sort time for 1000 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShaker sort on 2500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shaker_sort (marray, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray2, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray3, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray4, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray5, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray6, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray7, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray8, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray9, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (marray0, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShaker sort average sort time for 2500 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShaker sort on 5000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shaker_sort (larray, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray2, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray3, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray4, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray5, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray6, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray7, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray8, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray9, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shaker_sort (larray0, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShaker sort average sort time for 5000 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");
  printf("\n-----------------------------------------------------------------------\n");


/* Shell Sort 1
FIll, print, sort and measure execution time, print sorted
and display sorting time */
  printf("\nShell sort 1 using 1/2 array size gap:\n");

/* Fill the arrays */
  fill(array, n);  fill(array2, n);  fill(array3, n);  fill(array4, n);  fill(array5, n);
  fill(array6, n);  fill(array7, n);  fill(array8, n);  fill(array9, n);  fill(array0, n);
  fill(sarray, o);  fill(sarray2, o);  fill(sarray3, o);  fill(sarray4, o);  fill(sarray5, o);
  fill(sarray6, o);  fill(sarray7, o);  fill(sarray8, o);  fill(sarray9, o);  fill(sarray0, o);
  fill(marray, p);  fill(marray2, p);  fill(marray3, p);  fill(marray4, p);  fill(marray5, p);
  fill(marray6, p);  fill(marray7, p);  fill(marray8, p);  fill(marray9, p);  fill(marray0, p);
  fill(larray, q);  fill(larray2, q);  fill(larray3, q);  fill(larray4, q);  fill(larray5, q);
  fill(larray6, q);  fill(larray7, q);  fill(larray8, q);  fill(larray9, q);  fill(larray0, q);


  printf("\nShell sort on 500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort1 (array, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array2, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array3, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array4, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array5, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array6, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array7, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array8, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array9, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (array0, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 500 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 1000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort1 (sarray, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray2, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray3, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray4, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray5, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray6, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray7, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray8, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray9, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (sarray0, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 1000 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 2500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort1 (marray, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray2, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray3, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray4, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray5, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray6, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray7, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray8, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray9, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (marray0, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 2500 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 5000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort1 (larray, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray2, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray3, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray4, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray5, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray6, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray7, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray8, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray9, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort1 (larray0, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 5000 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");
  printf("\n-----------------------------------------------------------------------\n");

/* Shell Sort 2
FIll, print, sort and measure execution time, print sorted
and display sorting time */

/* Fill the arrays */
  fill(array, n);  fill(array2, n);  fill(array3, n);  fill(array4, n);  fill(array5, n);
  fill(array6, n);  fill(array7, n);  fill(array8, n);  fill(array9, n);  fill(array0, n);
  fill(sarray, o);  fill(sarray2, o);  fill(sarray3, o);  fill(sarray4, o);  fill(sarray5, o);
  fill(sarray6, o);  fill(sarray7, o);  fill(sarray8, o);  fill(sarray9, o);  fill(sarray0, o);
  fill(marray, p);  fill(marray2, p);  fill(marray3, p);  fill(marray4, p);  fill(marray5, p);
  fill(marray6, p);  fill(marray7, p);  fill(marray8, p);  fill(marray9, p);  fill(marray0, p);
  fill(larray, q);  fill(larray2, q);  fill(larray3, q);  fill(larray4, q);  fill(larray5, q);
  fill(larray6, q);  fill(larray7, q);  fill(larray8, q);  fill(larray9, q);  fill(larray0, q);


  printf("\nShell sort 2 using 1/10 array size gap:\n");
  printf("\nShell sort on 500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort2 (array, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array2, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array3, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array4, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array5, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array6, n);
  t2=clock();
  diff = t2-t1;;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array7, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array8, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array9, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (array0, n);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 500 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 1000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort2 (sarray, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray2, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray3, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray4, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray5, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray6, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray7, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray8, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray9, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (sarray0, o);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 1000 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 2500 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort2 (marray, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray2, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray3, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray4, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray5, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray6, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray7, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray8, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray9, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (marray0, p);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 2500 elements: %.10f seconds.\n", avg);

  printf("\n-----------------------------------------------------------------------\n");

  printf("\nShell sort on 5000 elements:\n");
  c=0;
  avg=0;

  t1=clock();
  shell_sort2 (larray, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray2, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray3, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray4, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray5, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray6, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray7, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray8, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray9, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  t1=clock();
  shell_sort2 (larray0, q);
  t2=clock();
  diff = t2-t1;
  time = diff / CLOCKS_PER_SEC;
  c += time;

  avg = c / 10;

  printf("\nShell sort average sort time for 5000 elements: %.10f seconds.\n", avg);
  printf("\n-----------------------------------------------------------------------\n");
  printf("\n-----------------------------------------------------------------------\n");

  return 0;
}
