package SortAlgorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class BucketSort {
	
	private int bucketNum = 100;
	
	public void setBucketNum(int num){bucketNum = num;}
	public int getBucketNum(){return bucketNum;}
	public void sort(double a[]){
		
		if(a.length<=1) return;
		ArrayList<Double> temp[] = new ArrayList[bucketNum];
		
		for(int i = 0;i < a.length;i++){
			int ttemp = (int)Math.floor(bucketNum*a[i]);
			if(temp[ttemp]==null) temp[ttemp] = new ArrayList<Double>();
			temp[ttemp].add(a[i]);
		}
		
		int pos = 0;
		for(int i=0;i<temp.length;i++){
			if(temp[i]!=null){
				Collections.sort(temp[i]);
				for(double x:temp[i]) a[pos++] = x;
			}
		}	
	}
	
	public static void main(String[] args){
		int arrayLenth = 100;
		double a[] = new double[arrayLenth];
		for(int i=0;i<arrayLenth;i++)
			a[i] = Math.random();
		BucketSort bucket_sort = new BucketSort();
		bucket_sort.sort(a);
		System.out.println("BucketSort Algorithm");
		System.out.println(Arrays.toString(a));
	}
}
