/*
 * Kieran Chang 12446452
 * University of Columbia Computer Science
 * CS3330 Object Oriented Programming SP18
 */
package javabubblesort;

/**
 *
 * @author Kieran
 */
public class JavaBubbleSort {

    //the entire sorting algorithm
    public void bubbleSort(int[] arr){
        int n = arr.length;
        for (int i = 0; i < n-1; i++)
            for (int j = 0; j < n-i-1; j++)
                if (arr[j] > arr[j+1])
                {
                    // swap temp and arr[i]
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
    }
    
    public void printArray(int[] arr){
        for(int i = 0; i < arr.length - 1; i++){
            System.out.println(arr[i]);
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        JavaBubbleSort jbs = new JavaBubbleSort();

        //create the array
        int[] array = {50, 30, 20, 40, 70, 60, 80};
        
        //print the array before sorting
        System.out.println("Before Sorting");
        jbs.printArray(array);
        jbs.bubbleSort(array);
        
        //print the array after sorting
        System.out.println("After Sorting");
        jbs.printArray(array);
    }
    
}
