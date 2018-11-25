


#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include"stopWatch.h"
#include"functions.h"


int main()
{
    using namespace std;

    
    int small[10];
    int medium[1000];
    int* large = new int[1000000];

    
    


    

    ofstream sortTimings;
    sortTimings.open("sortTimings.txt");

    
    randomizeAllArrays(small, medium, large);

    
    
    

    stopWatch shellPrattTimer1;
    shellSortPratt(small, 10);
    sortTimings << "shell pratt timer 1 took: " << shellPrattTimer1.elapsedTime() << endl;

    stopWatch shellPrattTimer2;
    shellSortPratt(medium, 1000);
    sortTimings << "shell pratt timer 2 took: " << shellPrattTimer2.elapsedTime() << endl;

    stopWatch shellPrattTimer3;
    shellSortPratt(large, 1000000);
    sortTimings << "shell pratt timer 3 took: " << shellPrattTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch shellShellTimer1;
    shellSortShell(small, 10);
    sortTimings << "shell Shell timer 1 took: " << shellShellTimer1.elapsedTime() << endl;

    stopWatch shellShellTimer2;
    shellSortShell(medium, 1000);
    sortTimings << "shell Shell timer 2 took: " << shellShellTimer2.elapsedTime() << endl;

    stopWatch shellShellTimer3;
    shellSortShell(large, 1000000);
    sortTimings << "shell Shell timer 3 took: " << shellShellTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch shellHibbardTimer1;
    shellSortHibbard(small, 10);
    sortTimings << "shell Hibbard timer 1 took: " << shellHibbardTimer1.elapsedTime() << endl;

    stopWatch shellHibbardTimer2;
    shellSortHibbard(medium, 1000);
    sortTimings << "shell Hibbard timer 2 took: " << shellHibbardTimer2.elapsedTime() << endl;

    stopWatch shellHibbardTimer3;
    shellSortHibbard(large, 1000000);
    sortTimings << "shell Hibbard timer 3 took: " << shellHibbardTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch shellSedgeWickTimer1;
    shellSortSedgeWick(small, 10);
    sortTimings << "shell SedgeWick timer 1 took: " << shellSedgeWickTimer1.elapsedTime() << endl;

    stopWatch shellSedgeWickTimer2;
    shellSortSedgeWick(medium, 1000);
    sortTimings << "shell SedgeWick timer 2 took: " << shellSedgeWickTimer2.elapsedTime() << endl;

    stopWatch shellSedgeWickTimer3;
    shellSortSedgeWick(large, 1000000);
    sortTimings << "shell SedgeWick timer 3 took: " << shellSedgeWickTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch mergeSortLRTimer1;
    mergeSortLR(small, 0, 9);
    sortTimings << "mergeSortLR timer 1 took: " << mergeSortLRTimer1.elapsedTime() << endl;

    stopWatch mergeSortLRTimer2;
    mergeSortLR(medium, 0, 999);
    sortTimings << "mergeSortLR timer 2 took: " << mergeSortLRTimer2.elapsedTime() << endl;

    stopWatch mergeSortLRTimer3;
    mergeSortLR(large, 0, 999999);
    sortTimings << "mergeSortLR timer 3 took: " << mergeSortLRTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch mergeSortLMRTimer1;
    mergeSortLMR(small, 0, 9);
    sortTimings << "mergeSortLMR timer 1 took: " << mergeSortLMRTimer1.elapsedTime() << endl;

    stopWatch mergeSortLMRTimer2;
    mergeSortLMR(medium, 0, 999);
    sortTimings << "mergeSortLMR timer 2 took: " << mergeSortLMRTimer2.elapsedTime() << endl;

    stopWatch mergeSortLMRTimer3;
    mergeSortLMR(large, 0, 999999);
    sortTimings << "mergeSortLMR timer 3 took: " << mergeSortLMRTimer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch quickSortPiv1Timer1;
    quickSortPiv1(small, 0, 9);
    sortTimings << "quickSortPiv1 timer 1 took: " << quickSortPiv1Timer1.elapsedTime() << endl;

    stopWatch quickSortPiv1Timer2;
    quickSortPiv1(medium, 0, 999);
    sortTimings << "quickSortPiv1 timer 2 took: " << quickSortPiv1Timer2.elapsedTime() << endl;

    stopWatch quickSortPiv1Timer3;
    quickSortPiv1(large, 0, 999999);
    sortTimings << "quickSortPiv1 timer 3 took: " << quickSortPiv1Timer3.elapsedTime() << endl;

    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);

    stopWatch quickSortPivMidTimer1;
    quickSortPivMid(small, 0, 9);
    sortTimings << "quickSortPivMid timer 1 took: " << quickSortPivMidTimer1.elapsedTime() << endl;

    stopWatch quickSortPivMidTimer2;
    quickSortPivMid(medium, 0, 999);
    sortTimings << "quickSortPivMid timer 2 took: " << quickSortPivMidTimer2.elapsedTime() << endl;

    stopWatch quickSortPivMidTimer3;
    quickSortPivMid(large, 0, 999999);
    sortTimings << "quickSortPivMid timer 3 took: " << quickSortPivMidTimer3.elapsedTime() << endl;


    sortTimings << endl << endl;

    randomizeAllArrays(small, medium, large);


    stopWatch quickSortPivMedian1;
    quickSortPivMedian(small, 0, 9);
    sortTimings << "quickSortPivMedian timer 1 took: " << quickSortPivMedian1.elapsedTime() << endl;

    stopWatch quickSortPivMedian2;
    quickSortPivMedian(medium, 0, 999);
    sortTimings << "quickSortPivMedian timer 2 took: " << quickSortPivMedian2.elapsedTime() << endl;

    stopWatch quickSortPivMedian3;
    quickSortPivMedian(large, 0, 999999);
    sortTimings << "quickSortPivMedian timer 3 took: " << quickSortPivMedian3.elapsedTime() << endl;

    sortTimings << endl << endl;


    
    sortTimings << "testing!!!!!!!!!!!!!!!!!!" << endl << endl << endl;
    sortTimings << "super large arrays 100 million elements" << endl << endl;

    int* superLarge = new int[100000000];

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);

    stopWatch shellPrattTimer4;
    shellSortPratt(superLarge, 100000000);
    sortTimings << "shell pratt timer 4 took: " << shellPrattTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);


    stopWatch shellShellTimer4;
    shellSortShell(superLarge, 100000000);
    sortTimings << "shell Shell timer 4 took: " << shellShellTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);


    stopWatch shellHibbardTimer4;
    shellSortHibbard(superLarge, 100000000);
    sortTimings << "shell Hibbard timer 4 took: " << shellHibbardTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);


    stopWatch shellSedgeWickTimer4;
    shellSortSedgeWick(superLarge, 100000000);
    sortTimings << "shell SedgeWick timer 4 took: " << shellSedgeWickTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);

    stopWatch mergeSortLRTimer4;
    mergeSortLR(superLarge, 0, 99999999);
    sortTimings << "mergeSortLR timer 4 took: " << mergeSortLRTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);


    stopWatch mergeSortLMRTimer4;
    mergeSortLMR(superLarge, 0, 99999999);
    sortTimings << "mergeSortLMR timer 4 took: " << mergeSortLMRTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);

    stopWatch quickSortPiv1Timer4;
    quickSortPiv1(superLarge, 0, 99999999);
    sortTimings << "quickSortPiv1 timer 4 took: " << quickSortPiv1Timer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);

    stopWatch quickSortPivMidTimer4;
    quickSortPivMid(superLarge, 0, 99999999);
    sortTimings << "quickSortPivMid timer 4 took: " << quickSortPivMidTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    insertRandNums(superLarge, 100000000, 1000000);

    stopWatch quickSortPivMedianTimer4;
    quickSortPivMedian(superLarge, 0, 99999999);
    sortTimings << "quickSortPivMedian timer 4 took: " << quickSortPivMedianTimer4.elapsedTime() << endl;

    sortTimings << endl << endl;

    sortTimings.close();

    return 0;
}




void insertRandNums(int list[], int size, int maxNum)
{
    srand(time(NULL));

    for (int iii = 0; iii < size; iii++)
    {
        list[iii] = rand() % maxNum + 1;
    }

}


void printList(int list[], int size)
{
    using namespace std;

    for (int iii = 0; iii < size; iii++)
    {
        cout << list[iii] << ' ';
    }
}



void randomizeAllArrays(int small[], int medium[], int large[])
{
    insertRandNums(small, 10, 10);
    insertRandNums(medium, 1000, 1000);
    insertRandNums(large, 1000000, 1000000);
}