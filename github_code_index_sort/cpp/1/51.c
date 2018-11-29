#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


void printArray( int numElements, int * array )
{
	for( int i = 0; i < numElements; i++ )
	{
		printf( "%d ", array[i] );
	}
	printf( "\n" );
}

void insertIntoArray( int numElements, int * array )
{
	int element = array[ numElements - 1 ];
	int elementPosition = numElements - 1;
	while( array[ elementPosition - 1 ] > element && elementPosition != 0 )
	{
		array[ elementPosition ] = array[ elementPosition - 1 ];
		elementPosition--;
		printArray( numElements, array );
	}

	array[ elementPosition ] = element;
	printArray( numElements, array );

}

int main() 
{
	int numElements;
	int array[1001];

	//	Get elements
	cin >> numElements;
	for( int i = 0; i < numElements; i++ )
	{
		cin >> array[i];
	}

	insertIntoArray( numElements, array );

    return 0;
}
