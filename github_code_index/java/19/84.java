package datastructures;

import java.util.Collections;

import java.util.LinkedList;
import java.util.List;
/***
 * Implementation of Bucket Sort. Reference CLRS
 * @author Mohua
 *
 */

public class Bucketsort {
	public static void sort(double [] arr){
		int n=arr.length;
		// Declare an array of linkedlist and initialize the list
		List<Double> [] B=new LinkedList[n];
		for (int i=0;i<n;i++){			
			B[i]=new LinkedList<Double>();				
		}
		// Distribute the elements over the buckets
		for(int i=0;i<n;i++){
			int index=(int) (n*arr[i]);
			B[index].add(arr[i]);
		}
		// Sort the individual lists of the array
		for(int i=0;i<n;i++){
			if(B[i]!=null){
			Collections.sort(B[i]);
			}
		}
		// Copy the sorted lists into the original array
		int k=0;
		for (int i=0;i<n;i++){
			int j=0;
				while(B[i]!=null && j<B[i].size()){
					//System.out.print(B[i].get(j)+ " ");
					arr[k++]=(double) B[i].get(j);
					j++;
				}
			
		}
		show(arr);
	}
private static void show(double[] arr){
	for (double x:arr){
		System.out.print(x+" ");
	}
	System.out.println();
	
}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		double[] arr={.79, .13, .16, .64, .39, .20, .89, .53, .71, .42};
		sort(arr);
	}

}
