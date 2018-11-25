




#include <iostream>
#include <string>

using namespace std;


template<class ItemType>
void merge(ItemType theArray[], int first, int mid, int last, ItemType tempArray[])
{
   
   int first1 = first;            
   int last1 = mid;               
   int first2 = mid + 1;          
   int last2 = last;              
   
   
   
   int index = first1;            
   while ((first1 <= last1) && (first2 <= last2))
   {
      
      if (theArray[first1] <= theArray[first2])
      {
         tempArray[index] = theArray[first1];
         first1++;
      }
      else
      {
         tempArray[index] = theArray[first2];
         first2++;
      }  
      index++;
   }  
   
   
   while (first1 <= last1)
   {
      
      tempArray[index] = theArray[first1];
      first1++;
      index++;
   }  
   
   
   while (first2 <= last2)
   {
      
      tempArray[index] = theArray[first2];
      first2++;
      index++;
   }  
   
   
   for (index = first; index <= last; index++)
      theArray[index] = tempArray[index];
}  


template<class ItemType>
void mergeSort(ItemType theArray[], int first, int last, ItemType tempArray[])
{
   if (first < last)
   {
      
      int mid = (first + last) / 2; 
      
      
      mergeSort(theArray, first, mid, tempArray);
      
      
      mergeSort(theArray, mid + 1, last, tempArray);
      
      
      merge(theArray, first, mid, last, tempArray);
   }  
}  

template<typename ItemType>
void mergeSort(ItemType theArray[], int n)
{
	ItemType* tempArray = new ItemType[n];  
	mergeSort(theArray, 0, n-1, tempArray);
	delete [] tempArray;
}
