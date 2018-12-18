






import java.util.*;

class KthLargest{ 

	public static void main(String[] args){
		
		

		
		int len = 1000;
		
		int[] heapArray = new int[len];
		randArray(heapArray, len);
		int[] quickArray = heapArray.clone();
		
		int size = heapArray.length - 1;
		int kth = 100;


		
		heap h = new heap();
			long heapStart = System.currentTimeMillis();	
				h.maxSort(heapArray, size/2);	
				
				h.deleteMax(heapArray, size, kth); 
				
			long heapEnd = System.currentTimeMillis();

		
		quickSort q = new quickSort();
			long quickStart = System.currentTimeMillis();
				q.quickSort(quickArray, 1, size);
				
				
				
			long quickEnd = System.currentTimeMillis();

		
		System.out.println("Length of array = " + len);
		System.out.println("Kth Largest value  = " + kth);
		System.out.println("");
		System.out.println("The Kth largest from heapSort  = " + heapArray[1]);
		System.out.println("Heap  time = " + (heapEnd - heapStart));
		System.out.println("The Kth largest from quickSort = " + quickArray[kth]);		
		System.out.println("Quick time = " + (quickEnd - quickStart));
	}


	
	public static void randArray(int[] heap, int len){
		Random rand = new Random();
		for(int i = 0; i < len; i++){		
			int n = rand.nextInt(10000) + 1;
			heap[i] = n;
		}
	}

	
	public static void swap(int[] heap, int i, int j){
		int tmp = heap[i];
		heap[i] = heap[j];
		heap[j] = tmp;
	}

	
	public static void arrayPrint(int[] heap, int size){
		for(int i = 1; i < size+1; i++){
			System.out.print(heap[i] + " ");
		}
		System.out.println("");
	}

	
	public static void treePrint(int[] heap, int size){
		

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


	
}


class heap{

	
	public static void deleteMax(int[] heap, int size, int kth){
		while(kth > 1){
			KthLargest.swap(heap, 1, size);
			size--; 
			maxSort(heap, (size/2)-1);
			kth--; 
		}
	}

	
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

	

	

	

	
}