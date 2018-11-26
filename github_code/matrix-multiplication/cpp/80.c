/*  Author: Brandon Lundberg
    File Name: matrix.cpp
    Purpose: Use multi-threading to do matrix multiplication
    Date: 3 March 2016
*/

/* Global Documentation
   
   Compile and Run:
   ➜  g++ -o matrix matrix.cpp -lpthread
   ➜  ./matrix 1001 2000 3000 1
   
   Command line inputs:
   Input 1: Number of rows in Matrix A
   Input 2: Number of columns in Matrix A (also number of rows in Matrix B)
   Input 3: Number of columns in Matrix B
   Input 4: Number of threads to use in the program
   
*/
#include <iostream>
#include <cstdlib> //for atoi()
#include <pthread.h>
#include <sys/wait.h> //for wait()
#include <sys/time.h> //for macro GET_TIME(double)
using namespace std;


#define GET_TIME(now)\
{ struct timeval t; gettimeofday(&t, NULL);\
  now = t.tv_sec + t.tv_usec/1000000.0; }

//globals --accessible to all threads
int thread_count;
long** matrixA;
long** matrixB;
long** matrixC;
int l, m, n;
pthread_mutex_t mutex1;

void *MatrixMultiplication(void* rank); //prototype for a Thread function

///////////////////
int main(int argc, char* argv[])
{
  long thread_id; //long for type conversion [long<-->void*] for 64 bit system

  // Convert the command line inputs to integers
  l = atoi(argv[1]);
  m = atoi(argv[2]);
  n = atoi(argv[3]);
  thread_count = atoi(argv[4]);
    cout << "L = " << l << " M = " << m << " N = " << n << " Number of threads: " << thread_count << endl << endl;
  // Create 2D arrays
  matrixA = new long*[l];
  for(int i = 0; i < l; i++)
  {
    matrixA[i] = new long[m];
  }

  matrixB = new long*[m];
  for(int i = 0; i < m; i++)
  {
    matrixB[i] = new long[n];
  }

  matrixC = new long*[l];
  for(int i = 0; i < l; i++)
  {
    matrixC[i] = new long[n];
  }

  // Initialize arrays
  for(int i = 0; i < l; i++)
    for(int j = 0; j < m; j++)
      matrixA[i][j] = (long)(i + j);


  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++)
      matrixB[i][j] = (long)(i + j + 1);


  for(int i = 0; i < l; i++)
    for(int j = 0; j < n; j++)
      matrixC[i][j] = (long)0;

  // Define thread array with the specified number of threads from the command line
  pthread_t myThreads[thread_count];
  // Initialize the lock used on matrix C (writing to the 2D array)
  pthread_mutex_init(&mutex1, NULL);

  // variables for time checking
  double start, stop, total;

  // Start timer when threads are created and begin running
  GET_TIME(start);

  //creates a certain number of threads
  for(thread_id = 0; thread_id < thread_count; thread_id++){
    pthread_create(&myThreads[thread_id], NULL, MatrixMultiplication, (void*)thread_id);
  }

  //wait until all threads finish
  for(thread_id = 0; thread_id < thread_count; thread_id++)
     pthread_join(myThreads[thread_id], NULL);

  // Stop timer. All threads have finished computation at this point
  GET_TIME(stop);
  // Calculate and print execution time
  total = stop - start;
  cout << "Total computation time: " << total << endl << endl;

  // Print first results
  cout << "First 20 * First 10: " << endl;
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      cout << matrixC[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  // Print last results
  cout << "Last 20 * Last 10: " << endl;
  for(int i = l - 21; i < l - 1; i++){
    for(int j = n - 11; j < n - 1; j++){
      cout << matrixC[i][j] << " ";
    }
    cout << endl;
  }


  return 0;
}//main

//////////////////slave function
void *MatrixMultiplication(void* args)
{

  int thread_id = (long)args; //rank is void* type, so can cast to (long) type only;
  // Calculate quotient and remainder
  int quotient = l / thread_count;
  int remainder = l % thread_count;

  // Find indexes for rows to be calculated by this thread
  int my_count, my_first_i, my_last_i;
  if(thread_id < remainder){
    my_count = quotient + 1;
    my_first_i = thread_id * my_count;
  }
  else{
    my_count = quotient;
    my_first_i = thread_id * my_count + remainder;
  }
  my_last_i = my_first_i + my_count - 1;

  // Print this threads start and stop indexes
  cout << "Thread " << thread_id << ": start row: " << my_first_i << " end row: " << my_last_i << endl;

  // Calculate matrix multiplication value for each designated location
  for(int i = my_first_i; i <= my_last_i; i++){
    for(int j = 0; j < n; j++){
      // Initialize sum
      long sum = 0;
      for(int k = 0; k < m; k++){
        // Update sum for each position
        sum += matrixA[i][k] * matrixB[k][j];
      }
      // Lock matrix C and write result for this location
      pthread_mutex_lock(&mutex1);
      matrixC[i][j] = sum;
      pthread_mutex_unlock(&mutex1);
    }
  }


  return NULL;
}//Hello