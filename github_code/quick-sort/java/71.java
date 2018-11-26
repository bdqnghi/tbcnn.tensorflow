

import java.lang.*;
import java.util.Arrays;
import java.util.Random;
public class quicksort {
	
private quicksort() {}
	
	
	private static int[] quicksort(int [] a, int i, int j){
		 if (j > i)
	      { 
	        int p_rand = (int)(Math.random()*(j-i) + i);
	        int p = partition(a, i, j, p_rand);
	        quicksort(a, i, p-1);
	        quicksort(a, p+1, j); 
	     }
	      return (int[]) a;
	}
	private static int partition(int a[], int start, int end, int pivot)
	{
		int value = a[pivot];
		swap(a,pivot,end);
		int val = start;
		for (int i = start; i < end; i++){
			if ((a[i])<=(value))
			{
				swap(a,i,val);
				val++;
			}	
		}
		swap(a,end,val);
		return val;		
	}
	public static String toString (int [] a){
		String t = "[";
		for (int i=  0; i < a.length; i++)
			t += " " + a[i];
		t += "]";
		return t;
	}
	private static int[] generateArray(int i) {
		// TODO Auto-generated method stub
		int [] array = new int[i];
		Random rand = new Random();
		for (int j =0; j<array.length;j++){
			array[j]=rand.nextInt();
		}
		return array;
	}
	public static void quicksort(int[] a){
		a = quicksort(a, 0, a.length -1);
	}
	private static void swap(int [] a, int i, int j){
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;	
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int arraySize = 100000;
		int [] test = generateArray(arraySize);
		//testing for 1 
		long startTime = System.currentTimeMillis();
		System.out.println("QuickSort start time is " + startTime + " milliseconds");
		quicksort(test);
		long endTime = System.currentTimeMillis();
		System.out.println("QuickSort end time is " + endTime + " milliseconds");
		System.out.println("QuickSort took to complete on first call quicksort: " +(endTime-startTime) + " seconds\n");
		
		//testing for 2 quicksort call
		startTime = System.currentTimeMillis();
		System.out.println("QuickSort start time is " + startTime + " milliseconds");
		quicksort(test);
		endTime = System.currentTimeMillis();
		System.out.println("QuickSort end time is " + endTime + " milliseconds");
		System.out.println("QuickSort took to complete on second call quicksort: " +(endTime-startTime) + " seconds");
		
		//testing quicksort fucntion. 
		//int[] a = {5 1,,100,32,43,67,89,0,45,76};
	    //System.out.println("Unsorted: " +  quicksort.toString(a));
	    //quicksort.sort(a);
	    //System.out.println("Sorted:   " + quicksort.toString(a));
	    //quicksort.sort(a);
	  }
	}      

