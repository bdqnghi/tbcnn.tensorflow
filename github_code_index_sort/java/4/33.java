public class HeapSortJava {

    public void heapify(int arr[], int n, int root) {
        int largestNumber = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < n && arr[left] > arr[largestNumber]) {
            largestNumber = left;
        }

        if (right < n && arr[right] > arr[largestNumber]) {
            largestNumber = right;
        }

        if (largestNumber != root) {
            int swap = arr[root];
            arr[root] = arr[largestNumber];
            arr[largestNumber] = swap;
            heapify(arr, n,largestNumber);
        }
    }

    public void sort(int arr[]) {
        int len = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i >= 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify(arr, i, 0);
        }
    }

    static void printArray(int arr[]) {
        int len = arr.length;
        for (int i = 0; i < len; i++) {
            System.out.println(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String args[]) {
        int arr[] = {34, 33, 75, 44, 89, 01};
        int len = arr.length;

        HeapSort heapSort = new HeapSort();
        heapSort.sort(arr);

        System.out.println("Sorted array is ");
        printArray(arr);
    }
}