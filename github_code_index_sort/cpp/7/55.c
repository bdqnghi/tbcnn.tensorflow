/*Myron Pow, CS2C, Dave Harden, 2/24/2016
SHELLSORT
we've implemented shellsort, and sedgewick's mashed sequence is very odd
explicit, implicit, sedgewick, and a random gap were implemented
Q&A at very bottom
*/
#include <iostream>
#include <time.h>
#include "FHvector.h"
using namespace std;

const int ARRAY_SIZE = 25000;


/*
void ShellSortX()
PRE: takes an array, gap array, and gaparraysize
POS: shell sorts array with the gap array
*/
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






/*
int sedgewick
PRE: int(term number of sequence, starts at 0)
POS: sedgewick # for that term
*/
int sedgewick(int n) 
{
    int sedgewickNumber;
    if (n % 2 ==0)
        sedgewickNumber = (9 * pow(4,(n/2)) - 9 * pow(2,(n/2)) + 1);
    else
        sedgewickNumber = (pow(4,((n+2)/2+1)) - 3 * pow(2,((n+2)/2+1)) + 1);
    return sedgewickNumber;
}






//main
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

    //implicit
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

    //explicit
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

    //sedgewick
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

    //put sedgewick Gap Sequence into Array
    cout << "Sedgewick Gap Sequence: " << endl;

    int* sedgewickGapArray = new int[sedgewickGapArraySize];
    for (int x = 0; x < sedgewickGapArraySize; ++x) 
    {
        sedgewickGapArray[x] = sedgewickSequence[x];
        cout << sedgewickGapArray[x] << ", ";
    }
    cout << endl << endl;

    //random
    /*This was made by literally altering knuth's sequence from 3*k+1 to 2.5*k+1
    This gave oddly improved sorting times, generally being equal to sedgewick, if
    only marginally
    NOTES
    a multiplier of 2 is roughly equal to a multiplier of 3
    both of which are roughly double sedge

    It should be noted that this is an estimate,
    and that 2.25/2.75 worked just as well
    */

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

//DISP TIMES
    // IMPLICIT
    startTime = clock();
    shellSortX(fhVectorOfInts1, implicitGapArray, impliedGapArraySize);
    stopTime = clock();

    cout << "Implicit ShellSort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
    // EXPLICIT
    startTime = clock();
    shellSortX(fhVectorOfInts2, explicitSequence, explicitSequenceSize); 
    stopTime = clock();

    cout << "Explicit ShellSort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
    //sedgewick
    startTime = clock();
    shellSortX(fhVectorOfInts3, sedgewickGapArray, sedgewickGapArraySize);
    stopTime = clock();

    cout << "Sedgewick Shell Sort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;
    //RANDOM
    startTime = clock();
    shellSortX(fhVectorOfInts4, randomGapArray, randomGapArraySize);
    stopTime = clock();

    cout << "random ShellSort Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl << endl;

    //verify, used for testing purposes
    //all should be identical
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

/*RUN 200000 ARRAY
Unsorted, first 10:
20659, 6167, 25315, 7940, 22213, 26123, 25545, 14922, 4169, 26554,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125, 6250, 12500, 25000, 50000, 100000,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208, 13021, 32553, 81383,

Implicit ShellSort Elapsed Time: 0.874 seconds.

Explicit ShellSort Elapsed Time: 3.507 seconds.

Sedgewick Shell Sort Elapsed Time: 0.49 seconds.

random ShellSort Elapsed Time: 0.484 seconds.

First 10, Implicit ShellSort: 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
First 10, Explicit ShellSort: 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
First 10, Sedgewick ShellSort:0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
First 10, random ShellSort:   0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
Press any key to continue . . .
*/





/*RUN 100000 ARRAY
Unsorted, first 10:
20865, 27957, 3878, 16600, 16671, 11363, 25022, 27112, 28591, 32441,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125, 6250, 12500, 25000, 50000,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208, 13021, 32553, 81383,

Implicit ShellSort Elapsed Time: 0.37 seconds.

Explicit ShellSort Elapsed Time: 1.761 seconds.

Sedgewick Shell Sort Elapsed Time: 0.233 seconds.

random ShellSort Elapsed Time: 0.226 seconds.

First 10, Implicit ShellSort: 0, 0, 0, 1, 1, 1, 1, 2, 2, 3,
First 10, Explicit ShellSort: 0, 0, 0, 1, 1, 1, 1, 2, 2, 3,
First 10, Sedgewick ShellSort:0, 0, 0, 1, 1, 1, 1, 2, 2, 3,
First 10, random ShellSort:   0, 0, 0, 1, 1, 1, 1, 2, 2, 3,
Press any key to continue . . .
*/




