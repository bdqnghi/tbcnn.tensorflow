/**@author Austin Feydt
 * 4/21/15
 * EECS 233
 * Programming Assignment #4
 *This class tests the sorting algorithms are various sizes and types of
 *integer arrays, and displays all of the results to the console to be used in the
 *report later*/
public class Reporting1 {
	public static void main(String args[]){
		
		/**Testing HeapSort*/
		//Sorted arrays
		int[] heapsorted1 = new int[1000];
		for(int i =1; i<= 1000; i++)
			heapsorted1[i-1] = i;
			
		int[] heapsorted2 = new int[10000];
		for(int i = 1; i<= 10000; i++)
			heapsorted2[i-1] = i;
		
		int[] heapsorted3 = new int[100000];
		for(int i = 1; i<= 100000; i++)
			heapsorted3[i-1] = i;
		
		int[] heapsorted4 = new int[1000000];
		for(int i = 1; i<= 1000000; i++)
			heapsorted4[i-1] = i;
		
		//Creates array of runtimes
		long[] heapSortedResults = new long[12];
		heapSortedResults[0] = Sorting.heapSort(heapsorted1);
		heapSortedResults[1] = Sorting.heapSort(heapsorted1);
		heapSortedResults[2] = Sorting.heapSort(heapsorted1);
		heapSortedResults[3] = Sorting.heapSort(heapsorted2);
		heapSortedResults[4] = Sorting.heapSort(heapsorted2);
		heapSortedResults[5] = Sorting.heapSort(heapsorted2);
		heapSortedResults[6] = Sorting.heapSort(heapsorted3);
		heapSortedResults[7] = Sorting.heapSort(heapsorted3);
		heapSortedResults[8] = Sorting.heapSort(heapsorted3);
		heapSortedResults[9] = Sorting.heapSort(heapsorted4);
		heapSortedResults[10] = Sorting.heapSort(heapsorted4);
		heapSortedResults[11] = Sorting.heapSort(heapsorted4);
		
		//Array of median runtimes
		long[] heapSortedMedians = new long[4];
		heapSortedMedians[0] = getMedian(heapSortedResults[0], heapSortedResults[1], heapSortedResults[2]);
		heapSortedMedians[1] = getMedian(heapSortedResults[3], heapSortedResults[4], heapSortedResults[5]);
		heapSortedMedians[2] = getMedian(heapSortedResults[6], heapSortedResults[7], heapSortedResults[8]);
		heapSortedMedians[3] = getMedian(heapSortedResults[9], heapSortedResults[10], heapSortedResults[11]);

		//Displays first section of results
		System.out.println("HeapSort Results:\n~~~~~~~~~~~~~~~~~\n"
				+ "Sorted Medians:\n"
				+ "Length 1000:    " + heapSortedMedians[0] + " nanoseconds\n"
				+ "Length 10000:   " + heapSortedMedians[1] + " nanoseconds\n"
				+ "Length 100000:  " + heapSortedMedians[2] + " nanoseconds\n"
				+ "Length 1000000: " + heapSortedMedians[3] + " nanoseconds\n");
		
		//Reverse Sorted arrays
		int[] heaprevsort1 = new int[1000];
		for(int i = 0; i < 1000; i++)
			heaprevsort1[i] = 1000-i;
		
		int[] heaprevsort2 = new int[10000];
		for(int i = 0; i < 10000; i++)
			heaprevsort2[i] = 10000-i;

		int[] heaprevsort3 = new int[100000];
		for(int i = 0; i < 100000; i++)
			heaprevsort3[i] = 100000-i;
		
		int[] heaprevsort4 = new int[1000000];
		for(int i = 0; i < 1000000; i++)
			heaprevsort4[i] = 1000000-i;
		
		//Creates array of runtimes
		long[] heapRevSortedResults = new long[12];
		heapRevSortedResults[0] = Sorting.heapSort(heaprevsort1);
		heapRevSortedResults[1] = Sorting.heapSort(heaprevsort1);
		heapRevSortedResults[2] = Sorting.heapSort(heaprevsort1);
		heapRevSortedResults[3] = Sorting.heapSort(heaprevsort2);
		heapRevSortedResults[4] = Sorting.heapSort(heaprevsort2);
		heapRevSortedResults[5] = Sorting.heapSort(heaprevsort2);
		heapRevSortedResults[6] = Sorting.heapSort(heaprevsort3);
		heapRevSortedResults[7] = Sorting.heapSort(heaprevsort3);
		heapRevSortedResults[8] = Sorting.heapSort(heaprevsort3);
		heapRevSortedResults[9] = Sorting.heapSort(heaprevsort4);
		heapRevSortedResults[10] = Sorting.heapSort(heaprevsort4);
		heapRevSortedResults[11] = Sorting.heapSort(heaprevsort4);
		
		//Creates array of median runtimes
		long[] heapRevsortedMedians = new long[4];
		heapRevsortedMedians[0] = getMedian(heapRevSortedResults[0], heapRevSortedResults[1], heapRevSortedResults[2]);
		heapRevsortedMedians[1] = getMedian(heapRevSortedResults[3], heapRevSortedResults[4], heapRevSortedResults[5]);
		heapRevsortedMedians[2] = getMedian(heapRevSortedResults[6], heapRevSortedResults[7], heapRevSortedResults[8]);
		heapRevsortedMedians[3] = getMedian(heapRevSortedResults[9], heapRevSortedResults[10], heapRevSortedResults[11]);

		//Displays results for reverse sort
		System.out.println("Revserve Sorted Medians:\n"
				+ "Length 1000:    " + heapRevsortedMedians[0] + " nanoseconds\n"
				+ "Length 10000:   " + heapRevsortedMedians[1] + " nanoseconds\n"
				+ "Length 100000:  " + heapRevsortedMedians[2] + " nanoseconds\n"
				+ "Length 1000000: " + heapRevsortedMedians[3] + " nanoseconds\n");
		
		//Random arrays: 10 of each size
		int[] heaprandom1 = new int[1000];
		int[] heaprandom2 = new int[1000];
		int[] heaprandom3 = new int[1000];
		int[] heaprandom4 = new int[1000];
		int[] heaprandom5 = new int[1000];
		int[] heaprandom6 = new int[1000];
		int[] heaprandom7 = new int[1000];
		int[] heaprandom8 = new int[1000];
		int[] heaprandom9 = new int[1000];
		int[] heaprandom10 = new int[1000];
		int[] heaprandom11 = new int[10000];
		int[] heaprandom12 = new int[10000];
		int[] heaprandom13 = new int[10000];
		int[] heaprandom14 = new int[10000];
		int[] heaprandom15 = new int[10000];
		int[] heaprandom16 = new int[10000];
		int[] heaprandom17 = new int[10000];
		int[] heaprandom18 = new int[10000];
		int[] heaprandom19 = new int[10000];
		int[] heaprandom20 = new int[10000];
		int[] heaprandom21 = new int[100000];
		int[] heaprandom22 = new int[100000];
		int[] heaprandom23 = new int[100000];
		int[] heaprandom24 = new int[100000];
		int[] heaprandom25 = new int[100000];
		int[] heaprandom26 = new int[100000];
		int[] heaprandom27 = new int[100000];
		int[] heaprandom28 = new int[100000];
		int[] heaprandom29 = new int[100000];
		int[] heaprandom30 = new int[100000];
		int[] heaprandom31 = new int[1000000];
		int[] heaprandom32 = new int[1000000];
		int[] heaprandom33 = new int[1000000];
		int[] heaprandom34 = new int[1000000];
		int[] heaprandom35 = new int[1000000];
		int[] heaprandom36 = new int[1000000];
		int[] heaprandom37 = new int[1000000];
		int[] heaprandom38 = new int[1000000];
		int[] heaprandom39 = new int[1000000];
		int[] heaprandom40 = new int[1000000];

		//Randomizes arrays
		for(int i = 0; i < 1000; i++){
			heaprandom1[i] = (int)(1000*Math.random());
			heaprandom2[i] = (int)(1000*Math.random());
			heaprandom3[i] = (int)(1000*Math.random());
			heaprandom4[i] = (int)(1000*Math.random());
			heaprandom5[i] = (int)(1000*Math.random());
			heaprandom6[i] = (int)(1000*Math.random());
			heaprandom7[i] = (int)(1000*Math.random());
			heaprandom8[i] = (int)(1000*Math.random());
			heaprandom9[i] = (int)(1000*Math.random());
			heaprandom10[i] = (int)(1000*Math.random());
		}
		for(int i = 0; i < 10000; i++){
			heaprandom11[i] = (int)(10000*Math.random());
			heaprandom12[i] = (int)(10000*Math.random());
			heaprandom13[i] = (int)(10000*Math.random());
			heaprandom14[i] = (int)(10000*Math.random());
			heaprandom15[i] = (int)(10000*Math.random());
			heaprandom16[i] = (int)(10000*Math.random());
			heaprandom17[i] = (int)(10000*Math.random());
			heaprandom18[i] = (int)(10000*Math.random());
			heaprandom19[i] = (int)(10000*Math.random());
			heaprandom20[i] = (int)(10000*Math.random());
		}
		for(int i = 0; i < 100000; i++){
			heaprandom21[i] = (int)(100000*Math.random());
			heaprandom22[i] = (int)(100000*Math.random());
			heaprandom23[i] = (int)(100000*Math.random());
			heaprandom24[i] = (int)(100000*Math.random());
			heaprandom25[i] = (int)(100000*Math.random());
			heaprandom26[i] = (int)(100000*Math.random());
			heaprandom27[i] = (int)(100000*Math.random());
			heaprandom28[i] = (int)(100000*Math.random());
			heaprandom29[i] = (int)(100000*Math.random());
			heaprandom30[i] = (int)(100000*Math.random());
		}
		for(int i = 0; i < 1000000; i++){
			heaprandom31[i] = (int)(1000000*Math.random());
			heaprandom32[i] = (int)(1000000*Math.random());
			heaprandom33[i] = (int)(1000000*Math.random());
			heaprandom34[i] = (int)(1000000*Math.random());
			heaprandom35[i] = (int)(1000000*Math.random());
			heaprandom36[i] = (int)(1000000*Math.random());
			heaprandom37[i] = (int)(1000000*Math.random());
			heaprandom38[i] = (int)(1000000*Math.random());
			heaprandom39[i] = (int)(1000000*Math.random());
			heaprandom40[i] = (int)(1000000*Math.random());
		}
		
		//Creates array of runtimes for 1000 entries
		long[]  heapRandom1k = new long[10];
		heapRandom1k[0] = Sorting.heapSort(heaprandom1);
		heapRandom1k[1] = Sorting.heapSort(heaprandom2);
		heapRandom1k[2] = Sorting.heapSort(heaprandom3);
		heapRandom1k[3] = Sorting.heapSort(heaprandom4);
		heapRandom1k[4] = Sorting.heapSort(heaprandom5);
		heapRandom1k[5] = Sorting.heapSort(heaprandom6);
		heapRandom1k[6] = Sorting.heapSort(heaprandom7);
		heapRandom1k[7] = Sorting.heapSort(heaprandom8);
		heapRandom1k[8] = Sorting.heapSort(heaprandom9);
		heapRandom1k[9] = Sorting.heapSort(heaprandom10);
		
		//Creates array of runtimes for 10000 entries
		long[] heapRandom10k = new long[10];
		heapRandom10k[0] = Sorting.heapSort(heaprandom11);
		heapRandom10k[1] = Sorting.heapSort(heaprandom12);
		heapRandom10k[2] = Sorting.heapSort(heaprandom13);
		heapRandom10k[3] = Sorting.heapSort(heaprandom14);
		heapRandom10k[4] = Sorting.heapSort(heaprandom15);
		heapRandom10k[5] = Sorting.heapSort(heaprandom16);
		heapRandom10k[6] = Sorting.heapSort(heaprandom17);
		heapRandom10k[7] = Sorting.heapSort(heaprandom18);
		heapRandom10k[8] = Sorting.heapSort(heaprandom19);
		heapRandom10k[9] = Sorting.heapSort(heaprandom20);
		
		//Creates array of runtimes for 100000 entries
		long[] heapRandom100k = new long[10];
		heapRandom100k[0] = Sorting.heapSort(heaprandom21);
		heapRandom100k[1] = Sorting.heapSort(heaprandom22);
		heapRandom100k[2] = Sorting.heapSort(heaprandom23);
		heapRandom100k[3] = Sorting.heapSort(heaprandom24);
		heapRandom100k[4] = Sorting.heapSort(heaprandom25);
		heapRandom100k[5] = Sorting.heapSort(heaprandom26);
		heapRandom100k[6] = Sorting.heapSort(heaprandom27);
		heapRandom100k[7] = Sorting.heapSort(heaprandom28);
		heapRandom100k[8] = Sorting.heapSort(heaprandom29);
		heapRandom100k[9] = Sorting.heapSort(heaprandom30);
		
		//Creates array of runtimes for 1000000 entries
		long[] heapRandom1000k = new long[10];
		heapRandom1000k[0] = Sorting.heapSort(heaprandom31);
		heapRandom1000k[1] = Sorting.heapSort(heaprandom32);
		heapRandom1000k[2] = Sorting.heapSort(heaprandom33);
		heapRandom1000k[3] = Sorting.heapSort(heaprandom34);
		heapRandom1000k[4] = Sorting.heapSort(heaprandom35);
		heapRandom1000k[5] = Sorting.heapSort(heaprandom36);
		heapRandom1000k[6] = Sorting.heapSort(heaprandom37);
		heapRandom1000k[7] = Sorting.heapSort(heaprandom38);
		heapRandom1000k[8] = Sorting.heapSort(heaprandom39);
		heapRandom1000k[9] = Sorting.heapSort(heaprandom40);		
		
		//Displays averages and variances for each random array
		System.out.println("Random Times:\n"
				+ "Length 1000:    Avg: " + meanVal(heapRandom1k)+ " nanoseconds,"
						+ " Variance: " + varianceVal(heapRandom1k) + " nanoseconds\n"
				+ "Length 10000:   Avg: " + meanVal(heapRandom10k) + " nanoseconds,"
						+ " Variance: " + varianceVal(heapRandom10k) + " nanoseconds\n"
				+ "Length 100000:  Avg: " + meanVal(heapRandom100k) + " nanoseconds,"
						+ " Variance: " + varianceVal(heapRandom100k) + " nanoseconds\n"
				+ "Length 1000000: Avg: " + meanVal(heapRandom1000k) + " nanoseconds,"
						+ " Variance: " + varianceVal(heapRandom1000k) + " nanoseconds\n");
		
		/**Testing QuickSort*/
		//Sorted arrays of each size
		int[] quicksorted1 = new int[1000];
		for(int i =1; i<= 1000; i++){
			quicksorted1[i-1] = i;
		}
			
		int[] quicksorted2 = new int[10000];
		for(int i = 1; i<= 10000; i++)
			quicksorted2[i-1] = i;
		
		int[] quicksorted3 = new int[100000];
		for(int i = 1; i<= 100000; i++)
			quicksorted3[i-1] = i;
		
		int[] quicksorted4 = new int[1000000];
		for(int i = 1; i<= 1000000; i++)
			quicksorted4[i-1] = i;
		
		//Creates array of runtimes
		long[] quickSortedResults = new long[12];
		quickSortedResults[0] = Sorting.quickSort(quicksorted1);
		quickSortedResults[1] = Sorting.quickSort(quicksorted1);
		quickSortedResults[2] = Sorting.quickSort(quicksorted1);
		quickSortedResults[3] = Sorting.quickSort(quicksorted2);
		quickSortedResults[4] = Sorting.quickSort(quicksorted2);
		quickSortedResults[5] = Sorting.quickSort(quicksorted2);
		quickSortedResults[6] = Sorting.quickSort(quicksorted3);
		quickSortedResults[7] = Sorting.quickSort(quicksorted3);
		quickSortedResults[8] = Sorting.quickSort(quicksorted3);
		quickSortedResults[9] = Sorting.quickSort(quicksorted4);
		quickSortedResults[10] = Sorting.quickSort(quicksorted4);
		quickSortedResults[11] = Sorting.quickSort(quicksorted4);
		
		//Creates array of median runtimes
		long[] quicksortedMedians = new long[4];
		quicksortedMedians[0] = getMedian(quickSortedResults[0], quickSortedResults[1], quickSortedResults[2]);
		quicksortedMedians[1] = getMedian(quickSortedResults[3], quickSortedResults[4], quickSortedResults[5]);
		quicksortedMedians[2] = getMedian(quickSortedResults[6], quickSortedResults[7], quickSortedResults[8]);
		quicksortedMedians[3] = getMedian(quickSortedResults[9], quickSortedResults[10], quickSortedResults[11]);


		//Displays sorted results
		System.out.println("\n\nQuickSort Results:\n~~~~~~~~~~~~~~~~~~\n"
				+"Sorted Medians:\n"
				+"Length 1000:     " + quicksortedMedians[0] + " nanoseconds\n"
				+"Length 10000:    " + quicksortedMedians[1] + " nanoseconds\n"
				+"Length 100000:   " + quicksortedMedians[2] + " nanoseconds\n"
				+"Length 1000000:  " + quicksortedMedians[3] + " nanoseconds\n");
		
		//Reverse Sorted arrays of each size
		int[] quickrevsort1 = new int[1000];
		for(int i = 0; i < 1000; i++)
			quickrevsort1[i] = 1000-i;
		
		int[] quickrevsort2 = new int[10000];
		for(int i = 0; i < 10000; i++)
			quickrevsort2[i] = 10000-i;

		int[] quickrevsort3 = new int[100000];
		for(int i = 0; i < 100000; i++)
			quickrevsort3[i] = 100000-i;
		
		int[] quickrevsort4 = new int[1000000];
		for(int i = 0; i < 1000000; i++)
			quickrevsort4[i] = 1000000-i;
		
		//Creates array of runtimes
		long[] quickRevSortedResults = new long[12];
		quickRevSortedResults[0] = Sorting.quickSort(quickrevsort1);
		quickRevSortedResults[1] = Sorting.quickSort(quickrevsort1);
		quickRevSortedResults[2] = Sorting.quickSort(quickrevsort1);
		quickRevSortedResults[3] = Sorting.quickSort(quickrevsort2);
		quickRevSortedResults[4] = Sorting.quickSort(quickrevsort2);
		quickRevSortedResults[5] = Sorting.quickSort(quickrevsort2);
		quickRevSortedResults[6] = Sorting.quickSort(quickrevsort3);
		quickRevSortedResults[7] = Sorting.quickSort(quickrevsort3);
		quickRevSortedResults[8] = Sorting.quickSort(quickrevsort3);
		quickRevSortedResults[9] = Sorting.quickSort(quickrevsort4);
		quickRevSortedResults[10] = Sorting.quickSort(quickrevsort4);
		quickRevSortedResults[11] = Sorting.quickSort(quickrevsort4);
		
		//Creates array of median runtimes
		long[] quickRevSortedMedians = new long[4];
		quickRevSortedMedians[0] = getMedian(quickRevSortedResults[0], quickRevSortedResults[1], quickRevSortedResults[2]);
		quickRevSortedMedians[1] = getMedian(quickRevSortedResults[3], quickRevSortedResults[4], quickRevSortedResults[5]);
		quickRevSortedMedians[2] = getMedian(quickRevSortedResults[6], quickRevSortedResults[7], quickRevSortedResults[8]);
		quickRevSortedMedians[3] = getMedian(quickRevSortedResults[9], quickRevSortedResults[10], quickRevSortedResults[11]);

		//Displays reverse sort results
		System.out.println("Reverse Sorted Medians:\n"
				+ "Length 1000:    " + quickRevSortedMedians[0] + " nanoseconds\n"
				+ "Length 10000:   " + quickRevSortedMedians[1] + " nanoseconds\n"
				+ "Length 100000:  " + quickRevSortedMedians[2] + " nanoseconds\n"
				+ "Length 1000000: " + quickRevSortedMedians[3] + " nanoseconds\n");
		
		//Random arrays: 10 of each size
		int[] quickrandom1 = new int[1000];
		int[] quickrandom2 = new int[1000];
		int[] quickrandom3 = new int[1000];
		int[] quickrandom4 = new int[1000];
		int[] quickrandom5 = new int[1000];
		int[] quickrandom6 = new int[1000];
		int[] quickrandom7 = new int[1000];
		int[] quickrandom8 = new int[1000];
		int[] quickrandom9 = new int[1000];
		int[] quickrandom10 = new int[1000];
		int[] quickrandom11 = new int[10000];
		int[] quickrandom12 = new int[10000];
		int[] quickrandom13 = new int[10000];
		int[] quickrandom14 = new int[10000];
		int[] quickrandom15 = new int[10000];
		int[] quickrandom16 = new int[10000];
		int[] quickrandom17 = new int[10000];
		int[] quickrandom18 = new int[10000];
		int[] quickrandom19 = new int[10000];
		int[] quickrandom20 = new int[10000];
		int[] quickrandom21 = new int[100000];
		int[] quickrandom22 = new int[100000];
		int[] quickrandom23 = new int[100000];
		int[] quickrandom24 = new int[100000];
		int[] quickrandom25 = new int[100000];
		int[] quickrandom26 = new int[100000];
		int[] quickrandom27 = new int[100000];
		int[] quickrandom28 = new int[100000];
		int[] quickrandom29 = new int[100000];
		int[] quickrandom30 = new int[100000];
		int[] quickrandom31 = new int[1000000];
		int[] quickrandom32 = new int[1000000];
		int[] quickrandom33 = new int[1000000];
		int[] quickrandom34 = new int[1000000];
		int[] quickrandom35 = new int[1000000];
		int[] quickrandom36 = new int[1000000];
		int[] quickrandom37 = new int[1000000];
		int[] quickrandom38 = new int[1000000];
		int[] quickrandom39 = new int[1000000];
		int[] quickrandom40 = new int[1000000];

		//Randomizes each array
		for(int i = 0; i < 1000; i++){
			quickrandom1[i] = (int)(1000*Math.random());
			quickrandom2[i] = (int)(1000*Math.random());
			quickrandom3[i] = (int)(1000*Math.random());
			quickrandom4[i] = (int)(1000*Math.random());
			quickrandom5[i] = (int)(1000*Math.random());
			quickrandom6[i] = (int)(1000*Math.random());
			quickrandom7[i] = (int)(1000*Math.random());
			quickrandom8[i] = (int)(1000*Math.random());
			quickrandom9[i] = (int)(1000*Math.random());
			quickrandom10[i] = (int)(1000*Math.random());
		}
		for(int i = 0; i < 10000; i++){
			quickrandom11[i] = (int)(10000*Math.random());
			quickrandom12[i] = (int)(10000*Math.random());
			quickrandom13[i] = (int)(10000*Math.random());
			quickrandom14[i] = (int)(10000*Math.random());
			quickrandom15[i] = (int)(10000*Math.random());
			quickrandom16[i] = (int)(10000*Math.random());
			quickrandom17[i] = (int)(10000*Math.random());
			quickrandom18[i] = (int)(10000*Math.random());
			quickrandom19[i] = (int)(10000*Math.random());
			quickrandom20[i] = (int)(10000*Math.random());
		}
		for(int i = 0; i < 100000; i++){
			quickrandom21[i] = (int)(100000*Math.random());
			quickrandom22[i] = (int)(100000*Math.random());
			quickrandom23[i] = (int)(100000*Math.random());
			quickrandom24[i] = (int)(100000*Math.random());
			quickrandom25[i] = (int)(100000*Math.random());
			quickrandom26[i] = (int)(100000*Math.random());
			quickrandom27[i] = (int)(100000*Math.random());
			quickrandom28[i] = (int)(100000*Math.random());
			quickrandom29[i] = (int)(100000*Math.random());
			quickrandom30[i] = (int)(100000*Math.random());
		}
		for(int i = 0; i < 1000000; i++){
			quickrandom31[i] = (int)(1000000*Math.random());
			quickrandom32[i] = (int)(1000000*Math.random());
			quickrandom33[i] = (int)(1000000*Math.random());
			quickrandom34[i] = (int)(1000000*Math.random());
			quickrandom35[i] = (int)(1000000*Math.random());
			quickrandom36[i] = (int)(1000000*Math.random());
			quickrandom37[i] = (int)(1000000*Math.random());
			quickrandom38[i] = (int)(1000000*Math.random());
			quickrandom39[i] = (int)(1000000*Math.random());
			quickrandom40[i] = (int)(1000000*Math.random());
		}
		
		//Creates array of runtimes for 1000 entries
		long[] quickRandom1k = new long[10];
		quickRandom1k[0] = Sorting.quickSort(quickrandom1);
		quickRandom1k[1] = Sorting.quickSort(quickrandom2);
		quickRandom1k[2] = Sorting.quickSort(quickrandom3);
		quickRandom1k[3] = Sorting.quickSort(quickrandom4);
		quickRandom1k[4] = Sorting.quickSort(quickrandom5);
		quickRandom1k[5] = Sorting.quickSort(quickrandom6);
		quickRandom1k[6] = Sorting.quickSort(quickrandom7);
		quickRandom1k[7] = Sorting.quickSort(quickrandom8);
		quickRandom1k[8] = Sorting.quickSort(quickrandom9);
		quickRandom1k[9] = Sorting.quickSort(quickrandom10);

		//Creates array of runtimes for 10000 entries
		long[] quickRandom10k = new long[10];
		quickRandom10k[0] = Sorting.quickSort(quickrandom11);
		quickRandom10k[1] = Sorting.quickSort(quickrandom12);
		quickRandom10k[2] = Sorting.quickSort(quickrandom13);
		quickRandom10k[3] = Sorting.quickSort(quickrandom14);
		quickRandom10k[4] = Sorting.quickSort(quickrandom15);
		quickRandom10k[5] = Sorting.quickSort(quickrandom16);
		quickRandom10k[6] = Sorting.quickSort(quickrandom17);
		quickRandom10k[7] = Sorting.quickSort(quickrandom18);
		quickRandom10k[8] = Sorting.quickSort(quickrandom19);
		quickRandom10k[9] = Sorting.quickSort(quickrandom20);
		
		//Creates array of runtimes for 100000 entries
		long[] quickRandom100k = new long[10];
		quickRandom100k[0] = Sorting.quickSort(quickrandom21);
		quickRandom100k[1] = Sorting.quickSort(quickrandom22);
		quickRandom100k[2] = Sorting.quickSort(quickrandom23);
		quickRandom100k[3] = Sorting.quickSort(quickrandom24);
		quickRandom100k[4] = Sorting.quickSort(quickrandom25);
		quickRandom100k[5] = Sorting.quickSort(quickrandom26);
		quickRandom100k[6] = Sorting.quickSort(quickrandom27);
		quickRandom100k[7] = Sorting.quickSort(quickrandom28);
		quickRandom100k[8] = Sorting.quickSort(quickrandom29);
		quickRandom100k[9] = Sorting.quickSort(quickrandom30);
		
		//Creates array of runtimes for 1000000 entries
		long[] quickRandom1000k = new long[10];
		quickRandom1000k[0] = Sorting.quickSort(quickrandom31);
		quickRandom1000k[1] = Sorting.quickSort(quickrandom32);
		quickRandom1000k[2] = Sorting.quickSort(quickrandom33);
		quickRandom1000k[3] = Sorting.quickSort(quickrandom34);
		quickRandom1000k[4] = Sorting.quickSort(quickrandom35);
		quickRandom1000k[5] = Sorting.quickSort(quickrandom36);
		quickRandom1000k[6] = Sorting.quickSort(quickrandom37);
		quickRandom1000k[7] = Sorting.quickSort(quickrandom38);
		quickRandom1000k[8] = Sorting.quickSort(quickrandom39);
		quickRandom1000k[9] = Sorting.quickSort(quickrandom40);
		
		//Displays averages and variances for each random array
		System.out.println("Random Times:\n"
				+"Length 1000:    Avg: " + meanVal(quickRandom1k) + " nanoseconds,"
				+ " Variance: " + varianceVal(quickRandom1k) + " nanoseconds\n"
				+"Length 10000:   Avg: " + meanVal(quickRandom10k) + " nanoseconds,"
				+ " Variance: " + varianceVal(quickRandom10k) + " nanoseconds\n"
				+"Length 100000:  Avg: " + meanVal(quickRandom100k) + " nanoseconds,"
				+ " Variance: " + varianceVal(quickRandom100k) + " nanoseconds\n"
				+"Length 1000000: Avg: " + meanVal(quickRandom1000k) + " nanoseconds,"
				+ " Variance: " + varianceVal(quickRandom1000k) + " nanoseconds\n");
	
		/**Testing MergeSort*/
		//Sorted arrays of each size
		int[] mergesorted1 = new int[1000];
		for(int i =1; i<= 1000; i++){
			mergesorted1[i-1] = i;
		}
			
		int[] mergesorted2 = new int[10000];
		for(int i = 1; i<= 10000; i++)
			mergesorted2[i-1] = i;
		
		int[] mergesorted3 = new int[100000];
		for(int i = 1; i<= 100000; i++)
			mergesorted3[i-1] = i;
		
		int[] mergesorted4 = new int[1000000];
		for(int i = 1; i<= 1000000; i++)
			mergesorted4[i-1] = i;
		
		//Creates array of runtimes
		long[] mergeSortedResults = new long[12];
		mergeSortedResults[0] = Sorting.mergeSort(mergesorted1);
		mergeSortedResults[1] = Sorting.mergeSort(mergesorted1);
		mergeSortedResults[2] = Sorting.mergeSort(mergesorted1);
		mergeSortedResults[3] = Sorting.mergeSort(mergesorted2);
		mergeSortedResults[4] = Sorting.mergeSort(mergesorted2);
		mergeSortedResults[5] = Sorting.mergeSort(mergesorted2);
		mergeSortedResults[6] = Sorting.mergeSort(mergesorted3);
		mergeSortedResults[7] = Sorting.mergeSort(mergesorted3);
		mergeSortedResults[8] = Sorting.mergeSort(mergesorted3);
		mergeSortedResults[9] = Sorting.mergeSort(mergesorted4);
		mergeSortedResults[10] = Sorting.mergeSort(mergesorted4);
		mergeSortedResults[11] = Sorting.mergeSort(mergesorted4);
		
		//Creates array of median runtimes
		long[] mergeSortedMedians = new long[4];
		mergeSortedMedians[0] = getMedian(mergeSortedResults[0], mergeSortedResults[1], mergeSortedResults[2]);
		mergeSortedMedians[1] = getMedian(mergeSortedResults[3], mergeSortedResults[4], mergeSortedResults[5]);
		mergeSortedMedians[2] = getMedian(mergeSortedResults[6], mergeSortedResults[7], mergeSortedResults[8]);
		mergeSortedMedians[3] = getMedian(mergeSortedResults[9], mergeSortedResults[10], mergeSortedResults[11]);

		//Displays results for sorted arrays
		System.out.println("\n\nMergeSort Results:\n~~~~~~~~~~~~~~~~~~\n"
				+"Sorted Medians:\n"
				+"Length 1000:     " + mergeSortedMedians[0] + " nanoseconds\n"
				+"Length 10000:    " + mergeSortedMedians[1] + " nanoseconds\n"
				+"Length 100000:   " + mergeSortedMedians[2] + " nanoseconds\n"
				+"Length 1000000:  " + mergeSortedMedians[3] + " nanoseconds\n");
		
		//Reverse Sorted arrays
		int[] mergerevsort1 = new int[1000];
		for(int i = 0; i < 1000; i++)
			mergerevsort1[i] = 1000-i;
		
		int[] mergerevsort2 = new int[10000];
		for(int i = 0; i < 10000; i++)
			mergerevsort2[i] = 10000-i;

		int[] mergerevsort3 = new int[100000];
		for(int i = 0; i < 100000; i++)
			mergerevsort3[i] = 100000-i;
		
		int[] mergerevsort4 = new int[1000000];
		for(int i = 0; i < 1000000; i++)
			mergerevsort4[i] = 1000000-i;
		
		//Creates array of runtimes
		long[] mergeRevSortedResults = new long[12];
		mergeRevSortedResults[0] = Sorting.mergeSort(mergerevsort1);
		mergeRevSortedResults[1] = Sorting.mergeSort(mergerevsort1);
		mergeRevSortedResults[2] = Sorting.mergeSort(mergerevsort1);
		mergeRevSortedResults[3] = Sorting.mergeSort(mergerevsort2);
		mergeRevSortedResults[4] = Sorting.mergeSort(mergerevsort2);
		mergeRevSortedResults[5] = Sorting.mergeSort(mergerevsort2);
		mergeRevSortedResults[6] = Sorting.mergeSort(mergerevsort3);
		mergeRevSortedResults[7] = Sorting.mergeSort(mergerevsort3);
		mergeRevSortedResults[8] = Sorting.mergeSort(mergerevsort3);
		mergeRevSortedResults[9] = Sorting.mergeSort(mergerevsort4);
		mergeRevSortedResults[10] = Sorting.mergeSort(mergerevsort4);
		mergeRevSortedResults[11] = Sorting.mergeSort(mergerevsort4);
		
		//Creates array of median runtimes
		long[] mergeRevSortedMedians = new long[4];
		mergeRevSortedMedians[0] = getMedian(mergeRevSortedResults[0], mergeRevSortedResults[1], mergeRevSortedResults[2]);
		mergeRevSortedMedians[1] = getMedian(mergeRevSortedResults[3], mergeRevSortedResults[4], mergeRevSortedResults[5]);
		mergeRevSortedMedians[2] = getMedian(mergeRevSortedResults[6], mergeRevSortedResults[7], mergeRevSortedResults[8]);
		mergeRevSortedMedians[3] = getMedian(mergeRevSortedResults[9], mergeRevSortedResults[10], mergeRevSortedResults[11]);

		//Displays results for reverse sorts
		System.out.println("Reverse Sorted Medians:\n"
				+ "Length 1000:    " + mergeRevSortedMedians[0] + " nanoseconds\n"
				+ "Length 10000:   " + mergeRevSortedMedians[1] + " nanoseconds\n"
				+ "Length 100000:  " + mergeRevSortedMedians[2] + " nanoseconds\n"
				+ "Length 1000000: " + mergeRevSortedMedians[3] + " nanoseconds\n");
	
		//Random arrays:10 of each size
		int[] mergerandom1 = new int[1000];
		int[] mergerandom2 = new int[1000];
		int[] mergerandom3 = new int[1000];
		int[] mergerandom4 = new int[1000];
		int[] mergerandom5 = new int[1000];
		int[] mergerandom6 = new int[1000];
		int[] mergerandom7 = new int[1000];
		int[] mergerandom8 = new int[1000];
		int[] mergerandom9 = new int[1000];
		int[] mergerandom10 = new int[1000];
		int[] mergerandom11 = new int[10000];
		int[] mergerandom12 = new int[10000];
		int[] mergerandom13 = new int[10000];
		int[] mergerandom14 = new int[10000];
		int[] mergerandom15 = new int[10000];
		int[] mergerandom16 = new int[10000];
		int[] mergerandom17 = new int[10000];
		int[] mergerandom18 = new int[10000];
		int[] mergerandom19 = new int[10000];
		int[] mergerandom20 = new int[10000];
		int[] mergerandom21 = new int[100000];
		int[] mergerandom22 = new int[100000];
		int[] mergerandom23 = new int[100000];
		int[] mergerandom24 = new int[100000];
		int[] mergerandom25 = new int[100000];
		int[] mergerandom26 = new int[100000];
		int[] mergerandom27 = new int[100000];
		int[] mergerandom28 = new int[100000];
		int[] mergerandom29 = new int[100000];
		int[] mergerandom30 = new int[100000];
		int[] mergerandom31 = new int[1000000];
		int[] mergerandom32 = new int[1000000];
		int[] mergerandom33 = new int[1000000];
		int[] mergerandom34 = new int[1000000];
		int[] mergerandom35 = new int[1000000];
		int[] mergerandom36 = new int[1000000];
		int[] mergerandom37 = new int[1000000];
		int[] mergerandom38 = new int[1000000];
		int[] mergerandom39 = new int[1000000];
		int[] mergerandom40 = new int[1000000];

		//Randomizes each array
		for(int i = 0; i < 1000; i++){
			mergerandom1[i] = (int)(1000*Math.random());
			mergerandom2[i] = (int)(1000*Math.random());
			mergerandom3[i] = (int)(1000*Math.random());
			mergerandom4[i] = (int)(1000*Math.random());
			mergerandom5[i] = (int)(1000*Math.random());
			mergerandom6[i] = (int)(1000*Math.random());
			mergerandom7[i] = (int)(1000*Math.random());
			mergerandom8[i] = (int)(1000*Math.random());
			mergerandom9[i] = (int)(1000*Math.random());
			mergerandom10[i] = (int)(1000*Math.random());
		}
		for(int i = 0; i < 10000; i++){
			mergerandom11[i] = (int)(10000*Math.random());
			mergerandom12[i] = (int)(10000*Math.random());
			mergerandom13[i] = (int)(10000*Math.random());
			mergerandom14[i] = (int)(10000*Math.random());
			mergerandom15[i] = (int)(10000*Math.random());
			mergerandom16[i] = (int)(10000*Math.random());
			mergerandom17[i] = (int)(10000*Math.random());
			mergerandom18[i] = (int)(10000*Math.random());
			mergerandom19[i] = (int)(10000*Math.random());
			mergerandom20[i] = (int)(10000*Math.random());
		}
		for(int i = 0; i < 100000; i++){
			mergerandom21[i] = (int)(100000*Math.random());
			mergerandom22[i] = (int)(100000*Math.random());
			mergerandom23[i] = (int)(100000*Math.random());
			mergerandom24[i] = (int)(100000*Math.random());
			mergerandom25[i] = (int)(100000*Math.random());
			mergerandom26[i] = (int)(100000*Math.random());
			mergerandom27[i] = (int)(100000*Math.random());
			mergerandom28[i] = (int)(100000*Math.random());
			mergerandom29[i] = (int)(100000*Math.random());
			mergerandom30[i] = (int)(100000*Math.random());
		}
		for(int i = 0; i < 1000000; i++){
			mergerandom31[i] = (int)(1000000*Math.random());
			mergerandom32[i] = (int)(1000000*Math.random());
			mergerandom33[i] = (int)(1000000*Math.random());
			mergerandom34[i] = (int)(1000000*Math.random());
			mergerandom35[i] = (int)(1000000*Math.random());
			mergerandom36[i] = (int)(1000000*Math.random());
			mergerandom37[i] = (int)(1000000*Math.random());
			mergerandom38[i] = (int)(1000000*Math.random());
			mergerandom39[i] = (int)(1000000*Math.random());
			mergerandom40[i] = (int)(1000000*Math.random());
		}
		
		//Creates array of runtimes for 1000 entries
		long[] mergeRandom1k = new long[10];
		mergeRandom1k[0] = Sorting.mergeSort(mergerandom1);
		mergeRandom1k[1] = Sorting.mergeSort(mergerandom2);
		mergeRandom1k[2] = Sorting.mergeSort(mergerandom3);
		mergeRandom1k[3] = Sorting.mergeSort(mergerandom4);
		mergeRandom1k[4] = Sorting.mergeSort(mergerandom5);
		mergeRandom1k[5] = Sorting.mergeSort(mergerandom6);
		mergeRandom1k[6] = Sorting.mergeSort(mergerandom7);
		mergeRandom1k[7] = Sorting.mergeSort(mergerandom8);
		mergeRandom1k[8] = Sorting.mergeSort(mergerandom9);
		mergeRandom1k[9] = Sorting.mergeSort(mergerandom10);
		
		//Creates array of runtimes for 10000 entries
		long[] mergeRandom10k = new long[10];
		mergeRandom10k[0] = Sorting.mergeSort(mergerandom11);
		mergeRandom10k[1] = Sorting.mergeSort(mergerandom12);
		mergeRandom10k[2] = Sorting.mergeSort(mergerandom13);
		mergeRandom10k[3] = Sorting.mergeSort(mergerandom14);
		mergeRandom10k[4] = Sorting.mergeSort(mergerandom15);
		mergeRandom10k[5] = Sorting.mergeSort(mergerandom16);
		mergeRandom10k[6] = Sorting.mergeSort(mergerandom17);
		mergeRandom10k[7] = Sorting.mergeSort(mergerandom18);
		mergeRandom10k[8] = Sorting.mergeSort(mergerandom19);
		mergeRandom10k[9] = Sorting.mergeSort(mergerandom20);
		
		//Creates array of runtimes for 100000 entries
		long[] mergeRandom100k = new long[10];
		mergeRandom100k[0] = Sorting.mergeSort(mergerandom21);
		mergeRandom100k[1] = Sorting.mergeSort(mergerandom22);
		mergeRandom100k[2] = Sorting.mergeSort(mergerandom23);
		mergeRandom100k[3] = Sorting.mergeSort(mergerandom24);
		mergeRandom100k[4] = Sorting.mergeSort(mergerandom25);
		mergeRandom100k[5] = Sorting.mergeSort(mergerandom26);
		mergeRandom100k[6] = Sorting.mergeSort(mergerandom27);
		mergeRandom100k[7] = Sorting.mergeSort(mergerandom28);
		mergeRandom100k[8] = Sorting.mergeSort(mergerandom29);
		mergeRandom100k[9] = Sorting.mergeSort(mergerandom30);
		
		//Creates array of runtimes for 1000000 entries
		long[] mergeRandom1000k = new long[10];
		mergeRandom1000k[0] = Sorting.mergeSort(mergerandom31);
		mergeRandom1000k[1] = Sorting.mergeSort(mergerandom32);
		mergeRandom1000k[2] = Sorting.mergeSort(mergerandom33);
		mergeRandom1000k[3] = Sorting.mergeSort(mergerandom34);
		mergeRandom1000k[4] = Sorting.mergeSort(mergerandom35);
		mergeRandom1000k[5] = Sorting.mergeSort(mergerandom36);
		mergeRandom1000k[6] = Sorting.mergeSort(mergerandom37);
		mergeRandom1000k[7] = Sorting.mergeSort(mergerandom38);
		mergeRandom1000k[8] = Sorting.mergeSort(mergerandom39);
		mergeRandom1000k[9] = Sorting.mergeSort(mergerandom40);
		
		//Displays averages and variances for each random array
		System.out.println("Random Times:\n"
				+"Length 1000:    Avg: " + meanVal(mergeRandom1k) + " nanoseconds,"
				+ " Variance: " + varianceVal(mergeRandom1k) + " nanoseconds\n"
				+"Length 10000:   Avg: " + meanVal(mergeRandom10k) + " nanoseconds,"
				+ " Variance: " + varianceVal(mergeRandom10k) + " nanoseconds\n"
				+"Length 100000:  Avg: " + meanVal(mergeRandom100k) + " nanoseconds,"
				+ " Variance: " + varianceVal(mergeRandom100k) + " nanoseconds\n"
				+"Length 1000000: Avg: " + meanVal(mergeRandom1000k) + " nanoseconds,"
				+ " Variance: " + varianceVal(mergeRandom1000k) + " nanoseconds\n");
	}
	
	/**This method compares three long, and outputs the median
	 * @param a  first number
	 * @param b  second number
	 * @param c  third number
	 * @return  the median of the three number*/
	public static long getMedian(long a, long b, long c){
		if(a > b){
			if(b>c)
				return b;
			else if(a>c)
				return c;
			else
				return a;
			}
		else{
			if(a>c)
				return a;
			else if( b>c)
				return c;
			else
				return b;
		}
	}
	
	/**This method returns the variance of the input array
	 * @param arrayOfSamples  array to be analyzed
	 * @return  the variance of the array*/
	public static double varianceVal(long[] arrayOfSamples){
		double avg = meanVal(arrayOfSamples);
		double var = 0;
		for(int i = 1; i <= arrayOfSamples.length; i++)
			var += Math.pow((arrayOfSamples[i-1] - avg),2);
		return var/(arrayOfSamples.length -1);
	}
	
	/**This method returns the mean value of the values in the input array
	 * @param arrayOfSamples  array to be analyzed
	 * @return  the average value in the array*/
	public static double meanVal(long[] arrayOfSamples){
		long l = 0;
		for(long i: arrayOfSamples){
			l+=i;
		}
		return l/arrayOfSamples.length;
	}
}