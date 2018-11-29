package util.sort;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by ych0112xzz on 2017/1/16.
 */
public class Bucket extends Sort {

    public static void main(String[] args) {
        int[] a = {21, 13, 56, 11, 1, 42, 4, 3, 64, 13, 0, 35, 11, 7, 17, 26, 120, 112, 365, 956, 212, 213};
        sort(a, 6700);
        assert isSorted(a);
        show(a);
    }

    public static void sort(int[] a, int step) {
        int len = a.length;
//        求最大最小值
        int min = a[0];
        int max = a[0];
        for (int i = 1; i < len; i++) {
            max = max >= a[i] ? max : a[i];
            min = min <= a[i] ? min : a[i];
        }

        //构建通
        ArrayList<ArrayList<Integer>> bucket = new ArrayList<>();
        for( int i = min ; i <= max ; i = i + step ){
            ArrayList<Integer> list = new ArrayList<Integer>();
            bucket.add(list);
        }

        //将数据放入桶里
        for(int i=0;i<len;i++) {
            int index=(a[i]-min)/step;
            bucket.get(index).add(a[i]);
        }

        //对每个桶里的元素排序，可以递归或其他排序，在此采用插入
        for(int i=0;i<bucket.size();i++) {
           insert(bucket.get(i));
        }

        // 将排序后的桶放回数组
        int k = 0;
        for(int i=0;i<bucket.size();i++) {
            for(int j=0;j<bucket.get(i).size();j++) {
                a[k++] = bucket.get(i).get(j);
            }
        }
    }

    private static void insert(ArrayList<Integer> list) {

        for(int i=1;i<list.size();i++) {
            int key = list.get(i);
            for(int j=i;j>0&&less(list.get(j),list.get(j-1));j--) {
                int tmp = list.get(j);
                list.set(j, list.get(j-1));
                list.set(j - 1, tmp);
            }
        }

    }

    public static boolean isSorted(int[] a) {
        for (int i = 1; i < a.length; i++) {
            if (less(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }


    public static void show(int a[]) {
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
    }
}
