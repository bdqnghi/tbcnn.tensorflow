package exercize0232_merge_wo_sentinel;

import java.util.ArrayList;
import java.util.List;

import utility.Utility;
import utility.sort.MultithreadedSort;
import utility.sort.Sort;

public class App
{

	public static void main(String[] args)
	{
		int cores = Runtime.getRuntime().availableProcessors();
		System.out.println("The number of cores is: " + cores);

		System.out.println(System.getenv("PROCESSOR_IDENTIFIER"));
		System.out.println(System.getenv("PROCESSOR_ARCHITECTURE"));
		System.out.println(System.getenv("PROCESSOR_ARCHITEW6432"));
		System.out.println(System.getenv("NUMBER_OF_PROCESSORS"));

		System.out.println("Free memory (bytes): "
				+ Runtime.getRuntime().freeMemory());

		System.out.println("Total memory (bytes): "
				+ Runtime.getRuntime().totalMemory());
		// App app = new App();
		
		List<Integer> sortArrayMerge = new ArrayList<>();

		Utility.populateArray(sortArrayMerge);
		List<Integer> sortArrayMergeParallel = Utility.copyArray(sortArrayMerge);
		List<Integer> sortArrayMergeParallelWO = Utility.copyArray(sortArrayMerge);
		List<Integer> sortArrayMergeParallelOptimized = Utility.copyArray(sortArrayMerge);
		// Utility.printArray(sortArray);
		// Utility.printArray(sortArrayCopy);

		long startParallelMergeWO = System.currentTimeMillis();
		MultithreadedSort.runParallelMerge(sortArrayMergeParallelWO, cores, MultithreadedSort.MERGE_SORT_WO_SENTINEL );
		long endParrallelMergeWO = System.currentTimeMillis();
		
		long startParallelMerge = System.currentTimeMillis();
		//MultithreadedSort.runParallelMerge(sortArrayMergeParallel, cores, MultithreadedSort.MERGE_SORT);
		long endParrallelMerge = System.currentTimeMillis();
		
		long startParallelMergeOptimized = System.currentTimeMillis();
		//MultithreadedSort.runParallelMerge(sortArrayMergeParallelOptimized, cores, MultithreadedSort.MERGE_SORT_OPTIMIZED);
		long endParallelMergeOptimized = System.currentTimeMillis();

		
		
		long startMerge = System.currentTimeMillis();
		//Sort.mergeSort(sortArrayMerge, 0, sortArrayMerge.size() - 1);
		long endMerge = System.currentTimeMillis();

		// The search without sentinels seems to perform slightly faster with
		// the ratio of times
		// approaching to 1 as the size of array grows
		System.out.println("Merge time paralle optimized is: " + (endParallelMergeOptimized - startParallelMergeOptimized)
				+ "\nMerge time is: " + (endMerge - startMerge)
				+ "\nParralel merge time WO is: " + (endParrallelMergeWO - startParallelMergeWO)
				+ "\nParralel merge time is: " + (endParrallelMerge - startParallelMerge));
//		 Utility.printArray(sortArrayMerge);
//		 Utility.printArray(sortArrayMergeWO);
//		 Utility.printArray(sortArrayMergeParallelWO);
//		 Utility.printArray(sortArrayMergeParallel);
//		 
//		//
	}
}
