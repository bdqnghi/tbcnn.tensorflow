/*
 * CuttingOfRod.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: AVINASH
 */

#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

#define TOTAL_POSSIBILITIES 8

int rodSizes[TOTAL_POSSIBILITIES] = {1,2,3,4,5,6,7,8};
int benefits[TOTAL_POSSIBILITIES] = {1,5,8,9,10,17,17,20};

//
//Tested
//Skipped Checking Boundary Conditions
//

int CuttingOfRod(int size){
	int maxFromSubset;
	int maxBenefit =0;
	int end = 0;
	while(size >= rodSizes[end] && end < TOTAL_POSSIBILITIES){
		end++;
	}

	for(int counter=0;counter < end;counter++){
		maxFromSubset = benefits[counter] + CuttingOfRod(size - rodSizes[counter]);
		if(maxBenefit < maxFromSubset){
			maxBenefit = maxFromSubset;
		}
	}
	return maxBenefit;
}

//int main(){
//	cout << "1 ->" << CuttingOfRod(1) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "2 ->" << CuttingOfRod(2) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "3 ->" << CuttingOfRod(3) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "4 ->" << CuttingOfRod(4) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "5 ->" << CuttingOfRod(5) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "6 ->" << CuttingOfRod(6) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "7 ->" << CuttingOfRod(7) << endl;
//	cout << "==============================================================================" << endl;
//	cout << "8 ->" << CuttingOfRod(8) << endl;
//	cout << "==============================================================================" << endl;
//}

