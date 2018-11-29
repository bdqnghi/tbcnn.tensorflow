import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Random;

public class AdaptiveSortImpl implements AdaptiveSortInterface{

	@Override
	public int[] adaptiveSort(int[] inputArr) {
		int[] pickAlgoArr = {1,2,3};
		int[] finalArray = null;
		finalArray = pickFirstSortRandomly(inputArr, pickAlgoArr);
		return finalArray;
	}	

	private int[] callBucketSortFirst(int[] inputArr) {

		BucketSortInterface sort = new BucketSortImpl();
		int arrayLength = getXPercentLengthOfTheArray(inputArr);
		long countToTimeRatio1 = 0;
		long countToTimeRatio2 = 0;
		long countToTimeRatioQuickSort1 = 0;
		long countToTimeRatioMergeSort1 = 0;
		long countToTimeRatioMergeSort2 = 0;
		long countToTimeRatioQuickSort2 = 0;
		int[] array_1 = null;
		int[] array_2 = null;
		int[] array_3 = null;
		int[] array_4 = null;
		int[] array_5 = null;
		int[] array_6 = null;
		int[] finalArray = null;
		array_1 = generateNewArray(inputArr, arrayLength);
		sort.bucketSort(array_1);
		countToTimeRatio1 = BucketSortImpl.total/BucketSortImpl.counter;
		BucketSortImpl.total = 0;
		BucketSortImpl.counter = 0;
		int[] nextArray_1 = new int[inputArr.length-arrayLength];
		nextArray_1 = deleteFirstXLengthOfArray(inputArr, arrayLength);
		arrayLength =  getXPercentLengthOfTheArray(nextArray_1);
		array_2 = generateNewArray(nextArray_1, arrayLength);
		sort.bucketSort(array_2);
		countToTimeRatio2 = BucketSortImpl.total/BucketSortImpl.counter;
		BucketSortImpl.total = 0;
		BucketSortImpl.counter = 0;
		if(countToTimeRatio2>=countToTimeRatio1){
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			int[] pickAlgoArr = {1,2};
			pickAlgoArr = shuffleArrayValues(pickAlgoArr);
			if(pickAlgoArr[0]==1){
				MergeSortInterface mergeSort = new MergeSortImpl();
				mergeSort.mergeSort(array_3);
				countToTimeRatioMergeSort1 = MergeSortImpl.total/MergeSortImpl.counter;
				MergeSortImpl.total = 0;
				MergeSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				mergeSort.mergeSort(array_4);
				countToTimeRatioMergeSort2 = MergeSortImpl.total/MergeSortImpl.counter;
				MergeSortImpl.total = 0;
				MergeSortImpl.counter = 0;
				if(countToTimeRatioMergeSort2>countToTimeRatioMergeSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					QuickSortInterface quickSort = new QuickSortImpl();
					quickSort.quickSort(array_5);
					QuickSortImpl.total = 0;
					QuickSortImpl.counter = 0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					mergeSort.mergeSort(array_5);
					MergeSortImpl.total = 0;
					MergeSortImpl.counter = 0;
				}
			}
			else if(pickAlgoArr[0]==2){
				QuickSortInterface quickSort = new QuickSortImpl();
				quickSort.quickSort(array_3);
				countToTimeRatioQuickSort1 = QuickSortImpl.total/QuickSortImpl.counter;
				QuickSortImpl.total = 0;
				QuickSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				quickSort.quickSort(array_4);
				countToTimeRatioQuickSort2 = QuickSortImpl.total/QuickSortImpl.counter;
				QuickSortImpl.total = 0;
				QuickSortImpl.counter = 0;
				if(countToTimeRatioQuickSort2>countToTimeRatioQuickSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength = getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					MergeSortInterface mergeSort = new MergeSortImpl();
					mergeSort.mergeSort(array_5);
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					quickSort.quickSort(array_5);
					QuickSortImpl.total = 0;
					QuickSortImpl.counter = 0;
				}
			}
		}else{
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			sort.bucketSort(array_3);
			countToTimeRatio2 = BucketSortImpl.total/BucketSortImpl.counter;
			BucketSortImpl.total = 0;
			BucketSortImpl.counter = 0;
			if(countToTimeRatio2>=countToTimeRatio1){
				int[] pickAlgoArr = {1,2};
				pickAlgoArr = shuffleArrayValues(pickAlgoArr);
				if(pickAlgoArr[0]==1){
					MergeSortInterface mergeSort = new MergeSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					mergeSort.mergeSort(array_4);
					countToTimeRatioMergeSort1 = MergeSortImpl.total/MergeSortImpl.counter;
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					mergeSort.mergeSort(array_5);
					countToTimeRatioMergeSort2 = MergeSortImpl.total/MergeSortImpl.counter;
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
					if(countToTimeRatioMergeSort2>=countToTimeRatioMergeSort1){
						QuickSortInterface quickSort = new QuickSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						quickSort.quickSort(array_6);
						QuickSortImpl.total=0;
						QuickSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						mergeSort.mergeSort(array_6);
						MergeSortImpl.total=0;
						MergeSortImpl.counter=0;
					}
				}else if(pickAlgoArr[0]==2){
					QuickSortInterface quickSort = new QuickSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					quickSort.quickSort(array_4);
					countToTimeRatioQuickSort1 = QuickSortImpl.total/QuickSortImpl.counter;
					QuickSortImpl.total=0;
					QuickSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					quickSort.quickSort(array_5);
					countToTimeRatioQuickSort2 = QuickSortImpl.total/QuickSortImpl.counter;
					QuickSortImpl.total=0;
					QuickSortImpl.counter=0;
					if(countToTimeRatioQuickSort2>=countToTimeRatioQuickSort1){
						MergeSortInterface mergeSort = new MergeSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						mergeSort.mergeSort(array_6);
						MergeSortImpl.total=0;
						MergeSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						quickSort.quickSort(array_6);
						QuickSortImpl.total=0;
						QuickSortImpl.counter=0;
					}
				}
				
			}else{
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				array_4 = nextArray_3;
				sort.bucketSort(array_4);
				BucketSortImpl.total=0;
				BucketSortImpl.counter=0;
			}
		}
		finalArray = getArrayAndWriteToFile(inputArr, array_1, array_2, array_3, array_4, array_5, array_6);
		
		return finalArray;
		
	
	}

