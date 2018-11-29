import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by maggie on 6/18/16.
 */
public class Sort_BucketSort {
    //let's do a more complicated bucket sort
    //1. Decide size of every bucket (In simple bucket sort, by default, every bucket size is 1)
    //2. Traverse original array, putting elements from array into bucket
    //3. sorting every bucket using insert sort
    //4. Creating a new array to put sorted elements
    //5. Traverse buckets, put elements of every bucket in ascending order

    public int[] bucketSort(int[] num, int bucketSize){
        if(num.length == 0 || num.length == 1) return num;
        //1. Decide size of every bucket -- find maxValue and minValue
        int max = Integer.MIN_VALUE;
        int min = Integer.MAX_VALUE;
        for(int i = 0; i < num.length; i++){
            if(max < num[i]){
                max = num[i];
            }
            if(min > num[i]){
                min = num[i];
            }
        }
        System.out.println("max:" + max + ";" + " min:" + min);
        int bucketCount = ((max - min)%bucketSize == 0)? (max - min)/bucketSize :(max - min)/bucketSize +1  ;
        //bucketCount is num of subList
        // elements in subList is unlimited
        List<List<Integer>> intermediate = new ArrayList<List<Integer>>(bucketCount);
        System.out.println("bucketCount: " + bucketCount);

        for(int i = 0; i < bucketCount; i++){
            intermediate.add(new ArrayList<Integer>());
        }
        for(int i = 0; i < num.length; i++){
            intermediate.get((num[i] - min)/bucketSize).add(num[i]);
        }

        // sort every subList
        int[] res = new int[num.length];
        int j = 0;
        for(int i = 0; i < bucketCount; i++){
            int[] tmp = new int[intermediate.get(i).size()];
            int k =0;
            for (Object o : intermediate.get(i)) {
                tmp[k] = (Integer)o;
                k++;
            }
            Arrays.sort(tmp);

            for(int c = 0; c < tmp.length;c++){
                res[j] = tmp[c];
                System.out.print(res[j]+ ",");
                j++;
            }
        }

        return res;

    }


    public static void main(String[] args){
        int[] arr = new int[]{2,3,1,3,8,4,5,6,6,7};
        Sort_BucketSort b = new Sort_BucketSort();
        b.bucketSort(arr,3);
    }





}
