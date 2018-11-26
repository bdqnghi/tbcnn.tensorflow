import java.util.Arrays;
/*
 * CSCI 355 Project 1
 * Chai Grindean
 * 
 * BubbleSort
 * Time Complexity: O(n^2)
 */

public class BubbleSort {
	static void bubbleSortFunction(int[]numList) {
		int n = numList.length; //Set n to length of the numList
		int t = 0; //t = Temporary variable
		//Creating Loop, using i as a counter
		for(int i=0; i < n; i++) { //outer loop
			for(int j = 1; j < (n-i); j++ ) { //inner loop
				if(numList[j-1] < numList[j]) {
					//If the number on the left is < than number on the right
					//Switch places
					t = numList[j-1];
					numList[j-1] = numList[j];
					numList[j] = t;
				}
			}
			System.out.println(Arrays.toString(numList)); //Prints out each line to show the sorting process
		}
	}
	public static void main(String[]args) {
		int numList[] = {4, 5, 7, 9, 1, 3, 2, 6, 0, 8};
		System.out.println("List of Numbers");
		
		//Creating loop to print entire numList
		for(int i=0; i<numList.length; i++) {
			System.out.print(numList[i]+" ");
		}
		System.out.println(); //line break
		bubbleSortFunction(numList); //Call bubbleSortFunction to sort numList
		
		System.out.println("Sorted List of Numbers");
		for(int i=0; i<numList.length; i++) {
			System.out.print(numList[i]+" ");
		}
	}
}
