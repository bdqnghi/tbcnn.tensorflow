import java.util.Random;

/**
 * This program captures the running times of various sort algorithms in the QuadraticSorts class
 * @author Zeph Nord
 * @version Lab10 
 * @version CPE103-03
 * @version Winter 2017
 */
public class Timing {
	private static Integer seed = 20000;
	private static Random random = new Random(seed);
	
	public static void main(String[] args) {
		/*
		 * Testing for lengths of 2.5k, 5k, 10k, 20k, 500k, 1000k, 2000k
		 */
		Integer[] array2500 = new Integer[2500];
		for (int i = 0; i < 2500; i++) {
			array2500[i] = random.nextInt(100000);
		}
		Integer[] array5000 = new Integer[5000];
		for (int i = 0; i < 5000; i++) {
			array5000[i] = random.nextInt(100000);
		}
		Integer[] array10000 = new Integer[10000];
		for (int i = 0; i < 10000; i++) {
			array10000[i] = random.nextInt(100000);
		}
		Integer[] array20000 = new Integer[20000];
		for (int i = 0; i < 20000 ; i++) {
			array20000 [i] = random.nextInt(100000);
		}
		Integer[] array500000 = new Integer[500000];
		for (int i = 0; i < 500000; i++) {
			array500000[i] = random.nextInt(100000);
		}
		Integer[] array1000000 = new Integer[1000000];
		for (int i = 0; i < 1000000; i++) {
			array1000000[i] = random.nextInt(1000000);
		}
		Integer[] array2000000 = new Integer[2000000];
		for (int i = 0; i < 2000000; i++) {
			array2000000[i] = random.nextInt(1000000);
		}
		
		System.out.println("Shell Sorts");
		shellSortClassicTiming(array2500);
		shellSortClassicTiming(array5000);
		shellSortClassicTiming(array10000);
		shellSortClassicTiming(array20000);
		shellSortClassicTiming(array500000);
		shellSortClassicTiming(array1000000);
		shellSortClassicTiming(array2000000);
		System.out.println("--------------------");
		
		System.out.println("Hibbard Sorts");
		shellSortHibbardTiming(array2500);
		shellSortHibbardTiming(array5000);
		shellSortHibbardTiming(array10000);
		shellSortHibbardTiming(array20000);
		shellSortHibbardTiming(array500000);
		shellSortHibbardTiming(array1000000);
		shellSortHibbardTiming(array2000000);
		System.out.println("--------------------");
		
		System.out.println("Sedgewick Sorts");
		shellSortSedgewickTiming(array2500);
		shellSortSedgewickTiming(array5000);
		shellSortSedgewickTiming(array10000);
		shellSortSedgewickTiming(array20000);
		shellSortSedgewickTiming(array500000);
		shellSortSedgewickTiming(array1000000);
		shellSortSedgewickTiming(array2000000);
		System.out.println("--------------------");
		
		System.out.println("Heap Sorts");
		heapSortTiming(array2500);
		heapSortTiming(array5000);
		heapSortTiming(array10000);
		heapSortTiming(array20000);
		heapSortTiming(array500000);
		heapSortTiming(array1000000);
		heapSortTiming(array2000000);
	}

	
	public static <T> void shellSortClassicTiming(Integer[] array) {
		long startTime = System.currentTimeMillis();
		
		ShellSorts.shell(array);
		
		
		long stopTime =  System.currentTimeMillis();
		long elapsedTime = stopTime - startTime;
		System.out.println("Shell sort: " + array.length + " " +  elapsedTime + " ms");
	}
	
	public static <T> void shellSortHibbardTiming(Integer[] array) {
		long startTime =  System.currentTimeMillis();
		
		ShellSorts.hibbard(array);
		
		
		long stopTime =  System.currentTimeMillis();
		long elapsedTime = stopTime - startTime;
		System.out.println("Hibbard Sort: " + array.length + " " +  elapsedTime + " ms");
	}
	
	public static <T> void shellSortSedgewickTiming(Integer[] array) {
		long startTime =  System.currentTimeMillis();
		
		ShellSorts.sedgewick(array);
		
		
		long stopTime =  System.currentTimeMillis();
		long elapsedTime = stopTime - startTime;
		System.out.println("Sedgewick Sort: " + array.length + " " +  elapsedTime + " ms");
	}
	
	public static <T> void heapSortTiming(Integer[] array) {
		long startTime = System.currentTimeMillis();
		
		ShellSorts.heapSort(array);
		
		
		long stopTime =  System.currentTimeMillis();
		long elapsedTime = stopTime - startTime;
		System.out.println("Heap Sort: " + array.length + " " +  elapsedTime + " ms");
	}
}
