#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;


int* arrMaker(int n, string type);


void bubbleSortCounter(int n, string type);


void bubbleSortClock(int n, string type);


void disBubbleSteps();


void disBubbleClock();

int main()
{
	disBubbleSteps();
	disBubbleClock();

	return 0;
}


int* arrMaker(int n, string type)
{
	int* arr = new int[n];

	
	if (type == "Sorted")
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = i + 1;
		}
	}
	
	else if (type == "Reversed")
	{
		for (int i = 0; i < n; i++)
		{
			arr[i] = n - 1;
		}
	}
	
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


void disBubbleSteps()
{
	string sorted = "Sorted";
	string reversed = "Reversed";
	string random = "Random";

	
	cout << "\n>>>>>>>>>>>>>>>>>>>>>>BUBBLE SORT STEPS<<<<<<<<<<<<<<<<<<<<<<<\n\n";
	cout << "--------------------------------------------------------------\n";
	cout << "    Array Type:" << "              N:" << "             Number of Steps:" << endl;
	cout << "--------------------------------------------------------------\n";
	
	bubbleSortCounter(100, sorted);
	bubbleSortCounter(100, reversed);
	bubbleSortCounter(100, random);
	
	bubbleSortCounter(200, sorted);
	bubbleSortCounter(200, reversed);
	bubbleSortCounter(200, random);
	
	bubbleSortCounter(300, sorted);
	bubbleSortCounter(300, reversed);
	bubbleSortCounter(300, random);
	
	bubbleSortCounter(400, sorted);
	bubbleSortCounter(400, reversed);
	bubbleSortCounter(400, random);
	
	bubbleSortCounter(500, sorted);
	bubbleSortCounter(500, reversed);
	bubbleSortCounter(500, random);
	
	bubbleSortCounter(1000, sorted);
	bubbleSortCounter(1000, reversed);
	bubbleSortCounter(1000, random);
	
	bubbleSortCounter(2000, sorted);
	bubbleSortCounter(2000, reversed);
	bubbleSortCounter(2000, random);
	
	bubbleSortCounter(4000, sorted);
	bubbleSortCounter(4000, reversed);
	bubbleSortCounter(4000, random);
}


void disBubbleClock()
{
	string sorted = "Sorted";
	string reversed = "Reversed";
	string random = "Random";

	
	cout << "\n>>>>>>>>>>>>>>>>>>>BUBBLE SORT NANOSECONDS<<<<<<<<<<<<<<<<<<<<\n\n";
	cout << "--------------------------------------------------------------\n";
	cout << "    Array Type:" << "              N:" << "             NanoSeconds:" << endl;
	cout << "--------------------------------------------------------------\n";
	
	bubbleSortClock(100, sorted);
	bubbleSortClock(100, reversed);
	bubbleSortClock(100, random);
	
	bubbleSortClock(200, sorted);
	bubbleSortClock(200, reversed);
	bubbleSortClock(200, random);
	
	bubbleSortClock(300, sorted);
	bubbleSortClock(300, reversed);
	bubbleSortClock(300, random);
	
	bubbleSortClock(400, sorted);
	bubbleSortClock(400, reversed);
	bubbleSortClock(400, random);
	
	bubbleSortClock(500, sorted);
	bubbleSortClock(500, reversed);
	bubbleSortClock(500, random);
	
	bubbleSortClock(1000, sorted);
	bubbleSortClock(1000, reversed);
	bubbleSortClock(1000, random);
	
	bubbleSortClock(2000, sorted);
	bubbleSortClock(2000, reversed);
	bubbleSortClock(2000, random);
	
	bubbleSortClock(4000, sorted);
	bubbleSortClock(4000, reversed);
	bubbleSortClock(4000, random);
}
