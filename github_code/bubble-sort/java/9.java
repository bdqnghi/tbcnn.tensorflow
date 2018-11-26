import java.io.*;
import java.util.*;

public class Solution {

    public static void bubbleSort(int arr[]) {
        int swaps = 0;
        int temp = 0;
        int lastSorted = arr.length - 1;

        for(int n = 0; n < arr.length; n++) {
            for(int i = 0; i < lastSorted; i++) {
                if(arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    swaps++;
                }
            }
            lastSorted--;
        }

        System.out.println("Array is sorted in " + swaps + " swaps.");
        System.out.println("First Element: " + arr[0]);
        System.out.println("Last Element: " + arr[arr.length - 1]);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int arr[] = new int[n];

        in.nextLine();
        for(int i = 0; i < n; i++) arr[i] = in.nextInt();

        bubbleSort(arr);
    }
}
