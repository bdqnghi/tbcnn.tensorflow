package idv.workshop.homework;

/*
 * 選擇排序是反覆進行「搜尋數列中得最小值,將它與最左邊得數對調」的操作
 * 搜尋數列中最小的值使用線性搜尋
 * 不過這邊直接跟右邊的比較
 *
 * 參考: https://yotsuba1022.gitbooks.io/data-structure-note/content/2.1.1-selection-sort.html
 */

public class SelectionSort {

    private static void swap(int[] input, int i, int j) {
        int tmp = input[i];
        input[i] = input[j];
        input[j] = tmp;
    }

    public static int[] sortDesc(int[] input) {
        for (int i = 0; i < input.length - 1; i++) {
            for (int j = i + 1; j < input.length; j++) {  //基本上跟泡沫排序只差在這行吧
                if (input[i] < input[j]) {
                    swap(input, i, j);
                }
            }
        }
        return input;
    }

    public static int[] sortAsc(int[] input) {
        for (int i = 0; i < input.length - 1; i++) {
            for (int j = i +1; j < input.length; j++) {  //一樣差在這行
                if (input[i] > input[j]) {
                    swap(input, i ,j);
                }
            }
        }
        return input;
    }
}
