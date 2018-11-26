import java.util.Scanner;

public class SortBubbleSort {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		System.out.print("Enter your Size :");
		int size = sc.nextInt();
		int[] inp = new int[size];

		System.out.println("Enter the values :");
		System.out.println("");
		for (int i = 0; i < size; i++) {

			inp[i] = sc.nextInt();
		}
		int temp = 0;

		for (int j = 0; j < size; j++) {

			for (int k = j + 1; k < size; k++) {
				if (inp[j] > inp[k]) {
					temp = inp[j];
					inp[j] = inp[k];
					inp[k] = temp;

				}
			}
		}

		System.out.println("Sorted values :");
		for (int j = 0; j < size; j++) {
			System.out.println(inp[j]);
		}

	}

}
