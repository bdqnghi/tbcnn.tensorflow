

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
    
    
    

    cout << "The array size is " << ARRAY_SIZE << endl<<endl;
    
    clock_t startTime, stopTime;
    srand(time(NULL));
    
    startTime = clock();  
    
    shellSort1(fhVectorOfInts1);
    
    stopTime = clock();  
    cout << "Implicit ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  
    
    shellSortX(fhVectorOfInts2, gapArray, gapArraySize);
    
    stopTime = clock();  
    cout << "Explicit ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  
    
    shellSortX(fhVectorOfInts3, sedgewickGapArray, sedgewickGapArraySize);
    
    stopTime = clock();  
    cout << "Sedgewick Shell Sort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    startTime = clock();  
    
    shellSortX(fhVectorOfInts4, myGapArray, myGapArraySize);
    
    stopTime = clock();  
    cout << "My ShellSort Elapsed Time: "
    << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
    << " seconds." << endl << endl;
    
    
    return 0;
}

 

