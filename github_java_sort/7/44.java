import java.util.Arrays;

public class Shellsort {
    static int[] gaps = {701, 301, 132, 57, 23, 10, 4, 1};
    static int[] unsorted = {80, 62, 45, 12, 52, 61, 76, 22, 95, 7, 2, 16, 8, 85, 17, 38, 25, 48, 60, 96};

    
    public int[] sort(int[] list) {
        for(int gap: gaps) {
            for (int i = gap; i < list.length; i+=1) {
                int j = i;
                int current = list[i];
                for (; j >= gap && list[j-gap] > current; j-=gap) {
                    list[j] = list[j-gap];
                }
                list[j] = current;
            }
        }
        return list;
    }

    public static void main(String[] args) {
        Shellsort sorter = new Shellsort();
        System.out.println(Arrays.toString(sorter.sort(unsorted)));
        return;
    }
}
