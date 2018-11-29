// Fun with sorting- Bubble Sort
// Lab 10: CIS 1144
// Author: Seth Miller

package sortingPackage;

// import random
import java.util.Random;

public class FunWithSorting
{
	public static void print (int [] n)
	// TASK: Displays an array
	{
		for ( int i = 0; i < n.length; i++ )
			System.out.print( n[i] + " " );
		System.out.println( );
		
	}// end of print method
	
	public static void sort( int [] numbers, int array_Size )
	// TASK: Sort array numbers using bubble-sort algorithm
	{
		int i, j, temp;
		int counter = 0;
		
		for ( i = (array_Size - 1); i >= 0; i-- )
		{
			for ( j = 1; j <= i; j++ )
			{
				if ( numbers[j-1] > numbers[j] )// Swap
				{
					temp = numbers[j-1];
					numbers[j-1] = numbers[j];
					numbers[j] = temp;
					counter++;
					
				}// end of if statement
				
			}// end of for loop with "j"
			
		}// end of for loop with "i"
		System.out.println(counter);
	}// end of sort method (bubble-sort)
	
	public static void main( String [] args )
	{
		int [] numArray = new int [ 100 ];
		Random rand = new Random( );
		
		for ( int i = 0; i < numArray.length; i++ )
		{
			numArray[i] = rand.nextInt( 1000 ) + 1;
		}
		
		print (numArray);
		sort(numArray, numArray.length);
		print (numArray);
		
	}// end of main
	
}// end of FunWithSorting