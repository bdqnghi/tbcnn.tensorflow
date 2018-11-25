




#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include "quick.h"


int* createArray(std::ifstream& inputFile, int& eltCount)
{
  
  eltCount = std::distance(std::istream_iterator<int>(inputFile), std::istream_iterator<int>());
  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  
  int *numArray = new int[eltCount];

  
  int currentNum, eltNum = 0;
  inputFile >> currentNum;
  while (!inputFile.eof())
    {
      numArray[eltNum] = currentNum;
      eltNum++;
      inputFile >> currentNum;
    }

  return numArray;
}

void writeArray(std::ofstream& outputFile, int* array, int eltCount)
{
  for (int i = 0; i < eltCount; i++)
    {
      outputFile << array[i] << " ";
    }

  return;
}

void quickSort(int* a, int p, int r)
{
  if (p < r)
    {
      int q = pivot(a, p, r);
      quickSort(a, p, q - 1);
      quickSort(a, q + 1, r);
    }
  return;
}

int pivot(int* a, int p, int r)
{
  int x = a[r], i = p - 1, temp;
  for (int j = p; j < r; j++)
    {
      if (a[j] <= x)
	{
	  i++;
	  temp = a[i];
	  a[i] = a[j];
	  a[j] = temp;
	}
    }
  i++;
  temp = a[i];
  a[i] = a[r];
  a[r] = temp;
  return i;
}
