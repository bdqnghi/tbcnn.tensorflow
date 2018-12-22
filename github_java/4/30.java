import java.util.Arrays;
import java.util.Random;
public class insertionsort
{
    
    /**
     * Ordena un arreglo utilizando el orden de inserción
     * 
     * @param  A    arreglo de enteros
     * @return     max  elemento mas grande del arreglo
     */
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

      /**
     * crea un arreglo aleatorio
     * 
     * @param  n    entero
     * @return     array arreglo aleatorio
     */
    public static int[] crearArreglo(int n) {
        int max = 10000;
        int[] array = new int[n];
        Random generator = new Random();
        for (int i =0; i<n; i++)
            array[i] = generator.nextInt(max);
        return array;
    } 

     /**
     * Toma el tiempo que dura en ejecutarce el metodo ArrayMax
     * 
     * @param  n    entero
     * @return     estimatedTime long
     */
    public static long tomarTimepo(int n){
        int [] arreglo = crearArreglo(n);
        long startTime = System.currentTimeMillis();
        InsertionSort(arreglo);
        long estimatedTime = System.currentTimeMillis() - startTime;
        return estimatedTime;
    }
}
