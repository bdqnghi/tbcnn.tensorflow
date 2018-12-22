package Sorting;

public class Insertionsort {
	public static void main(String[] args) {

		int[] arr = { 100, 10, 20, 1, 63, 1, 5 };
		printa(arr, arr.length);
		insertion(arr, arr.length);
	}

	public static void printa(int[] arr, int n) {
		for (int i = 0; i < n; i++)
			System.out.print(arr[i] + " ");

		System.out.println();
	}

	public static void insertion(int[] arr, int n) {
		System.out.println("insertion sort");
		for (int j = 1; j < n; j++) {
			int min = arr[j];
			for (int i = j - 1; i >= 0; i--) {
				if (arr[i] > min) {
					arr[i + 1] = arr[i];
					arr[i] = min;

				}
			}

		}
		printa(arr, n);
	}

}