/*RUN 50000 ARRAY
Unsorted, first 10:
21155, 1525, 20925, 28315, 17164, 394, 7118, 28728, 23563, 9551,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125, 6250, 12500, 25000,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208, 13021, 32553,

Implicit ShellSort Elapsed Time: 0.168 seconds.

Explicit ShellSort Elapsed Time: 0.577 seconds.

Sedgewick Shell Sort Elapsed Time: 0.109 seconds.

random ShellSort Elapsed Time: 0.107 seconds.

First 10, Implicit ShellSort: 2, 2, 3, 4, 4, 6, 6, 6, 7, 7,
First 10, Explicit ShellSort: 2, 2, 3, 4, 4, 6, 6, 6, 7, 7,
First 10, Sedgewick ShellSort:2, 2, 3, 4, 4, 6, 6, 6, 7, 7,
First 10, random ShellSort:   2, 2, 3, 4, 4, 6, 6, 6, 7, 7,
Press any key to continue . . .
*/




/*RUN 25000 ARRAY
Unsorted, first 10:
23366, 3700, 23577, 715, 20547, 4582, 17095, 13043, 3021, 8845,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125, 6250, 12500,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208, 13021,

Implicit ShellSort Elapsed Time: 0.071 seconds.

Explicit ShellSort Elapsed Time: 0.168 seconds.

Sedgewick Shell Sort Elapsed Time: 0.05 seconds.

random ShellSort Elapsed Time: 0.051 seconds.

First 10, Implicit ShellSort: 1, 2, 3, 3, 4, 4, 4, 4, 4, 5,
First 10, Explicit ShellSort: 1, 2, 3, 3, 4, 4, 4, 4, 4, 5,
First 10, Sedgewick ShellSort:1, 2, 3, 3, 4, 4, 4, 4, 4, 5,
First 10, random ShellSort:   1, 2, 3, 3, 4, 4, 4, 4, 4, 5,
Press any key to continue . . .
*/





/*RUN 12500 ARRAY
Unsorted, first 10:
8969, 5064, 6950, 11865, 11823, 4412, 11001, 9854, 3043, 9161,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125, 6250,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208,

Implicit ShellSort Elapsed Time: 0.033 seconds.

Explicit ShellSort Elapsed Time: 0.074 seconds.

Sedgewick Shell Sort Elapsed Time: 0.023 seconds.

random ShellSort Elapsed Time: 0.023 seconds.

First 10, Implicit ShellSort: 0, 0, 0, 0, 0, 1, 1, 2, 4, 8,
First 10, Explicit ShellSort: 0, 0, 0, 0, 0, 1, 1, 2, 4, 8,
First 10, Sedgewick ShellSort:0, 0, 0, 0, 0, 1, 1, 2, 4, 8,
First 10, random ShellSort:   0, 0, 0, 0, 0, 1, 1, 2, 4, 8,
Press any key to continue . . .
*/




/*RUN 6250 ARRAY
Unsorted, first 10:
3029, 4105, 110, 4120, 2418, 4504, 5522, 1675, 298, 2418,

Implicit Gap Sequence:
1, 3, 6, 12, 24, 48, 97, 195, 390, 781, 1562, 3125,

Explicit Gap Sequence:
1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576,

Sedgewick Gap Sequence:
1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905,

random Gap Sequence: 1, 3, 8, 21, 53, 133, 333, 833, 2083, 5208,

Implicit ShellSort Elapsed Time: 0.014 seconds.

Explicit ShellSort Elapsed Time: 0.03 seconds.

Sedgewick Shell Sort Elapsed Time: 0.011 seconds.

random ShellSort Elapsed Time: 0.01 seconds.

First 10, Implicit ShellSort: 0, 1, 1, 1, 1, 2, 2, 2, 4, 5,
First 10, Explicit ShellSort: 0, 1, 1, 1, 1, 2, 2, 2, 4, 5,
First 10, Sedgewick ShellSort:0, 1, 1, 1, 1, 2, 2, 2, 4, 5,
First 10, random ShellSort:   0, 1, 1, 1, 1, 2, 2, 2, 4, 5,
Press any key to continue . . .
*/

/* QUESTIONS AND ANSWERS
ARRAYSIZ:6250   12500     25000    50000    100000   200000
IMPLICIT:0.014   0.033  . 0.071  . 0.168  . 0.37  . 0.874  .
EXPLICIT:0.03    0.074  . 0.168  . 0.577  . 1.761  . 3.507  .
SEDGEWCK:0.011   0.023  . 0.05  . 0.109  . 0.233  . 0.49  .
RANDOM  :0.01    0.023  . 0.051  . 0.107  . 0.226  . 0.484  .
all time is in seconds.

The explicit shellsort was noticiably worse than the implcit shellsort
, probably due to the fact that the explicit set was forcibly even,
and thus closer towards the worst-case detailed on page 298.
Admittedly, the implicit also has odd indices, which brings up the
question if the implict and explicit are equal if the arraysize is
2^n.
I shall further note that my random gap sequence is approximately
equal to sedgewick, and was noticiably easier to code.
*/