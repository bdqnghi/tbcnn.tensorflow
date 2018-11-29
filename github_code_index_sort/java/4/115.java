import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class Heap {
	protected int arr_to_sort[];
	protected int heapSize;	
	public void setArrToSort(int arr_to_sort[]) {
		this.arr_to_sort = arr_to_sort;
	}	
	protected void printMergedArray(int sortedArray[],int heapSize) {
		for ( int i = 0 ; i < heapSize;  i++) 
			System.out.print(sortedArray[i] + " ");
		System.out.println();
	}
	protected int findParentIndex(int idx) {
		if ( idx % 2 == 1) // odd , it must be left child 
			return (int)Math.floor((idx -1)/2);
		else	 // even, right child
			return (int)Math.floor((idx -2)/2);
	}
	protected int findLeftIndex(int idx) {
		return 2*idx +1;
	}
	protected int findRightIndex(int idx) {
		return 2*idx +2;
	}
	protected void print() {
		printMergedArray(arr_to_sort,heapSize);
	}
	protected int size() {
		return heapSize;
	}
	
	
}
class MinHeap extends Heap{
	public int minimum() {
		return arr_to_sort[0];
	}
	public void min_heapify(int[] arr,int start,int end) {
		int root = start;
		int smallest,swap;
		int left = findLeftIndex(root);
		int right= findRightIndex(root);
		while(left <= end) {
			smallest = root;
			if(arr[left] < arr[root]) {
				smallest = left;
			}
			if (right <=end) {
				if(arr[right] < arr[smallest]) {
					smallest = right;
				}
			}
			if(smallest != root) {
				swap = arr[root];
				arr[root]= arr[smallest];
				arr[smallest]= swap;
				root = smallest;
				left = findLeftIndex(root);
				right= findRightIndex(root);
			} else {
				break;
			}
		}

	}
	public void createMinHeap() {
		for(int i= (findParentIndex(arr_to_sort.length)-1); i>=0 ; i--) {
			min_heapify(arr_to_sort,i,arr_to_sort.length-1);
		}
		heapSize = arr_to_sort.length;
		print();
	}
	// i : index k : value
	public boolean decreaseKey(int nIndex,int k) {
		if (nIndex == -1)
			return false;
		if ( arr_to_sort[nIndex] < k) // setting arr[nIndex] to a larger value might violate min-heap property
			return false;
		arr_to_sort[nIndex] = k;
		int nParentIdx = findParentIndex(nIndex),swap;
		while (nParentIdx >= 0) {
			if ( arr_to_sort[nParentIdx] > arr_to_sort[nIndex] ) {
				swap = arr_to_sort[nIndex];
				arr_to_sort[nIndex ] 	= arr_to_sort[nParentIdx];
				arr_to_sort[nParentIdx] = swap;
				nIndex = nParentIdx;
				nParentIdx = findParentIndex(nParentIdx);
			}
			else { 
				break;
			}
		}
		return true;
	}
	public boolean insert(int x) {
		if (heapSize == arr_to_sort.length)
			return false;
		
		heapSize++;
		arr_to_sort[heapSize-1] = x;
		decreaseKey(heapSize-1,x);
		return true;
	} 
	public int extractMin() {
		if ( heapSize == -1)
			return heapSize;
		int max = arr_to_sort[0];
		arr_to_sort[0] = arr_to_sort[heapSize-1];
		heapSize--;
		min_heapify(arr_to_sort,0,heapSize-1);
		return max;
	}
}

class MaxHeap extends Heap{
	private void max_heapify(int arr[],int start,int end) {
		int root = start;
		int largest,swap;
		int left = findLeftIndex(root);
		int right= findRightIndex(root);
		while(left <= end) {
			largest = root;
			if(arr[left] > arr[root]) {
				largest = left;
			}
			if (right <=end) {
				if(arr[right] > arr[largest]) {
					largest = right;
				}
			}
			if(largest != root) {
				swap = arr[root];
				arr[root]= arr[largest];
				arr[largest]= swap;
				root = largest;
				left = findLeftIndex(root);
				right= findRightIndex(root);
			} else {
				break;
			}
		}
	}
	public void createMaxHeap() {
		for(int i= (findParentIndex(arr_to_sort.length)-1); i>=0 ; i--) {
			max_heapify(arr_to_sort,i,arr_to_sort.length-1);
		}
		heapSize = arr_to_sort.length;
		printMergedArray(arr_to_sort,heapSize);
	}
	
