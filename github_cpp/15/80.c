


#include <iostream>
#include <cstdlib> 
#include <pthread.h>
#include <sys/wait.h> 
#include <sys/time.h> 
using namespace std;


#define GET_TIME(now)\
{ struct timeval t; gettimeofday(&t, NULL);\
  now = t.tv_sec + t.tv_usec/1000000.0; }


int thread_count;
long** matrixA;
long** matrixB;
long** matrixC;
int l, m, n;
pthread_mutex_t mutex1;

void *MatrixMultiplication(void* rank); 


int main(int argc, char* argv[])
{
  long thread_id; 

  
  l = atoi(argv[1]);
  m = atoi(argv[2]);
  n = atoi(argv[3]);
  thread_count = atoi(argv[4]);
    cout << "L = " << l << " M = " << m << " N = " << n << " Number of threads: " << thread_count << endl << endl;
  
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

  
  for(int i = 0; i < l; i++)
    for(int j = 0; j < m; j++)
      matrixA[i][j] = (long)(i + j);


  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++)
      matrixB[i][j] = (long)(i + j + 1);


  for(int i = 0; i < l; i++)
    for(int j = 0; j < n; j++)
      matrixC[i][j] = (long)0;

  
  pthread_t myThreads[thread_count];
  
  pthread_mutex_init(&mutex1, NULL);

  
  double start, stop, total;

  
  GET_TIME(start);

  
  for(thread_id = 0; thread_id < thread_count; thread_id++){
    pthread_create(&myThreads[thread_id], NULL, MatrixMultiplication, (void*)thread_id);
  }

  
  for(thread_id = 0; thread_id < thread_count; thread_id++)
     pthread_join(myThreads[thread_id], NULL);

  
  GET_TIME(stop);
  
  total = stop - start;
  cout << "Total computation time: " << total << endl << endl;

  
  cout << "First 20 * First 10: " << endl;
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 10; j++){
      cout << matrixC[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  
  cout << "Last 20 * Last 10: " << endl;
  for(int i = l - 21; i < l - 1; i++){
    for(int j = n - 11; j < n - 1; j++){
      cout << matrixC[i][j] << " ";
    }
    cout << endl;
  }


  return 0;
}


void *MatrixMultiplication(void* args)
{

  int thread_id = (long)args; 
  
  int quotient = l / thread_count;
  int remainder = l % thread_count;

  
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

  
  cout << "Thread " << thread_id << ": start row: " << my_first_i << " end row: " << my_last_i << endl;

  
  for(int i = my_first_i; i <= my_last_i; i++){
    for(int j = 0; j < n; j++){
      
      long sum = 0;
      for(int k = 0; k < m; k++){
        
        sum += matrixA[i][k] * matrixB[k][j];
      }
      
      pthread_mutex_lock(&mutex1);
      matrixC[i][j] = sum;
      pthread_mutex_unlock(&mutex1);
    }
  }


  return NULL;
}