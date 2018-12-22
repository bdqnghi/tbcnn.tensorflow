


public class ShellSort {

    public static void main(String[] args) {
        int[] a = {26,81,12,54,92,76,20,37,19,48};
        ShellSort shellSort = new ShellSort();
        System.out.println("---排序前---");
        shellSort.print(a);
        shellSort.sort(a);
        System.out.println("---排序后---");
        shellSort.print(a);
    }

    private void sort(int[] a) {
        int dk = a.length/2;
        while( dk >= 1  ){
            shellSort(a, dk);
            dk = dk/2;
        }

    }

    private void shellSort(int[] a, int dk) {
        for(int i=dk;i<a.length;i++){
            if(a[i]<a[i-dk]){
                int j;
                int x=a[i];
                a[i]=a[i-dk];
                for(j=i-dk;  j>=0 && x<a[j];j=j-dk){
                    a[j+dk]=a[j];
                }
                a[j+dk]=x;
            }

        }

    }


    private void print(int[] a) {
        for (int i = 0; i < a.length-1; i++) {
            System.out.print(a[i] + " ");
        }
    }
}
