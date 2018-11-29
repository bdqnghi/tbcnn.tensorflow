
/*--------------------------------------------------------------------
 Title: Programming Assignment 5 - (Sorting Algorithms) - Bozelka
 File: Driver for the Assignment
 Abstract: In this assignment the sorting algorithm selction sort
 is examined. In part a of the assignment a simple selection sort
 algo is created. In part two that algo is modified to only sort
 0 - k elements, where k is a positive integer entered by the user.
 In part 3 the modified sort is used to obtain the median of an array,
 where k is half the size of the array (since only have the array needs
 to be sorted to obtain the median).
 Author: Matthew Bozelka
 ID: 002276039
 Date: 02/07/2016
 --------------------------------------------------------------------*/

#include <iostream>
using namespace std;


void SelectionSort(int arr[], int size); // part a of assignment
int SelectionSortPartB(int arr[], int arrSize, int sortSectionSize); // part b of assignment
double median(int arr[], int size); // partc of assignment
void printArray(int arr[], int size); // helper function to print arrays


int main(int argc, const char * argv[]) {
    
    int selectionSortArrPartA[10] = {4, 6, 8, 15, 20, 22, 10, 3, 9, 2};
    int selectionSortArrPartB[10] = {4, 6, 8, 15, 20, 22, 10, 3, 9, 2};
    int selectionSortArrPartC[7] = {22, 6, 15, 8, 20, 4, -9};
    int userInputSize;
    double getMedian;
    
    
    /******************************************
     Part A Driver
     *****************************************/
    cout << "Selection sort Part A unsorted\n";
    printArray(selectionSortArrPartA, 10);
    
    SelectionSort(selectionSortArrPartA, 10);
    
    cout << "Selection sort Part A sorted\n";
    printArray(selectionSortArrPartA, 10);
    
    
    /******************************************
     Part B Driver
     *****************************************/
    do{
        cout << "Enter an integer >= 0: ";
        cin >> userInputSize;
        cin.clear();
        cin.ignore(10000, '\n');
        
        if(userInputSize <= 0)
            cout << "\nBad Input (try again)\n";
    }while(userInputSize <= 0);
    
    cout << "Selection sort Part B unsorted\n";
    printArray(selectionSortArrPartB, 10);
    
    userInputSize = SelectionSortPartB(selectionSortArrPartB, 10, userInputSize);
    
    cout << "Selection sort Part B sorted\n";
    printArray(selectionSortArrPartB, userInputSize);
    
    
    /******************************************
     Part C Driver
     *****************************************/
    cout << "Part C array unsorted: \n";
    printArray(selectionSortArrPartC, 7);
    getMedian = median(selectionSortArrPartC, 7);
    cout << "Median for part C array is: \n";
    cout << getMedian << endl << endl;
    
    
    return 0;
}


/*
    PART A selection sort
*/
void SelectionSort(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        int swapIndex = i;
        
        for(int j = i + 1; j < size; j++)
        {
            if(arr[j] < arr[swapIndex])
                swapIndex = j;
        }
        
        if(swapIndex != i)
        {
            int temp = arr[swapIndex];
            arr[swapIndex] = arr[i];
            arr[i] = temp;
        }
    }
}




/*
    PART B selection sort
    modified to sort only 0 -k elements
    in an array.
 */
int SelectionSortPartB(int arr[], int arrSize, int sortSectionSize)
{
    
    if(sortSectionSize > arrSize || sortSectionSize < 0)
    {
        cout << "K is out of bounds. The whole array will be sorted.\n\n";
        sortSectionSize = arrSize;
    }
    
    for(int i = 0; i < sortSectionSize; i++)
    {
        int swapIndex = i;
        
        for(int j = i + 1; j < arrSize; j++)
        {
            if(arr[j] < arr[swapIndex])
                swapIndex = j;
        }
        
        if(swapIndex != i)
        {
            int temp = arr[swapIndex];
            arr[swapIndex] = arr[i];
            arr[i] = temp;
        }
    }
    
    return sortSectionSize;
}


/*
  PART C median
  returns the median of an array
  sorts the array in half first
*/
double median(int arr[], int size)
{
    
    int halved = size/2;
    
    // if even
    if(size % 2 == 0)
    {
        SelectionSortPartB(arr, size, halved + 1);
        return (double) (arr[halved] + arr[halved - 1])/2;
    }
    
    SelectionSortPartB(arr, size, halved);
    return (double) arr[halved];
}


/*
    helper function to print the array
*/
void printArray(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << ((i == size -1) ? "\n\n" : ", ");
    }
}
