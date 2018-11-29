// ShellSort.cpp : Defines the entry point for the console application.
//


//
//  main.cpp
//  Shell Sort
//
//  Created by Jake Cordelli on 4/24/17.
//  Copyright � 2017 Jake Cordelli. All rights reserved.
//  Code Assistance from http://www.sanfoundry.com/cplusplus-program-implement-shell-sort/
//  Implemented and modified by Jake Cordelli
#include "stdafx.h"
#include <iostream>


using namespace std;

//Print values
//This simply prints the array
void print_ar(int ar[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}

//Shell sort function
void shell_sort(int ar[], int size)
{
	int j;

	//Narrow the array by 2 everytime
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; ++i)
		{
			int temp = ar[i];
			for (j = i; j >= gap && temp < ar[j - gap]; j -= gap)
			{
				ar[j] = ar[j - gap];
			}
			ar[j] = temp;
		}
	}
}


int main(int argc, const char * argv[]) {

	//Elements in the array that need to be sorted 
	int ar[] = { 1, 4, 16, 30, 29, 18, 100, 2, 43, 1 };

	//Prints initial array 
	cout << "Intial Array : ";
	print_ar(ar, 10);

	//Shell sort function called 
	shell_sort(ar, 10);

	//Prints sorted array 
	cout << "Sorted Array : ";
	print_ar(ar, 10);

	return 0;
}



