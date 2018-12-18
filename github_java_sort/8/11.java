package datastructure;

public class QuickSortJava {

	int partition(int arr[], int left, int right)
	{
		
		
	      int i = left, j = right;
	      
	      int tmp;
	      
	      
	      int pivot = arr[(left + right) / 2];
	     
	      while (i <= j) {
	            while (arr[i] < pivot)
	            {
	                  i++;
	            }
	            while (arr[j] > pivot)
	            {
	                  j--;
	            }
	            if (i <= j) {
	                  tmp = arr[i];
	                  arr[i] = arr[j];
	                  arr[j] = tmp;
	                  i++;
	                  j--;
	            }
	      }
	     
	      return i;
	}
	 
	int[] quickSort(int arr[], int left, int right) {
		
	      int index = partition(arr, left, right);
	      
	      if (left < index - 1)
	            quickSort(arr, left, index - 1);
	      if (index < right)
	            quickSort(arr, index, right);
	      
	      return arr;
	}
	
	public static void main(String[] args) {
		int a[]={2,1,3,4,5};
		
		
		int [] aa=new QuickSortJava().quickSort(a,0,4);
		for(int k:aa)
		{
			System.out.print(k+" ");
		}
	}
}
