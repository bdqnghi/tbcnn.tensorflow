


	
	
	


#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Kruskal.h"
#include "Prim.h"

using namespace std;

string filePath = "C:\\Users\\Kaylee\\Desktop\\mst test.txt";			


int main()
{	
	
	
		
	double inputDouble;
	string currentInput;

	ifstream inFile(filePath, ios::binary);
	if (inFile.fail())
	{	
		cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		cin >> currentInput;
		exit(1);
	}

	inFile >> currentInput;
	inputDouble = atoi(currentInput.c_str());		

	
	int nValue = inputDouble;
	double* adjMatrix = new double[nValue * nValue];		
	string* nodeNamesMatrix = new string[nValue];

	Kruskal KrsukalAlgorithm(nValue);			
	Prim PrimAlgorithm(nValue);

	for (int pos = 0; pos < nValue; pos++)
	{	
		inFile >> nodeNamesMatrix[pos];
	}

	for (int pos = 0; pos < (nValue * nValue); pos++)
	{	
		inFile >> currentInput;
		inputDouble = atof(currentInput.c_str());		
		adjMatrix[pos] = inputDouble;
	}


	PrimAlgorithm.runPrim(nodeNamesMatrix, adjMatrix);

    return 0;
}

