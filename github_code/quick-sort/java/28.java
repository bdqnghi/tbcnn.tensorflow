
public class Sort_QuickSort {

    static int[] arr;

    public static void main(String[] args){

        arr = new int[50];
        for(int i=0; i<50; i++){
            arr[i] = (int)(Math.random()*100);
        }

        for(int x: arr){
            System.out.print(x+" ");
        }
        System.out.println();

        quicksort(0, 49);

        for(int x: arr){
            System.out.print(x+" ");
        }
        System.out.println();
    }

    public static void quicksort(int left, int right){

        if(right-left<=0){
            return;
        }else{
            int partition = partition(left, right, arr[left]);
            quicksort(left, partition-1);
            quicksort(partition+1, right);
        }

    }

    public static int partition(int left, int right, int pivot){

        int leftMark = left;
        int rightMark = right+1;

        while(true){
            while(leftMark<right && arr[++leftMark]<pivot){}
            while(rightMark>left && arr[--rightMark]>pivot){}
            if(leftMark>=rightMark){
                break;
            }else{
                swap(leftMark, rightMark);
            }
        }
        swap(rightMark,left);
        return rightMark;

    }

    public static void swap(int a, int b){
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

}

