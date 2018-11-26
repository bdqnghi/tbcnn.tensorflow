package algorithms.sorting.heap;

import algorithms.sorting.heap.operations.HeapOperationsFactory;

/**
 * Created by Chen Li on 2018/2/10.
 */
public class HeapSortFactory {

  private HeapOperationsFactory operationsFactory = new HeapOperationsFactory();

  public HeapSort bestHeapSort() {
    return noExchangeHeapSort();
  }

  public HeapSort defaultHeapSort() {
    HeapSort heapSort = new HeapSort("defaultHeapSort");
    heapSort.setHeapOperations(operationsFactory.basicMaxHeapOperations());
    return heapSort;
  }

  public HeapSort noExchangeHeapSort() {
    HeapSort heapSort = new HeapSort("noExchangeHeapSort");
    heapSort.setHeapOperations(operationsFactory.noExchangeMaxHeapOperations());
    return heapSort;
  }

  public HeapSort multiwayHeapSort(int ways) {
    HeapSort heapSort = new HeapSort("multiwayHeapSort:" + ways);
    heapSort.setHeapOperations(operationsFactory.multiwayMaxHeapOperations(ways));
    return heapSort;
  }

  public LessCompareHeapSort lessCompareHeapSort() {
    LessCompareHeapSort heapSort = new LessCompareHeapSort("lessCompare");
    heapSort.setHeapOperations(operationsFactory.noExchangeMaxHeapOperations());
    return heapSort;
  }
}
