
package javabubblesort;


public class JavaBubbleSort {

    
    public void bubbleSort(int[] arr){
        int n = arr.length;
        for (int i = 0; i < n-1; i++)
            for (int j = 0; j < n-i-1; j++)
                if (arr[j] > arr[j+1])
                {
                    
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
    
    
    public static void main(String[] args) {
        JavaBubbleSort jbs = new JavaBubbleSort();

        
        int[] array = {50, 30, 20, 40, 70, 60, 80};
        
        
        System.out.println("Before Sorting");
        jbs.printArray(array);
        jbs.bubbleSort(array);
        
        
        System.out.println("After Sorting");
        jbs.printArray(array);
    }
    
}
