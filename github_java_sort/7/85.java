package cn.summerchill.sort;


class DataWrapShellSort implements Comparable<DataWrapShellSort> {
    int data;
    String flag;

    public DataWrapShellSort(int data, String flag) {
        this.data = data;
        this.flag = flag;
    }

    public String toString() {
        return data + flag;
    }

    
    public int compareTo(DataWrapShellSort dw) {
        return this.data > dw.data ? 1 : (this.data == dw.data ? 0 : -1);
    }
}

public class ShellSort {
    public static void shellSort(DataWrapShellSort[] data) {
        System.out.println("开始排序：");
        int arrayLength = data.length;
        
        int h = 1;
        
        while (h <= arrayLength / 3) {
            h = h * 3 + 1;
        }
        while (h > 0) {
            System.out.println("===h的值:" + h + "===");
            for (int i = h; i < arrayLength; i++) {
                
                DataWrapShellSort tmp = data[i];
                
                
                if (data[i].compareTo(data[i - h]) < 0) {
                    int j = i - h;
                    
                    for (; j >= 0 && data[j].compareTo(tmp) > 0; j -= h) {
                        data[j + h] = data[j];
                    }
                    
                    data[j + h] = tmp;
                }
                System.out.println(java.util.Arrays.toString(data));
            }
            h = (h - 1) / 3;
        }
    }

    public static void main(String[] args) {
        DataWrapShellSort[] data = { new DataWrapShellSort(9, ""), new DataWrapShellSort(-16, ""), new DataWrapShellSort(21, "*"), new DataWrapShellSort(23, ""),
                new DataWrapShellSort(-30, ""), new DataWrapShellSort(-49, ""), new DataWrapShellSort(21, ""), new DataWrapShellSort(30, "*"),
                new DataWrapShellSort(30, ""), };
        System.out.println("排序之前：\n" + java.util.Arrays.toString(data));
        shellSort(data);
        System.out.println("排序之后：\n" + java.util.Arrays.toString(data));
    }
}
