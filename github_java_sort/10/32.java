
package bucketsort;

import java.util.Scanner;


public class Bucketsort {
     
 public static int[] bucketSort(int[] arr) {					
  int i, j, terbesar = 0;int[] ember = new int [50];
										
  for(i = 0; i < arr.length; i++ ) {	   	
   if(terbesar < arr[i]){				
    terbesar = arr[i];					
   	}	
  } 
  for(i = 0; i < arr.length; i++ ) {	
   	   ember[arr[i]]++;				
  	} 
  for (i = 0, j = 0; i < ember.length; i++) {  
   for (; ember[i] > 0; (ember[i])--) { 
    arr[j] = i;			
    j++;				
              }
         } 
  return arr;								
 }
 
 public static void main(String[] args) { 						
  System.out.print("Berapa data yang mau diurutkan? ");				
  Scanner sc = new Scanner(System.in);						
  int panjang = sc.nextInt(); 							
  int[] arr = new int[panjang];							
  for(int i = 1; i <= panjang; i++ ){	
   System.out.print("Angka ke " + i + ": ");			
   arr[i-1] = sc.nextInt();					
  }
  System.out.print("Sebelum diurutkan: ");					
  for (int i = 0; i < arr.length; i++) {	
   System.out.print(arr[i] + " ");				
  }
  System.out.println("\n"); 							
  arr = bucketSort(arr);						
  System.out.print("Setelah diurutkan: ");					
  for (int i = 0; i < arr.length; i++) {	  
   System.out.print(arr[i] + " ");					
  }
  System.out.println();							
 }}  


