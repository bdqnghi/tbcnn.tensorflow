/*
File: RodCutting.cpp

Author Henry Daniels-Koch
Date: 11/1/16

*/

#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string.h>

using namespace std;

int maxrev_recursive(int* price, int i, int n){

	if (i==0){
		return 0;
	}

	if(i==1){
		return price[i-1];
	}

	int max = 0;

	for(int j=1; j < (i+1); j++){
		int cut = price[j-1] + maxrev_recursive(price, i-j, n);


		//Best cut so far
		if(cut > max){
			max = cut;
		}
	}
	//Return max
	return max;
}

int maxrev_DP(int* price, int* table, int i, int n){


	if (i==0){
		return 0;
	}

	if(i==1){
		return price[i-1];
	}

	//Have already found this value before
	if(table[i-1] != -1){
		return table[i-1];
	}

	int max = 0;

	for(int j=1; j < (i+1); j++){

		int cut = price[j-1] + maxrev_DP(price, table, i-j, n);

		//Best cut so far
		if(cut > max){
			max = cut;
		}
	}

	//Store max for this cut
	table[i-1] = max;

	//Return max
	return max;
}



int main(int argc, char* argv[]) {	

	//Array size
	if (argc != 2){
		cout << "Invalid Arguments (" << argc << "). Need [directions] [filetype] -- Exiting." << endl;
		return 1;
	}

	int n = stoi(argv[1]);

	//Array has less than 2 elements and is already sorted
	if (n < 2){

		if (n==1){
			cout << "List is sorted, but only has one element in it" << endl;
		} else {
			cout << "List has no elements in it. Change list size. " << endl;
		}
		return 0;
	}

	//declare and allocate the array
	int * price = new int[n];
	unsigned long seed = time(0);
	srand(int(seed));

	//Set first price
	price[0] = rand() % 100;

	//Initialize with -1 for dynamic programming
	int * table = new int[n];

	/*price[0] = 1;
	price[1] = 5;
	price[2] = 8;
	price[3] = 9;
	price[4] = 19;
	price[5] = 17;
	price[6] = 17;
	price[7] = 20;
	price[8] = 24;
	price[9] = 30;*/

	//Populate the array with random data
	for(int i = 1; i < n; i++){

		//Generate random number from 0 to previous price
		price[i] = rand() % 100 + price[i-1];
		table[i] = -1;
		//cout << price[i] << endl;
	}

	//Recursion
	cout << "running rev_recursive with n = " << n << endl;
	clock_t start = clock();
	int maxRevRecurs = maxrev_recursive(price, n, n);
	clock_t end = clock();
	cout << "Max revenue recursive: " << maxRevRecurs << endl;
	double solveTime  = (double)(end-start) / CLOCKS_PER_SEC;
    cout << "Solution found in " << solveTime << " seconds" << endl << endl;

	//DP
	cout << "running rev_dynprogr with n = " << n << endl;
	clock_t startDP = clock();
	int maxRevDP = maxrev_DP(price, table, n, n);
	clock_t endDP = clock();

    double solveTimeDP  = (double)(endDP-startDP) / CLOCKS_PER_SEC;
	cout << "Max revenue DP: " << maxRevDP << endl;
	cout << "Solution found in " << solveTimeDP << " seconds" << endl;

}


