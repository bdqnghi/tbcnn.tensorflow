//============================================================================
// Name        : radix-sort.cpp
// Author      : Alan Villarreal, Christopher Spear, Sidian Wu
// Date        : 02/14/13
// Copyright   : what
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <vector>
#include <cmath>

void RadixSort::sort(int a[], int size)
{
	int temp;
	int m=0;
	bool done = false;
	int digit = 0;
	std::vector<std::vector<int> >buckets;
	buckets.resize(10);

	while(!done){
		done = true;
		//Determine which bucket each element should enter
		for(int j=0;j<size;j++){
			temp=(int)((a[j])/pow(10.0,digit))/*%10*/;
			if(temp) done = false;
			temp %= 10;
			buckets[temp].push_back((a[j]));
		}
		//Transfer results of buckets back into main array
		for(int k=0;k<10;k++){
			for(int l=0; l<buckets[k].size();l++){
				a[m]=buckets[k][l];
				m++;
			}
			//Clear previous bucket
			buckets[k].clear();
		}
		m=0;
		digit ++;
	}
	buckets.clear();
}
