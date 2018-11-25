#define _USE_MATH_DEFINES	


#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "TestCases.hpp" 



SortStats bubbleSort(std::vector<int>& sortVector);
SortStats selectionSort(std::vector<int>& sortVector);
void printStats(int currentStep, std::chrono::duration<double> bubbleTime, std::chrono::duration<double> selectionTime);
void randomVecSort();





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



int main()
{
	runTestCases(); 
	std::cout << std::endl << std::endl; 
	randomVecSort(); 

	std::cin.get(); 
	return 0;
}


SortStats bubbleSort(std::vector<int>& sortVector)
{
	SortStats sortVals_bubble;		  
	sortVals_bubble.compareCount = 0; 
	sortVals_bubble.swapCount = 0;	  

	int vecSize = sortVector.size();
	bool swapped = false;
	int temp = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> bubbleStart_f = std::chrono::high_resolution_clock::now();		
	do
	{																													
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
				
				sortVals_bubble.swapCount++;
			}
		};																												
	} while (swapped);

	std::chrono::time_point<std::chrono::high_resolution_clock> bubbleEnd_f = std::chrono::high_resolution_clock::now();		
	std::chrono::duration<double> timeBubble_f = bubbleEnd_f - bubbleStart_f;													
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

	std::chrono::time_point<std::chrono::high_resolution_clock> selectionStart_f = std::chrono::high_resolution_clock::now();	
	for (int i = 0; i < (vecSize - 1); i++)																				
	{
		minimumPos = i; 

		for (int j = i + 1; j < vecSize; j++)
		{
			sortVals_selection.compareCount++;
			if (sortVector[j] < sortVector[minimumPos])
			{
				minimumPos = j;
			}
			
		}

		if (minimumPos != i) 
		{
			tempVal = sortVector[i];
			sortVector[i] = sortVector[minimumPos];
			sortVector[minimumPos] = tempVal;
			sortVals_selection.swapCount++; 
		}
	}																													

	std::chrono::time_point<std::chrono::high_resolution_clock> selectionEnd_f = std::chrono::high_resolution_clock::now();		
	std::chrono::duration<double> timeBubble_f = selectionEnd_f - selectionStart_f;												
	sortVals_selection.time = timeBubble_f.count();																				
	return sortVals_selection;
}


void printStats(int currentStep, std::chrono::duration<double> bubbleTime, std::chrono::duration<double> selectionTime)
{
	using namespace std;

	cout << "Number of items" << right << setw(8) << ": " << currentStep << endl;				
	cout << "Bubble sort Time" << right << setw(7) << ": " << bubbleTime.count() << endl;		
	cout << "Selection sort time" << right << setw(4) << ": " << selectionTime.count() << endl;	
	cout << "Sort Time Difference" << right << setw(3) << ": " << (bubbleTime.count() - selectionTime.count()) << endl << endl;
}


void randomVecSort()
{
	std::cout << "--- Timing Results ---" << std::endl << std::endl; 

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int size = 100;
	std::vector<int> bubbleVector(0);				
	std::vector<int> selectionVector(0);			

	for (int i = 0; i < 10; i++)                    
	{
		std::vector<int> bubbleVector(0);			
		std::vector<int> selectionVector(0); 
		for (int j = 0; j < size; j++)				
		{
			int currentRand = rand() % 1000 + 1;    
			bubbleVector.push_back(currentRand);    
			selectionVector.push_back(currentRand); 
		}

		
		std::chrono::time_point<std::chrono::high_resolution_clock> bubbleStart = std::chrono::high_resolution_clock::now();	
		bubbleSort(bubbleVector);																								
		std::chrono::time_point<std::chrono::high_resolution_clock> bubbleEnd = std::chrono::high_resolution_clock::now();		
		std::chrono::duration<double> timeBubble = bubbleEnd - bubbleStart;														

		
		std::chrono::time_point<std::chrono::high_resolution_clock> selectionStart = std::chrono::high_resolution_clock::now(); 
		selectionSort(selectionVector);																							
		std::chrono::time_point<std::chrono::high_resolution_clock> selectionEnd = std::chrono::high_resolution_clock::now();	
		std::chrono::duration<double> timeSelection = selectionEnd - selectionStart;											


		printStats(size, timeBubble, timeSelection); 
		size += 100; 
	}
}


