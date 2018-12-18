import java.util.Arrays;

public class Driver implements DriverInterface {

	static BubbleSort bubble;
	static InsertionSort insertion;
	static SelectionSort selection;


	
	@Override
	public Integer[] createArray(ArrayType arrayType, int arraySize) {
		
		switch (arrayType) {
			case Equal:
				Integer[] equalArray = new Integer[arraySize];
				for (int value = 0; value < equalArray.length; value++) {
					equalArray[value] = 1;
				}
				return equalArray;
			case Random:
				Integer[] randArray = new Integer[arraySize];
				for (int value = 0; value < randArray.length; value++) {
					randArray[value] = (int)(Math.random() * 100000);
				}
				return randArray;
			case Increasing:
				Integer[] incArray = new Integer[arraySize];
				for (int i = 0; i < incArray.length; i++) {
					incArray[i] = i + 1;
				}
				return incArray;
			case Decreasing:
				Integer[] decArray = new Integer[arraySize];
				int counter = arraySize;
				for (int i = 0; i < decArray.length ; i++) {
					
					decArray[i] = counter--;
				}
				return decArray;
			case IncreasingAndRandom:
				
				
				
				Integer[] incAndRandArray = new Integer[arraySize];
				incAndRandArray[0] = 1;
				
				int arrayAt90Percent = (int) (incAndRandArray.length * .90);
				for (int i = 1; i < arrayAt90Percent; i++) {
					incAndRandArray[i] = i + 1;
				}
				for (int i = arrayAt90Percent; i < incAndRandArray.length ; i++) {
					incAndRandArray[i] = (int)(Math.random() * 100000);
				}
				return incAndRandArray;
		}
		
		return null;
	}

	@Override
	public RunTime runSort(SortType sortType, ArrayType arrayType, int arraySize, int numberOfTimes) {
		

			switch (sortType) {
				case BubbleSort:

					bubble = new BubbleSort();
					Integer[] bubbleArray;
					
					for (int counter = 0; counter < numberOfTimes; counter++) {
						bubbleArray = createArray(arrayType, arraySize);
						bubble.sort(bubbleArray);

					}
					

		
					return bubble;
				case InsertionSort:

					insertion = new InsertionSort();
					Integer[] insertionArray;
					for (int counter = 0; counter < numberOfTimes; counter++) {
						insertionArray = createArray(arrayType, arraySize);
						insertion.sort(insertionArray);
					}
					
					return insertion;
				case SelectionSort:

					selection = new SelectionSort();
					Integer[] selectionArray;
					for (int counter = 0; counter < numberOfTimes; counter++) {
						selectionArray = createArray(arrayType, arraySize);
						selection.sort(selectionArray);
					}
					
					return selection;
			} 

		
		return null;
	}
	
	public void sortPrint(String sortType, String arrayType, String arraySize, RunTime run) {
		
		
		System.out.println(sortType + "Sort, " + arrayType + ", " + arraySize);
		System.out.println("--------------------------------------------------------------------------------------------------------------");
		System.out.println(Arrays.toString(run.getRunTimes()) + " --- " + run.getAverageRunTime());
		System.out.println();
	}
	
	public static void main(String[] args) {
		
		Driver testDrive = new Driver();
		
		System.out.println("Bubble Sort");
		System.out.println("========================================================================");
		System.out.println();
		
		
		
		
		
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Equal, 1000, 10);
		testDrive.sortPrint("Bubble", "Equal", "1,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Random, 1000, 10);
		testDrive.sortPrint("Bubble", "Random", "1,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Increasing, 1000, 10);	
		testDrive.sortPrint("Bubble", "Increasing", "1,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Decreasing, 1000, 10);	
		testDrive.sortPrint("Bubble", "Decreasing", "1,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.IncreasingAndRandom, 1000, 10);	
		testDrive.sortPrint("Bubble", "Increasing & Random", "1,000", bubble);
		
		
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Equal, 10000, 10);
		testDrive.sortPrint("Bubble", "Equal", "10,000", bubble);	
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Random, 10000, 10);
		testDrive.sortPrint("Bubble", "Random", "10,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Increasing, 10000, 10);	
		testDrive.sortPrint("Bubble", "Increasing", "10,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.Decreasing, 10000, 10);
		testDrive.sortPrint("Bubble", "Decreasing", "10,000", bubble);
		
		testDrive.runSort(SortType.BubbleSort, ArrayType.IncreasingAndRandom, 10000, 10);	
		testDrive.sortPrint("Bubble", "Increasing & Random", "10,000", bubble);
		
		System.out.println();
		System.out.println("Insertion Sort");
		System.out.println("========================================================================");
		System.out.println();
		
		
		
		
		
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Equal, 1000, 10);
		testDrive.sortPrint("Insertion", "Equal", "1,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Random, 1000, 10);
		testDrive.sortPrint("Insertion", "Random", "1,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Increasing, 1000, 10);	
		testDrive.sortPrint("Insertion", "Increasing", "1,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Decreasing, 1000, 10);	
		testDrive.sortPrint("Insertion", "Decreasing", "1,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.IncreasingAndRandom, 1000, 10);	
		testDrive.sortPrint("Insertion", "Increasing & Random", "1,000", insertion);
		
		
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Equal, 10000, 10);
		testDrive.sortPrint("Insertion", "Equal", "10,000", insertion);	
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Random, 10000, 10);
		testDrive.sortPrint("Insertion", "Random", "10,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Increasing, 10000, 10);	
		testDrive.sortPrint("Insertion", "Increasing", "10,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.Decreasing, 10000, 10);
		testDrive.sortPrint("Insertion", "Decreasing", "10,000", insertion);
		
		testDrive.runSort(SortType.InsertionSort, ArrayType.IncreasingAndRandom, 10000, 10);	
		testDrive.sortPrint("Insertion", "Increasing & Random", "10,000", insertion);
		
		System.out.println();
		System.out.println("Selection Sort");
		System.out.println("========================================================================");
		System.out.println();
		
		
		
		
		
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Equal, 1000, 10);
		testDrive.sortPrint("Selection", "Equal", "1,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Random, 1000, 10);
		testDrive.sortPrint("Selection", "Random", "1,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Increasing, 1000, 10);	
		testDrive.sortPrint("Selection", "Increasing", "1,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Decreasing, 1000, 10);	
		testDrive.sortPrint("Selection", "Decreasing", "1,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.IncreasingAndRandom, 1000, 10);	
		testDrive.sortPrint("Selection", "Increasing & Random", "1,000", selection);
		
		
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Equal, 10000, 10);
		testDrive.sortPrint("Selection", "Equal", "10,000", selection);	
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Random, 10000, 10);
		testDrive.sortPrint("Selection", "Random", "10,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Increasing, 10000, 10);	
		testDrive.sortPrint("Selection", "Increasing", "10,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.Decreasing, 10000, 10);
		testDrive.sortPrint("Selection", "Decreasing", "10,000", selection);
		
		testDrive.runSort(SortType.SelectionSort, ArrayType.IncreasingAndRandom, 10000, 10);	
		testDrive.sortPrint("Selection", "Increasing & Random", "10,000", selection);
		
	}

}
