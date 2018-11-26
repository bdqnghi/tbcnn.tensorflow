package Algorithm;

/**
 * Created by tonytan on 12/1/2017.
 *
 * Bucket sort: cost most memory
 */
public class BucketSort {

    static int[] data = {1,2,7,4,6,3,9};//assume all data < 10
    static int[] bucket = new int[10];

    public static void bucketSort(int[] data){
        for (int i=0; i<data.length; i++){
            bucket[data[i]] = data[i];
        }
    }

    public static void main(String[] args){
        bucketSort(data);
        for (int i:bucket) {
            if (i==0) continue;
            System.out.print(i);
        }
    }
}
