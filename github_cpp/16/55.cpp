
#include <iostream>
#include <time.h>
#include "FHvector.h"
using namespace std;

const int ARRAY_SIZE = 25000;



template <typename Comparable>
void shellSortX(FHvector<Comparable> & compArray, int * gapArray, int gapArraySize)
{
    int pos, sortPos, gap, gapArrayPos;
    Comparable temp;
    for (gapArrayPos = gapArraySize - 1; gapArrayPos >= 0; gapArrayPos--) 
    {
        gap = gapArray[gapArrayPos];
        for (pos = gap; pos < compArray.size(); pos++)
        {
            temp = compArray[pos];

            for (sortPos = pos; sortPos >= gap &&
                temp < compArray[sortPos - gap]; sortPos -= gap)
            {
                compArray[sortPos] = compArray[sortPos - gap];
            }
            compArray[sortPos] = temp;
        }
    }
}







int sedgewick(int n) 
{
    int sedgewickNumber;
    if (n % 2 ==0)
        sedgewickNumber = (9 * pow(4,(n/2)) - 9 * pow(2,(n/2)) + 1);
    else
        sedgewickNumber = (pow(4,((n+2)/2+1)) - 3 * pow(2,((n+2)/2+1)) + 1);
    return sedgewickNumber;
}







int main()
{
    FHvector<int> fhVectorOfInts1;
    FHvector<int> fhVectorOfInts2;
    FHvector<int> fhVectorOfInts3;
    FHvector<int> fhVectorOfInts4;

    clock_t startTime, stopTime;
    srand(time(NULL));
    int randInt;

    FHvector<int> impliedSequence;
    FHvector<int> sedgewickSequence;
    FHvector<int> randomSequence;

    int impliedGapArraySize; 
    int explicitSequenceSize;
    int sedgewickGapArraySize;
    int randomGapArraySize;

    for (int x = 0; x < ARRAY_SIZE; ++x) 
    {
        randInt = rand() % ARRAY_SIZE;
        fhVectorOfInts1.push_back(randInt);
        fhVectorOfInts2.push_back(randInt);
        fhVectorOfInts3.push_back(randInt);
        fhVectorOfInts4.push_back(randInt);
    }

    cout << "Unsorted, first 10:"<< endl;
    for (int x = 0; x < 10; ++x) 
    {
        cout << fhVectorOfInts1[x] << ", ";
    }
    cout << endl << endl;

    
    for (int x = ARRAY_SIZE / 2; x > 0; x /= 2) 
    {
        impliedSequence.push_back(x);
    }
    impliedGapArraySize = impliedSequence.size();
    cout << "Implicit Gap Sequence: "<< endl;

    int* implicitGapArray = new int[impliedGapArraySize];
    for (int x = 0; x < impliedGapArraySize; ++x) 
    {
        implicitGapArray[x] = impliedSequence[impliedGapArraySize - (x+1)];
        cout << implicitGapArray[x] << ", ";
    }
    cout << endl << endl;

    
    int explicitSequence[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
        2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
        1048576 };
    explicitSequenceSize = 21;

    cout << "Explicit Gap Sequence: " << endl;
    for (int x = 0; x < explicitSequenceSize; x++)
    {
        cout << explicitSequence[x] << ", ";
    }
    cout << endl << endl;

    
    for (int k = 0; k < ARRAY_SIZE; k++) 
    {
        int sedgewickNumber = sedgewick(k);
        if (sedgewickNumber > ARRAY_SIZE) 
        {
            break;
        }
        
        sedgewickSequence.push_back(sedgewickNumber);
    }
    sedgewickGapArraySize = sedgewickSequence.size();

    
    cout << "Sedgewick Gap Sequence: " << endl;

    int* sedgewickGapArray = new int[sedgewickGapArraySize];
    for (int x = 0; x < sedgewickGapArraySize; ++x) 
    {
        sedgewickGapArray[x] = sedgewickSequence[x];
        cout << sedgewickGapArray[x] << ", ";
    }
    cout << endl << endl;

    
    

    for (int k = 1; k < ARRAY_SIZE; k = 2.5*k+1) 
    {
        randomSequence.push_back(k);
    }
    randomGapArraySize = randomSequence.size();

    cout << "random Gap Sequence: ";

    int* randomGapArray = new int[randomGapArraySize];
    for (int x = 0; x < randomGapArraySize; ++x) 
    {
        randomGapArray[x] = randomSequence[x];
        cout << randomGapArray[x] << ", ";
    }
    cout << endl << endl;


    
    startTime = clock();
    shellSortX(fhVectorOfInts1, implicitGapArray, impliedGapArraySize);
    stopTime = clock();

    cout << "Implicit ShellSort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
    
    startTime = clock();
    shellSortX(fhVectorOfInts2, explicitSequence, explicitSequenceSize); 
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
    shellSortX(fhVectorOfInts4, randomGapArray, randomGapArraySize);
    stopTime = clock();

    cout << "random ShellSort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    
    
    cout << "First 10, Implicit ShellSort: ";
    for (int x = 0; x < 10; ++x)
    {
        cout << fhVectorOfInts1[x] << ", ";
    }
    cout << endl;

    cout << "First 10, Explicit ShellSort: ";
    for (int x = 0; x < 10; ++x)
    {
        cout << fhVectorOfInts2[x] << ", ";
    }
    cout << endl;

    cout << "First 10, Sedgewick ShellSort:";
    for (int x = 0; x < 10; ++x)
    {
        cout << fhVectorOfInts3[x] << ", ";
    }
    cout << endl;

    cout << "First 10, random ShellSort:   ";
    for (int x = 0; x < 10; ++x)
    {
        cout << fhVectorOfInts4[x] << ", ";
    }
    cout << endl;

    delete[] implicitGapArray;
    implicitGapArray = NULL;
    delete[] randomGapArray;
    randomGapArray = NULL;
    delete[] sedgewickGapArray;
    sedgewickGapArray = NULL;

    return 0;
}






























