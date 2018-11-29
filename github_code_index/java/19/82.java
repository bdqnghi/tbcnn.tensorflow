package sort.distributive;

import java.util.Random;
import java.util.concurrent.locks.ReentrantLock;

import sort.Sort;
import sort.swap.QuickSort;

public class BucketSort extends Sort {

	/**
	 * @param args
	 */
	
	private static  int i =0;
	public int a(){
		return  i++;
	}
	public int b(){
		return ++i;
	}
	public static void main(String[] args) {
		BucketSort a = new BucketSort();
		System.out.println(a.a());
		System.out.println(a.b());
		BucketSort b = new BucketSort();
		System.out.println(b.a());

		// TODO Auto-generated method stub
	/*	QuickSort qs = new QuickSort();
		int[] data = qs.integerToInt(qs.getIntegerRandArray(10, 100));
		for (int i = 0; i < data.length; i++) {
			System.out.print(data[i]+" , ");
		}
		System.out.println();
		qs.quickSortInt(data, data.length, 0, data.length-1);
		for (int i = 0; i < data.length; i++) {
			System.out.print(data[i]+" , ");
		}*/
		
	/*	BucketSort bs = new BucketSort();
		int[] data = bs.integerToInt(bs.getIntegerRandArray(10, 100));
		System.out.println("befort:");
		for (int i = 0; i < data.length; i++) {
			System.out.print(data[i]+" , ");
		}
		System.out.println();
		System.out.println("after");
		bs.bucketSort(data);
		for (int i = 0; i < data.length; i++) {
			System.out.print(data[i]+" , ");
		}*/
	}
	
	class Node{
		int num = 0;
		int[] node = new int[10];
	}
	
	public void bucketSort(int[] data){
		int max = data[0] , min = data[0];
		for (int i = 0; i < data.length; i++) {
			if(max < data[i]){
				max = data[i];
			}
			if(min > data[i]){
				min = data[i];
			}
		}
		
		int bucketSize = (max - min + 1)/10 + 1;
		Node[] bucket = new Node[bucketSize];
		for (int i = 0; i < bucket.length; i++) {
			bucket[i] = new Node();
		}
		
		for (int i = 0; i < data.length; i++) {
			int k = (data[i] - min + 1)/10;
			bucket[k].node[bucket[k].num] = data[i];
			bucket[k].num++;
		}
		
		int pos = 0 ; 
		
		QuickSort qs = new QuickSort();
		for (int i = 0; i < bucket.length; i++) {
			qs.quickSortInt(bucket[i].node, bucket[i].num, 0, bucket[i].num-1);
			
			for (int j = 0; j < bucket[i].num; j++ , pos++) {
				data[pos] = bucket[i].node[j];
			}
		}
		
		
	}

}
