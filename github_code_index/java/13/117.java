package sorting;

public class ShellSort {
    public static int ITERATION_COEFFICIENT = 2;

    public static void shellSort(int[] data) {
        for (int step = data.length / ITERATION_COEFFICIENT; step >= 1; step /= ITERATION_COEFFICIENT) {
            for (int i = 0; i < step; i++) {
                for (int j = i + step; j < data.length; j += step) {
                    if (data[j] < data[j - step]) {
                        int tmp = data[j];
                        int k = j - step;
                        for (; k >= 0 && data[k] > tmp; k -= step) {
                            data[k + step] = data[k];
                        }
                        data[k + step] = tmp;
                    }
                }
            }
        }
    }

    public static void shellSortOptim(int[] data) {
        int step = data.length / ITERATION_COEFFICIENT;
        for (; step >= 1; step /= ITERATION_COEFFICIENT) {
            for (int i = step; i < data.length; i++) {
                int tmp = data[i];
                int k = i - step;
                if (data[i] >= data[k]) {
                    continue;
                }
                for (; k >= 0 && data[k] > tmp; k -= step) {
                    data[k + step] = data[k];
                }
                data[k + step] = tmp;
            }
        }

    }
}
