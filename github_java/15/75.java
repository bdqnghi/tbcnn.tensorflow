package dp;

public class RodCutting {
    public static void main(String[] args) {
        int a[] = {0,3,5,8,9,10,17,17,20};
        int max = getMaxweight(8,a);
        System.out.println("max is"+max);
    }

    private static int getMaxweight(int n, int[] a) {
        int size = a.length , max = Integer.MIN_VALUE;
        int[] memoize = new int[size];
        for(int i = 0; i < size ; i++) {
            max = a[i];
            for(int k = 0; k <= i/2; k++) {
                max = Math.max(max, memoize[k]+memoize[i-k]);
            }
            memoize[i] = max;
        }
        return n>size?memoize[size]:memoize[n];
    }
}
