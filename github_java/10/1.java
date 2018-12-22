package com.skelsey2.bubblesort;

import java.util.Arrays;
import java.util.stream.IntStream;

public class JavaBubbleSort {
	// public jar to maven central?
	/**
	 * Use to test bubble sort method or the JUnit Class
	 */
	public static void main(String[] args) {

		int ranNumber = (int) Math.floor(((Math.random()+1)*100)); 
		int testArray[] = new int[ranNumber];
		for(int i = 0; i < testArray.length -1; i++){
			System.out.println("setting: " + testArray[i]);
			testArray[i] =  (int) Math.floor(((Math.random()+1)*100));
			System.out.println("i: " + testArray[i]);
		}
		System.out.println(Arrays.toString(testArray));
		int expectedArray[] = new int[ranNumber];
		expectedArray = Arrays.copyOf(testArray, testArray.length);
		Arrays.sort(expectedArray);
		System.out.println( Arrays.toString(expectedArray)+ " " + Arrays.toString(testArray));
		
//		int[] array = { 1, 4, 8, 10, 12, 5, 0, 3, 9, 44, 55 };
//		System.out.println("BubbleSort of: " + Arrays.toString(array));
//		bubbleSort3(array);
//		System.out.println(Arrays.toString(array));

//		IntStream i = IntStream.of(6, 5, 7, 1, 2, 3, 3);
//		IntStream i2 = i.flatMap(n -> IntStream.of(n * n));
//		i2.forEach(System.out::println);
	}

	public static int[] bubbleSort1(int[] arr) {
		boolean swap = true;
		while (swap) {
			swap = false;
			for (int i = 0; i < arr.length - 1; i++) {
//				System.out.println(Arrays.toString(arr));
				if (arr[i] > arr[i + 1]) {
					swap = true;
//					System.out.println("SWAP OCCURED");
					int temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}
		}
		return arr;
	}

	public static int[] bubbleSort2(int[] arr) {
		int i = 0, n = arr.length;
		boolean swap = true;
		while (i < n - 1 && swap) {
			swap = false;
			for (int j = 1; j < n - i; j++) {
				if (arr[j - 1] > arr[j]) {
					swap = true;
					int temp = arr[j - 1];
					arr[j - 1] = arr[j];
					arr[j] = temp;
				}
			}
		}
		return arr;
	}

	static int swapCount= 0;
	static boolean swap = true;
	public static int[] bubbleSort3(int[] arr) {
		int n = arr.length;
		
		IntStream.range(0, n - 1)
			.flatMap(i -> {
//				System.out.println("initial i: " + i);
				if(swap){
					i = 0;
				} else {
//					System.out.println("value of i" + i + "value of n-1: " + (n-1) );
					i = n-1;
				}
				swap =false;
//				System.out.println("Array: " + Arrays.toString(arr));
//				System.out.println("\t i: " + i);
//				System.out.println("The IntStream Range: " + Arrays.toString(IntStream.range(i + 1, n -1).toArray()));
				return IntStream.range(i + 1, n - i);})
				.forEach(j -> {
								swapCount++;
//								System.out.println("\t\tj: " + j);
								if (arr[j - 1] > arr[j]) {
									
									swap = true;
									int temp = arr[j];
									arr[j] = arr[j - 1];
									arr[j - 1] = temp;
								}
							  }
						 );
//		System.out.println(swapCount);
		return arr;
	}
}