	private int[] callMergeSortFirst(int[] inputArr) {
		MergeSortInterface sort = new MergeSortImpl();
		int arrayLength = getXPercentLengthOfTheArray(inputArr);
		long countToTimeRatio1 = 0;
		long countToTimeRatio2 = 0;
		long countToTimeRatioBucketSort1 = 0;
		long countToTimeRatioBucketSort2 = 0;
		long countToTimeRatioQuickSort1 = 0;
		long countToTimeRatioQuickSort2 = 0;
		int[] array_1 = null;
		int[] array_2 = null;
		int[] array_3 = null;
		int[] array_4 = null;
		int[] array_5 = null;
		int[] array_6 = null;
		int[] finalArray = null;
		array_1 = generateNewArray(inputArr, arrayLength);
		sort.mergeSort(array_1);
		countToTimeRatio1 = MergeSortImpl.total/MergeSortImpl.counter;
		MergeSortImpl.total = 0;
		MergeSortImpl.counter = 0;
		int[] nextArray_1 = new int[inputArr.length-arrayLength];
		nextArray_1 = deleteFirstXLengthOfArray(inputArr, arrayLength);
		arrayLength =  getXPercentLengthOfTheArray(nextArray_1);
		array_2 = generateNewArray(nextArray_1, arrayLength);
		sort.mergeSort(array_2);
		countToTimeRatio2 = MergeSortImpl.total/MergeSortImpl.counter;
		MergeSortImpl.total = 0;
		MergeSortImpl.counter = 0;
		if(countToTimeRatio2>=countToTimeRatio1){
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			int[] pickAlgoArr = {1,2};
			pickAlgoArr = shuffleArrayValues(pickAlgoArr);
			if(pickAlgoArr[0]==1){
				BucketSortInterface bucketSort = new BucketSortImpl();
				bucketSort.bucketSort(array_3);
				countToTimeRatioBucketSort1 = BucketSortImpl.total/BucketSortImpl.counter;
				BucketSortImpl.total = 0;
				BucketSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				bucketSort.bucketSort(array_4);
				countToTimeRatioBucketSort2 = BucketSortImpl.total/BucketSortImpl.counter;
				BucketSortImpl.total = 0;
				BucketSortImpl.counter = 0;
				if(countToTimeRatioBucketSort2>countToTimeRatioBucketSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					QuickSortInterface quickSort = new QuickSortImpl();
					quickSort.quickSort(array_5);
					QuickSortImpl.total = 0;
					QuickSortImpl.counter = 0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					bucketSort.bucketSort(array_5);
					BucketSortImpl.total = 0;
					BucketSortImpl.counter = 0;
				}
			}
			else if(pickAlgoArr[0]==2){
				QuickSortInterface quickSort = new QuickSortImpl();
				quickSort.quickSort(array_3);
				countToTimeRatioQuickSort1 = QuickSortImpl.total/QuickSortImpl.counter;
				QuickSortImpl.total = 0;
				QuickSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				quickSort.quickSort(array_4);
				countToTimeRatioQuickSort2 = QuickSortImpl.total/QuickSortImpl.counter;
				QuickSortImpl.total = 0;
				QuickSortImpl.counter = 0;
				if(countToTimeRatioQuickSort2>countToTimeRatioQuickSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength = getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					BucketSortInterface bucketSort = new BucketSortImpl();
					bucketSort.bucketSort(array_5);
					BucketSortImpl.total=0;
					BucketSortImpl.counter=0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					quickSort.quickSort(array_5);
					QuickSortImpl.total = 0;
					QuickSortImpl.counter = 0;
				}
			}
		}else{
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			sort.mergeSort(array_3);
			countToTimeRatio2 = MergeSortImpl.total/MergeSortImpl.counter;
			MergeSortImpl.total = 0;
			MergeSortImpl.counter = 0;
			if(countToTimeRatio2>=countToTimeRatio1){
				int[] pickAlgoArr = {1,2};
				pickAlgoArr = shuffleArrayValues(pickAlgoArr);
				if(pickAlgoArr[0]==1){
					BucketSortInterface bucketSort = new BucketSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					bucketSort.bucketSort(array_4);
					countToTimeRatioBucketSort1 = BucketSortImpl.total/BucketSortImpl.counter;
					BucketSortImpl.total=0;
					BucketSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					bucketSort.bucketSort(array_5);
					countToTimeRatioBucketSort2 = BucketSortImpl.total/BucketSortImpl.counter;
					BucketSortImpl.total=0;
					BucketSortImpl.counter=0;
					if(countToTimeRatioBucketSort2>=countToTimeRatioBucketSort1){
						QuickSortInterface quickSort = new QuickSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						quickSort.quickSort(array_6);
						QuickSortImpl.total=0;
						QuickSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						bucketSort.bucketSort(array_6);
						BucketSortImpl.total=0;
						BucketSortImpl.counter=0;
					}
				}else if(pickAlgoArr[0]==2){
					QuickSortInterface quickSort = new QuickSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					quickSort.quickSort(array_4);
					countToTimeRatioQuickSort1 = QuickSortImpl.total/QuickSortImpl.counter;
					QuickSortImpl.total=0;
					QuickSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					quickSort.quickSort(array_5);
					countToTimeRatioQuickSort2 = QuickSortImpl.total/QuickSortImpl.counter;
					QuickSortImpl.total=0;
					QuickSortImpl.counter=0;
					if(countToTimeRatioQuickSort2>=countToTimeRatioQuickSort1){
						BucketSortInterface bucketSort = new BucketSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						bucketSort.bucketSort(array_6);
						BucketSortImpl.total=0;
						BucketSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						quickSort.quickSort(array_6);
						QuickSortImpl.total=0;
						QuickSortImpl.counter=0;
					}
				}
				
			}else{
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				array_4 = nextArray_3;
				sort.mergeSort(array_4);
				MergeSortImpl.total = 0;
				MergeSortImpl.counter = 0;
			}
		}
		finalArray = getArrayAndWriteToFile(inputArr, array_1, array_2, array_3, array_4, array_5, array_6);
		
		return finalArray;
	}

