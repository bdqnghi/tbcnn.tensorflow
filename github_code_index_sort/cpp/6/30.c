// Filename: radix.cpp
// Author: Johnathan Inkley
// Date: 2016 11 13
// Description: Definition for the radix sort function

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "radix.h"

int* createArray(std::ifstream& inputFile, int& eltCount)
{
  // First count elts in file
  eltCount = std::distance(std::istream_iterator<int>(inputFile), std::istream_iterator<int>());
  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  // Create blank array of correct size
  int *numArray = new int[eltCount];

  // Read numbers into array
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

int* countingSort(int* a, int k, int n, int exp)
{
  int ind, tot = 0, oldTot = 0, *b, *c;
  c = new int[k];
  b = new int[n];
  for (int i = 0; i < k; i++)
    {
      c[i] = 0;
    }
  for (int j = 0; j < n; j++)
    {
      ind = a[j]/exp - k * (a[j]/(k*exp));
      //      std::cout << "a is " << a[j] << " and ind is " << ind << std::endl;
      c[ind]++;
    }
  for (int i = 0; i < k; i++)
    {
      //      oldTot = c[i];
      //      c[i] = tot;
      //      tot += oldTot;
      tot += c[i];
      c[i] = oldTot;
      oldTot = tot;
    }
  for (int j = 0; j < n; j++)
    {
      ind = a[j]/exp - k * (a[j]/(k*exp));
      b[c[ind]] = a[j];
      c[ind]++;
    }
  delete[] c;
  return b;
}

int* radixSort(int* a, int k, int n)
{

  int max = a[0];
  for (int i = 1; i < n; i++)
    {
      if (a[i] > max)
	max = a[i];
    }
  int exp = 1, *b;
  while (exp <= max)
  {
      b = countingSort(a, k, n, exp);
      delete[] a;
      a = b;
      exp *= k;
  }
  return a;
}
