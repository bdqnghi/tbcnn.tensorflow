/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package learnjava;

/**
 *
 * @author Anusha K
 */
public class Selectionsort {
    
    int[] sort(int[] array){  
        for(int i=0;i<array.length;i++){
        int min=i;
        for(int j=i+1;j<array.length;j++){
            if(array[min]>array[j]){
                min=j;
            }
        }
       int temp=array[i];
        array[i]=array[min];
        array[min]=temp;
        }
        return array;
    }
    
    
    char[] charsort(char[] array){  
        for(int i=0;i<array.length;i++){
        int min=i;
        for(int j=i+1;j<array.length;j++){
            if(array[min]>array[j]){
                min=j;
            }
        }
       char temp=array[i];
        array[i]=array[min];
        array[min]=temp;
        }
        return array;
    }
    
   public static void main(String args[]){
      int array[]=new int[]{4,3,2,5,1};
      Selectionsort ins=new Selectionsort();
      array=ins.sort(array);
      char arr[]=new char[]{'b','c','a'};
      ins.charsort(arr);
      for(int i=0;i<array.length;i++)
          System.out.print(array[i]+" ");
      
      System.out.println();
      for(int i=0;i<arr.length;i++)
              System.out.print(arr[i]+" ");
  
      
  }
   
}
