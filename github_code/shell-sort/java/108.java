package jwc62f.edu.umkc.assignment.two;

import java.io.IOException;
import java.util.Vector;

public class Run {
	
	private static Vector<Integer> vector_nearlysorted = null;
	private static Vector<Integer> vector_reverse = null;
	private static Vector<Integer> vector_random = null;
	private static String[] strings_nearlysorted = null;
	private static String[] strings_reverse = null;
	private static String[] strings_random = null;
	private static int[] integers_nearlysorted = null;
	private static int[] integers_reverse = null;
	private static int[] integers_random = null;

	public static void main(String[] args) {
		Vector_SortCountTime();
	}
	public static void Vector_SortCountTime() {
		
		for(int i = 0; i < 4; i++) {
			vector_nearlysorted = Generator.GetNearlySortedVector(1000);
			vector_reverse = Generator.GetReverseVector(1000);
			vector_random = Generator.GetRandomVector(1000);
			try {
				switch(i) {
					case 0: //selection sort
						Object[] stats = Sort.Selection(vector_nearlysorted);
						System.out.println("selection sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(vector_reverse);
						System.out.println("selection sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(vector_random);
						System.out.println("selection sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 1: //bubble sort
						stats = Sort.Bubble(vector_nearlysorted);
						System.out.println("bubble sort vs nearly sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(vector_reverse);
						System.out.println("bubble sort vs reverse sorted data:    " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(vector_random);
						System.out.println("bubble sort vs random sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 2: //insertion sort
						stats = Sort.Insertion(vector_nearlysorted);
						System.out.println("insertion sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(vector_reverse);
						System.out.println("insertion sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(vector_random);
						System.out.println("insertion sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 3: //shell
						stats = Sort.Shell(vector_nearlysorted);
						System.out.println("shell sort vs nearly sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(vector_reverse);
						System.out.println("shell sort vs reverse sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(vector_random);
						System.out.println("shell sort vs random sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
				}
			} catch(Exception e) {
				
			} finally {
				
			}
		}
	}
	
	
	
	/*#####################  EVERYTHING BELOW THIS LINE IS BEYOND THE SCOPE OF THIS ASSIGNMENT ##############*/
	/*#######################################################################################################*/
	
	
	
	
	
	public static void Integer_SortCountTime() {
		for(int i = 0; i < 4; i++) {
			integers_nearlysorted = Generator.GetNearlySortedArray(1000);
			integers_reverse = Generator.GetReverseArray(1000);
			integers_random = Generator.GetRandomArray(1000);
			try {
				switch(i) {
					case 0: //selection sort
						Object[] stats = Sort.Selection(integers_nearlysorted);
						System.out.println("selection sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(integers_reverse);
						System.out.println("selection sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(integers_random);
						System.out.println("selection sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 1: //bubble sort
						stats = Sort.Bubble(integers_nearlysorted);
						System.out.println("bubble sort vs nearly sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(integers_reverse);
						System.out.println("bubble sort vs reverse sorted data:    " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(integers_random);
						System.out.println("bubble sort vs random sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 2: //insertion sort
						stats = Sort.Insertion(integers_nearlysorted);
						System.out.println("insertion sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(integers_reverse);
						System.out.println("insertion sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(integers_random);
						System.out.println("insertion sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 3: //shell
						stats = Sort.Shell(integers_nearlysorted);
						System.out.println("shell sort vs nearly sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(integers_reverse);
						System.out.println("shell sort vs reverse sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(integers_random);
						System.out.println("shell sort vs random sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
				}
			} catch(Exception e) {
				
			} finally {
				
			}
		}
	}
	public static void String_SortCountTime() {
		for(int i = 0; i < 4; i++) {
			try {
				strings_nearlysorted = Util.GetStringCSV("1000strings_nearlysorted.csv");
				strings_reverse = Util.GetStringCSV("1000strings_reverse.csv");
				strings_random = Util.GetStringCSV("1000strings_random.csv");
			} catch (IOException e) {
				e.printStackTrace();
			}
			try {
				switch(i) {
					case 0: //selection sort
						Object[] stats = Sort.Selection(strings_nearlysorted);
						System.out.println("selection sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(strings_reverse);
						System.out.println("selection sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Selection(strings_random);
						System.out.println("selection sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 1: //bubble sort
						stats = Sort.Bubble(strings_nearlysorted);
						System.out.println("bubble sort vs nearly sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(strings_reverse);
						System.out.println("bubble sort vs reverse sorted data:    " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Bubble(strings_random);
						System.out.println("bubble sort vs random sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 2: //insertion sort
						stats = Sort.Insertion(strings_nearlysorted);
						System.out.println("insertion sort vs nearly sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(strings_reverse);
						System.out.println("insertion sort vs reverse sorted data: " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Insertion(strings_random);
						System.out.println("insertion sort vs random sorted data:  " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
					case 3: //shell
						stats = Sort.Shell(strings_nearlysorted);
						System.out.println("shell sort vs nearly sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(strings_reverse);
						System.out.println("shell sort vs reverse sorted data:     " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						stats = Sort.Shell(strings_random);
						System.out.println("shell sort vs random sorted data:      " + stats[0] + " milliseconds\t" + stats[1] + " comparisons\t" + stats[2] + " exchanges");
						break;
				}
			} catch(Exception e) {
				
			} finally {
				
			}
		}
	}

	
	
	public static void Print(int[] v) {
		for(int i = 0; i < v.length; i++){
			System.out.println(v[i]);
		}
	}
}
