 /*
  *
  * bubblesort.cpp
  *
  * This file has the definition of bubblesort.h
  *
  *
  * @Author:          Saujan Thapa
  * @Student number:  n9003096
  * @Unit:            CAB301
  * @version:         1.0
  */

 #include "bubblesort.h"
 #include <iostream>
 #include <ctime>
 #include <ratio>
 #include <chrono>

 using namespace std;

//constructor of class bubblesort
bubblesort :: bubblesort(int *A,int size)
{
  r_array= new int [size];
  temp = new int [size];
  //copying the value of A to r_array
  for (int i=0;i<size;i++)
  {
    r_array[i]=A[i];
    temp[i]=A[i];
  }
  s_array=A;
  length=size;
  is_correct=true;
  no_operation=0;
}

//this method calculates the time taken to sort the array using bubble sort
void bubblesort :: calcualte_timespan_inbubble_sort(void)
{
  //pulling the system time
  chrono::high_resolution_clock::time_point t1=chrono::high_resolution_clock::now();
  int temp=0;
  int count=length-1;
  bool sflag=true;
  while(sflag)
  {
    sflag=false;
    for(int index=0;index<count;index++)
    {
      if (s_array[index+1]<s_array[index])
      {
        temp=s_array[index];
        s_array[index]=s_array[index+1];
        s_array[index+1]=temp;
        sflag=true;
      }
    }
    count--;
  }
  //pulling the system time after the sorting is done
  chrono::high_resolution_clock::time_point t2=chrono::high_resolution_clock::now();
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
  //total time taken by bubblesort algorithm
  time_elapsed=time_span.count();
  //end
}

//this method calculates the no. of basic operation to sort the array using bubble sort
void bubblesort :: calculate_no_opration_inbubble_sort(void)
{
  int count=length-1;
  no_operation+=2;
  int swap=0;
  no_operation +=1;
  bool sflag=true;
  no_operation +=1;
  while(sflag)
  {
    no_operation +=1;
    sflag=false;
    no_operation +=1;
    for(int index=0;index<count;index++)
    {
      no_operation +=3;
      if (temp[index+1]<temp[index])
      {
        no_operation +=1;
        swap=temp[index];
        no_operation +=1;
        temp[index]=temp[index+1];
        no_operation +=1;
        temp[index+1]=swap;
        no_operation +=1;
        sflag=true;
        no_operation +=1;
      }
    }
    count--;
    no_operation +=2;
  }
}
//this method feeds the length of the array
int bubblesort :: size_of_array(void)
{
  return length;
}

// this method feeds the sorted non-decreasing array
int* bubblesort :: sorted_array(void)
{
  return s_array;
}

// this method feeds the original array
int* bubblesort :: raw_array(void)
{
  return r_array;
}

// this method feedbacks the number of basic operation
long long bubblesort :: number_of_operation(void)
{
  return no_operation;
}

//this method feeds the time taken by the method sort_the_array() for sorting the array
double bubblesort :: time_taken(void)
{
  return time_elapsed;
}

//this method tests if the elements are sorted in the array
bool bubblesort :: is_algorithm_correct(void)
{
  for (int index=0;index<length-1;index++)
  {
    is_correct=is_correct &((s_array[index]<=s_array[index+1])?true:false);
  }
  return is_correct;
}

bubblesort :: ~bubblesort()
{

}
