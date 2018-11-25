 

 #include "bubblesort.h"
 #include <iostream>
 #include <ctime>
 #include <ratio>
 #include <chrono>

 using namespace std;


bubblesort :: bubblesort(int *A,int size)
{
  r_array= new int [size];
  temp = new int [size];
  
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


void bubblesort :: calcualte_timespan_inbubble_sort(void)
{
  
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
  
  chrono::high_resolution_clock::time_point t2=chrono::high_resolution_clock::now();
  chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
  
  time_elapsed=time_span.count();
  
}


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

int bubblesort :: size_of_array(void)
{
  return length;
}


int* bubblesort :: sorted_array(void)
{
  return s_array;
}


int* bubblesort :: raw_array(void)
{
  return r_array;
}


long long bubblesort :: number_of_operation(void)
{
  return no_operation;
}


double bubblesort :: time_taken(void)
{
  return time_elapsed;
}


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
