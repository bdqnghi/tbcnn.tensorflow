import java.util.*;
public class Main {
   static Scanner scn = new Scanner(System.in);

	public static void main(String[] args) {
		
		int[] arr = takeInput();

	    selectionsort(arr);
	    display(arr);
	}
	public static int[] takeInput() {
	
		int n = scn.nextInt();
		int[] arr = new int[n];
	
		for (int i = 0; i < n; i++) {
			arr[i] = scn.nextInt();
		}
		return arr;
	}

	public static void display(int[] arr)

	{
	

		for (int val : arr) {
			System.out.println(val);
		}
	}
	public static void selectionsort(int[] arr) {
		int n = arr.length;
		for (int i = 0; i < n - 1; i++) {
			int min = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[min]) {
					min = j;
				}
			}

			
			int temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}
