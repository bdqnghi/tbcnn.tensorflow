package com.compit.programming.basics.sort;

import java.util.Random;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
/**
 * @author: chaudharimehul
 * @date:	Jun 1, 2017
 * Quick Sort
 */
public class Quick {

	static void sort(int[] array, int left, int right){
		if(left >= right){
			return;
		}
		int pivotIndex = partition(array, left, right);
		sort(array, left, pivotIndex -1);
		sort(array, pivotIndex+1, right);
	}

	static void swap(int x, int y){
		int temp = x;
		x = y;
		y = temp;
	}
	static int partition(int[] array, int left, int right){

		int pivot = array[right];
		int partitionIndex = left;
		int tempData;
		for(int i = left ; i < right ; i++){
			if( array[i] > pivot){
				//if array[i] value is greater than pivot do not do anything
				//partitionIndex should point to value greater than pivot
			}else{
				tempData = array[i];
				array[i] = array[partitionIndex];
				array[partitionIndex] = tempData;
				partitionIndex++;
			}
		}
		tempData = array[partitionIndex];
		array[partitionIndex] = array[right];
		array[right] = tempData;

		return partitionIndex;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random random = new Random();
		int maxSize = 1000000;
		int[] array = new int[maxSize];

		String fileName = "quickSort" + new SimpleDateFormat("yyyy-MM-dd").format(new Date()) +".txt";
		FileWriter fwr = null;
		BufferedWriter bfw = null;

		for(int i = 0 ; i < array.length ; i++){
			array[i] = random.nextInt(maxSize);
		}

		System.out.println("");

		long startTime = System.currentTimeMillis();

		sort(array, 0, array.length - 1);

		System.out.println("Time taken to quick sort array: " + (System.currentTimeMillis() - startTime));

		try{
			fwr = new FileWriter(fileName);
			bfw = new BufferedWriter(fwr);

			for(int i = 0 ; i < array.length ; i++){
				bfw.write("[" + array[i]+ "],");
			}

			bfw.write("\n");
			bfw.close();
			fwr.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}

		System.out.println("");

	}

}
