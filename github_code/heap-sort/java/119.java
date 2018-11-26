package com.minjoon.Sort.Heap;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Heap {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		File file = new File("./Data.txt");
		FileReader fr;
		BufferedReader br;

		String data = "";
		String[] numberArr = {};
		try {
			fr = new FileReader(file);
			br = new BufferedReader(fr);

			data = br.readLine();
			numberArr = data.split(" ");

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("before Heap Sort");
		for (String number : numberArr) {
			System.out.print(number + " ");
		}
		System.out.println();

		System.out.println("\nSorting....");
		HeapSort.sort(numberArr);
		System.out.println("Done!.\n");

		System.out.println("after Heap Sort");
		for (String number : numberArr) {
			System.out.print(number + " ");
		}
		System.out.println();
	}

}
