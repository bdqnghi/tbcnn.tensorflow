package algorithm_1week;

import java.io.File;

public class Main {
	public static void main(String[] args){
		int[] insertionArray, binaryInsertionArray, MergeSortArray, MergeSort_3sublistArray;
					
		File file = new File("C:/Users/������/Desktop/�˰�����/�ǽ�/1week/data02.txt");
		FileInputOutput fileIO = new FileInputOutput(file);
		insertionArray = fileIO.readFile();
		binaryInsertionArray = fileIO.readFile();
		MergeSortArray = fileIO.readFile();
		MergeSort_3sublistArray = fileIO.readFile();
		
		Insertion insertion = new Insertion(insertionArray);
		long start = System.nanoTime();
		insertionArray = insertion.compare();
		long end = System.nanoTime();
		System.out.println("Insertion ����ð�: " + (end-start) + "ns");
		
		BinaryInsertionSort binaryInsertion = new BinaryInsertionSort(binaryInsertionArray);
		start = System.nanoTime();
		binaryInsertionArray = binaryInsertion.compare();
		end = System.nanoTime();
		System.out.println("binary_Insertion ����ð�: " + (end-start) + "ns");
		
		MergeSort mergeSort = new MergeSort(MergeSortArray);
		start = System.nanoTime();
		MergeSortArray = mergeSort.doMergeSort();
		end = System.nanoTime();
		System.out.println("Merge ����ð�: " + (end-start) + "ns");
		
		MergeSort_3sublist sublistSort = new MergeSort_3sublist(MergeSort_3sublistArray);
		start = System.nanoTime();
		MergeSort_3sublistArray = sublistSort.doMergeSort_3sublist();
		end = System.nanoTime();
		System.out.println("Merge_3way ����ð�: " + (end-start) + "ns");
		
		fileIO.fileOutput("hw01_00_201402377_insertion" ,insertionArray);
		fileIO.fileOutput("hw01_00_201402377_binary_insertion", binaryInsertionArray);
		fileIO.fileOutput("hw01_00_201402377_merge", MergeSortArray, mergeSort.mergeCount());
		fileIO.fileOutput("hw01_00_201402377_3way_merge", MergeSort_3sublistArray, sublistSort.mergeCount());
	}
}
