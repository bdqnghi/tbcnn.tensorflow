package com.sorting;

/**
 * Created with IntelliJ IDEA.
 * User: abyss
 * Date: 8/9/12
 * Time: 12:03 PM
 * To change this template use File | Settings | File Templates.
 */
public class Insertionsort {
    private int[] numbers;


    public void sort(int[] values) {
        // Check for empty or null array
        if (values ==null || values.length==0){
            return;
        }
        this.numbers = values;
        for(int i = 1; i < numbers.length; i++) {
           int j = i;
           int value = numbers[i];

           while(j > 0 && (numbers[j-1] > value))     {
               numbers[j] = numbers[j-1];
               j--;
           }

           numbers[j] = value;
        }
        for(int n=0; n< numbers.length; n++) {
            System.out.print(numbers[n] + ", ");
        }
    }

    public static void main(String ... args)  {
        Insertionsort is = new Insertionsort();
        int a[] = {3,7,8,5,2,1,9,5,4};
        is.sort(a);
   }

}
