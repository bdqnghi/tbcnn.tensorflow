/**
 * Ha K Hwang
 * 01/21/2015
 * CS3410 HW1 
 * 
 * This program creates two 2D arrays of size 50 or greater for each side, then 
 * generates random integers ranging from 1~99 and assigns each random integer 
 * to an element of both arrays. The program then multiplies the two matrices
 * and displays the resulting matrix, along with the time it took to calculate
 * the multiplication.
 * 
 * To develop this program, the two matrices to be multiplied and the resulting
 * matrix were needed. Then codes to generate random variables (1~99) were 
 * necessary. A String array encompassing both starting arrays would have been
 * nice, but it kept giving compile errors--thus, two manual arrays were hard
 * coded. Then it was necessary to discover a triple loop that would multiply 
 * row elements of the first array to the column elements of the second array.  
 * Then, a method to add timestamp for both just prior to and just after the
 * multiplication was needed. Date object's timestamp function was used, with 
 * nano parameter being used for time difference calculation. The last part
 * was developing the looping condition depending on user entry. 
 * 
 * Arrays were used, and boolean logic for looping.
 * 
 * If the user enters a value greater than or equal to 50, the program will
 * generate two n x n matrices, then display them.  And the resulting matrix
 * will be displayed, along with time it took for the multiplication.  If the
 * entered value is not greater or equal to 50, the user will be prompted to
 * enter appropriate value repeatedly.
 * 
 * class matrix has 1 main method, which does matrix multiplication of 2 matrices
 * and displays the resulting matrix and the time taken for multiplication.
 */
package Matrix;
import java.util.*;
import java.sql.Timestamp;

public class matrix {

public static void main(String args[])
{
    //sets up looping conditions, initially true
    boolean runAgain = true;
    while (runAgain) 
    {
        System.out.println("\n\n" + "This program calculates product of two matrices" + "\n");
        int minSize = 50;    
        Scanner input = new Scanner(System.in);
        System.out.println("Please enter matrix dimensions (greater than " + minSize + "): ");
        int number = input.nextInt();

        //if entered value < minSize, then user is repeatedly asked to enter a 
        //value greater than or equal to minSize
        while (number < minSize)
        {     
            System.out.println("Please enter a number GREATER than or EQUAL to " + minSize + ": ");
            number = input.nextInt();
        }    
        
        //make 2D array of size [number][number]
        int[][] array1 = new int[number][number];
        int[][] array2 = new int[number][number];
        int[][] arrayProduct = new int[number][number];

        
        //fill the two arrays with random numbers (range: 1~99)        
        int minNum = 1;
        int maxNum = 99;
        Random random = new Random();
        System.out.println("\n" + "The first matrix is: " + "\n");
        for (int i = 0; i < array1.length; i++)
        {
            for (int j = 0; j < array1.length; j++)
            {                
                int randomNum = random.nextInt((maxNum - minNum) + 1) + minNum;
                array1[i][j] = randomNum;
                System.out.print(randomNum + " ");
            }
            System.out.println();
        }
        System.out.println("\n\n\n\n" + "The second matrix is: " + "\n"); 
        for (int i = 0; i < array2.length; i++)
        {
            for (int j = 0; j < array2.length; j++)
            {                
                int randomNum = random.nextInt((maxNum - minNum) + 1) + minNum;
                array2[i][j] = randomNum;
                System.out.print(randomNum + " ");
            }
            System.out.println();
        }
        System.out.println("\n\n\n");


        //records starting time for matrix multiplication operation
        java.util.Date date0 = new java.util.Date();
        Timestamp time0 = new Timestamp(date0.getTime());        

        //does matrix multiplication of 2 matrices 
        int sum = 0;
        for (int i = 0; i < array1.length; i++)
        {
            for (int j = 0; j < array2.length; j++)
            {                
                for (int k = 0; k < arrayProduct.length; k++)
                {    
                    sum += array1[i][k] * array2[k][j];                        
                }

                arrayProduct[i][j] = sum;
                //System.out.print(sum + " ");
                sum = 0;
            }
            //System.out.println();
        }
        //System.out.println("\n\n\n");
        
        //records end time for matrix multiplication        
        java.util.Date date1 = new java.util.Date();
        Timestamp time1 = new Timestamp(date1.getTime());
        
        

        //displays resulting matrix multiplication matrix
        System.out.println("The result of the matric multiplication is : " + "\n");
        for (int i = 0; i < array2.length; i++)
        {
            for (int j = 0; j < array2.length; j++)
            {                
                System.out.print(arrayProduct[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println("\n\n\n\n");

        
        //prints start time and end time
        System.out.println("The Start time is " + time0);
        double timeStart = time0.getNanos();
        double timeEnd = time1.getNanos();
        System.out.println("The end time is " + time1 + "\n");
        
        //calculates time taken for matrix multiplication using Nanosecond values
        //nano- means 9 zeros
        double timeDiff = (timeEnd - timeStart) / 1000000000;
        System.out.println("Total time taken: " + timeDiff + " seconds\n\n\n\n");
        
        
        //Asks user if they want to run the program again
        //if "yes" or "no" is not entered, it will ask until "yes" or "no"
        boolean validResponse = false;        
        while (!validResponse) 
        {
            String repeat = input.nextLine().trim();

            if (repeat.equalsIgnoreCase("no")) 
            {
                runAgain = false;
                validResponse = true;
                System.out.println("Thank you for using this program. Have a nice day!");
            }
            else if (repeat.equalsIgnoreCase("yes")) 
            {
                validResponse = true;
            }
            else 
            {
                System.out.println("Run again? Please enter either \'yes\' or \'no\'" );
            } //end of if/else if/else    
        } //end of while

    } //end of looping while    
} //end of main method
} //end of class