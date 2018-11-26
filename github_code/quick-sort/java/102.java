public class sort {

    public static void main(String[] args) {
        int N = 1;
        System.out.println(N + " nums");
        
        for (int x = 1; x <= 8; x++, N *= 10) {
            int[] ary = new int[N];
            for (int i = 0; i < ary.length; i++) {
                ary[i] = new Double(Math.random() * 10.0).intValue();
            }
            System.out.println("======sorting " + N + " nums======");

            long s = System.currentTimeMillis();
            quicksort(ary, 0, ary.length - 1);
            long e = System.currentTimeMillis();
            System.out.println("quicksort time:" + (e - s));
        }
    }

    public static void quicksort(int[] a, int start, int end) {
        if (start >= end)
            return;

        int pavot = a[start];
        int i = start;
        int j = end;

        while (i < j) {
            while (i < j && a[j] > pavot)
                j--;
            while (i < j && a[i] <= pavot)
                i++;
            if (i != j) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
        if (i == j) {
            int t = a[start];
            a[start] = a[i];
            a[j] = t;
        }
        quicksort(a, start, i - 1);
        quicksort(a, i + 1, end);
    }
}
