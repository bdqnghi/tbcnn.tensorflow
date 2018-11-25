
void choosePivot(DataType theArray[], int first, int last);



void partition(DataType theArray[],
               int first, int last, int& pivotIndex)
{
   
   choosePivot(theArray, first, last);
   DataType pivot = theArray[first];     

   
   int lastS1 = first;           
   int firstUnknown = first + 1; 
                                 

   
   for (; firstUnknown <= last; ++firstUnknown)
   {  
      

      
      if (theArray[firstUnknown] < pivot)
      {  
         ++lastS1;
         swap(theArray[firstUnknown], theArray[lastS1]);
      }  

      
   }  

   
   swap(theArray[first], theArray[lastS1]);
   pivotIndex = lastS1;
}  


void quicksort(DataType theArray[], int first, int last)
{
   int pivotIndex;

   if (first < last)
   {  
      partition(theArray, first, last, pivotIndex);

      
      quicksort(theArray, first, pivotIndex-1);
      quicksort(theArray, pivotIndex+1, last);
   }  
}  
