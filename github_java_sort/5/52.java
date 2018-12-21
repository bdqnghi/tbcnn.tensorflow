



package sortingPackage;


import java.util.Random;

public class FunWithSorting
{
	public static void print (int [] n)
	
	{
		for ( int i = 0; i < n.length; i++ )
			System.out.print( n[i] + " " );
		System.out.println( );
		
	}
	
	public static void sort( int [] numbers, int array_Size )
	
	{
		int i, j, temp;
		int counter = 0;
		
		for ( i = (array_Size - 1); i >= 0; i-- )
		{
			for ( j = 1; j <= i; j++ )
			{
				if ( numbers[j-1] > numbers[j] )
				{
					temp = numbers[j-1];
					numbers[j-1] = numbers[j];
					numbers[j] = temp;
					counter++;
					
				}
				
			}
			
		}
		System.out.println(counter);
	}
	
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
		
	}
	
}