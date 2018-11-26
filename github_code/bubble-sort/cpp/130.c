/***************************************************************************
 *
 *  Sorting algorithms and couting work 
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides general structs and stuff for main
 */

#ifndef __MAIN_H
#define __MAIN_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 *  Structs to accumulate some stats about our sorting
 */
struct SortStats {
	unsigned long int compares = 0;  // How many *compares* a sort does
	unsigned long int moves = 0;     // How many *moves/swaps* a sort does
	int comparesPct = 0;
	int movesPct = 0;
	double sortTime = 0.0;          // Time given sort took to execute
	int sortTimePct = 0;            // Percentage of time against Bubble Sort benchmark
};

struct SortingStats {
	SortStats bubblesort;
	SortStats insertionsort;
	SortStats mergesort;
	SortStats quicksort;
};

/**
 *  Print out a single sorting stats struct
 */
void print_SortingStats( SortingStats * stats )
{
	if( stats->bubblesort.compares )
	{
		stats->bubblesort.comparesPct = 
			100 * stats->bubblesort.compares / stats->bubblesort.compares;
		stats->insertionsort.comparesPct = 
			100 * stats->insertionsort.compares / stats->bubblesort.compares;
		stats->mergesort.comparesPct = 
			100 * stats->mergesort.compares / stats->bubblesort.compares;
		stats->quicksort.comparesPct = 
			100 * stats->quicksort.compares / stats->bubblesort.compares;
	}

	if( stats->bubblesort.moves )
	{
		stats->bubblesort.movesPct = 
			100 * stats->bubblesort.moves / stats->bubblesort.moves;
		stats->insertionsort.movesPct = 
			100 * stats->insertionsort.moves / stats->bubblesort.moves;
		stats->mergesort.movesPct = 
			100 * stats->mergesort.moves / stats->bubblesort.moves;
		stats->quicksort.movesPct = 
			100 * stats->quicksort.moves / stats->bubblesort.moves;
	}

	if( stats->bubblesort.sortTime )
	{
		stats->bubblesort.sortTimePct = 
			100 * stats->bubblesort.sortTime / stats->bubblesort.sortTime;
		stats->insertionsort.sortTimePct = 
			100 * stats->insertionsort.sortTime / stats->bubblesort.sortTime;
		stats->mergesort.sortTimePct = 
			100 * stats->mergesort.sortTime / stats->bubblesort.sortTime;
		stats->quicksort.sortTimePct = 
			100 * stats->quicksort.sortTime / stats->bubblesort.sortTime;
	}

	cout << fixed;
	cout << "   [#] Sorting stats dump - percent is vs. BS as the benchmark: " << endl;
	cout << setw(26) << "        Sort algorithm -- " 
			<< setw(21) << right << "Compares         : " 
			<< setw(21) << right << "Moves         : "
			<< setw(10) << right << "Sort Time (sec)" << endl;
	cout << setw(26) << left << "    [#] Bubble sort    -- " 
			<< setw(10) << right << stats->bubblesort.compares 
			<< " (" << setw(4) << stats->bubblesort.comparesPct << "%)" << " : " 
			<< setw(10) << right << stats->bubblesort.moves
			<< " (" << setw(4) << stats->bubblesort.movesPct << "%)" << " : "
			<< setw(10) << right << stats->bubblesort.sortTime
			<< " (" << setw(4) << stats->bubblesort.sortTimePct << "%)" << endl;
	cout << setw(26) << left << "    [#] Insertion sort -- " 
			<< setw(10) << right << stats->insertionsort.compares 
			<< " (" << setw(4) << stats->insertionsort.comparesPct << "%)" << " : " 
			<< setw(10) << right << stats->insertionsort.moves
			<< " (" << setw(4) << stats->insertionsort.movesPct << "%)" << " : "
			<< setw(10) << right << stats->insertionsort.sortTime
			<< " (" << setw(4) << stats->insertionsort.sortTimePct << "%)" << endl;
	cout << setw(26) << left << "    [#] Merge sort     -- " 
			<< setw(10) << right << stats->mergesort.compares 
			<< " (" << setw(4) << stats->mergesort.comparesPct << "%)" << " : " 
			<< setw(10) << right << stats->mergesort.moves
			<< " (" << setw(4) << stats->mergesort.movesPct << "%)" << " : "
			<< setw(10) << right << stats->mergesort.sortTime
			<< " (" << setw(4) << stats->mergesort.sortTimePct << "%)" << endl;
	cout << setw(26) << left << "    [#] Quick sort     -- " 
			<< setw(10) << right << stats->quicksort.compares
			<< " (" << setw(4) << stats->quicksort.comparesPct << "%)" << " : " 
			<< setw(10) << right << stats->quicksort.moves
			<< " (" << setw(4) << stats->quicksort.movesPct << "%)" << " : "
			<< setw(10) << right << stats->quicksort.sortTime
			<< " (" << setw(4) << stats->quicksort.sortTimePct << "%)" << endl;
    cout << scientific;
}

#endif
