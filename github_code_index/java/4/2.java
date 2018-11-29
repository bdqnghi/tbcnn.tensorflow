package chapter9;
/** Use priority queue to sort a list */
public class PriorityQueueSort {
	
	public static <E> void sort(PositionalList<E> list, PriorityQueue<E,?> heap){
		int n = list.size();
		// Phase 1
		for (int j = 0; j < n; j++){ // Push all elements into a heap
			E element = list.remove(list.first());
			heap.insert(element, null);
		}
		// Phase 2
		for(int j = 0; j < n;j++){ // Get all elements in nondecreasing order
			E element = heap.removeMin().getKey();
			list.addLast(element);
		}
	}
	/*
	 * Selection-sort:
	 * (Selecting the minimum element is the dominant factor)
	 * If we use unsorted priority queue to realize the above algorithm
	 * Each action in phase 1 takes O(1), n actions take O(n)
	 * Phase 2 takes O(n + (n - 1) + ... + 2 + 1) = O(n ^ 2)
	 * Therefore selection-sort takes up O(n ^ 2) time complexity
	 * 
	 * Insertion-sort:
	 * (Inserting element is the dominant factor)
	 * If we use sorted priority queue to realize the above algorithm
	 * Phase 1 takes O(n ^ 2) while phase 2 takes O(n)
	 * Therefore insertion-sort takes up O(n ^ 2) time complexity
	 * 
	 * Heap-sort
	 * If we use heap priority queue to realize the above algorithm
	 * Both insertion and selection takes O(nlogn)
	 * Therefore heap-sort takes up O(nlogn) time complexity
	 */
}
