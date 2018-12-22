/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package relearn1;
import java.util.*;
/**
 *
 * @author Red1498
 */
public class desmath {
      
    public static void select(int[] array){  //only taking array of int type when called
        
        for (int i=0;i<array.length-1;i++)  // place holder/where we are currently in the array(only itterates when we finish switching)
        {  
            int index=i; 
            for (int j=i+1;j<array.length;j++){// itterating through the array after the placeholder   
                if (array[j]<array[index]){  // comparing to see if the number in the array currently is smaller 
                    index=j;// stores j into index
                }  
            }  
            int small=array[index];  //stores the array of the location of the index to small
            array[index]=array[i];  // stores the array of the location of the placeholder to the array of the location of the index
            array[i]=small;  //puts the small into the location of i in the array
            
            //thus placing the smallest number into the left most position then second smallest third smallest etc
        }  
    }  
    public static void main(String a[]){ 

            int[] test = {350,420,69,911,72,711,80085,1};//numbers in the array

            System.out.println("Numbers before they are sorted"); 

            for(int i=0;i<test.length; i++){  //itterating to print which location of the array we are printing
                System.out.print(test[i]+" ");  
            }  

            System.out.println();  //formating

            select(test);//calling it and sorting array   

            System.out.println("Numbers after they are sorted");  

            for(int i=0; i<test.length;i++){  //itterating to print which location of the array we are printing
                System.out.print(test[i]+" ");  
            }  

    }
}