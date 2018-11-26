public class quickSort {

	public static void sort(Comparable[] a)
     {
        StdRandom.shuffle(a);          // Eliminate dependence on input.
        sort(a, 0, a.length - 1);
     }

	private static void sort(Comparable[] a, int lo, int hi, int pivot) {
		while(lo < hi) {
			int j = partition(a, lo, hi);
			sort(a, lo, pivot);
			sort(a, pivot + 1, hi);
		}

		return;
	}

	public static void partition(Comparable[] a, int lo, int hi) {
		// Partition into a[lo..i-1], a[i], a[i+1..hi].
		int i = lo; // left part
		int j = hi + 1; // right part
		Comparable pivot = a[lo];  // partitioning item

		while(true) {
			// Scan right, scan left, check for scan complete, and exchange.
			while(less(a[++i], pivot)) if(i == hi) break;
			while(less(pivot, a[--j])) if(j == lo) break;
			if(i >= j) break;
			exch(a, i, j);
		}

		exch(a, lo, j); // Put v = a[j] into position
		return j; // with a[lo..j-1] <= a[j] <= a[j+1..hi].

	}
}