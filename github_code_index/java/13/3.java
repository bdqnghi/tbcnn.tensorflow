package alg4th.sort;

public class ShellSort {
    Sortable sortable;

    public ShellSort(Sortable sortable) {
        this.sortable = sortable;
    }

    private void sort(Comparable[] t) {
        int n = t.length;
        int h = 1;
        while (h < n/3) {
            h = h * 3 + 1;
        }

        while (h >= 1) {
            for (int i = h; i < n; i++) {
                for (int j = i; j >= h && sortable.less(t[j], t[j - h]); j -= h) {
                    sortable.exhg(t, j, j - h);
                    System.out.print("i= " + i + " j=" + j + "  ");
                    sortable.show(t);
                }
            }
            h /= 3;
        }
    }


    public static void main(String[] args) {

        ShellSort shellSort = new ShellSort(new Sortable());
        String[] array = {"bed", "bug", "dad", "yes", "zoo", "all", "bad", "yet"};

        shellSort.sort(array);
        shellSort.sortable.show(array);
        shellSort.sortable.assertIsSorted(array);
    }
}
