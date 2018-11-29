/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package Sortings;

/**
 *
 * @author Ana Lucía Hernández (17138). Luis Delgado (17187)
 */
public class HeapSort {
    private Integer[] arrayHeap;
    private Integer comparable;
    
    public HeapSort()
    {
        comparable =0;
    }
           /**
     * 
     * @param o: objeto con el cual se desea comparar la instancia. 
     * @return devuelve 0 si son iguales, -1 si comparable es menor y 1 si es mayor que el argumento
     */ 
    public int compareTo(Object o) {
        Integer num1 = (Integer) o;
        return comparable.compareTo(num1); // devuelve 0 si son iguales, -1 si comparable es menor y 
        //1 si es mayor que el argumento
    }
    /**
     * Método que comienza a separar el array y a montar subtrees. 
     * @param arr: array de números enteros a ordenar
     * CODIGO EXTRAIDO DE: https://www.geeksforgeeks.org/heap-sort/ 
     */
    public void heapSort(Integer arr[])
    {
        int n = arr.length;
 
        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
 
        // One by one extract an element from heap
        for (int i=n-1; i>=0; i--)
        {
            // Move current root to end
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
 
            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
        arrayHeap = arr;
    }
 
    /**
     * Para realizarle el heap al subtree que se encuentra en el índice i.
     * @param arr: array a ordenar
     * @param n: tamaño del heap
     * @param i: índice del array
     * CODIGO EXTRAIDO DE: https://www.geeksforgeeks.org/heap-sort/ 
     */
    void heapify(Integer arr[], int n, int i)
    {
        int largest = i;  // Initialize largest as root
        int l = 2*i + 1;  // left = 2*i + 1
        int r = 2*i + 2;  // right = 2*i + 2
 
        // If left child is larger than root
        if (l < n && arr[l] > arr[largest])
            largest = l;
 
        // If right child is larger than largest so far
        if (r < n && arr[r] > arr[largest])
            largest = r;
 
        // If largest is not root
        if (largest != i)
        {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;
 
            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }
    public Integer[] getHeapArray()
    {
        return arrayHeap;
    }
}
