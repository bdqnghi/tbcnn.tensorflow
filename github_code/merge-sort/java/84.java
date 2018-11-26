class MergeSort {

  void mergeSort(int[] arr, int l, int r) {
    if (l < r) {
      int mid = (l + r) / 2;
      mergeSort(arr, l, mid);
      mergeSort(arr, mid + 1, r);
      merge(arr, l, r, mid);
    }
  }

  void merge(int[] arr, int l, int r, int mid) {
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int L[] = new int [n1];
    int R[] = new int [n2];

    for (int i = 0; i < n1; i++)
      L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
      R[j] = arr[mid + j + 1];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        arr[k] = L[i];
        i++;
      } else {
        arr[k] = R[j];
        j++;
      }
      k++;
    }

    while (i < n1) {
      arr[k] = L[i];
      i++;
      k++;
    }

    while (j < n2) {
      arr[k] = R[j];
      j++;
      k++;
    }
  }

  void printArray(int[] arr) {
    for (int i = 0; i < arr.length; i++) {
      System.out.print(arr[i] + " ");
    }
    System.out.println();
  }

  public static void main(String[] args) {
    MergeSort sort = new MergeSort();
    int[] arr = {37, 27, 43, 3, 9, 82 , 10};
    sort.mergeSort(arr, 0, arr.length - 1);
    sort.printArray(arr);
  }
}

// mergeSort(arr, 0, 6);  l = 0, r = 6, mid = 3
// mergeSort(arr, 0, 3);  l = 0, r = 3, mid = 1
// mergeSort(arr, 0, 1);  l = 0, r = 1, mid = 0
// mergeSort(arr, 0, 0);  l = 0, r = 0, mid = 0
//
// mergeSort(arr, 0, 6);  l = 0, r = 6, mid = 3
// mergeSort(arr, 0, 3);  l = 0, r = 3, mid = 1
// mergeSort(arr, 0, 1);  l = 0, r = 1, mid = 0
// // mergeSort(arr, 0, 0);  l = 0, r = 0, mid = 0
// mergeSort(arr, 1, 1)   l = 1, r = 1, mid = 1
//
// mergeSort(arr, 0, 6);  l = 0, r = 6, mid = 3
// mergeSort(arr, 0, 3);  l = 0, r = 3, mid = 1
// mergeSort(arr, 0, 1);  l = 0, r = 1, mid = 0
// // mergeSort(arr, 0, 0);  l = 0, r = 0, mid = 0
// // mergeSort(arr, 1, 1) l = 1, r = 1, mid = 1
// merge(arr, 0, 1, 0);
//
// mergeSort(arr, 0, 6);  l = 0, r = 6, mid = 3
// mergeSort(arr, 0, 3);  l = 0, r = 3, mid = 1
// // mergeSort(arr, 0, 1);  l = 0, r = 1, mid = 0
// // mergeSort(arr, 0, 0);  l = 0, r = 0, mid = 0
// // mergeSort(arr, 1, 1) l = 1, r = 1, mid = 1
// // merge(arr, 0, 1, 0);
// mergeSort(arr, 2, 3);