	public int maximum() {
		return arr_to_sort[0];
	}
	/**
	* NOTE : if index is already known, then the searchKey is omitted and operation is 
	* done in O(log n) time
	*/
	public boolean increaseKey(int nIndex,int k) {
		//increase x to k ie. set x=k
		if (nIndex == -1) //element not present in heap
			return false;
		//int x = arr_to_sort[nIndex];
		if ( k < arr_to_sort[nIndex]) // setting x to a smaller value will be violation of max-heap property
			return false;
		arr_to_sort[nIndex] = k;
		int swap,i;
		while ( nIndex >= 0) { // preserve max-heap property
			i = findParentIndex(nIndex);
			if ( i < 0) // this is root element, hence parent index cannot be found
				break;
			if ( arr_to_sort[i] < arr_to_sort[nIndex] ) {
				swap = arr_to_sort[nIndex];
				arr_to_sort[nIndex] = arr_to_sort[i];
				arr_to_sort[i] = swap;
				nIndex = i;
			} else {
				break;
			}
		}
		return true;
	}
	/**
	* To remove max from heap, and still maintain heap property, we need to 
	* call max_heapify from 1 to n-1 once arr_to_sort[0] is removed
	*/
	public int extractMax() {
		int max = arr_to_sort[0];
		arr_to_sort[0] = arr_to_sort[arr_to_sort.length-1];
		heapSize--;
		max_heapify(arr_to_sort,0,heapSize-1);
		return max;
	}
	public boolean insert(int x) {
		if (heapSize == arr_to_sort.length)
			return false;
		heapSize++;
		arr_to_sort[heapSize-1] = -32767;
		return increaseKey(heapSize-1,x);	
		
	}
	/*Searching in heap cannot be done better than O(n) 
	* Imagine a case where the element x is smaller than both left[root] and right[root]
	* Or , if the element x is not present in heap, and  it is smaller than all elements in heap,
	* in such a case, a sequential search is the only way
	*/
	private int searchKey(int x) {
		int nResult =-1;
		for(int i=0;i<heapSize-1;i++)
		{
			if(arr_to_sort[i] == x)
			{
				nResult = x;
				break;
			}
		}
		return nResult;
	}
}

class PriorityQueue {
	public static int getNumber(BufferedReader br, boolean bDimension) throws IOException{
		int nResult = 0;
		String inputNumber;
		String regex = ( bDimension == true) ? "[0-9]+" : "^-?[0-9]+$"; 
		while ( true ) { 
			inputNumber	= br.readLine();	
			if ( inputNumber.matches(regex) ) {
				nResult = Integer.parseInt(inputNumber);
				if (bDimension) {
					if (nResult >= 0)
						break;
				}
				else 
					break;	
				System.out.println("\nPlease enter a valid number ! Try again...");	
			}	
			else {
				System.out.println("\nPlease enter a valid number ! Try again...");
			}
				
		}
		return nResult;
	}	
	 
	public static void main(String[] args) throws IOException{
		System.out.println("Enter the maximum range required :");
		int dimension;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			dimension = getNumber(br,true);
			//dimension = 1;;
			if ( dimension == 0) {
				System.out.println("Array size is 0 ! Exiting...");
				return;
			}
			if ( dimension > 200) {
				System.out.println("Array size exceeds limit ( 200) ! Exiting...");
				return;
			}		
			int nCtr   = 0;
			int[] inputArray =  new int[dimension];
			System.out.println("Enter the " + dimension + " elements :");
			while ( nCtr < dimension ) { 	
				inputArray[nCtr] = getNumber(br,false);
				nCtr++;
			}
			System.out.println("Use max-heap or min-heap ( 1 / 2 ) ?");
			int choice = getNumber(br,false);
			if ((choice != 1) && (choice != 2)) {
				System.out.println("Choice was wrong... Will use max-heap as default !");
				choice = 1;
			}
			switch(choice) {
				case 1:
					MaxHeap max = new MaxHeap();
					max.setArrToSort(inputArray);
					max.createMaxHeap();
					System.out.println("Maximum value is " + max.maximum());
					System.out.println("Extracting maximum value :" + max.extractMax());
					
					System.out.println("Heap is now :");
					max.print();
					
					System.out.println(Boolean.valueOf(max.insert(5)));
					System.out.println("Inserted 5 into heap ....");
					System.out.println("Heap is now :");
					  max.print();
					
					System.out.println("Increase last element to 20...");
					max.increaseKey(max.size()-1,20);
					System.out.println("Heap is now :");
					max.print();

				break;	
				case 2:
					MinHeap min = new MinHeap();
					min.setArrToSort(inputArray);
					min.createMinHeap();
					System.out.println("Minimum value is " + min.minimum());
					System.out.println("Heap is now :");
					min.print();
					
					System.out.println("Extracting maximum value :" + min.extractMin());
					
					System.out.println("Heap is now :");
					min.print();
					
					System.out.println(Boolean.valueOf(min.insert(5)));
					System.out.println("Inserted 5 into heap ....");
					System.out.println("Heap is now :");
					min.print();
					
					System.out.println("Decreasing last element to -20...");
					min.decreaseKey(min.size()-1,-20);
					System.out.println("Heap is now :");
					min.print();
					
				break;
			}
		}
		catch(Exception ex) {
			ex.printStackTrace();
		}
		finally 
		{
			try {	
				br.close();
			}
			catch(Exception ex2) {
			}		
		}
		
	}
	
	
	
}
