/*
 * Assignment #12: Compare sorting algorithms
 *
 * CMPE 180-92 Data Structures and Algorithms in C++
 * Department of Computer Engineering
 * R. Mak, Nov. 20, 2016
 */
#include "ShellSortSuboptimal.h"

/**
 * Default constructor.
 */
ShellSortSuboptimal::ShellSortSuboptimal() {}

/**
 * Destructor.
 */
ShellSortSuboptimal::~ShellSortSuboptimal() {}

/**
 * Get the name of this sorting algorithm.
 * @return the name.
 */
string ShellSortSuboptimal::name() const { return "Shellsort suboptimal"; }

/**
 * Run the suboptimal shellsort algorithm.
 * @throws an exception if an error occurred.
 */
void ShellSortSuboptimal::run_sort_algorithm() throw (string)
{
    /***** Complete this member function. *****/
	//source::http://www.programming-algorithms.net/article/41653/Shell-sort
	int g = size / 2;
while (g > 0) {
for (int i = 0; i < size - g; i++) { 
int j = i + g;
int tmp = array[j];
while (j >= g && tmp > array[j - g]) {
array[j] = array[j - g];
j -= g;
}
array[j] = tmp;
}
if (g == 2) { 

g = 1;

} else {

g =g/2;

}

}
return array;
}
}
