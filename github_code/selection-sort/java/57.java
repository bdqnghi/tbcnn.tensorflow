//import java.util.Scanner;

public class JavaSelectionSort {
		
	public static final int MAXSIZE = 100000;
	public static int[] nums = new int[MAXSIZE];

	public static void swap (int pos1, int pos2) {
		
		int temp = nums[pos1];
		nums[pos1] = nums[pos2];
		nums[pos2] = temp;
		
	} // end swap

	public static void selectionSort () {
		
		int endOfSortedRegion;
		int j;
		int minLocation;
		
		for (endOfSortedRegion = 0; endOfSortedRegion < MAXSIZE - 1; endOfSortedRegion++) {
			
			minLocation = endOfSortedRegion;
			
			for (j = endOfSortedRegion + 1; j < MAXSIZE; j++)
				
				if (nums[j] < nums[minLocation])
					minLocation = j;

				
			if (minLocation != endOfSortedRegion)
				swap(minLocation, endOfSortedRegion);
		}

	} // end selectionSort

	public static void printNums () {
		
		int i;
		
		for (i = 0; i < MAXSIZE; i++)
			System.out.println(nums[i]);
		
	} // end printNums

	public static void main(String[] args) {
		
		//Scanner input = new Scanner(System.in);
		
		int i;
		//System.out.println("Please enter " +  MAXSIZE + " integers, in any order: ");
		
		for (i = 0; i < MAXSIZE; i++) {
			//System.out.print("number " + ( i + 1) + ":");
			nums[i] = (int)(Math.random()*MAXSIZE);
		}
		
		long start = System.currentTimeMillis();	
		selectionSort();
		long finish = System.currentTimeMillis();
		System.out.println("\nThe array in order:");
		//printNums();
		System.out.println("Your sort took " + (finish - start) + " msecs." );


		
	} // end main



}
