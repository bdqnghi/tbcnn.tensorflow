package upwork;

import java.util.ArrayList;

public class MaxHeapPriorityQueue<K,V> extends HeapPriorityQueue<K,V>{

	int size = 0;
	
	public int size() { return size; }

	/** perform heap-sort in place **/
	  public void sortInPlace() {

		  int n = heap.size();

		  ArrayList<Entry<K, V>> removedItem = new ArrayList<>();

		  heapify();

		  // One by one extract an element from heap
		  for (int i = n - 1; i >= 0; i--) {
			  removedItem.add(removeMin());
		  }

		  // Clear heap
		  heap.clear();

		  // add all elements extracted above in the heap
		  heap.addAll(removedItem);

		  printKeys();

	  }
}
