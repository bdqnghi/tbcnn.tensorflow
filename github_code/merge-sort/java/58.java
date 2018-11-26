import static org.junit.Assert.*;
import java.util.*;
import org.junit.Test;

public class MergeSortTest {
	
	/**
	 * This method tests if an array of any Comparable is sorted
	 * @param a The array to test
	 * @return Whether or not array is sorted
	 */
	public static <AnyType extends Comparable<? super AnyType>> boolean isSorted(AnyType[] a) {
		AnyType previousValue = null;
		for (AnyType x : a) {
			if (previousValue == null) previousValue = x;
			else if (x.compareTo(previousValue) < 0) return false;
			else previousValue = x;
		}
		return true;
		
	}
	
	/**
	 * Tests isSorted method to ensure it returns the correct values.
	 */
	@Test
	public void testIsSorted() {
		Integer[] a = new Integer[]{1,2,3,4};
		assertTrue(isSorted(a));
		Integer[] b = new Integer[]{3,4,2,1};
		assertFalse(isSorted(b));
		Character[] c = new Character[]{'a', 'b', 'c', 'd'};
		assertTrue(isSorted(c));
		Character[] d = new Character[]{'F', 'A', 'a', 'f', 'a'};
		assertFalse(isSorted(d));
	}

	/**
	 * Tests mergeSort with some assorted arrays of ints
	 */
	@Test
	public void testShortInts() {
		Integer[] a = new Integer[]{1,4,9,3};
		Integer[] b = new Integer[]{1,2,3,4};
		Integer[] c = new Integer[]{79, 32, 19, 2, 16};
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}
	
	/**
	 * Tests mergeSort with some slightly longer arrays of ints.
	 */
	@Test
	public void testMediumInts() {
		Integer[] a = new Integer[]{1,4,9,3,10,19,35,2,3,14,0};
		Integer[] b = new Integer[]{1,2,3,4,9,7,5,4,3,2,1,50,502,1525,12351};
		Integer[] c = new Integer[]{79, 32, 19, 2, 16,31,352,0,34,234,12351235};
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}
	
	/**
	 * Tests mergeSort with very long arrays of randomly generated integers.
	 */
	@Test
	public void testLotsofRandomNums() {
		Random rng = new Random();
		Integer[] a = new Integer[64];
		Integer[] b = new Integer[12361];
		Integer[] c = new Integer[rng.nextInt(500000)];
		for (int i = 0; i<a.length; i++) {
			a[i]=rng.nextInt();
		}
		for (int i = 0; i<b.length; i++) {
			b[i]=rng.nextInt();
		}
		for (int i = 0; i<c.length; i++) {
			c[i]=rng.nextInt();
		}
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}
	
	/**
	 * Tests mergeSort with some given arrays of strings.
	 */
	@Test
	public void testStrings() {
		String[] a = new String[]{"Hi","My","Name","Is","Aaron"};
		String[] b = new String[]{"A","Short", "String", "Of", "Tests"};
		String[] c = new String[]{"Test", "ALL!", "THE!", "STRINGS!!!!", "And then test some more"};
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}
	
	/**
	 * Tests mergeSort with some arrays randomly generated strings of random length.
	 */
	@Test
	public void testRandomStrings() {
		Random rng = new Random();
		String[] a = new String[rng.nextInt(50)];
		String[] b = new String[rng.nextInt(100)];
		String[] c = new String[rng.nextInt(300)];
		for (int i = 0; i<a.length; i++) {
			int stringLength = rng.nextInt(20);
			StringBuilder builder = new StringBuilder();
			for (int j = 0; j<stringLength; j++) {
				builder.append((char)(rng.nextInt(255)));
			}
			a[i] = builder.toString();
		}
		for (int i = 0; i<b.length; i++) {
			int stringLength = rng.nextInt(20);
			StringBuilder builder = new StringBuilder();
			for (int j = 0; j<stringLength; j++) {
				builder.append((char)(rng.nextInt(255)));
			}
			b[i] = builder.toString();
		}
		for (int i = 0; i<c.length; i++) {
			int stringLength = rng.nextInt(20);
			StringBuilder builder = new StringBuilder();
			for (int j = 0; j<stringLength; j++) {
				builder.append((char)(rng.nextInt(255)));
			}
			c[i] = builder.toString();
		}
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}
	
	/**
	 * Tests mergeSort with arrays of Characters, some being randomly generated.
	 */
	@Test
	public void testChars() {
		Random rng = new Random();
		Character[] a = new Character[]{'a', 'b', 'f', 'q'};
		Character[] b = new Character[]{'q','Z', 'F', 'V', '5', '-', '='};
		Character[] c = new Character[rng.nextInt(200)];
		for (int i = 0; i<c.length; i++) {
			c[i]=(char)rng.nextInt(255);
		}
		MergeSort.mergeSort(a);
		MergeSort.mergeSort(b);
		MergeSort.mergeSort(c);
		assertTrue(isSorted(a));
		assertTrue(isSorted(b));
		assertTrue(isSorted(c));
	}

}
