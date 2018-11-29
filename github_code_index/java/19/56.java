/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package bucketsort;

import java.util.Arrays;
import javax.swing.JOptionPane;
/**
 *
 * @author toledo
 */
public class Bucketsort {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
      int [] numbers= {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3}; 
      bucketSort(numbers);
      System.out.println("bucketsort:  " + Arrays.toString(numbers));
   }
    
    public static void bucketSort(int[] arr) {
      int maxValue = arr[0];
      for (int i = 1; i < arr.length; i++) {
          if (arr[i] > maxValue) {
              maxValue = arr[i];
          }
      }
  
      int [] bucket=new int[maxValue+1];
 
      for (int i=0; i<bucket.length; i++) {
         bucket[i]=0;
      }
 
      for (int i=0; i<arr.length; i++) {
         bucket[arr[i]]++;
      }
 
      int pos=0;
      for (int i=0; i<bucket.length; i++) {
         for (int j=0; j<bucket[i]; j++) {
            arr[pos++]=i;
         }
      }
   }
}
