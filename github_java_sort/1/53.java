package com.minjoon.Sort.Insertion;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


public class Insertion {

	public static void main(String[] args) {
		
		File file = new File("./Data.txt");
		FileReader fr;
		BufferedReader br;

		String data = "";
		String[] numberArr = {};
		String target = "";
		int targetPosition = 0;
		try {
			fr = new FileReader(file);
			br = new BufferedReader(fr);

			data = br.readLine();
			numberArr = data.split(" ");
			target = br.readLine();

		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
		System.out.println("before Insertion Sort");
		for (String number : numberArr) {
			System.out.print(number+" ");
		}
		System.out.println("\n"+"target : "+target);
		targetPosition = InsertionSort.sort(numberArr, target);
		
		System.out.println("after Insertion Sort");
		for (String number : numberArr) {
			System.out.print(number+" ");
		}
		System.out.println();
		
		System.out.println(targetPosition);
		
		
		
	}

}
