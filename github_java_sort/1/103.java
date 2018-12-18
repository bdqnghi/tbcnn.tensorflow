




public class InsertionSort {

	private static int ITEMS[] = { 645, 245, 568, 324, 152, 324 };

	public static void main(final String[] args) {
		echoItems("Before");
		insertionSort();
		echoItems("After");
	}

	public static void insertionSort() {
		int ii = 0, jj = 0;
		for (ii = 1; ii < InsertionSort.ITEMS.length; ii++) {
			jj = ii;
			while ((jj > 0)
					&& (InsertionSort.ITEMS[jj] < InsertionSort.ITEMS[jj - 1])) {
				swap(jj, jj - 1);
				jj -= 1;
			}
		}
	}

	public static void swap(final int ii, final int jj) {
		final int temp = InsertionSort.ITEMS[ii];
		InsertionSort.ITEMS[ii] = InsertionSort.ITEMS[jj];
		InsertionSort.ITEMS[jj] = temp;
	}

	public static void echoItems(final String msg) {
		System.out.print(String.format("%6s Sorting Items[] = ", msg));
		for (int ii = 0; ii < InsertionSort.ITEMS.length; ii++) {
			System.out.print(String.format("%04d", InsertionSort.ITEMS[ii]));
			if (ii < (InsertionSort.ITEMS.length - 1)) {
				System.out.print(", ");
			}
		}
		System.out.println();
	}
}
