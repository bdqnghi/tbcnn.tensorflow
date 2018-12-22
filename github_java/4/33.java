import common.SeqProvider;
import common.Util;

/**
 * @author Drazzi-lee
 * 
 */
public class InsertionSort {
	public static int[] unsort;
	public static int[] sortedASC;
	public static int[] sortedDESC;

	/**
	 * INSERTION SORT METHOD: FROM SMALL TO LARGE
	 * @param seq The array to be sorted.
	 * @param isASC True: ASC; False: DESC
	 * @return
	 */
	private static int[] insertSort(int[] seq, boolean isASC) {
		int[] tmp_seq = new int[seq.length];
		System.arraycopy(seq, 0, tmp_seq, 0, seq.length);
		for (int i = 1; i < tmp_seq.length; i++) {
			int tmp = tmp_seq[i];
			int j = i - 1;
			while (j >= 0 && (isASC? (tmp_seq[j] > tmp) : (tmp_seq[j] < tmp))) {
				tmp_seq[j + 1] = tmp_seq[j];
				j--;
			}
			tmp_seq[j + 1] = tmp;
		}
		return tmp_seq;
	}

	public static void main(String[] args) {
		unsort = SeqProvider.getIntSeq(30);
		sortedASC = insertSort(unsort, true);
		sortedDESC = insertSort(unsort, false);
		
		Util.printArray("Int[] unsort: ", unsort);
		Util.printArray("Int[] sorted by Insertion-Sort from small to large: ", sortedASC);
		Util.printArray("Int[] sorted by Insertion-Sort from large to small: ", sortedDESC);
	}
}
