
import java.util.Scanner;

public class JavaQuickSort {
    static Scanner myScanner = new Scanner(System.in);
    public static void main(String[] args) {
        int n = myScanner.nextInt();
        int[] array = new int[n];
        for (int i = 0; i < array.length ; i++) {
            array[i]=myScanner.nextInt();
        }
        QuickSort.sort(array);
        for (int i = 0; i < array.length; i++) {
            System.out.print(array[i]+" ");
        }
        int low = 0, high = array.length -1,key;
        System.out.println("whch vlu u wnt to serch?");
        key = myScanner.nextInt();
        while(low<=high){
            int mid = (low+high)/2;
            if(array[mid]==key){
                System.out.println("Value Found: "+key);
                break;
            }
            if(array[mid] > key) high = mid-1;
            else if(array[mid] < key) low = mid+1;
            else{
                System.out.println("Value Not found!!");
            }
        }
    }
}
