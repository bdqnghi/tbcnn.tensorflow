/*
 * Luis Murillo
 * CS942 Discrete Structures
 * Fall 2014
 */
package discretesort;
import java.util.Scanner;
/**
 *
 * 
@author 11wElOaNcO11
 */

public class MatrixMultiplication
 {
    
   
	 public static void main(String[] args)
 	{

        		// TODO code application logic here
       
		 int m, n, p, q; 

        		 int sum = 0, c, d, k;
    
    /**
         * Description of above variables:
  
       * m and n is for the first m x n matrix
      
       * p and q is for the second p x q matrix; n = p
    
       * Note: Part of matrix multiplication definition is that the columns
       
       * of a certain matrix must match the rows of another certain matrix
         
       * Sum is like an accumulator initialized to zero
  
       * c, d, and k are indices for loops and array controls.
        
       */
       

	 // Create a Scanner Object for user input
       
	 Scanner in = new Scanner(System.in);
       
	 // Prompt user for input
       
	 System.out.println("Enter the number of rows and columns of first matrix");
     
	   // Ask user for input
     
	   System.out.print("Enter the number of rows here:");
       
	   m = in.nextInt();
        
	System.out.print("Enter the number of columns here:");
        n = in.nextInt();
        
        // Create a two-dimensional array with inputed values by user
        // This will be the first matrix
        int first[][] = new int[m][n];
        
        // Ask user to fill values for the first matrix
        System.out.println("Enter the elements of first matrix");
        
        for (c = 0; c < m; c++)
            for(d = 0; d < n; d++) {
                System.out.print("Enter the value at position " + (c+1) + (d+1) + " Value = ");
                first[c][d] = in.nextInt();
            }
        //Display results of first matrix construction
        System.out.println("This is your first matrix:");
        for (c = 0; c < m; c++)
            {
                for (d = 0; d < n; d++)
                {
                    System.out.print(first[c][d] + "\t");
                }
                System.out.print("\n");
            }
        //
        // Prompt for user input
        System.out.println("\nEnter the number of rows and columns of second matrix");
        // Ask user for input
        System.out.print("Enter the number of rows here:");
        p = in.nextInt();
        System.out.print("Enter the number of columns here:");
        q = in.nextInt();
        
        // Check for matrix compatibility dimensionality
        // See description of variables above       
        if (n != p)
            System.out.println("Matrices with entered dimensions cannot be multiplied.");
        else 
        {
            // Create a second two-dimensional array with user inputed values
            int second[][] = new int[p][q];
            // Create another two-dimensional array with number of rows from
            // first matrix and number of columns from second matrix
            int multiply[][] = new int[m][q];
            
            System.out.println("Enter the elements of second matrix");
            
            for(c = 0; c < p; c++)
                for(d = 0; d < q; d++) {
                    System.out.print("Enter the value at position " + (c+1) + (d+1) + " Value = ");
                    second[c][d] = in.nextInt();
                }
            // Display the results of second matrix construction
            System.out.println("This is your second matrix");
            for (c = 0; c < p; c++)
            {
                for (d = 0; d < q; d++)
                {
                    System.out.print(second[c][d] + "\t");
                }
                System.out.print("\n");
            }
            //          
            // Calculate the correct value for each entry in the multiply array
            // Which is, will be the product of the first and second arrays
            for(c = 0; c < m; c++)
            {
                for(d = 0; d < q; d++)
                {
                    for(k = 0; k < p; k++)
                    {
                        sum = sum + first[c][k]*second[k][d];
                    }
                    multiply[c][d] = sum;
                    sum = 0;
                }
            }
            // Display the results to the user
            System.out.println("\nProduct of entered matrices is:");
            
            for (c = 0; c < m; c++)
            {
                for (d = 0; d < q; d++)
                {
                    System.out.print(multiply[c][d] + "\t");
                }
                System.out.print("\n");
            }
        }
    } 
}
Enter file contents here
