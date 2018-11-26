// Filename: bucket.cpp
// Author: Johnathan Inkley
// Date: 2016 11 13
// Description: Definition for the bucket sort function

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "bucket.h"

double* createArray(std::ifstream& inputFile, int& eltCount)
{
  // First count elts in file
  eltCount = std::distance(std::istream_iterator<double>(inputFile), std::istream_iterator<double>());
  inputFile.clear();
  inputFile.seekg(0, std::ios::beg);

  // Create blank array of correct size
  double *numArray = new double[eltCount];

  // Read numbers into array
  double currentNum;
  int eltNum = 0;
  inputFile >> currentNum;
  while (!inputFile.eof())
    {
      numArray[eltNum] = currentNum;
      eltNum++;
      inputFile >> currentNum;
    }

  return numArray;
}

void writeArray(std::ofstream& outputFile, double* array, int eltCount)
{
  for (int i = 0; i < eltCount; i++)
    {
      outputFile << array[i] << " ";
    }

  return;
}

double* bucketSort(double* a, int n)
{
  int ind;
  std::vector<double> *b;
  b = new std::vector<double>[n];
  for (int i = 0; i < n; i++)
    {
      ind = (int) n*a[i];
      b[ind].push_back(a[i]);
    }
  for (int i = 0; i < n; i++)
    {
      insertionSort(b[i]);
    }
  double* c;
  c = new double[n];
  int count = 0;
  for (int i = 0; i < n; i++)
    {
      for (std::vector<double>::iterator it = b[i].begin(); it != b[i].end(); it++)
	{
	  c[count] = *it;
	  count++;
	}
    }
  delete[] b;
  return c;
}

void insertionSort(std::vector<double>& vec)
{
  int m = vec.size();
  double current;
  for (int i = 1; i < m; i++)
    {
      current = vec[i];
      for (int j = 0; j < i; j++)
	{
	  if (current < vec[j])
	    {
	      for (int k = i - 1; k >= j; k--)
		{
		  vec[k+1] = vec[k];
		}
	      vec[j] = current;
	    }
	}
    }
  return;
}

