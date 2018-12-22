package sorting;

class HeapSortJava {

  int[] doHeapSort(int[] arr) {
    int n = arr.length;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapify(arr, n, i);
    }
    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
      int temp = arr[0];
      arr[0] = arr[i]; // arr[0] == root
      arr[i] = temp;
      // call max heapify on the reduced heap
      heapify(arr, i, 0);
    }
    return arr;
  }

  // To heapify a subtree rooted with node i which is
  // an index in arr[]. n is size of heap
  private void heapify(int arr[], int n, int i) {
    // 08 11 09 02 10 16 -> 08 11 16 02 10 09 -> 08 11 16 02 10 09 -> 11 08 16 02 10 09
    // -> 16 08 11 02 10 09
    int largest = i; // initialize largest as root
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
      largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
      largest = r;
    }
    // if not same position, replace element
    if (largest != i) {
      int swap = arr[i];
      arr[i] = arr[largest];
      arr[largest] = swap;
      // Recursively heapify the affected sub-tree
      heapify(arr, n, largest);
    }
  }

}
