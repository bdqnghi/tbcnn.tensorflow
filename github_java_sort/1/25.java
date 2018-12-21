package algo.cormen.javacode.src;


/**
 * Algorithm to demonstrate INSERTION-SORT on a set of data
 * @author Rishu
 *
 */

/**
 * pseudocode: INSERTION-SORT(A)  
 * 
 * Input: A[1..n] - an array of integers
 * Output: Sorted Array such that A[1]<=A[2]<=A[3]....A[n]
 * Begin:
 * 		for j<- 2 to n do
 * 			key<- A[j]
 * 
 *  // insert A[j] into the sorted sequence A[1..j-1]
 *  
 *  	i<- (j-1)
 *  
 *  	while( i>0 and A[i]>key ) do
 *  
 *  		A[i+1] <- A[i]
 * 			i--
 * 
 *		A[i+1]<- key
 *
 * End
 * 
 * The Running Time of this algo is O(n^2) since every element in the array is calculated twice.
 *
 */
public class InsertionSortAlgo {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Integer[] A={5,2,4,6,1,3};  //Data set - Array A
		
		for(int i=1; i<A.length; i++){  // start picking up the data to compare
			
			int key=A[i];
			
			int j=i-1;   
			
			System.out.println("Key : "+key);  //printing the key values to understand the flow
			
			/*
			 * Compare condition/ sorting condition. Start from position 0 till the end and compare the A[j] and key value
			 */
			while(j>=0 && A[j]>key){
				
				A[j+1]=A[j];   // find the appropiate pos. and place the value
				
				j--;
			}
			
			A[j+1]=key;
			
			//Printing the array
			PrintArray(A);
			
		}
		
		
	}
	
	/*
	 * Method to display the Array in final order
	 */
	public static void PrintArray(Integer[] arr){
		
		for(int i=0; i<arr.length; i++){
			
			System.out.print(arr[i]+" ");
			
		}
		System.out.println("\n");
		
	}
}
