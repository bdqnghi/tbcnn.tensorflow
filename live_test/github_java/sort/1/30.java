import java.util.Arrays;
import java.util.Random;
public class insertionsort
{
    
    
    public static void InsertionSort(int[] A)
    {
        int temp,j;
        for (int i = 0; i < A.length; i++)
        {
            j = i;
            while (j > 0 && A[j-1] > A[j])
            {
                temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                j = j-1;
            }           
        }
        System.out.println(Arrays.toString(A));
    }

      
    public static int[] crearArreglo(int n) {
        int max = 10000;
        int[] array = new int[n];
        Random generator = new Random();
        for (int i =0; i<n; i++)
            array[i] = generator.nextInt(max);
        return array;
    } 

     
    public static long tomarTimepo(int n){
        int [] arreglo = crearArreglo(n);
        long startTime = System.currentTimeMillis();
        InsertionSort(arreglo);
        long estimatedTime = System.currentTimeMillis() - startTime;
        return estimatedTime;
    }
}
