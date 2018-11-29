
//Joe Martinez
//Kth Largest with heapSort and quickSort
//Main class file and a separate class files for heap and quick. 

/*
This program creates a large array of random numbers then that array is sorted
with heapSort which then uses deleteMax to find the kth largest. quickSort sorts 
it's array in descending order then uses the kth value to find the kth largest. 
*/

import java.util.*;

class KthLargest{ 

	public static void main(String[] args){
		//SHORT ARRAY
		//int heap[] = {0,150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};

		//LONG ARRAY (CREATES RANDOM ARRAY OF LENGTH "len" THEN COPIES IT)
		int len = 1000;
		
		int[] heapArray = new int[len];
		randArray(heapArray, len);
		int[] quickArray = heapArray.clone();
		
		int size = heapArray.length - 1;
		int kth = 100;


		//PERFORMS MAX HEAP SORT, THEN DELETEMAX TO FIND KTH LARGEST
		heap h = new heap();
			long heapStart = System.currentTimeMillis();	
				h.maxSort(heapArray, size/2);	
				//arrayPrint(heap, size); 
				h.deleteMax(heapArray, size, kth); 
				//arrayPrint(heap, size+1-kth);     
			long heapEnd = System.currentTimeMillis();

		//PERFORMS QUICKSORT IN DESCENDING ORDER
		quickSort q = new quickSort();
			long quickStart = System.currentTimeMillis();
				q.quickSort(quickArray, 1, size);
				//arrayPrint(heap, size);
				//System.out.print("quickSort array: ");
				//arrayPrint(quickArray, size);
			long quickEnd = System.currentTimeMillis();

		//PRINT STATEMENTS
		System.out.println("Length of array = " + len);
		System.out.println("Kth Largest value  = " + kth);
		System.out.println("");
		System.out.println("The Kth largest from heapSort  = " + heapArray[1]);
		System.out.println("Heap  time = " + (heapEnd - heapStart));
		System.out.println("The Kth largest from quickSort = " + quickArray[kth]);		
		System.out.println("Quick time = " + (quickEnd - quickStart));
	}


	//CREATES RANDOM ARRAY WITH GIVEN SIZE
	public static void randArray(int[] heap, int len){
		Random rand = new Random();
		for(int i = 0; i < len; i++){		
			int n = rand.nextInt(10000) + 1;
			heap[i] = n;
		}
	}

	//SWAP FUNCTION
	public static void swap(int[] heap, int i, int j){
		int tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}

	//PRINT ARRAY IN ARRAY FORMAT
	public static void arrayPrint(int[] heap, int size){
		for(int i = 1; i < size+1; i++){
			System.out.print(heap[i] + " ");
		}
		System.out.println("");
	}

	//PRINT ARRAY IN TREE FORMAT
	public static void treePrint(int[] heap, int size){
		// 2^0 = 1, 2^1 = 2, 2^2 = 4, 2^3 = 8		

		for(int i = 1; i < 2; i++){
			System.out.println("                   " + heap[i]);
		}
		for(int i = 2; i < 4; i++){
			System.out.print("         " + heap[i] + "            ");
		}
		System.out.println(" ");
		for(int i = 4; i < 8; i++){
			System.out.print("     " + heap[i] + "     ");
		}
		System.out.println(" ");
		for(int i = 8; i <= size; i++){
			System.out.print("  " + heap[i] + "  ");
		}
	}
}


class quickSort{

	//QUICKSORT FUNCTION
	public static void quickSort(int[] heap, int left, int right){
		int i = left; 
		int j = right;
		int pivot = heap[left + (right-left)/2];

		while(i <= j){
			while(heap[i] > pivot){ i++; }
			while(heap[j] < pivot){ j--; }
			if(i <= j){
				KthLargest.swap(heap, i, j);
				i++; j--;
			}
		}

		if(left < j){
			quickSort(heap, left, j);
		}
		if(i < right){
			quickSort(heap, i, right);
		}
	}


	/* //USED TO FIND INDEX OF MEDIAN PIVOT
	public static int findPivot(int[] heap, int size){
		int pIndex = 0; 
		int first  = heap[1];
		int second = heap[size/2];
		int third  = heap[size];

		int median = Math.max(Math.min(first,second), 
			Math.min(Math.max(first, second), third));

		if(median == first){  pIndex = 1;      }
		if(median == second){ pIndex = size/2; }
		if(median == third){  pIndex = size;   }

		return pIndex;
	}
	*/
}


class heap{

	//DELETES TOP NODE AND RESORTS USING maxSort
	public static void deleteMax(int[] heap, int size, int kth){
		while(kth > 1){
			KthLargest.swap(heap, 1, size);
			size--; 
			maxSort(heap, (size/2)-1);
			kth--; 
		}
	}

	//SORTS IN DESCENDING 
	public static void maxSort(int[] heap, int hole){
		while(hole > 0){
			int maxIndex = 0;
			int maxChild = Math.max(heap[hole*2], heap[(hole*2)+1]);
			if(maxChild == heap[hole*2])  { maxIndex = hole*2; }
			if(maxChild == heap[hole*2+1]){ maxIndex = hole*2+1; }
			
			if(heap[hole] < heap[maxIndex]){
				KthLargest.swap(heap, hole, maxIndex);
				maxSort(heap, hole);
			}
			else{
				hole--;
			}
		}
	}

	/* //SORTS IN ASCENDING
	public static void minSort(int[] heap, int hole){
		while(hole > 0){
			int minIndex = 0;
			int minChild = Math.min(heap[hole*2], heap[(hole*2)+1]);
			if(minChild == heap[hole*2])  { minIndex = hole*2; }
			if(minChild == heap[hole*2+1]){ minIndex = hole*2+1; }
			
			if(heap[hole] > heap[minIndex]){
				swap(heap, hole, minIndex);
				minSort(heap, hole);
			}
			else{
				hole--;
			}
		}
	}
	*/

	/*
	public static void build(int[] heap, int size, int leaves){
		for(int i = 1; i <= leaves; i--){
			perculateDown(heap, i);
		}
	}
	*/

	/*
	public static void perculateDown(int[] heap, int hole){
		int x = 0;
		while(hole > 0){
			if(heap[hole/2] > x){
				int tmp = heap[hole/2];
				heap[hole/2] = x;
				heap[hole] = tmp;
				hole = hole/2;
			}
		}
	}
	*/

	/*
	public static void heapInsert(int[] heap, int x, int size){
		heap[heap.length + 1] = x;
		size++;
		int hole = size;

		while(hole > 0){
			if(heap[hole/2] > x){
				int tmp = heap[hole/2];
				heap[hole/2] = x;
				heap[hole] = tmp;
				hole = hole/2;
			}
		}
	}
	*/
}