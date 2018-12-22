/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package heap;

/**
 *
 * @author Mahin
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Scanner;

public class Heap {

    /**
     * @param args the command line arguments
     */

        // TODO code application logic here
        
    private int array[];
    public static int n; 
    
    public static void sort(int arr[])  //the Main Sort
    {
            buildMaxHeap(arr);
            
            for(int i=arr.length-1; i>=0; i--){
                int temp=arr[0];
                arr[0] = arr[i];
                arr[i]= temp;

                n--;
                
                maxHeapify(arr,0);
		}
    }
    
    public static void maxHeapify(int[] arr, int i) //sinking!!!
    {
		int leftChild= (2*i)+1;
		int rightChild=(2*i)+2;
		
                int max;
                
                if((leftChild < n) && (arr[leftChild] > arr[i])) //Checking LeftChild
			max=leftChild;
                else max = i;
                
		if( (rightChild < n) && (arr[rightChild] > arr[max])) //checking RightChild
			max=rightChild;
		
                if(max!=i){
			int temp = arr[max];
			arr[max] = arr[i];
			arr[i] = temp;
                        maxHeapify(arr, max);
		}
	}  
    
    public static void main(String[] args)throws IOException {
        try{
            int size,c;
            int array[];
            
            File input = new File("input.txt");         //inputFile
            File output = new File("output.txt");       //OutputFile
            
            Scanner sc = new Scanner(input);                //Taking File input
            PrintWriter pw = new PrintWriter(output);
            
            size = sc.nextInt();
            c=0;
            array = new int [size];
            
            while(sc.hasNext()){
            array[c++] = sc.nextInt();
            }
            
            sort(array);                    //THE main SORT calling 
           
             for(c = 0;c<array.length;c++){
                 System.out.print(array[c]+" ");
            }
            System.out.println("");
            
            for(c = 0;c<array.length;c++){
                pw.print(array[c]+" ");
            }
            pw.close();
        }
        catch(FileNotFoundException e){
            System.out.print(e);
        }
    }
    
    public static void buildMaxHeap(int [] array){
    
        n=array.length;
        
        for(int i=array.length/2; i>=0; i--){
            maxHeapify(array, i);
        }
    }
}
