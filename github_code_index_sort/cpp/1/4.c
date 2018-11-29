#include "InsertionSort.h"
#include "VectorSorter.h"
/**
 * Constructor.
 * @param name the name of the algorithm.
 */
//InsertionSort::InsertionSort(string name) : VectorSorter(name) {}
InsertionSort::InsertionSort(string name): VectorSorter(name){}

/**
 * Destructor.
 */
InsertionSort::~InsertionSort() {}

/**
 * Run the insertion sort algorithm.
 * @throws an exception if an error occurred.
 */
/*void InsertionSort::run_sort_algorithm() throw (string)
{
    **** Complete this member function. ****
	Element temp;
	int j;
	for(int i=1;i<size;i++)   // loop through all the element;
	{
		j=i;
		compare_count++;
		while(j>0 && data[j-1]>data[j])
		{
			compare_count++;
			temp=data[j];
			data[j]=data[j-1];
			move_count++;
			data[j-1]=temp;
			//move_count++;
			j--;
		}

	}

}*/

void InsertionSort::run_sort_algorithm() throw (string)
{
	//reference from http://stackoverflow.com/questions/5709637/c-vector-insertion-sort-algorithm-method-pass-vector-into-method
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
