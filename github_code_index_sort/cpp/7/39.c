/*
 Nga Yi Chan
 Assignment 7
 Professor Harden
 Mar 1 , 2017
 
 This program generate the gap sequence in 4 different ways and then sort it by 
 calling shellSort. It can show the sorted sequence.It will also display the 
 time used for further analysis.
 */

#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;
#include "FHvector.h"
#define ARRAY_SIZE 50000

template <typename Comparable>
void shellSort1( FHvector<Comparable> & a )
{
    int k, pos, arraySize, ONE;
    Comparable tmp;
    
    arraySize = a.size();
    for (ONE = arraySize/2;  ONE > 0;  ONE /= 2)
    {
        for(pos = ONE ; pos < arraySize; pos++ )
        {
            tmp = a[pos];
            for(k = pos; k >= ONE && tmp < a[k - ONE]; k -= ONE )
                a[k] = a[k - ONE];
            a[k] = tmp;
        }
    }
}

template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int gapArray[], int gapArraySize)
{
    int k, pos, arraySize, gap, gapArrayPos;
    Comparable tmp;
    
    arraySize = a.size();
    for (gapArrayPos = gapArraySize - 1; gapArrayPos >= 0; --gapArrayPos)
    {
        gap = gapArray[gapArrayPos];
        
        for (pos = gap; pos < arraySize; pos++)
        {
            tmp = a[pos];
            for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)
                a[k] = a[k - gap];
            a[k] = tmp;
        }
    }
}


int main(){
    
    FHvector<int> fhVectorOfInts1;
    FHvector<int> fhVectorOfInts2;
    FHvector<int> fhVectorOfInts3;
    FHvector<int> fhVectorOfInts4;
    
    int randomInt;
    for (int x = 0; x < ARRAY_SIZE; ++x)
    {
        randomInt = rand() % ARRAY_SIZE;
        fhVectorOfInts1.push_back(randomInt);
        fhVectorOfInts2.push_back(randomInt);
        fhVectorOfInts3.push_back(randomInt);
        fhVectorOfInts4.push_back(randomInt);
    }
    
    int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
        2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
        1048576 };
    int gapArraySize = 21;
    
    /*
    cout << "Explicit Gap Sequence: ";
    
    for (int x = 0; x < gapArraySize; x++){
        if( gapArray[x] > ARRAY_SIZE )
            break;
        cout << " " << gapArray[x] << ",";
    }
    cout <<"\n"<< endl;
     */
   
    
    int sedgewickGapArray[30];
    int sedgewickGapArraySize;
    
    for(int i = 0; i < 30; ++i)
    {
        int val;
        if(i%2 == 0)
            val = 9*pow(2, i) - 9*pow(2, i/2) + 1;
            else
                val = 8*pow(2, i) - 6*pow(2, (i+1)/2) + 1;
        
        if( val > ARRAY_SIZE )
            break;
        
        sedgewickGapArray[i] = val;
        sedgewickGapArraySize++;
    }
    

    cout << "Sedgewick Gap Sequence: ";
    
    for (int x = 0; x < sedgewickGapArraySize; ++x)
    {
        cout << " " << sedgewickGapArray[x] << ",";
    }
    cout <<"\n"<< endl;


    int myGapArray[30];
    int myGapArraySize;
    
    for(int i = 0; i < 30; ++i)
    {
        int val = pow(2, i) + 3 * i ;
        
        if( val > ARRAY_SIZE )
            break;
        
        myGapArray[i] = val;
        myGapArraySize++;
    }
    
    /*
     cout << "My Gap Sequence: ";
    
    for (int x = 0; x < myGapArraySize; ++x) {
        cout << " " << myGapArray[x] << ",";
    }
    cout <<"\n"<< endl;
     */
    
//--------------------------------------------------------------------------
    cout << "The array size is " << ARRAY_SIZE << endl<<endl;
    
    clock_t startTime, stopTime;
    srand(time(NULL));
    
    startTime = clock();  // ------------------ start
    
    shellSort1(fhVectorOfInts1);
    
    stopTime = clock();  // ---------------------- stop
    cout << "Implicit ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  // ------------------ start
    
    shellSortX(fhVectorOfInts2, gapArray, gapArraySize);
    
    stopTime = clock();  // ---------------------- stop
    cout << "Explicit ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  // ------------------ start
    
    shellSortX(fhVectorOfInts3, sedgewickGapArray, sedgewickGapArraySize);
    
    stopTime = clock();  // ---------------------- stop
    cout << "Sedgewick Shell Sort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  // ------------------ start
    
    shellSortX(fhVectorOfInts4, myGapArray, myGapArraySize);
    
    stopTime = clock();  // ---------------------- stop
    cout << "My ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    return 0;
}
/*
 The array size is 10000
 
 Implicit ShellSort Elapsed Time: 0.006101 seconds.
 
 Explicit ShellSort Elapsed Time: 0.00974 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.004374 seconds.
 
 My ShellSort Elapsed Time: 0.004379 seconds.
 
--------------------------------------------------------------------------
 The array size is 20000
 
 Implicit ShellSort Elapsed Time: 0.012286 seconds.
 
 Explicit ShellSort Elapsed Time: 0.036616 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.010071 seconds.
 
 My ShellSort Elapsed Time: 0.009935 seconds.
 
 --------------------------------------------------------------------------
 The array size is 40000
 
 Implicit ShellSort Elapsed Time: 0.03056 seconds.
 
 Explicit ShellSort Elapsed Time: 0.083363 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.019917 seconds.
 
 My ShellSort Elapsed Time: 0.021378 seconds.
 
 --------------------------------------------------------------------------
 The array size is 100000
 
 Implicit ShellSort Elapsed Time: 0.087704 seconds.
 
 Explicit ShellSort Elapsed Time: 0.362304 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.060227 seconds.
 
 My ShellSort Elapsed Time: 0.063575 seconds.
 
 --------------------------------------------------------------------------
 The array size is 160000
 
 Implicit ShellSort Elapsed Time: 0.152495 seconds.
 
 Explicit ShellSort Elapsed Time: 0.592605 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.099495 seconds.
 
 My ShellSort Elapsed Time: 0.107548 seconds.
 
 --------------------------------------------------------------------------
 The array size is 200000
 
 Implicit ShellSort Elapsed Time: 0.195471 seconds.
 
 Explicit ShellSort Elapsed Time: 0.725818 seconds.
 
 Sedgewick Shell Sort Elapsed Time: 0.120599 seconds.
 
 My ShellSort Elapsed Time: 0.131878 seconds.
 
 --------------------------------------------------------------------------
             Implied        Explicit          Sedgewick        My
 N:
 10,000      0.006101s       0.00974s         0.004374s      0.004379s
 20,000      0.012286s      0.036616s         0.010071s      0.009935s
 40,000       0.03056s      0.083363s         0.019917s      0.021378s
 100,000     0.087704s      0.362304s         0.060227s      0.063575s
 160,000     0.152495s      0.592605s         0.099495s      0.107548s
 200,000     0.195471s      0.725818s         0.120599s      0.131878s
 
 Question
 
 shellSort1 and shellSortX has different gap sequence so the time is different.
 shellSort1 is faster because its gap is bigger since it is array/2. 
 For examples, the sequence of array size of 500
 Implied:  1, 3, 7, 15, 31, 62, 125, 250,
 Explicit: 1, 2, 4, 8, 16, 32, 64, 128, 256,
 It proves that the gap is smaller, therefore, it can be complete faster.

 

 */
 

