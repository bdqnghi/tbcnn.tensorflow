import java.util.*;

public class Classwork {
    static void print(Object obj) {
    System.out.println(obj);
    }
    public static void main(String[] args) {
        int [] [] arr1 = {
                          {1,2,3,},
                          {4,5,6},
                          {7,8,9,}
                        };
        int [] [] arr2 = {
                          {1,0,0},
                          {0,1,0},
                          {0,0,1}
                        };
        int [] [] arr3 = new int [arr1.length][arr1[0].length];
        int arraylength = arr1.length;
        int subarraylength = arr1[1].length;
        for ( int x = 0; x < arraylength;x++) {
            for (int z = 0; z < subarraylength; z++) {
                int temp = 0;
                int sum = 0 ;
                for ( int p = 0; p < subarraylength; p++) {
                    temp = arr1[z][p] * arr2[p][x];
                    sum += temp;
                    arr3[z][x] = sum;
                }
            }
            
        }
        for (int [] k : arr3) {
            System.out.print(Arrays.toString(k));
            System.out.print("\n");
        }
    }
}
  