
import java.util.Random;


public class QuickSort implements IntSorter{
	
	
	private SortMode mode;
	private Random rand;
	
	private int arraySizeAtWhichRunInsertionSort;
	
	private final int DONT_RUN_INSERTION_SORT=-1;
	
	private InsertionSort is;
	
	
	public QuickSort(){
		this.mode=SortMode.FIXED;
		rand=new Random();
		this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		is=new InsertionSort();
	}
	
	
	public QuickSort(SortMode m){
		this.mode=m;
		rand=new Random();
		this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		is=new InsertionSort();
	}
	
	
	public QuickSort(SortMode m, int arraySizeAtWhichRunInsertionSort){
		this.mode=m;
		rand=new Random();
		is=new InsertionSort();
		
		
		if((m==SortMode.FIXED_AND_INSERTION || m==SortMode.RANDOM_AND_INSERTION) && (arraySizeAtWhichRunInsertionSort>=2)){
			this.arraySizeAtWhichRunInsertionSort=arraySizeAtWhichRunInsertionSort;
		}
		else{
			this.arraySizeAtWhichRunInsertionSort=this.DONT_RUN_INSERTION_SORT;
		}
	}

	
	public void sort(int[] v) {
		
		
		if(v.length>1){
			sort(v,0,v.length-1);
		}
	}
	
	
	
	private void sort(int []v, int low, int high){
		
		int subArraySize=high-low;
		
		if(subArraySize<=0){
			return;
		}
		
		
		if(subArraySize<=this.arraySizeAtWhichRunInsertionSort && this.arraySizeAtWhichRunInsertionSort!=this.DONT_RUN_INSERTION_SORT){
			is.sort(v,low,high);
			return;
		}
		
		else{
			
			int pivotIndex;
			
			if(this.mode==SortMode.FIXED || this.mode==SortMode.FIXED_AND_INSERTION){
				pivotIndex=low;
			}
			
			else{
				pivotIndex=rand.nextInt(high-low+1)+low;
			}
			pivotIndex=low;
			
			
			int pivot=v[pivotIndex];

			int indexFromLeft = low;
			int indexFromRight = high;
			
		    
		    while (indexFromLeft <= indexFromRight) {
		      
		      
		      while (v[indexFromLeft] < pivot) {
		    	 indexFromLeft++;
		      }
		      
		      
		      while (v[indexFromRight] > pivot) {
		    	  indexFromRight--;
		      }

		      
		      if (indexFromLeft <= indexFromRight) {
		        swap(v,indexFromLeft, indexFromRight);
		        indexFromLeft++;
		        indexFromRight--;
		      }
		    }
		    
		    
		    if (low < indexFromRight)
		      sort(v,low, indexFromRight);
		    
		    if (indexFromLeft < high)
		      sort(v,indexFromLeft, high);
		}
		
		
	}
	
	
	public SortMode getSortMode(){
		return this.mode;
	}
	
	
	public int getArraySizeAtWhichRunInsertionSort(){
		return this.arraySizeAtWhichRunInsertionSort;
	}
	
	
	private void swap(int []v, int i1, int i2){
		int temp=v[i1];
		v[i1]=v[i2];
		v[i2]=temp;
	}

}
