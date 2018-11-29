import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Created by maggie on 6/20/16.
 */
public class Sort_HeapSort {
    //heapSort can be implemented by Priority Queue

    public class IntegerDescendingComparator implements Comparator<Integer>{
        @Override
        public int compare(Integer x, Integer y){
            if(x > y) return -1;
            if(x < y) return 1;
            return 0;
        }

    }


    public int[] heapSort(int[] num){
        Comparator<Integer> comparator = new IntegerDescendingComparator();

        if(num.length == 0 || num.length == 1) return num;
        int[] res = new int[num.length];
        PriorityQueue pq = new PriorityQueue(comparator);
        for(int i = 0; i < num.length; i++){
            pq.add(num[i]);
        }
        for(int i = 0; i < num.length;i++){
            int tmp = (Integer)pq.remove();
            res[i] = tmp;
            System.out.print(res[i]+ ",");
        }

        return res;

    }

    public static void main(String[] args){
        int[] arr = new int[]{2,3,1,3,8,4};
        Sort_HeapSort t = new Sort_HeapSort();
        t.heapSort(arr);
    }

}
