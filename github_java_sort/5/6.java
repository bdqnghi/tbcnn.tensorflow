import java.util.Arrays;


public class BubbleSort {
	static void bubbleSortFunction(int[]numList) {
		int n = numList.length; 
		int t = 0; 
		
		for(int i=0; i < n; i++) { 
			for(int j = 1; j < (n-i); j++ ) { 
				if(numList[j-1] < numList[j]) {
					
					
					t = numList[j-1];
					numList[j-1] = numList[j];
					numList[j] = t;
				}
			}
			System.out.println(Arrays.toString(numList)); 
		}
	}
	public static void main(String[]args) {
		int numList[] = {4, 5, 7, 9, 1, 3, 2, 6, 0, 8};
		System.out.println("List of Numbers");
		
		
		for(int i=0; i<numList.length; i++) {
			System.out.print(numList[i]+" ");
		}
		System.out.println(); 
		bubbleSortFunction(numList); 
		
		System.out.println("Sorted List of Numbers");
		for(int i=0; i<numList.length; i++) {
			System.out.print(numList[i]+" ");
		}
	}
}
