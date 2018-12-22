package sort;

import java.util.Scanner;

public class selectionsort {
	public static int max(int[] a, int index) {
		int max = Integer.MIN_VALUE;
		int maxi = 0;
		for (int i = 0; i <= index; i++) {
			if (a[i] > max) {
				max = a[i];
				maxi = i;
			}
		}
		return maxi;
	}

	public static void swap(int maxi, int[] a, int i) {
		int temp = a[i];
		a[i] = a[maxi];
		a[maxi] = temp;
	}

	public static void sort(int[] a) {
		int i = a.length - 1;
		while (i > 0) {
			int maxi = max(a, i);
			swap(maxi, a, i);
			i--;
		}

	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int[] a = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = sc.nextInt();
		}
		sort(a);
		for (int i = 0; i < n; i++) {
			System.out.println(a[i] + " ");
		}
		System.out.println();
	}
}