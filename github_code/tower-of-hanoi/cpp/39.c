/*
 * TowerOfHanoi.cpp
 *
 *  Created on: Jul 22, 2012
 *      Author: nitiraj
 */
#include <iostream>
#include "../objects/Stack.h"

using namespace std;

static void simpleSolveTowerOfHanoi(const char* from, const char* to, const char* temp, int numOfDisks)
{
	if(numOfDisks == 1)
	{
		cout << "(if)Putting disk " << numOfDisks << " from=" << from << " into " << to << endl;
	}
	else
	{
		// move disks in 'to' to 'temp' using 'from'
		// move 1 disk from 'from' to 'to'
		// move disks in 'temp' to 'to' using 'from'
		simpleSolveTowerOfHanoi(from,temp,to,numOfDisks-1);
		cout << "(else)Putting disk " << numOfDisks << " from=" << from << " into " << to << endl;
		simpleSolveTowerOfHanoi(temp,to,from,numOfDisks-1);
	}
}

static void solveTowerOfHanoi(Stack<int>& from, Stack<int>& to, Stack<int>& temp, int numOfDisks)
{
	if(numOfDisks == 1)
	{
		int next = from.pop();
		cout << "(if)Putting " << next << " from=" << from.getName() << " into " << to.getName() << endl;
		to.push(next);
	}
	else
	{
		// move disks in 'to' to 'temp' using 'from'
		// move 1 disk from 'from' to 'to'
		// move disks in 'temp' to 'to' using 'from'
		solveTowerOfHanoi(from,temp,to,numOfDisks-1);
		int next = from.pop();
		cout << "(else)Putting " << next << " from=" << from.getName() << " into " << to.getName() << endl;
		to.push(next);
		solveTowerOfHanoi(temp,to,from,numOfDisks-1);
	}
}

static void TowerOfHanoi(int numberOfDisks)
{
	try
	{
		Stack<int>original("original");
		Stack<int> final("final");
		Stack<int> temp("temp");
		// using my own stack so that I can use cout
		for( int i = numberOfDisks ; i > 0  ; i-- )
		{
			original.push(i);
		}

		cout << "Initially ::\n " << "original = " << original << "\nfinal = " << final << "\ntemp = " << temp << endl;

		solveTowerOfHanoi( original,final,temp,numberOfDisks);

		cout << "Finally ::\n " << "original = " << original << "\nfinal = " << final << "\ntemp = " << temp << endl;
	}
	catch( const char* msg)
	{
		cout << "Exception occured : " << msg << endl;
	}
}


static void SimpleTowerOfHanoi(int numberOfDisks)
{
	simpleSolveTowerOfHanoi( "original","final","temp",numberOfDisks);
}

