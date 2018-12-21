package Sorting;

import java.util.Iterator;

































public class SelectionSort_JAVA {
    public static void sorting (int[] list, int n) {
        int i, j, least, temp;
        
        for (i = 0; i < n - 1; i++) {
            least = i;
            
            
            
            for (j = i + 1; j < n; j++) {
                if (list[j] < list[least]) {
                    least = j;
                }
            }
            
            
            if (i != least) {
                temp = list[i];
                list[i] = list[least];
                list[least] = temp;
            }
        }
    }
    
    public static void main(String[] args) {
        int test[]  = {10, 9, 2, 7, 80};
        
        sorting(test, test.length);
        
        for (int data : test) {
            System.out.print(data + ", ");
        }
    }
}
