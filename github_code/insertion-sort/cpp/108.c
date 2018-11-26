#include "ShellSort.h"
using namespace std;


InsertionSortNS::LinkedList* ShellSortNS::ShellSort::sort(InsertionSortNS::LinkedList*inputList)
{
  cout<<"Sorting...";
  InsertionSortNS::LinkedList* listToSort=new InsertionSortNS::LinkedList();
  int largestGapSequence=0;
  for(int i=0; i<inputList->size(); i++)
    {
      listToSort->push_back(inputList->get(i));
    }
  for(int i=1; i<=listToSort->size();i++)
    {
      int possibleValue = pow(2,i)-1;//(2^i)-1 From Hibbard's recommended increments
      if(possibleValue>listToSort->size())
	{
	  largestGapSequence = i-1;
	  break;
	}
    }
  //if largestGapSequence equals Zero, then list is empty
  for(int i= largestGapSequence; i>0;i--)
    {
      listToSort=insertionSort(listToSort,pow(2,i)-1);
    }
  cout<<"Complete\n";
  return listToSort;
}


InsertionSortNS::LinkedList* ShellSortNS::ShellSort::insertionSort(InsertionSortNS::LinkedList *listToSort,int sortSize)
{
  InsertionSortNS::LinkedList* sortedList= new InsertionSortNS::LinkedList();
  for(int i=0; i<listToSort->size() + sortSize;)
    {
      InsertionSortNS::LinkedList* temp = subList(listToSort,sortSize,i);
      sortedList->merge(temp);
      i+=sortSize;
    }  
  for(int i=0;i<listToSort->size()+sortSize;)
    {
      sortedList=columnSort(sortedList,sortSize,i);
      i+=sortSize;
    }

  return sortedList;
}


InsertionSortNS::LinkedList* ShellSortNS::ShellSort::subList(InsertionSortNS::LinkedList* listToSort, int sortSize, int start)
{
  InsertionSortNS::LinkedList* temp = new InsertionSortNS::LinkedList();
  for(int i=0; i<sortSize; i++)
    {
      if(start<listToSort->size())
	temp->push_back(listToSort->get(start));
      start++;
    }
  return temp;
}

InsertionSortNS::LinkedList* ShellSortNS::ShellSort::columnSort(InsertionSortNS::LinkedList* listToSort, int sortSize, int start)
{
  InsertionSortNS::LinkedList* temp = new InsertionSortNS::LinkedList();
  for(int i=start; i<listToSort->size();)
    {     
      temp->push_back(listToSort->get(i));
      i+=sortSize;
    }
  temp = InsertionSortNS::InsertionSort::sort(*temp);
  for(int i=start, count =0; i<listToSort->size();count++)
    {
      listToSort->remove(i);
      listToSort->insert(i,temp->get(count));
      i+=sortSize;
    }
  return listToSort;
}
