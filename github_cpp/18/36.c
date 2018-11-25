

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


		
		if(cut > max){
			max = cut;
		}
	}
	
	return max;
}

int maxrev_DP(int* price, int* table, int i, int n){


	if (i==0){
		return 0;
	}

	if(i==1){
		return price[i-1];
	}

	
	if(table[i-1] != -1){
		return table[i-1];
	}

	int max = 0;

	for(int j=1; j < (i+1); j++){

		int cut = price[j-1] + maxrev_DP(price, table, i-j, n);

		
		if(cut > max){
			max = cut;
		}
	}

	
	table[i-1] = max;

	
	return max;
}



int main(int argc, char* argv[]) {	

	
	if (argc != 2){
		cout << "Invalid Arguments (" << argc << "). Need [directions] [filetype] -- Exiting." << endl;
		return 1;
	}

	int n = stoi(argv[1]);

	
	if (n < 2){

		if (n==1){
			cout << "List is sorted, but only has one element in it" << endl;
		} else {
			cout << "List has no elements in it. Change list size. " << endl;
		}
		return 0;
	}

	
	int * price = new int[n];
	unsigned long seed = time(0);
	srand(int(seed));

	
	price[0] = rand() % 100;

	
	int * table = new int[n];

	

	
	for(int i = 1; i < n; i++){

		
		price[i] = rand() % 100 + price[i-1];
		table[i] = -1;
		
	}

	
	cout << "running rev_recursive with n = " << n << endl;
	clock_t start = clock();
	int maxRevRecurs = maxrev_recursive(price, n, n);
	clock_t end = clock();
	cout << "Max revenue recursive: " << maxRevRecurs << endl;
	double solveTime  = (double)(end-start) / CLOCKS_PER_SEC;
    cout << "Solution found in " << solveTime << " seconds" << endl << endl;

	
	cout << "running rev_dynprogr with n = " << n << endl;
	clock_t startDP = clock();
	int maxRevDP = maxrev_DP(price, table, n, n);
	clock_t endDP = clock();

    double solveTimeDP  = (double)(endDP-startDP) / CLOCKS_PER_SEC;
	cout << "Max revenue DP: " << maxRevDP << endl;
	cout << "Solution found in " << solveTimeDP << " seconds" << endl;

}


