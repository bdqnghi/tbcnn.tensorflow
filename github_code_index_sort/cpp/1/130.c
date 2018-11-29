// InsertionSort_Cpp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "InsertionSort_Cpp.h"
/*
 Funkcja sortuj�ca tablic� przekazan� jako wska�nik zgodnie z algorytmem insertion sort
 Wersja 1.0
 Argumenty:
 int *arrayToSort - wska�nik na tablic�, kt�ra b�dzie sortowana
 int arraySize - d�ugo�� tablicy, kt�ra b�dzie sortowana

 Warto�� zwracana :
 Funkcja sortuje elementy w tablicy przekazanej jako wska�nik.
 */
void _stdcall insertionSort(int* arrayToSort, int arraySize)
{
	int keyValue, counter;
	for (int i = 1; i < arraySize; i++)
	{
		keyValue = arrayToSort[i];
		for (counter = i - 1; counter >= 0 && arrayToSort[counter] > keyValue; counter--)
		{
			arrayToSort[counter + 1] = arrayToSort[counter];
		}
		arrayToSort[counter + 1] = keyValue;
	}
}
/*
 Funkcja sprawdzaj�ca, czy tablica jest posortowana
 Wersja: 1.0

 Arguemtny:
 int arraySize - d�ugo�� tablicy, kt�ra b�dzie sprawdzana
 int *sortedArray - wska�nik na tablic�, kt�ra jest sprawdzana

 Warto�� zwracana:
 boolean - informacja czy tablica jest posortowana lub nie
 true - tablica jest posortowana
 false - tablica nie jest posortowana
 */

bool _stdcall checkIfSorted(int arraySize, int* sortedArray)
{
	for (int i = 0; i < arraySize - 1; i++)
	{
		if (sortedArray[i] > sortedArray[i + 1])
			return false;
	}
	return true;
}