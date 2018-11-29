package com.algos.week3.main;

import java.util.Scanner;

import com.algos.week3.elementarysorts.InsertionSort;
import com.algos.week3.elementarysorts.SelectionSort;
import com.algos.week3.elementarysorts.ShellSort;
import com.algos.week3.shuffle.KnuthShuffle;
import com.algos.week3.sorting.MergeSort;

public class Program {
	static Scanner scanner;
	static Integer[] intArray;
	static Character[] charArray;
	static String[] stringArray;
	static int response;

	public static void main(String[] args) {
		// sortInteger(); // 7 10 5 3 8 4 2 9 6 1
		//sortCharacter(); // S O R T E X A M P L
		 sortString(); // test aditya chukka string array
		// shuffleArray();
	}

	private static void sortString() {
		System.out.println("Enter the size of (String)array:");
		scanner = new Scanner(System.in);
		int N = scanner.nextInt();
		stringArray = new String[N];
		System.out.println("Enter the array Elements:");
		for (int i = 0; i < N; i++) {
			stringArray[i] = scanner.next();
		}
		System.out.println("Select the sorting method to be used");
		System.out.println("1.SelectionSort\n2.InsertionSort\n3.ShellSort\n4.MergeSort");
		response = scanner.nextInt();
		callSortingFunction(response, 3);
	}

	private static void sortCharacter() {
		System.out.println("Enter the size of (char)array:");
		scanner = new Scanner(System.in);
		int N = scanner.nextInt();
		charArray = new Character[N];
		System.out.println("Enter the array Elements:");
		for (int i = 0; i < N; i++) {
			charArray[i] = scanner.next(".").charAt(0);
		}
		System.out.println("Select the sorting method to be used");
		System.out.println("1.SelectionSort\n2.InsertionSort\n3.ShellSort\n4.MergeSort");
		response = scanner.nextInt();
		callSortingFunction(response, 2);
	}

	private static void sortInteger() {
		System.out.println("Enter the size of (int)array:");
		scanner = new Scanner(System.in);
		int N = scanner.nextInt();
		intArray = new Integer[N];
		System.out.println("Enter the array Elements:");
		for (int i = 0; i < N; i++) {
			intArray[i] = scanner.nextInt();
		}
		System.out.println("Select the sorting method to be used");
		System.out.println("1.SelectionSort\n2.InsertionSort\n3.ShellSort\n4.MergeSort");
		response = scanner.nextInt();
		callSortingFunction(response, 1);
	}

	private static void callSortingFunction(int response, int arrayType) {
		switch (response) {
		case 1:
			selectionSort(arrayType);
			break;
		case 2:
			insertionSort(arrayType);
			break;
		case 3:
			shellSort(arrayType);
			break;
		case 4:
			mergeSort(arrayType);
			break;
		default:
			System.out.println("Wrong option Bro!!");
			break;
		}
	}

	private static void mergeSort(int arrayType) {
		System.out.println("Before Merge Sort");
		switch (arrayType) {
		case 1:
			mergeSortIntArray();
			break;
		case 2:
			mergeSortCharArray();
			break;
		case 3:
			mergeSortStringArray();
			break;
		default:
			System.out.println("Array Type Not supported!!");
			break;
		}
	}

	private static void mergeSortIntArray() {
		MergeSort<Integer> mergeSort = new MergeSort<>();
		mergeSort.display(intArray);
		mergeSort.sort(intArray);
		System.out.println("After Merge Sort");
		mergeSort.display(intArray);
	}

	private static void mergeSortCharArray() {
		MergeSort<Character> mergeSort = new MergeSort<>();
		mergeSort.display(charArray);
		mergeSort.sort(charArray);
		System.out.println("After Merge Sort");
		mergeSort.display(charArray);
	}

