#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>

#include "bubbleSort.h"
#include "mergeSort.h"
#include "radixSort.h"

using namespace std;

int main()
{

	int* toBeSorted = new int[1000000];

	for (int i = 0; i < 10; i++)
	{

		srand (time(NULL));
	
		for(int i = 0; i < 1000; i++)
		{
			toBeSorted[i] = rand() % 1000000 + 1;
		}

		ofstream fout;
		fout.open("data.txt");

		for(int i = 0; i < 1000; i++)
		{
			fout << toBeSorted[i] << endl;
		}
	
		int* bubbleSorted = new int[1000];
		int* mergeSorted = new int[1000];
		int* radixSorted = new int[1000];
	
		for(int i = 0; i < 1000; i++)
		{
			bubbleSorted[i] = toBeSorted[i];
			mergeSorted[i] = toBeSorted[i];
			radixSorted[i] = toBeSorted[i];
		}
	
		fout.close();
	
		clock_t time1;
		time1 = clock();
	
		BubbleSort firstSort;
	
		firstSort.sort(bubbleSorted, 1000);
	
		int bubbleComp = firstSort.getComparisonNum();
		int bubbleSwap = firstSort.getSwapNum();
	
		fout.open("bubble1000-" + to_string(i));
	
		fout << "Bubble Sort with " << 1000 << " items:" << endl;
		fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;
	
		time1 = clock() - time1;
		fout << "This took " << ((float)time1/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 1000; i++)
		{
			fout << bubbleSorted[i] << endl;
		}
		fout.close();
	
		clock_t time2;
		time2 = clock();
	
		MergeSort secondSort;
	
		secondSort.sort(mergeSorted, 0, 1000);
	
		int mergeComp = secondSort.getComparisonNum();
		int mergeSwap = secondSort.getSwapNum();
	
		fout.open("merge1000-" + to_string(i));
	
		fout << "Merge sort with " << 1000 << " items:" << endl;
		fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;
	
		time2 = clock() - time2;
		fout << "This took " << ((float)time2/CLOCKS_PER_SEC) << " seconds." << 	endl;

		for(int i = 0; i < 1000; i++)
		{
			fout << mergeSorted[i] << endl;
		}
		fout.close();
	
		clock_t time3;
		time3 = clock();
	
		RadixSort thirdSort;
	
		thirdSort.sort(radixSorted, 1000, 7);
	
		int radixComp = thirdSort.getComparisonNum();
		int radixSwap = thirdSort.getSwapNum();
	
		fout.open("radix1000-" + to_string(i));
	
		fout << "Radix Sort with " << 1000 << " items:" << endl;
		fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;
	
		time3 = clock() - time3;
		fout << "This took " << ((float)time3/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 1000; i++)
		{
			fout << radixSorted[i] << endl;
		}
		fout.close();
	
		secondSort.reset();
		delete[] bubbleSorted;
		delete[] mergeSorted;
		delete[] radixSorted;
		
		
	

	
		for(int i = 1000; i < 10000; i++)
		{
			toBeSorted[i] = rand() % 1000000 + 1;
		}
	
		
		fout.open("data.txt");
	
		for(int i = 0; i < 10000; i++)
		{
			fout << toBeSorted[i] << endl;
		}
	
		bubbleSorted = new int[10000];
		mergeSorted = new int[10000];
		radixSorted = new int[10000];
	
		for(int i = 0; i < 10000; i++)
		{
			bubbleSorted[i] = toBeSorted[i];
			mergeSorted[i] = toBeSorted[i];
			radixSorted[i] = toBeSorted[i];
		}
	
		fout.close();
	
		clock_t time4;
		time4 = clock();
	
		
	
		firstSort.sort(bubbleSorted, 10000);
	
		bubbleComp = firstSort.getComparisonNum();
		bubbleSwap = firstSort.getSwapNum();
	
		fout.open("bubble10000-" + to_string(i));
	
		fout << "Bubble Sort with " << 10000 << " items:" << endl;
		fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;
	
		time4 = clock() - time4;
		fout << "This took " << ((float)time4/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 10000; i++)
		{
			fout << bubbleSorted[i] << endl;
		}
		fout.close();
	
		clock_t time5;
		time5 = clock();
	
		
	
		secondSort.sort(mergeSorted, 0, 10000);
	
		mergeComp = secondSort.getComparisonNum();
		mergeSwap = secondSort.getSwapNum();
	
		fout.open("merge10000-" + to_string(i));
	
		fout << "Merge sort with " << 10000 << " items:" << endl;
		fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;
	
		time5 = clock() - time5;
		fout << "This took " << ((float)time5/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 10000; i++)
		{
			fout << mergeSorted[i] << endl;
		}
		fout.close();
	
		clock_t time6;
		time6 = clock();
	
		
	
		thirdSort.sort(radixSorted, 10000, 7);
	
		radixComp = thirdSort.getComparisonNum();
		radixSwap = thirdSort.getSwapNum();
	
		fout.open("radix10000-" + to_string(i));
	
		fout << "Radix Sort with " << 10000 << " items:" << endl;
		fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;
	
		time6 = clock() - time6;
		fout << "This took " << ((float)time6/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 10000; i++)
		{
			fout << radixSorted[i] << endl;
		}
		fout.close();
	
		secondSort.reset();
		delete[] bubbleSorted;
		delete[] mergeSorted;
		delete[] radixSorted;
	

	
		for(int i = 10000; i < 100000; i++)
		{
			toBeSorted[i] = rand() % 1000000 + 1;
		}
	
		
		fout.open("data.txt");
	
		for(int i = 0; i < 100000; i++)
		{
			fout << toBeSorted[i] << endl;
		}
	
		bubbleSorted = new int[100000];
		mergeSorted = new int[100000];
		radixSorted = new int[100000];
	
		for(int i = 0; i < 100000; i++)
		{
			bubbleSorted[i] = toBeSorted[i];
			mergeSorted[i] = toBeSorted[i];
			radixSorted[i] = toBeSorted[i];
		}
	
		fout.close();
	
		clock_t time7;
		time7 = clock();
	
		
	
		firstSort.sort(bubbleSorted, 100000);
	
		bubbleComp = firstSort.getComparisonNum();
		bubbleSwap = firstSort.getSwapNum();
	
		fout.open("bubble100000-" + to_string(i));
	
		fout << "Bubble Sort with " << 100000 << " items:" << endl;
		fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;
	
		time7 = clock() - time7;
		fout << "This took " << ((float)time7/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 100000; i++)
		{
			fout << bubbleSorted[i] << endl;
		}
		fout.close();
	
		clock_t time8;
		time8 = clock();
	
		
	
		secondSort.sort(mergeSorted, 0, 100000);
	
		mergeComp = secondSort.getComparisonNum();
		mergeSwap = secondSort.getSwapNum();
	
		fout.open("merge100000-" + to_string(i));
	
		fout << "Merge sort with " << 100000 << " items:" << endl;
		fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;
	
		time8 = clock() - time8;
		fout << "This took " << ((float)time8/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 100000; i++)
		{
			fout << mergeSorted[i] << endl;
		}
		fout.close();
	
		clock_t time9;
		time9 = clock();
	
		
	
		thirdSort.sort(radixSorted, 100000, 7);
	
		radixComp = thirdSort.getComparisonNum();
		radixSwap = thirdSort.getSwapNum();
	
		fout.open("radix100000-" + to_string(i));
	
		fout << "Radix Sort with " << 100000 << " items:" << endl;
		fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;
	
		time9 = clock() - time9;
		fout << "This took " << ((float)time9/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 100000; i++)
		{
			fout << radixSorted[i] << endl;
		}
		fout.close();
	
		secondSort.reset();
		delete[] bubbleSorted;
		delete[] mergeSorted;
		delete[] radixSorted;
	

	
		for(int i = 100000; i < 1000000; i++)
		{
			toBeSorted[i] = rand() % 1000000 + 1;
		}
	
		
		fout.open("data.txt");
	
		for(int i = 0; i < 1000000; i++)
		{
			fout << toBeSorted[i] << endl;
		}
	
		bubbleSorted = new int[1000000];
		mergeSorted = new int[1000000];
		radixSorted = new int[1000000];
	
		for(int i = 0; i < 1000000; i++)
		{
			bubbleSorted[i] = toBeSorted[i];
			mergeSorted[i] = toBeSorted[i];
			radixSorted[i] = toBeSorted[i];
		}
	
		fout.close();

		if (i == 0 || i == 1)
		{
			clock_t time12;
			time12 = clock();
		
			
		
			firstSort.sort(bubbleSorted, 1000000);
		
			bubbleComp = firstSort.getComparisonNum();
			bubbleSwap = firstSort.getSwapNum();
		
			fout.open("bubble1000000-" + to_string(i));
		
			fout << "Bubble Sort with " << 1000000 << " items:" << endl;
			fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;
		
			time12 = clock() - time12;
			fout << "This took " << ((float)time12/CLOCKS_PER_SEC) << " seconds." << endl;
		
			for(int i = 0; i < 1000000; i++)
			{
				fout << bubbleSorted[i] << endl;
			}
			fout.close();
		}
	
		clock_t time10;
		time10 = clock();
	
		
	
		secondSort.sort(mergeSorted, 0, 1000000);
	
		mergeComp = secondSort.getComparisonNum();
		mergeSwap = secondSort.getSwapNum();
	
		fout.open("merge1000000-" + to_string(i));
	
		fout << "Merge sort with " << 1000000 << " items:" << endl;
		fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;
	
		time10 = clock() - time10;
		fout << "This took " << ((float)time10/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 1000000; i++)
		{
			fout << mergeSorted[i] << endl;
		}
		fout.close();
	
		clock_t time11;
		time11 = clock();
	
		
	
		thirdSort.sort(radixSorted, 1000000, 7);
	
		radixComp = thirdSort.getComparisonNum();
		radixSwap = thirdSort.getSwapNum();
	
		fout.open("radix1000000-" + to_string(i));
	
		fout << "Radix Sort with " << 1000000 << " items:" << endl;
		fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;
	
		time11 = clock() - time11;
		fout << "This took " << ((float)time11/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
		for(int i = 0; i < 1000000; i++)
		{
			fout << radixSorted[i] << endl;
		}
		fout.close();
	
		secondSort.reset();
		delete[] bubbleSorted;
		delete[] mergeSorted;
		delete[] radixSorted;
	}



	ifstream fin1, fin2, fin3;

	fin1.open("sortedData1000");
	fin2.open("sortedData1000");
	fin3.open("sortedData1000");
	
	int* bubbleSorted = new int[1000];
	int* mergeSorted = new int[1000];
	int* radixSorted = new int[1000];
	
	for(int i = 0; i < 1000; i++)
	{
		fin1 >> bubbleSorted[i];
		fin2 >> mergeSorted[i];
		fin3 >> radixSorted[i];
	}

	fin1.close();
	fin2.close();
	fin3.close();

	ofstream fout;

	clock_t time1;
	time1 = clock();

	BubbleSort firstSort;

	firstSort.sort(bubbleSorted, 1000);

	int bubbleComp = firstSort.getComparisonNum();
	int bubbleSwap = firstSort.getSwapNum();

	fout.open("sortedBubble1000");

	fout << "Bubble Sort with " << 1000 << " items:" << endl;
	fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;

	time1 = clock() - time1;
	fout << "This took " << ((float)time1/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
	for(int i = 0; i < 1000; i++)
	{
		fout << bubbleSorted[i] << endl;
	}
	fout.close();

	clock_t time2;
	time2 = clock();

	MergeSort secondSort;

	secondSort.sort(mergeSorted, 0, 1000);

	int mergeComp = secondSort.getComparisonNum();
	int mergeSwap = secondSort.getSwapNum();

	fout.open("sortedMerge1000");

	fout << "Merge sort with " << 1000 << " items:" << endl;
	fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;

	time2 = clock() - time2;
	fout << "This took " << ((float)time2/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 1000; i++)
	{
		fout << mergeSorted[i] << endl;
	}
	fout.close();

	clock_t time3;
	time3 = clock();

	RadixSort thirdSort;

	thirdSort.sort(radixSorted, 1000, 7);

	int radixComp = thirdSort.getComparisonNum();
	int radixSwap = thirdSort.getSwapNum();

	fout.open("sortedRadix1000");

	fout << "Radix Sort with " << 1000 << " items:" << endl;
	fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;

	time3 = clock() - time3;
	fout << "This took " << ((float)time3/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 1000; i++)
	{
		fout << radixSorted[i] << endl;
	}
	fout.close();

	secondSort.reset();
	delete[] bubbleSorted;
	delete[] mergeSorted;
	delete[] radixSorted;



	fin1.open("sortedData10000");
	fin2.open("sortedData10000");
	fin3.open("sortedData10000");
	
	bubbleSorted = new int[10000];
	mergeSorted = new int[10000];
	radixSorted = new int[10000];
	
	for(int i = 0; i < 10000; i++)
	{
		fin1 >> bubbleSorted[i];
		fin2 >> mergeSorted[i];
		fin3 >> radixSorted[i];
	}

	fin1.close();
	fin2.close();
	fin3.close();

	

	clock_t time4;
	time4 = clock();

	

	firstSort.sort(bubbleSorted, 10000);

	bubbleComp = firstSort.getComparisonNum();
	bubbleSwap = firstSort.getSwapNum();

	fout.open("sortedBubble10000");

	fout << "Bubble Sort with " << 10000 << " items:" << endl;
	fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;

	time4 = clock() - time4;
	fout << "This took " << ((float)time4/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
	for(int i = 0; i < 10000; i++)
	{
		fout << bubbleSorted[i] << endl;
	}
	fout.close();

	clock_t time5;
	time5 = clock();

	

	secondSort.sort(mergeSorted, 0, 10000);

	mergeComp = secondSort.getComparisonNum();
	mergeSwap = secondSort.getSwapNum();

	fout.open("sortedMerge10000");

	fout << "Merge sort with " << 10000 << " items:" << endl;
	fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;

	time5 = clock() - time5;
	fout << "This took " << ((float)time5/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 10000; i++)
	{
		fout << mergeSorted[i] << endl;
	}
	fout.close();

	clock_t time6;
	time6 = clock();

	

	thirdSort.sort(radixSorted, 10000, 7);

	radixComp = thirdSort.getComparisonNum();
	radixSwap = thirdSort.getSwapNum();

	fout.open("sortedRadix10000");

	fout << "Radix Sort with " << 10000 << " items:" << endl;
	fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;

	time6 = clock() - time6;
	fout << "This took " << ((float)time6/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 10000; i++)
	{
		fout << radixSorted[i] << endl;
	}
	fout.close();

	secondSort.reset();
	delete[] bubbleSorted;
	delete[] mergeSorted;
	delete[] radixSorted;



	fin1.open("sortedData100000");
	fin2.open("sortedData100000");
	fin3.open("sortedData100000");
	
	bubbleSorted = new int[100000];
	mergeSorted = new int[100000];
	radixSorted = new int[100000];
	
	for(int i = 0; i < 100000; i++)
	{
		fin1 >> bubbleSorted[i];
		fin2 >> mergeSorted[i];
		fin3 >> radixSorted[i];
	}

	fin1.close();
	fin2.close();
	fin3.close();

	

	clock_t time7;
	time7 = clock();

	

	firstSort.sort(bubbleSorted, 100000);

	bubbleComp = firstSort.getComparisonNum();
	bubbleSwap = firstSort.getSwapNum();

	fout.open("sortedBubble100000");

	fout << "Bubble Sort with " << 100000 << " items:" << endl;
	fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;

	time7 = clock() - time7;
	fout << "This took " << ((float)time7/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
	for(int i = 0; i < 100000; i++)
	{
		fout << bubbleSorted[i] << endl;
	}
	fout.close();

	clock_t time8;
	time8 = clock();

	

	secondSort.sort(mergeSorted, 0, 100000);

	mergeComp = secondSort.getComparisonNum();
	mergeSwap = secondSort.getSwapNum();

	fout.open("sortedMerge100000");

	fout << "Merge sort with " << 100000 << " items:" << endl;
	fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;

	time8 = clock() - time8;
	fout << "This took " << ((float)time8/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 100000; i++)
	{
		fout << mergeSorted[i] << endl;
	}
	fout.close();

	clock_t time9;
	time9 = clock();

	

	thirdSort.sort(radixSorted, 100000, 7);

	radixComp = thirdSort.getComparisonNum();
	radixSwap = thirdSort.getSwapNum();

	fout.open("sortedRadix100000");

	fout << "Radix Sort with " << 100000 << " items:" << endl;
	fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;

	time9 = clock() - time9;
	fout << "This took " << ((float)time9/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 100000; i++)
	{
		fout << radixSorted[i] << endl;
	}
	fout.close();

	secondSort.reset();
	delete[] bubbleSorted;
	delete[] mergeSorted;
	delete[] radixSorted;



	fin1.open("sortedData1000000");
	fin2.open("sortedData1000000");
	fin3.open("sortedData1000000");
	
	bubbleSorted = new int[1000000];
	mergeSorted = new int[1000000];
	radixSorted = new int[1000000];
	
	for(int i = 0; i < 1000000; i++)
	{
		fin1 >> bubbleSorted[i];
		fin2 >> mergeSorted[i];
		fin3 >> radixSorted[i];
	}

	fin1.close();
	fin2.close();
	fin3.close();

	

	clock_t time10;
	time10 = clock();

	

	firstSort.sort(bubbleSorted, 1000000);

	bubbleComp = firstSort.getComparisonNum();
	bubbleSwap = firstSort.getSwapNum();

	fout.open("sortedBubble1000000");

	fout << "Bubble Sort with " << 1000000 << " items:" << endl;
	fout << bubbleComp << " comparisons with " << bubbleSwap << " swaps." << 	endl;

	time10 = clock() - time10;
	fout << "This took " << ((float)time10/CLOCKS_PER_SEC) << " seconds." << 	endl;
	
	for(int i = 0; i < 1000000; i++)
	{
		fout << bubbleSorted[i] << endl;
	}
	fout.close();

	clock_t time11;
	time11 = clock();

	

	secondSort.sort(mergeSorted, 0, 1000000);

	mergeComp = secondSort.getComparisonNum();
	mergeSwap = secondSort.getSwapNum();

	fout.open("sortedMerge1000000");

	fout << "Merge sort with " << 1000000 << " items:" << endl;
	fout << mergeComp << " comparisons with " << mergeSwap << " swaps." << endl;

	time11 = clock() - time11;
	fout << "This took " << ((float)time11/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 1000000; i++)
	{
		fout << mergeSorted[i] << endl;
	}
	fout.close();

	clock_t time12;
	time12 = clock();

	

	thirdSort.sort(radixSorted, 1000000, 7);

	radixComp = thirdSort.getComparisonNum();
	radixSwap = thirdSort.getSwapNum();

	fout.open("sortedRadix1000000");

	fout << "Radix Sort with " << 1000000 << " items:" << endl;
	fout << radixComp << " comparisons with " << radixSwap << " swaps." << endl;

	time12 = clock() - time12;
	fout << "This took " << ((float)time12/CLOCKS_PER_SEC) << " seconds." << 	endl;

	for(int i = 0; i < 1000000; i++)
	{
		fout << radixSorted[i] << endl;
	}
	fout.close();

	secondSort.reset();
	delete[] bubbleSorted;
	delete[] mergeSorted;
	delete[] radixSorted;
	
}





