#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

//Creates an array - Sorted(0-n), Reversed(n-0) or mixed values of 0-n.
int* arrMaker(int n, string type);

//Will sort an array using bubble sort and keep a counter for the steps that it takes to sort the array.
void bubbleSortCounter(int n, string type);

//Will sort an array using bubble sort and use chrono high resolution clock to calculate time elapsed.
void bubbleSortClock(int n, string type);

//Will display data using Bubble sort (Steps)
void disBubbleSteps();

//Will display data using Bubble sort(NanoSeconds)
void disBubbleClock();

int main()
{
	disBubbleSteps();
	disBubbleClock();

	return 0;
}

//Creates an array and returns it
int* arrMaker(int n, string type)
{
	int* arr = new int[n];

	//Creates an array with numbers in order 1, 2, 3, ... n.
	if (type == "Sorted")
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = i + 1;
		}
	}
	//Creates an array with numbers reversed n, n-1, ... 3, 2 , 1;
	else if (type == "Reversed")
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = n - 1;
		}
	}
	//Creates a sorted array and then mixes to create a random array.(Random Permutation)
	else if (type == "Random")
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = i;
		}
		for (int i = 0; i < n; i++)
		{
			int j = rand() % n;
			swap(arr[i], arr[j]);
		}
	}
	else
	{
		cout << "Error type not recognized";
	}
	return arr;
}

//Bubble sort with integer steps counter
void bubbleSortCounter(int n, string type)
{
	int steps = 0;
	int* arr = arrMaker(n, type);

	int iteration = 1;
	steps++;

	while (iteration < n - 1)
	{
		steps++;
		for (int i = 0; i < n - iteration; i++)
		{
			steps++;
			if (arr[i] > arr[++i])
			{
				steps++;
				swap(arr[i], arr[++i]);
				steps++;
			}
		}
		iteration++;
		steps++;
	}

	cout <<setw(14) << type << setw(16) << n <<setw(24) << steps << endl;
}

//Bubble sort with clock
void bubbleSortClock(int n, string type)
{
	int* arr = arrMaker(n, type);
	
	high_resolution_clock::time_point start = high_resolution_clock::now();
	int iteration = 1;
	while (iteration < n - 1)
	{
		for (int i = 0; i < n - iteration; i++)
		{
			if (arr[i] > arr[++i])
			{
				swap(arr[i], arr[++i]);
			}
		}
		iteration++;
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	high_resolution_clock::duration timeElapsed = (end - start);
	cout << setw(14) <<type <<setw(16) <<n <<setw(24) <<timeElapsed.count() << endl;
}

//Display Bubble Sort steps
void disBubbleSteps()
{
	string sorted = "Sorted";
	string reversed = "Reversed";
	string random = "Random";

	//Display data:
	cout << "\n>>>>>>>>>>>>>>>>>>>>>>BUBBLE SORT STEPS<<<<<<<<<<<<<<<<<<<<<<<\n\n";
	cout << "--------------------------------------------------------------\n";
	cout << "    Array Type:" << "              N:" << "             Number of Steps:" << endl;
	cout << "--------------------------------------------------------------\n";
	//N = 100
	bubbleSortCounter(100, sorted);
	bubbleSortCounter(100, reversed);
	bubbleSortCounter(100, random);
	//N = 200
	bubbleSortCounter(200, sorted);
	bubbleSortCounter(200, reversed);
	bubbleSortCounter(200, random);
	//N = 300
	bubbleSortCounter(300, sorted);
	bubbleSortCounter(300, reversed);
	bubbleSortCounter(300, random);
	//N = 400
	bubbleSortCounter(400, sorted);
	bubbleSortCounter(400, reversed);
	bubbleSortCounter(400, random);
	//N = 500
	bubbleSortCounter(500, sorted);
	bubbleSortCounter(500, reversed);
	bubbleSortCounter(500, random);
	//N = 1000
	bubbleSortCounter(1000, sorted);
	bubbleSortCounter(1000, reversed);
	bubbleSortCounter(1000, random);
	//N = 2000
	bubbleSortCounter(2000, sorted);
	bubbleSortCounter(2000, reversed);
	bubbleSortCounter(2000, random);
	//N = 4000
	bubbleSortCounter(4000, sorted);
	bubbleSortCounter(4000, reversed);
	bubbleSortCounter(4000, random);
}

//Display Bubble Sort NanoSeconds
void disBubbleClock()
{
	string sorted = "Sorted";
	string reversed = "Reversed";
	string random = "Random";

	//Display data:
	cout << "\n>>>>>>>>>>>>>>>>>>>BUBBLE SORT NANOSECONDS<<<<<<<<<<<<<<<<<<<<\n\n";
	cout << "--------------------------------------------------------------\n";
	cout << "    Array Type:" << "              N:" << "             NanoSeconds:" << endl;
	cout << "--------------------------------------------------------------\n";
	//N = 100
	bubbleSortClock(100, sorted);
	bubbleSortClock(100, reversed);
	bubbleSortClock(100, random);
	//N = 200
	bubbleSortClock(200, sorted);
	bubbleSortClock(200, reversed);
	bubbleSortClock(200, random);
	//N = 300
	bubbleSortClock(300, sorted);
	bubbleSortClock(300, reversed);
	bubbleSortClock(300, random);
	//N = 400
	bubbleSortClock(400, sorted);
	bubbleSortClock(400, reversed);
	bubbleSortClock(400, random);
	//N = 500
	bubbleSortClock(500, sorted);
	bubbleSortClock(500, reversed);
	bubbleSortClock(500, random);
	//N = 1000
	bubbleSortClock(1000, sorted);
	bubbleSortClock(1000, reversed);
	bubbleSortClock(1000, random);
	//N = 2000
	bubbleSortClock(2000, sorted);
	bubbleSortClock(2000, reversed);
	bubbleSortClock(2000, random);
	//N = 4000
	bubbleSortClock(4000, sorted);
	bubbleSortClock(4000, reversed);
	bubbleSortClock(4000, random);
}
