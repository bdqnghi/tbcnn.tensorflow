import java.util.Arrays;
import java.util.Random;

public class quickSortMain {

	public static void main(String[] args) {
		sortN(10000, 5);
		sortN(10000,5,1);
		sortN(1000,5,10);
		sortN(100,5,100);
		
		randomizedSortN(10000, 5);
		randomizedSortN(10000,5,1);
		randomizedSortN(1000,5,10);
		randomizedSortN(100,5,100);
		
		threePivotSortN(10000, 5);
		threePivotSortN(10000,5,1);
		threePivotSortN(1000,5,10);
		threePivotSortN(100,5,100);
		
		switchToInsertionSortN(10000, 5);
		switchToInsertionSortN(10000,5,1);
		switchToInsertionSortN(1000,5,10);
		switchToInsertionSortN(100,5,100);
		
	}
	
	public static void sortN(int n,int times) {
		System.out.println("*** Testing sorting arrays with " + n + " values, " + times + " times.***");
		long javaAverageCompares = 0;
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = randomTestIntArray(n);
			TestInteger[] testArray2 = testArray.clone();
			long javaTime = javaSort(testArray);
			long quickTime = testTime(testArray2);
			System.out.println("Java used " + javaTime + " compares.");
			System.out.println("Our quick sort used " + quickTime + " compares.");
			javaAverageCompares = javaTime + javaAverageCompares;
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		javaAverageCompares = javaAverageCompares/times;
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, java took " + javaAverageCompares + " compares.");
		System.out.println("On average, our quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void sortN(int length,int times,int blocks) {
		System.out.println("*** Testing sorting arrays with " + length*blocks + " values, " + blocks + " blocks, " + times + " times.***");
		long javaAverageCompares = 0;
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = semisortedTestInts(blocks,length);
			TestInteger[] testArray2 = testArray.clone();
			long javaTime = javaSort(testArray);
			long quickTime = testTime(testArray2);
			System.out.println("Java used " + javaTime + " compares.");
			System.out.println("Our quick sort used " + quickTime + " compares.");
			javaAverageCompares = javaTime + javaAverageCompares;
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		javaAverageCompares = javaAverageCompares/times;
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, java took " + javaAverageCompares + " compares.");
		System.out.println("On average, our quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void randomizedSortN(int n,int times) {
		System.out.println("*** Testing sorting arrays with " + n + " values, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = randomTestIntArray(n);
			long quickTime = randomizedQuickSort(testArray);
			System.out.println("Our randomized quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our randomized quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void randomizedSortN(int length,int times,int blocks) {
		System.out.println("*** Testing sorting arrays with " + length*blocks + " values, " + blocks + " blocks, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = semisortedTestInts(blocks,length);
			long quickTime = randomizedQuickSort(testArray);
			System.out.println("Our randomized quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our randomized quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void threePivotSortN(int n,int times) {
		System.out.println("*** Testing sorting arrays with " + n + " values, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = randomTestIntArray(n);
			long quickTime = threePivotQuickSort(testArray);
			System.out.println("Our three pivot quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our three pivot quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void threePivotSortN(int length,int times,int blocks) {
		System.out.println("*** Testing sorting arrays with " + length*blocks + " values, " + blocks + " blocks, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = semisortedTestInts(blocks,length);
			long quickTime = threePivotQuickSort(testArray);
			System.out.println("Our three pivot quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our three pivot quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void switchToInsertionSortN(int n,int times) {
		System.out.println("*** Testing sorting arrays with " + n + " values, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = randomTestIntArray(n);
			long quickTime = switchToInsertionQuickSort(testArray);
			System.out.println("Our switch to insertion quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our switch to insertion quick sort took " + quickSortAverageCompares + " compares.");
	}
	
	public static void switchToInsertionSortN(int length,int times,int blocks) {
		System.out.println("*** Testing sorting arrays with " + length*blocks + " values, " + blocks + " blocks, " + times + " times.***");
		long quickSortAverageCompares = 0;
		for (int i = 0; i < times; i++){
			TestInteger[] testArray = semisortedTestInts(blocks,length);
			long quickTime = switchToInsertionQuickSort(testArray);
			System.out.println("Our switch to insertion quick sort used " + quickTime + " compares.");
			quickSortAverageCompares = quickTime + quickSortAverageCompares;
		}
		quickSortAverageCompares = quickSortAverageCompares/times;
		System.out.println("On average, our switch to insertion quick sort took " + quickSortAverageCompares + " compares.");
	}

	private static <T extends Comparable<T>> long testTime(T[] arr ) {
		quickSort.comparisonCount = 0;
		quickSort.quickSort(arr);
		return quickSort.comparisonCount;
	}
	
	private static <T extends Comparable<T>> long javaSort(T[] arr ) {
		TestInteger.javaCompares = 0;
		Arrays.sort(arr);
		return TestInteger.javaCompares;
	}
	
	private static <T extends Comparable<T>> long randomizedQuickSort(T[] arr ) {
		randomizedQuickSort.comparisonCount = 0;
		randomizedQuickSort.quickSort(arr);
		return randomizedQuickSort.comparisonCount;
	}
	
	private static <T extends Comparable<T>> long threePivotQuickSort(T[] arr ) {
		threePivotQuickSort.comparisonCount = 0;
		threePivotQuickSort.quickSort(arr);
		return threePivotQuickSort.comparisonCount;
	}
	
	private static <T extends Comparable<T>> long switchToInsertionQuickSort(T[] arr ) {
		insertionQuickSort.comparisonCount = 0;
		insertionQuickSort.quickSort(arr);
		return insertionQuickSort.comparisonCount;
	}
	
	public static TestInteger[] randomTestIntArray(int arrayLength) {
		Random rand = new Random();
		TestInteger[] randomTestInts = new TestInteger[arrayLength];
		
		for (int i = 0; i < arrayLength; i++) {
			randomTestInts[i] = new TestInteger(rand.nextInt(1000000));
		}
		return randomTestInts;
	}
	
	public static TestInteger[] semisortedTestInts(int blocks, int length){
		TestInteger[] testintarray = new TestInteger[blocks*length];
		for (int i = 0;i<blocks;i++){
			TestInteger[] temparray = randomTestIntArray(length);
			javaSort(temparray);
			System.arraycopy(temparray,0,testintarray,length*i,length);
		}
		return testintarray;
	}
	
	public static boolean isSorted(Integer[] arr){
		int i = 0;
		boolean isSorted = true;
		while (arr[i+1]<arr.length){
			if (arr[i] > arr[i+1]){
				isSorted = false;
			}
		}
		return isSorted;
	}
}
