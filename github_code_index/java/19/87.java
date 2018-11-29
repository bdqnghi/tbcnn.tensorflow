package com.prep.algorithm;

public class Bucketsort {

	  public static void sort(int[] a, int maxVal){
	        int [] bucket=new int[maxVal+1];
	        
	        for (int i=0; i<bucket.length; i++){
	            bucket[i]=0;
	        }
	        
	        for (int i=0; i<a.length; i++){
	            bucket[a[i]]++;
	        }
	        	        
	        int outPos=0;
	        for (int i=0; i<bucket.length; i++){
	            for (int j=0; j<bucket[i]; j++){
	                a[outPos++]=i;
	            }
	        }
	    }

	    public static void main(String[] args){
	        
	        int [] data= {90,80,70,60,50,40,30,20,10,10}; //ArrayUtil.randomIntArray(10,maxVal+1);

	        sort(data,90);

	        for(int i=0;i<data.length;i++)
	        	System.out.print(data[i] +" , ");

	        System.out.println("\r\n");

	    }
	
}
