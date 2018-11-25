#include "InsertionSort.h"
#include "VectorSorter.h"


InsertionSort::InsertionSort(string name): VectorSorter(name){}


InsertionSort::~InsertionSort() {}




void InsertionSort::run_sort_algorithm() throw (string)
{
	
	int i,j;
	for(i=1; i<size; i++)
	 {
	     j=i;
	     Element smallest =data[i];
	     while (j>0)
	     {

	    	   if(smallest<data[j-1])
	    	   {
	    		   compare_count++;
	    		   data[j]=data[j-1];
	    		   move_count++;
	    		   j--;
	    	   }
	    	   else
	    	   {
	    		   compare_count++;
	    		   break;
	    	   }
	     }
	     if(data[j].get_value()!=smallest.get_value())
	     {
	    	 data[j]=smallest;
	    	 move_count++;
	     }
	 }
}
