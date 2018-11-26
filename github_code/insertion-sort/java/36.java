import java.io.*;		//import java.io package for input and out put

public class javaInsertionSort{ // creating main class

	public static void main(String a[]){	//Declearing the main function
	
		int i;		//Creating an integer type variable for loops using
		
		int array[] = {12,9,4,99,120,1,3,10,7,25};	//Creating a new Array
		
		System.out.println("       Java Insertion Sort\n\n");   
		System.out.println("Values Before the sort:\n");    
		for(i = 0; i < array.length; i++)	// craeting a for loop for printing the values of Array
		
		System.out.print( array[i]+"  ");
		
		System.out.println();
		
		sort(array, array.length); /* call to the function by passing the 
		value of Array and the length of Array*/  
		     
		System.out.print("Values after the sort:\n");    
		for(i = 0; i <array.length; i++)
		System.out.print(array[i]+"  ");
		System.out.println();   
		System.out.println("PAUSE");                 
	}

	public static void sort(int array[], int n){	/*Create a function and gets 
	the value of Array and the length of Array*/	
		for (int i = 1; i < n; i++){	//create a for loop for cheack the values of Array
			int j = i;
			int B = array[i];
			while ((j > 0) && (array[j-1] > B)){ /* Comparison Array Value */
			
				array[j] = array[j-1];
				
				j--;
				
			}
			
			array[j] = B;
			
		}
		
	}
	
}