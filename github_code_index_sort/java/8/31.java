import java.util.Arrays;
class QuickQuickSort {
	public static void quicksort(int[] arr) {
		quicksort(arr, 0, arr.length - 1);
	}
	public static void quicksort(int[] arr, int l, int h) {
		if (l >= h) return;
		int v = partition(arr, l, h);
		quicksort(arr, l, v - 1);
		quicksort(arr, v + 1, h);
	}

	public static int partition(int[] arr, int l, int h) {
		int lastSwap = l + 1;
		int pivot = arr[l];
		int i = l + 1;
		while (i <= h) {
			if (arr[i] < pivot) {
				swap(arr, lastSwap++, i);
			}
			i++;
		}
		swap(arr, l, lastSwap - 1);
		return lastSwap - 1;
	}

	private static void swap(int[] arr, int i, int j) {
		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}

	public static void main(String[] args) {
		int[] vals = {4,4,3,2,8,5,4,7};
		System.out.println(Arrays.toString(vals));
		quicksort(vals);
		System.out.println(Arrays.toString(vals));
	}
}