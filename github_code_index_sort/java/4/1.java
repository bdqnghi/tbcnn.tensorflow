
public class Heapsort {
    public static void sort(Comparable[] a) {
        int N = a.length-1;
        
        // The root nodes in a heap starts from N/2
        for(int i=N/2; i>=1; i--) {
            sink(a, i, N);
        }
        
        // Heap ignores a[0]
        for(int i=N; i>=1; i--) {
            swap(a, 1, i);
            sink(a, 1, i-1);
        }
    }
    
    private static void sink(Comparable[] mPQ, int i, int N) {
        while((2*i <= N && less(mPQ, i, 2*i)) || 
                (2*i+1 <= N && less(mPQ, i, 2*i+1))) {
            
            int largerChild = 2*i;
            if(largerChild<N && less(mPQ, 2*i, 2*i+1)) {
                largerChild = 2*i+1;
            } 
            
            // exchange parent with the larger child
            swap(mPQ, largerChild, i);
            i = largerChild;
        }      
    }
    
    public static boolean isSorted(Comparable[] a) {
        // Heapsort ignores a[0]
        for(int i=2; i<a.length; i++) {
            if(less(a, i, i-1)) {
                return false;
            }
        }
        return true;
    }
    
    private static void swap(Comparable a[], int i, int j) {
        Comparable tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    
    private static boolean less(Comparable[] a, int i, int j) {
        return a[i].compareTo(a[j]) < 0;
    }
    
    public static void printArray(Comparable a[]) {
        for(int i=0; i<a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }
}
