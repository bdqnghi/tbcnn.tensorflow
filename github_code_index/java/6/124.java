

public class Sort_MergeSort {

    static int[] arr;

    public static void main(String[] args){

        arr = new int[6];
        for(int i=0; i<6; i++){
            arr[i] = (int)(Math.random()*100);
        }

        for(int x: arr){
            System.out.print(x+" ");
        }
        System.out.println();

        MergeSort(0, arr.length-1);

        for(int y: arr){
            System.out.print(y+" ");
        }
        System.out.println();

    }

    public static void MergeSort(int left, int right){

        if(left==right){
            return;
        }

        int mid = (left+right)/2;

        MergeSort(left, mid);
        MergeSort(mid+1, right);

        Merge(left, mid, right);

    }

    public static void Merge(int left, int mid, int right){

        int[] after = new int[right-left+1];
        int lb = left;
        int rb = mid+1;
        int count = 0;

        while(lb<=mid && rb<=right){
            if(arr[lb]<=arr[rb]){
                after[count++] = arr[lb++];
            }else{
                after[count++] = arr[rb++];
            }
        }

        while(lb<=mid){
            after[count++] = arr[lb++];
        }

        while(rb<=right){
            after[count++] = arr[rb++];
        }

        for(int i=0; i<after.length; i++){
            arr[left++] = after[i];
        }

    }

}
