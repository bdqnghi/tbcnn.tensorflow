import java.util.*;

/**
 * Created by marne on 1/30/2017.
 */
public class BucketSort {

    public ArrayList<Integer> bucketSort(int[] array){

        ArrayList<Integer> result = new ArrayList<>();
        int min = array[0];
        int max = array[0];
        int bucket = 10;

        for(int i =1;i<array.length;i++){
            if(array[i] > max)
                max = array[i];
            if(array[i] < min)
                min = array[i];

        }

        //hash function
        int divider =(int) Math.ceil((max+1)/bucket);
        //Hashtable<Integer,ArrayList<Integer>> hashTable = new Hashtable<>(10);
        List<ArrayList<Integer>> bucketList = new LinkedList<ArrayList<Integer>>();

        for(int i=0;i<10;i++){
            bucketList.add(new ArrayList<Integer>());
        }


        int i=0;
//        for (Integer key :
//                hashTable.keySet()) {
//            hashTable.put(i++,new ArrayList<>());
//        }

        ArrayList<Integer> arrayList ;
        for(int h=0;h<array.length;h++){

            int index = array[h]/divider;
            if(bucketList.get(index) == null){
                bucketList.add(index,new ArrayList<Integer>(Arrays.asList(array[h])));
                //hashTable.put(index, new ArrayList<Integer>(Arrays.asList(array[h])));
            }
            else {
                bucketList.get(index).add((Integer) array[h]);
            }
            //arrayList.add(array[h]);

        }

        for (ArrayList<Integer> al :
                bucketList) {
            arrayList = al;

            int[] arrayInsertSort = new int[arrayList.size()];
            for(int a=0;a<arrayList.size();a++){
                arrayInsertSort[a] = arrayList.get(a).intValue();
            }
            InsertionSort insertionSort = new InsertionSort();
            int[] insertSortResult = insertionSort.sortIt(arrayInsertSort);

            for (int ele :
                    insertSortResult) {
                result.add(ele);
            }


        }





        return result;

    }

    public int[] bucketSort2(int[] array){
        int i,j,k;
        //int nBuckets = 10;
        int[] bucket = new int[10];

        for(j=0;j<bucket.length;j++){
            bucket[j] = 0;
        }

        for(i=0;i<array.length;i++){
            ++bucket[array[i]];
        }

        for(i=0,j=0;j<bucket.length;j++){
            for(k= bucket[j];k>0;--k){
                array[i++] = j;
            }
        }
        return array;
    }

    public static void main(String[] args){
        int[] arrayToSort = {9,61,7,8,61,3,5,99};

        //get a hash function

        BucketSort bucketSort = new BucketSort();
        ArrayList<Integer> resultList = bucketSort.bucketSort(arrayToSort);


        //int[] result = bucketSort.bucketSort2(arrayToSort);

//        for (int ele :
//                result) {
//            System.out.print(ele+" ");
//        }


        System.out.println();



        for (Integer element :
                resultList) {
            System.out.print(element+" ");
        }

        System.out.println();


    }
}
