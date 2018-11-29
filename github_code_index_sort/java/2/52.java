/**
 * Created by maggie on 6/18/16.
 */
public class Sort_MergeSort {
    public int[] mergeSort(int[] num){
        if(num.length == 0 || num.length == 1) return num;
        int left = 0;
        int right = num.length-1;
        mergeSortHelper(num, left, right);
        System.out.print( "[");
        for(int i =0; i< num.length; i++){
           System.out.print(num[i] + ",");
        }
        System.out.print( "]");
        return num;
    }

    // divided array and sorted array
    public void mergeSortHelper(int[] num, int left, int right){
        if(left < right){
            int middle = left + (right - left)/2;
            mergeSortHelper(num, left, middle);
            mergeSortHelper(num, middle+1, right);
            merge(num,left,middle,right);
        }
    }

    // this method is aiming at sort two sorted list into on list
    public void merge(int[] num, int left, int middle, int right){
        int[] tmp = new int[right+1 - left];

        int j = middle+1;
        int i = left;
        int k = 0;
        while(i<= middle && j<= right){
            if(num[i] < num[j]){
                tmp[k] = num[i];
                i++;

            }else{
                tmp[k] = num[j];
                j++;
            }

            k++;
        }
        while(k < tmp.length){
            if(i <= middle){
                tmp[k] = num[i];
                i++;

            }
            if(j<= right){
                tmp[k] = num[j];
                j++;
            }
            k++;
        }

        for(int e = 0; e< tmp.length; e++){
            num[left+e] = tmp[e];
        }
    }


    public static void main(String[] args){
        //int[] arr = new int[]{2,2,3,1,6,7,5,6,7,4,8};
        int[] arr = new int[]{2,3,1,3,8,4};
        Sort_MergeSort t = new Sort_MergeSort();
        //t.merge(arr,0,1,3);
        t.mergeSort(arr);
    }
}
