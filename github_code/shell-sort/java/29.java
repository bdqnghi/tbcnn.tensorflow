package algorithm.sort;

public class ShellSort {
    /*private void shellsort(int[] a) {
        int d = a.length / 2;
        while (true) {
            for (int i = 0; i < d; i++) {
                for (int j = i; j + d < a.length; j += d) {
                    int temp;
                    if (a[j] > a[j + d]) {
                        temp = a[j];
                        a[j] = a[j + d];
                        a[j + d] = temp;
                    }
                }
            }
            if (d == 1) {
                break;
            }
            d--;
        }
    }*/

    private void shellsort(int[] a) {
        int d = a.length / 2;
        while (true) {
            for (int i = 0; i < a.length; i++) {
                for (int j = i; j + d < a.length; j += d) {
                    int temp;
                    if (a[j] > a[j + d]) {
                        temp = a[j];
                        a[j] = a[j + d];
                        a[j + d] = temp;
                    }
                }
            }
            d--;
            if (d == 1) {
                break;
            }
        }
    }


    public static void main(String[] args) {
        int[] a = {11, 21, 42, 62, 1, 4, 2, 52, 73, 36, 98};
        ShellSort shellSort = new ShellSort();
        //shellSort.shellsort(a);
        for (int arr : a) {
            System.out.println(arr);
        }
    }
}
