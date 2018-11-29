
import java.util.Random;

/**
 * @version 22-02-2015
 * @author IvanLiljeqvist
 * 
 * Class representing quicksort - an algorithm for used for sorting.
 *
 */
public class QuickSort implements IntSorter{
	
	/* sorting mode of this class */
	private SortMode mode;
	private Random rand;
	/* size at which insertion sort should be run instead of quick sort.*/
	private int arraySizeAtWhichRunInsertionSort;
	/* code to not use insertion sort. */
	private final int DONT_RUN_INSERTION_SORT=-1;
	
	private InsertionSort is;
	
	/**
	 * Inititalizes the class.
	 * Sets mode to FIXED. This means that the pivotal point will by default be set to the first element.
	 */
	public QuickSort(){
		this.mode=SortMode.FIXED;
		rand=new Random();
		this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		is=new InsertionSort();
	}
	
	/**
	 * Initializes the class and sets the sort mode of the sorting to parameter m.
	 * The insertion sort will not be enabled with this constructor. 
	 * Use the constructor where you set the array size that will trigger the insertion sort instead.
	 * @param m - the sort mode.
	 */
	public QuickSort(SortMode m){
		this.mode=m;
		rand=new Random();
		this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		is=new InsertionSort();
	}
	
	/**
	 * Initializes the class and sets the mode of the sorting to parameter m.
	 * Sets the array size when the insertion sort should start running.
	 * Insertion sort will only  be enabled if the array size at which it should run is >=2 and if the mode supports it.
	 * @param m - the sort mode.
	 * @param arraySizeAtWhichRunInsertionSort - at which size of array to switch to insertion sort.
	 */
	public QuickSort(SortMode m, int arraySizeAtWhichRunInsertionSort){
		this.mode=m;
		rand=new Random();
		is=new InsertionSort();
		
		//check so that the mode supports insertion sort
		if((m==SortMode.FIXED_AND_INSERTION || m==SortMode.RANDOM_AND_INSERTION) && (arraySizeAtWhichRunInsertionSort>=2)){
			this.arraySizeAtWhichRunInsertionSort=arraySizeAtWhichRunInsertionSort;
		}
		else{
			this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		}
	}

	/**
	 * Sorts an array of integers.
	 * @param the array you want to be sorted.
	 */
	public void sort(int[] v) {
		
		//if more than one element - sort.
		if(v.length>1){
			sort(v,0,v.length-1);
		}
	}
	
	/**
	 * Sorts an array within an area than is bounded by the parameters low and high.
	 * 
	 * @param v - the array you want to sort.
	 * @param low - the lower boundary of the area you want to sort.
	 * @param high - the higher boundary of the area you want to sort.
	 */
	
	private void sort(int []v, int low, int high){
		
		int subArraySize=high-low;
		//if low less or equal high
		if(subArraySize<=0){
			return;
		}
		
		//if the array size is small enough for insertion sort and insertion sort is enabled - use it
		if(subArraySize<=this.arraySizeAtWhichRunInsertionSort && this.arraySizeAtWhichRunInsertionSort!=this.DONT_RUN_INSERTION_SORT){
			is.sort(v,low,high);
			return;
		}
		//use quick sort instead otherwise
		else{
			
			int pivotIndex;
			//if fixed pivotal point
			if(this.mode==SortMode.FIXED || this.mode==SortMode.FIXED_AND_INSERTION){
				pivotIndex=low;
			}
			//else randomize pivotal point
			else{
				pivotIndex=rand.nextInt(high-low+1)+low;
			}
			pivotIndex=low;
			
			//extract the pivot value
			int pivot=v[pivotIndex];

			int indexFromLeft = low;
			int indexFromRight = high;
			
		    //Go from both sides
		    while (indexFromLeft <= indexFromRight) {
		      // Keep looking for an index from left that is higher than pivot
		      // Searching from the left
		      while (v[indexFromLeft] < pivot) {
		    	 indexFromLeft++;
		      }
		      // Keep looking for an index from right that is lower than pivot
		      // Searching from the right
		      while (v[indexFromRight] > pivot) {
		    	  indexFromRight--;
		      }

		      // Now we've found two index that we can switch. One from the right that is lower, and one from the left that is higher
		      if (indexFromLeft <= indexFromRight) {
		        swap(v,indexFromLeft, indexFromRight);
		        indexFromLeft++;
		        indexFromRight--;
		      }
		    }
		    
		    //now recursively sort the left sub array
		    if (low < indexFromRight)
		      sort(v,low, indexFromRight);
		    //recursively sort right sub array
		    if (indexFromLeft < high)
		      sort(v,indexFromLeft, high);
		}
		
		
	}
	
	/**
	 * Returns the sort mode of a QuickSort instance.
	 */
	public SortMode getSortMode(){
		return this.mode;
	}
	
	/**
	 * Returns the array size at which this instance of QuickSort will turn on insertion sort.
	 */
	public int getArraySizeAtWhichRunInsertionSort(){
		return this.arraySizeAtWhichRunInsertionSort;
	}
	
	/**
	 * Swaps the elements at indexes specified by the parameters.
	 * 
	 * @param v - array in which to swap the elements.
	 * @param i1 - index of the first element.
	 * @param i2 - index of the second element.
	 */
	private void swap(int []v, int i1, int i2){
		int temp=v[i1];
		v[i1]=v[i2];
		v[i2]=temp;
	}

}
