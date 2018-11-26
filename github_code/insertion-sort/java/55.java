/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package coding.cormen;
import java.util.*;
/**
 *
 * @author getsa
 */
public class insertionsort 
{
     Scanner alpha = new Scanner(System.in);
    public static void main(String[] args)
    {        
        insertionsort beeta = new insertionsort();        
        int[] A = beeta.arrayinput();        
        int[] B = beeta.insertionsort(A);        
        beeta.printarray(B);           
    }
    void printarray(int[] arr)
    {
        int[] myarray = insertionsort(arr);
        for(int i=0;i<myarray.length;i++)
        {
         System.out.println(myarray[i]);   
        }    
    }
    int[] insertionsort(int[] array)
        {
           int[] arr = array;         
           for (int i=1;i<arr.length;i++)
           {
               int key = arr[i];
               int j = i-1;
               while((j>=0)&&(key>arr[j]))
               {
                   arr[j+1] = arr[j];
                   arr[j] = key;
                   j--;
               }
               
           }         
           return arr;
           
        }
    public int[] arrayinput()
        {
            System.out.println("Enter the size of the array");
            int n = alpha.nextInt();
            int [] array = new int [n];
            System.out.println("Enter the elements of the array");
            for(int i=0;i<n;i++)
            {
               array[i] = alpha.nextInt();
            }
            return array;
            
        }

}
