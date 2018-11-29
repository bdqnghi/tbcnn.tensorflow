/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package datastructures;

/**
 *
 * @author dwaraknath
 */
public class Shellsort {
     static int[] ar=new int[10];
    public static void randomarray(){
        for(int i=0;i<ar.length;i++){
            ar[i]=(int)(Math.random()*10);
        }
    }
    public static void printarray(){
        for(int i=0;i<ar.length;i++){
            System.out.println(ar[i]);
            //System.out.println();
        }
    }
    public static void shellsort(){
       int interval=3;
      while(interval>0){ 
       for(int i=0;i<ar.length;i++){
           for(int j=interval;j<ar.length;j=j+interval){
               if(ar[i]<ar[j]){
                   int temp=ar[i];
                   ar[i]=ar[j];
                   ar[j]=temp;
               }
           }
       }
       interval=interval-1;
    }}
    public static void main(String args[]){
        randomarray();
        printarray();
        shellsort();
        printarray();
    }
}
