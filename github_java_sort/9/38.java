
package selectionsort;

import java.util.Scanner;
import java.util.Arrays;


public class Selectionsort {

    
    private static Scanner input = new Scanner(System.in);
    private static String answer;

    public static void main(String[] args) {

        
        
        System.out.print("How many numbers?: ");
        int n = input.nextInt();

        int[] nums = new int[n];

        
        System.out.print("Random or normal?: ");
        answer = input.next();

        
        if (answer.equalsIgnoreCase("R")) {

            
            for (int k = 0; k < n; k++) {
                int rand = (int) (Math.random() * (10 - 1) + 1);
                nums[k] = rand;
            }

            
            outputting(nums);

            
        } else if (answer.equalsIgnoreCase("n")) {

            
            for (int o = 0; o < nums.length; o++) {
                System.out.print("What is a number?: ");
                nums[o] = input.nextInt();
            }
            
            outputting(nums);

        }

    }

    
    public static void outputting(int[] nums) {
        SelectionSorting newSorting = new SelectionSorting(nums);
        System.out.println("Iliterative or Recursive?");
        answer = input.next();
        if(answer.equalsIgnoreCase("I")){
             System.out.println(Arrays.toString(newSorting.Isorting()));
             System.out.println(newSorting.Duration());
        }
        else if(answer.equalsIgnoreCase("R")){
            System.out.println(Arrays.toString(newSorting.Rsorting(0)));
            System.out.println(newSorting.DurationR(0));
        }
       
        
        System.out.println(newSorting.comparisons() + " comparisons");
    }
}
