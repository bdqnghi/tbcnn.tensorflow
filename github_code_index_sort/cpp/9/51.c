#define _USE_MATH_DEFINES	// This must be before all includes, in order for the M_PI to come in the cmath include


#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "TestCases.hpp" //#include statements

//====================================================//
//---Defining the functions---//
SortStats bubbleSort(std::vector<int>& sortVector);
SortStats selectionSort(std::vector<int>& sortVector);
void printStats(int currentStep, std::chrono::duration<double> bubbleTime, std::chrono::duration<double> selectionTime);
void randomVecSort();
//====================================================//


//================================================================================
//===============================================================================
void runTestCases()
{
	executeTest(testCase1, bubbleSort, "Bubble Sort: 10 items");
	executeTest(testCase2, bubbleSort, "Bubble Sort: 500 items");
	executeTest(testCase3, bubbleSort, "Bubble Sort: 500 to 1000 items");

	executeTest(testCase1, selectionSort, "Selection Sort: 10 items");
	executeTest(testCase2, selectionSort, "Selection Sort: 500 items");
	executeTest(testCase3, selectionSort, "Selection Sort: 500 to 1000 items");

	executeTest(testCaseCompare, bubbleSort, selectionSort, "Sort Compare Test");
}
//===============================================================================
//================================================================================

int main()
{
	runTestCases(); //runs test cases, obviously
	std::cout << std::endl << std::endl; //establishing the space between runTestCases() and randomVecSort();
	randomVecSort(); //calling the function that will sort the vectors

	std::cin.get(); //must make a keystroke before program ends
	return 0;
}


SortStats bubbleSort(std::vector<int>& sortVector)
{
	SortStats sortVals_bubble;		  //Initializing the struct values
	sortVals_bubble.compareCount = 0; //
	sortVals_bubble.swapCount = 0;	  //

	int vecSize = sortVector.size();
	bool swapped = false;
	int temp = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> bubbleStart_f = std::chrono::high_resolution_clock::now();		//start clock
	do
	{																													//--begins bubble function--//
		swapped = false;
		for (int i = 0; i < (vecSize - 1); i++)
		{
			sortVals_bubble.compareCount++;
			if (sortVector[i] > sortVector[i + 1])
			{
				int temp = sortVector[i];
				sortVector[i] = sortVector[i + 1];
				sortVector[i + 1] = temp;
				swapped = true;
				//since a swap occured, the swapCount is incremented by 1
				sortVals_bubble.swapCount++;
			}
		};																												//--ends bubble function--//
	} while (swapped);

	std::chrono::time_point<std::chrono::high_resolution_clock> bubbleEnd_f = std::chrono::high_resolution_clock::now();		//end clock
	std::chrono::duration<double> timeBubble_f = bubbleEnd_f - bubbleStart_f;													//calculate time it took
	sortVals_bubble.time = timeBubble_f.count();
	return sortVals_bubble;
}


SortStats selectionSort(std::vector<int>& sortVector)
{
	SortStats sortVals_selection;
	sortVals_selection.compareCount = 0;
	sortVals_selection.swapCount = 0;

	int vecSize = sortVector.size();

	int minimumPos, tempVal;

	std::chrono::time_point<std::chrono::high_resolution_clock> selectionStart_f = std::chrono::high_resolution_clock::now();	//start clock
	for (int i = 0; i < (vecSize - 1); i++)																				//--begins selection function--//
	{
		minimumPos = i; //set pos_min to the current index of array

		for (int j = i + 1; j < vecSize; j++)
		{
			sortVals_selection.compareCount++;
			if (sortVector[j] < sortVector[minimumPos])
			{
				minimumPos = j;
			}
			//minimumPos keeps track of where the minimum value is at the moment
		}

		if (minimumPos != i) //if minimumPos no longer equals 'i,' values are swapped 
		{
			tempVal = sortVector[i];
			sortVector[i] = sortVector[minimumPos];
			sortVector[minimumPos] = tempVal;
			sortVals_selection.swapCount++; //swapping function
		}
	}																													//--ends selection function--//

	std::chrono::time_point<std::chrono::high_resolution_clock> selectionEnd_f = std::chrono::high_resolution_clock::now();		//end clock
	std::chrono::duration<double> timeBubble_f = selectionEnd_f - selectionStart_f;												//calculate time it took
	sortVals_selection.time = timeBubble_f.count();																				//the sortVals_selection.time is filled
	return sortVals_selection;
}


void printStats(int currentStep, std::chrono::duration<double> bubbleTime, std::chrono::duration<double> selectionTime)
{
	using namespace std;

	cout << "Number of items" << right << setw(8) << ": " << currentStep << endl;				//prints out the number of items//
	cout << "Bubble sort Time" << right << setw(7) << ": " << bubbleTime.count() << endl;		//-------------- time it took for bubble sort to run//
	cout << "Selection sort time" << right << setw(4) << ": " << selectionTime.count() << endl;	//-------------- time it took for selection sort to run//
	cout << "Sort Time Difference" << right << setw(3) << ": " << (bubbleTime.count() - selectionTime.count()) << endl << endl;
}


void randomVecSort()
{
	std::cout << "--- Timing Results ---" << std::endl << std::endl; //preparing the console output

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int size = 100;
	std::vector<int> bubbleVector(0);				//creating the vector to be bubble sorted
	std::vector<int> selectionVector(0);			//creating the vector to be selection sorted

	for (int i = 0; i < 10; i++)                    //ensuring that the test runs by stepping from 100 to 1000
	{
		std::vector<int> bubbleVector(0);			//creating the vectors to be bubble sorted
		std::vector<int> selectionVector(0); 
		for (int j = 0; j < size; j++)				//generating the vectors
		{
			int currentRand = rand() % 1000 + 1;    //generating the random number for position int j
			bubbleVector.push_back(currentRand);    //filling the bubble position w/ random number
			selectionVector.push_back(currentRand); //filling the selection position w/ random number
		}

		//====BUBBLE_SORT_TESTS====//
		std::chrono::time_point<std::chrono::high_resolution_clock> bubbleStart = std::chrono::high_resolution_clock::now();	//start clock
		bubbleSort(bubbleVector);																								//Running the test function
		std::chrono::time_point<std::chrono::high_resolution_clock> bubbleEnd = std::chrono::high_resolution_clock::now();		//end clock
		std::chrono::duration<double> timeBubble = bubbleEnd - bubbleStart;														//compute full time

		//====BUBBLE_SORT_TESTS====//
		std::chrono::time_point<std::chrono::high_resolution_clock> selectionStart = std::chrono::high_resolution_clock::now(); //start clock
		selectionSort(selectionVector);																							//Running the test function
		std::chrono::time_point<std::chrono::high_resolution_clock> selectionEnd = std::chrono::high_resolution_clock::now();	//end clock
		std::chrono::duration<double> timeSelection = selectionEnd - selectionStart;											//compute full time


		printStats(size, timeBubble, timeSelection); //printing the output using function
		size += 100; //incrementing the test size by 100 per run
	}
}