	private static void mergeSortStringArray() {
		MergeSort<String> mergeSort = new MergeSort<>();
		mergeSort.display(stringArray);
		mergeSort.sort(stringArray);
		System.out.println("After Merge Sort");
		mergeSort.display(stringArray);
	}

	private static void shellSort(int arrayType) {
		System.out.println("Before Shell Sort");
		switch (arrayType) {
		case 1:
			shellSortIntArray();
			break;
		case 2:
			shellSortCharArray();
			break;
		case 3:
			shellSortStringArray();
			break;
		default:
			System.out.println("Array Type Not supported!!");
			break;
		}
	}

	private static void shellSortIntArray() {
		ShellSort<Integer> shellSort = new ShellSort<>();
		shellSort.display(intArray);
		shellSort.sort(intArray);
		System.out.println("After Shell Sort");
		shellSort.display(intArray);
	}

	private static void shellSortCharArray() {
		ShellSort<Character> shellSort = new ShellSort<>();
		shellSort.display(charArray);
		shellSort.sort(charArray);
		System.out.println("After Shell Sort");
		shellSort.display(charArray);
	}

	private static void shellSortStringArray() {
		ShellSort<String> shellSort = new ShellSort<>();
		shellSort.display(stringArray);
		shellSort.sort(stringArray);
		System.out.println("After Shell Sort");
		shellSort.display(stringArray);
	}

	private static void insertionSort(int arrayType) {
		System.out.println("Before Insertion Sort");
		switch (arrayType) {
		case 1:
			insertionSortIntArray();
			break;
		case 2:
			insertionSortCharArray();
			break;
		case 3:
			insertionSortStringArray();
			break;
		default:
			System.out.println("Array Type Not supported!!");
			break;
		}
	}

	private static void insertionSortStringArray() {
		InsertionSort<String> insertionSort = new InsertionSort<>();
		insertionSort.display(stringArray);
		insertionSort.sort(stringArray);
		System.out.println("After Insertion Sort");
		insertionSort.display(stringArray);
	}

	private static void insertionSortCharArray() {
		InsertionSort<Character> insertionSort = new InsertionSort<>();
		insertionSort.display(charArray);
		insertionSort.sort(charArray);
		System.out.println("After Insertion Sort");
		insertionSort.display(charArray);
	}

	private static void insertionSortIntArray() {
		InsertionSort<Integer> insertionSort = new InsertionSort<>();
		insertionSort.display(intArray);
		insertionSort.sort(intArray);
		System.out.println("After Insertion Sort");
		insertionSort.display(intArray);
	}

	private static void selectionSort(int arrayType) {
		System.out.println("Before Selection Sort");
		switch (arrayType) {
		case 1:
			selectionSortIntArray();
			break;
		case 2:
			selectionSortCharArray();
			break;
		case 3:
			selectionSortStringArray();
			break;
		default:
			System.out.println("Array Type Not supported!!");
			break;
		}
	}

	private static void selectionSortStringArray() {
		SelectionSort<String> selectionSort = new SelectionSort<>();
		selectionSort.display(stringArray);
		selectionSort.sort(stringArray);
		System.out.println("After Selection Sort");
		selectionSort.display(stringArray);
	}

	private static void selectionSortCharArray() {
		SelectionSort<Character> selectionSort = new SelectionSort<>();
		selectionSort.display(charArray);
		selectionSort.sort(charArray);
		System.out.println("After Selection Sort");
		selectionSort.display(charArray);
	}

	private static void selectionSortIntArray() {
		SelectionSort<Integer> selectionSort = new SelectionSort<>();
		selectionSort.display(intArray);
		selectionSort.sort(intArray);
		System.out.println("After Selection Sort");
		selectionSort.display(intArray);
	}

	private static void shuffleArray() {
		KnuthShuffle<Integer> knuthShuffle = new KnuthShuffle<>();
		knuthShuffle.shuffle(intArray);
		System.out.println("After Shuffling");
		knuthShuffle.display(intArray);
	}
}
