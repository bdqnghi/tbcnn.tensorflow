/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package radixsort_java;

/**
 *
 * @author Phi
 */
public class RadixSort_Java {

    /**
     * @param args the command line arguments
     */
    static int [] a = {99, 86, 48,61,93,62,91,94,41,67};
    static int size = 10;
    private static void radixSort(int maxDigit) {
        int b[][] = new int[10][10000];
        int len[] = new int[10];
        int h = 1;
        for (int i = 0; i < maxDigit; i++) {
            for (int j = 0; j < 10; j++) {
                len[j] = 0;
            }
            for (int j = 0; j < 10; j++) {
                int digit = a[j] / h % 10;
                b[digit][len[digit]++] = a[j];
            }
            int index = 0;
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < len[j]; k++) {
                    a[index++] = b[j][k];
                }
            }
            h *= 10;
        }
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        radixSort(2);
        for (int i = 0; i < size; i++) {
            System.out.print(a[i] + " ");
        }
    }
    
}