	private int[] callQuickSortFirst(int[] inputArr) {
		QuickSortInterface sort = new QuickSortImpl();
		int arrayLength = getXPercentLengthOfTheArray(inputArr);
		long countToTimeRatio1 = 0;
		long countToTimeRatio2 = 0;
		long countToTimeRatioMergeSort1 = 0;
		long countToTimeRatioMergeSort2 = 0;
		long countToTimeRatioBucketSort1 = 0;
		long countToTimeRatioBucketSort2 = 0;
		int[] array_1 = null;
		int[] array_2 = null;
		int[] array_3 = null;
		int[] array_4 = null;
		int[] array_5 = null;
		int[] array_6 = null;
		int[] finalArray= null;
		array_1 = generateNewArray(inputArr, arrayLength);
		sort.quickSort(array_1);
		countToTimeRatio1 = QuickSortImpl.total/QuickSortImpl.counter;
		QuickSortImpl.total = 0;
		QuickSortImpl.counter = 0;
		int[] nextArray_1 = new int[inputArr.length-arrayLength];
		nextArray_1 = deleteFirstXLengthOfArray(inputArr, arrayLength);
		arrayLength =  getXPercentLengthOfTheArray(nextArray_1);
		array_2 = generateNewArray(nextArray_1, arrayLength);
		sort.quickSort(array_2);
		countToTimeRatio2 = QuickSortImpl.total/QuickSortImpl.counter;
		QuickSortImpl.total = 0;
		QuickSortImpl.counter = 0;
		if(countToTimeRatio2>=countToTimeRatio1){
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			int[] pickAlgoArr = {1,2};
			pickAlgoArr = shuffleArrayValues(pickAlgoArr);
			if(pickAlgoArr[0]==1){
				MergeSortInterface mergeSort = new MergeSortImpl();
				mergeSort.mergeSort(array_3);
				countToTimeRatioMergeSort1 = MergeSortImpl.total/MergeSortImpl.counter;
				MergeSortImpl.total = 0;
				MergeSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				mergeSort.mergeSort(array_4);
				countToTimeRatioMergeSort2 = MergeSortImpl.total/MergeSortImpl.counter;
				MergeSortImpl.total = 0;
				MergeSortImpl.counter = 0;
				if(countToTimeRatioMergeSort2>countToTimeRatioMergeSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					BucketSortInterface bucketSort = new BucketSortImpl();
					bucketSort.bucketSort(array_5);
					BucketSortImpl.total = 0;
					BucketSortImpl.counter = 0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					mergeSort.mergeSort(array_5);
					MergeSortImpl.total = 0;
					MergeSortImpl.counter = 0;
				}
			}
			else if(pickAlgoArr[0]==2){
				BucketSortInterface bucketSort = new BucketSortImpl();
				bucketSort.bucketSort(array_3);
				countToTimeRatioBucketSort1 = BucketSortImpl.total/BucketSortImpl.counter;
				BucketSortImpl.total = 0;
				BucketSortImpl.counter = 0;
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
				array_4 = generateNewArray(nextArray_3, arrayLength);
				bucketSort.bucketSort(array_4);
				countToTimeRatioBucketSort2 = BucketSortImpl.total/BucketSortImpl.counter;
				BucketSortImpl.total = 0;
				BucketSortImpl.counter = 0;
				if(countToTimeRatioBucketSort2>countToTimeRatioBucketSort1){
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					MergeSortInterface mergeSort = new MergeSortImpl();
					mergeSort.mergeSort(array_5);
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
				}else{
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = nextArray_4;
					bucketSort.bucketSort(array_5);
					BucketSortImpl.total = 0;
					BucketSortImpl.counter = 0;
				}
			}
		}else{
			int[] nextArray_2 = new int[nextArray_1.length-arrayLength];
			nextArray_2 = deleteFirstXLengthOfArray(nextArray_1, arrayLength);
			arrayLength =  getXPercentLengthOfTheArray(nextArray_2);
			array_3 = generateNewArray(nextArray_2, arrayLength);
			sort.quickSort(array_3);
			countToTimeRatio2 = QuickSortImpl.total/QuickSortImpl.counter;
			QuickSortImpl.total = 0;
			QuickSortImpl.counter = 0;
			if(countToTimeRatio2>=countToTimeRatio1){
				int[] pickAlgoArr = {1,2};
				pickAlgoArr = shuffleArrayValues(pickAlgoArr);
				if(pickAlgoArr[0]==1){
					MergeSortInterface mergeSort = new MergeSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					mergeSort.mergeSort(array_4);
					countToTimeRatioMergeSort1 = MergeSortImpl.total/MergeSortImpl.counter;
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					mergeSort.mergeSort(array_5);
					countToTimeRatioMergeSort2 = MergeSortImpl.total/MergeSortImpl.counter;
					MergeSortImpl.total=0;
					MergeSortImpl.counter=0;
					if(countToTimeRatioMergeSort2>=countToTimeRatioMergeSort1){
						BucketSortInterface bucketSort = new BucketSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						bucketSort.bucketSort(array_6);
						BucketSortImpl.total=0;
						BucketSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_5, arrayLength);
						array_6 = nextArray_5;
						mergeSort.mergeSort(array_6);
						MergeSortImpl.total=0;
						MergeSortImpl.counter=0;
					}
				}else if(pickAlgoArr[0]==2){
					BucketSortInterface bucketSort = new BucketSortImpl();
					int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
					nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_3);
					array_4 = generateNewArray(nextArray_3, arrayLength);
					bucketSort.bucketSort(array_4);
					countToTimeRatioBucketSort1 = BucketSortImpl.total/BucketSortImpl.counter;
					BucketSortImpl.total=0;
					BucketSortImpl.counter=0;
					int[] nextArray_4 = new int[nextArray_3.length-arrayLength];
					nextArray_4 = deleteFirstXLengthOfArray(nextArray_3, arrayLength);
					arrayLength =  getXPercentLengthOfTheArray(nextArray_4);
					array_5 = generateNewArray(nextArray_4, arrayLength);
					bucketSort.bucketSort(array_5);
					countToTimeRatioBucketSort2 = BucketSortImpl.total/BucketSortImpl.counter;
					BucketSortImpl.total=0;
					BucketSortImpl.counter=0;
					if(countToTimeRatioBucketSort2>=countToTimeRatioBucketSort1){
						MergeSortInterface mergeSort = new MergeSortImpl();
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						mergeSort.mergeSort(array_6);
						MergeSortImpl.total=0;
						MergeSortImpl.counter=0;
					}else{
						int[] nextArray_5 = new int[nextArray_4.length-arrayLength];
						nextArray_5 = deleteFirstXLengthOfArray(nextArray_4, arrayLength);
						array_6 = nextArray_5;
						bucketSort.bucketSort(array_6);
						BucketSortImpl.total=0;
						BucketSortImpl.counter=0;
					}
				}
				
			}else{
				int[] nextArray_3 = new int[nextArray_2.length-arrayLength];
				nextArray_3 = deleteFirstXLengthOfArray(nextArray_2, arrayLength);
				array_4 = nextArray_3;
				sort.quickSort(array_4);
				QuickSortImpl.total=0;
				QuickSortImpl.counter=0;
			}
		}
		finalArray = getArrayAndWriteToFile(inputArr, array_1, array_2, array_3, array_4, array_5, array_6);
		return finalArray;  
		
	}

	private int[] getArrayAndWriteToFile(int[] inputArr, int[] array_1, int[] array_2, int[] array_3, int[] array_4,
			int[] array_5, int[] array_6) {
		List<Integer> finalArrayList = new ArrayList<Integer>();
		int length = 0;
		if(array_1 != null){
			length = array_1.length;
			for(int i=0;i<array_1.length;i++){
				finalArrayList.add(array_1[i]);
			}
		}
		if(array_2 != null){
			length = length+array_2.length;
			for(int i=0;i<array_2.length;i++){
				finalArrayList.add(array_2[i]);
			}
		}
		if(array_3 != null){
			length = length+array_3.length;
			for(int i=0;i<array_3.length;i++){
				finalArrayList.add(array_3[i]);
			}
		}
		if(array_4 != null){
			length = length+array_4.length;
			for(int i=0;i<array_4.length;i++){
				finalArrayList.add(array_4[i]);
			}
		}
		if(array_5 != null){
			length = length+array_5.length;
			for(int i=0;i<array_5.length;i++){
				finalArrayList.add(array_5[i]);
			}
		}
		if(array_6 != null){
			length = length+array_6.length;
			for(int i=0;i<array_6.length;i++){
				finalArrayList.add(array_6[i]);
			}
		}
		Iterator<Integer> it = finalArrayList.iterator();
		int[] finalArray = new int[inputArr.length];
		for (int i = 0; i < finalArray.length && it.hasNext(); i++) {
			finalArray[i] = it.next();
		}
		BucketSortInterface bucketSort = new BucketSortImpl();
		bucketSort.bucketSort(finalArray);
		System.out.println("Total time taken in nano seconds : "+BucketSortImpl.total);
		BufferedWriter outputWriter = null;
		try {
			outputWriter = new BufferedWriter(new FileWriter("AdaptiveSort.txt"));
		} catch (IOException e) {
			// TODO
			e.printStackTrace();
		}
		for(int i=0;i<finalArray.length;i++){
			try {
				outputWriter.write(Integer.toString(finalArray[i]));
				outputWriter.newLine();
			} catch (IOException e) {
				// TODO 
				e.printStackTrace();
			}			
		}
		try {
			outputWriter.flush();
			outputWriter.close(); 
		} catch (IOException e) {
			// TODO 
			e.printStackTrace();
		}
		return finalArray;
	}

	private int[] generateNewArray(int[] inputArr, int arrayLength) {
		int[] newArr = new int[arrayLength];
		for(int i=0;i<arrayLength;i++){
			newArr[i]=inputArr[i];
		}
		return newArr;
	}

	private int[] deleteFirstXLengthOfArray(int[] inputArr, int arrayLength) {
		int newLength = inputArr.length-arrayLength;
		int[] newArr = new int[newLength];
		System.arraycopy(inputArr, arrayLength, newArr, 0, newLength);
		return newArr;
		
	}

	private int getXPercentLengthOfTheArray(int[] inputArr) {
		int length = (10*inputArr.length)/100;
		return length;
	}

	private int[] shuffleArrayValues(int[] inputArr) {
		int index;
		Random random = new Random();
		for (int i = inputArr.length - 1; i > 0; i--) {
			index = random.nextInt(i + 1);
			if (index != i) {
				inputArr[index] ^= inputArr[i];
				inputArr[i] ^= inputArr[index];
				inputArr[index] ^= inputArr[i];
			}
		}
		return inputArr;
	}

	private int[] pickFirstSortRandomly(int[] inputArr, int[] pickAlgoArr) {
		pickAlgoArr = shuffleArrayValues(pickAlgoArr);
		int[] finalArray = null;
		if(pickAlgoArr[0]==1){
			finalArray = callQuickSortFirst(inputArr);
		}
		else if(pickAlgoArr[0]==2){
			finalArray = callMergeSortFirst(inputArr);
		}
		else if(pickAlgoArr[0]==3){
			finalArray = callBucketSortFirst(inputArr);
		}
		return finalArray;
	}
}
