package aGettingStarted_school;







import java.util.Scanner;

public class GFG_4_SelectionSort {
	void selectionSort(int arr[]) {

		int n = arr.length;
		GfG obj = new GfG();
		for (int i = n - 1; i >= 0; i--) {
			int j = obj.select(arr, i);
			
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	void printArray(int arr[]) {
		int n = arr.length;
		for (int i = 0; i < n; i++)
			System.out.print(arr[i] + " ");
		System.out.println();
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		GFG_4_SelectionSort ss = new GFG_4_SelectionSort();
		System.out.println("Input");
		int t = sc.nextInt();
		while (t > 0) {
			int n = sc.nextInt();
			int arr[] = new int[n];
			for (int i = 0; i < n; i++) {
				arr[i] = sc.nextInt();
			}

			
			ss.selectionSort(arr);

			ss.printArray(arr);
			t--;
		}

	}
}

class GfG {

	
	int select(int arr[], int i) {
		
		int index_of_max;
		index_of_max = i;
		
		for (int j = 0; j <= i; j++) {
			if (arr[j] > arr[index_of_max]) {
				index_of_max = j;
			}
		}
		return index_of_max;
	}
}
