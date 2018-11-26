import java.util.Arrays;
public class Heapsort {

    public static void Main(String[] args) {
        Heapsort object = new Heapsort();
        double[] array = {2, 4, -1, 2, 5, 20, 3, 9, -8, 12, -14, 23};
        System.out.println("Unsorted " + Arrays.toString(array));
        array = sort(array);
        System.out.println("Sorted " + Arrays.toString(array));
    }

    public static double[] sort(double[] input) {
        int length = input.length;
        reorder(input, length);
        int end = length - 1;
        while (end > 0) {

            double temp = input[end];
            input[end] = input[0];
            input[0] = temp;

            input = pushDown(input, 0, end - 1);

            end--;
        }
        return input;
    }

    public static double[] reorder(double[] input, int length) {
        int start = (count - 2) / 2;

        while (start >= 0) {
            input = pushDown(input, start, length - 1);
            start--;
        }
    }

    public static double[] pushDown(double[] input, int begin, int end) {
        int root = begin;
        while ((root * 2 + 1) <= end) {
            int child = root * 2 + 1;
            if (child + 1 <= end && input[child] < input[child + 1]) {
                child = child + 1;
            }
            if (input[root] < input[child]) {
                int temp = input[root];
                input[root] = input[child];
                input[child] = temp;
                root = child;
            } else {
                return input;
            }
        }
    }
}
