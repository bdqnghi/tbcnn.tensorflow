/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sort_time;

import static java.lang.Math.pow;

/**
 *
 * @author Blizius
 */
public class Sort_time {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        double [] randomInsertSortTime = new double [7];
        double [] randomInsertBinarySortTime = new double [7];
        double [] randomQuickSortTime = new double [7];
        double [] randomHeapSortTime = new double [7];
        double [] nearlyRandomInsertSortTime = new double [7];
        double [] nearlyRandomInsertBinarySortTime = new double [7];
        double [] nearlyRandomQuickSortTime = new double [7];
        double [] nearlyRandomHeapSortTime = new double [7];
        double [] sortedInsertSortTime = new double [7];
        double [] sortedInsertBinarySortTime = new double [7];
        double [] sortedQuickSortTime = new double [7];
        double [] sortedHeapSortTime = new double [7];
        
        for (int k = 2; k < 9; k++){                        
            randomInsertSortTime [k-2] = SortTime(k,1,1);
            nearlyRandomInsertSortTime [k-2] = SortTime(k,2,1);
            sortedInsertSortTime [k-2] = SortTime(k,3,1);
            randomInsertBinarySortTime [k-2] = SortTime(k,1,2);
            nearlyRandomInsertBinarySortTime [k-2] = SortTime(k,2,2);
            sortedInsertBinarySortTime [k-2] = SortTime(k,3,2);
            randomQuickSortTime [k-2] = SortTime(k,1,3);
            nearlyRandomQuickSortTime [k-2] = SortTime(k,2,3);
            sortedQuickSortTime [k-2] = SortTime(k,3,3);
            randomHeapSortTime [k-2] = SortTime(k,1,4);
            nearlyRandomHeapSortTime [k-2] = SortTime(k,2,4);
            sortedHeapSortTime [k-2] = SortTime(k,3,4);
            System.out.format("%f %f %f %f %f %f %f %f %f %f %f %f\n",randomInsertSortTime [k-2],nearlyRandomInsertSortTime [k-2],
            sortedInsertSortTime [k-2], randomInsertBinarySortTime [k-2], nearlyRandomInsertBinarySortTime [k-2],
            sortedInsertBinarySortTime [k-2], randomQuickSortTime [k-2], nearlyRandomQuickSortTime [k-2], 
            sortedQuickSortTime [k-2], randomHeapSortTime [k-2], nearlyRandomHeapSortTime [k-2],
            sortedHeapSortTime [k-2]);
        }        
    }

    /**
     * generování náhodného pole
     *
     * @param length délka pole
     * @return náhodné pole intů
     */
    public static int[] rndArray(int length) {
        int[] array = new int[length];
        for (int i = 0; i < length; i++) {
            array[i] = rnd(length);
        }
        return array;
    }

    /**
     * generování seřazeného pole
     *
     * @param length délka pole
     * @return seřazené pole intů
     */
    public static int[] sortedArray(int length) {
        int[] array = new int[length];
        array[0] = (int) (Math.random() * 100) + 1;
        for (int i = 1; i < length; i++) {
            array[i] = array[i - 1] + (int) (Math.random() * 100) + 1;
        }
        return array;
    }

    /**
     * generování 2% náhodného pole
     *
     * @param length délka pole
     * @return téměř seřazené pole intů (2 % prvků náhodné)
     */
    public static int[] almostSortedArray(int length) {
        int[] array = new int[length];
        array[0] = (int) (Math.random() * 100) + 1;
        for (int i = 1; i < length; i++) {
            array[i] = array[i - 1] + (int) (Math.random() * 100) + 1;
        }
        for (int i = 50; i < length; i += 50) {
            array[i] = rnd(length);
        }
        return array;
    }

    /**
     * generování náhodného intu
     *
     * @param length délka pole
     * @return náhodný int od 0 do hodnoty délky pole
     */
    public static int rnd(int length) {
        return (int) (Math.random() * length);
    }
    /**
     * třídící funkce, algoritmus Insert Sort
     * @param array pole k setřídění
     */
    public static void insertSort(int [] array){        
        for (int i = 1; i < array.length; i++){
            int a = array[i];
            for (int k = i; k > 0 && a <= array[k-1]; k--){                               
                array[k] = array[k-1];
                array[k-1] = a;                                              
            }                      
        }
    }
    /**
     * třídící funkce, algoritmus Insert Binary Sort
     * @param array pole k setřídění
     */
    public static void insertBinarySort (int [] array){
        for (int i = 1; i < array.length; i++){
            int a = array[i];            
            int p = i-1;
            int l = 0;
            while (l <= p){
                int k = (l+p)/2;
                if (a > array[k]){
                    l = k+1;
                }
                else{
                    p = k-1;
                }
            }
            int j = i;
            while (j > l){
                array[j] = array[j-1];
                j--;
            }   
            array[l] = a;
        }
    }
    /**
     * třídící funkce, algoritmus Quick Sort
     * @param array pole k setřídění
     * @param l index levého konce pole
     * @param p index pravého konce pole
     */
    public static void quickSort(int []array, int l, int p){
        int i = l;
        int j = p;
        int piv = array[((l+p)/2)];
        while (i <= j){
            while (piv > array[i])
                i++;
            while (piv < array[j])
                j--;
            if (i <= j){
                int a = array[i];
                array[i] = array[j];
                array[j] = a;
                i++;
                j--;
            }
        }
        if (l < j)
            quickSort(array, l, j);
        if (i < p)
            quickSort(array, i, p);
    }
    /**
     * třídící funkce, algoritmus Heap Sort
     * @param array pole k setřízení
     */
    public static void heapSort(int []array){
        int []heap = new int [array.length + 1];
        for (int i = 1; i < heap.length; i++){
            heap [i] = array[i-1];
            fixHeapUp(heap, i);
        }
        for (int i = heap.length-1; i > 1; i--){              
            array[i-1] = heap[1];
            heap[1] = heap[i];
            fixHeapDown(heap, i);
            if (i == 2){
                array[0] = heap[2];
            }
        }           
    }
    /**
     * oprava haldy nahoru
     * @param heap vstupní halda (pole)
     * @param i index aktuálně přidávaného prvku do haldy
     */
    public static void fixHeapUp (int []heap, int i){
        while (i > 1 && heap[i] < heap[i/2]){
            int a = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = a;
            i = i/2;
        }
    }
    /**
     * oprava haldy dolů
     * @param heap vstupní halda (pole)
     * @param i aktuální délka nesetříděné haldy
     */
    public static void fixHeapDown(int []heap, int i){
        int j = 1;  //index rodiče
        while (2*j < i){
            int k = 2*j;    //index potomka
            if ((k <= i) && (heap[k] > heap[k+1])){
                k++;                
            }
            if (heap[k] < heap[j]){
                int a = heap[j];
                heap[j] = heap[k];
                heap[k] = a;                
            }
            else{                
                break;
            }
            j = k;            
        }        
    }
    /**
     * měření časů jednotlivých třízení jednotlivých typů polí pro různé délky
     * @param k mocnina desíti, pro délku pole a rozdělení na krátké a dlouhé pole
     * @param type typ pole, zda se bude generovat náhodné - 1, téměř náhodné - 2
     *  a setřízené - 3
     * @param algor typ algoritmu, který se použije. 1 - Insert Sort, 2- Insert Binary Sort,
     * 3 - QuickSort, 4 - Heap Sort
     * @return hodnotu průměrného času třídění daného algoritmu nad danýmc typem pole pro danou délku pole
     */
    public static double SortTime(int k, int type, int algor){
        int length = (int)pow(10,k);
        if (k < 5){
            double time = 0;
            for(int i = 0; i < 50; i++){
                int[] array = new int [length];
                if (type == 1)
                    array = rndArray(length);
                else if (type == 2)
                    array = almostSortedArray(length);
                else
                    array = sortedArray(length);
                
                if (algor == 1){
                    double t0 = System.nanoTime();
                    insertSort(array);
                    time += System.nanoTime() - t0;
                }
                else if (algor == 2){
                    double t0 = System.nanoTime();
                    insertBinarySort(array);
                    time += System.nanoTime() - t0;
                }
                else if (algor == 3){
                    double t0 = System.nanoTime();
                    quickSort(array, 0, length-1);
                    time += System.nanoTime() - t0;
                }
                else {
                    double t0 = System.nanoTime();
                    heapSort(array);
                    time += System.nanoTime() - t0;
                }
            }
            return time/50;
        }
        else{
            double time = 0;
            for(int i = 0; i < 3; i++){
                int[] array = new int [length];
                if (type == 1)
                    array = rndArray(length);
                else if (type == 2)
                    array = almostSortedArray(length);
                else
                    array = sortedArray(length);
                
                if (algor == 1){
                    double t0 = System.nanoTime();
                    insertSort(array);
                    time += System.nanoTime() - t0;
                }
                else if (algor == 2){
                    double t0 = System.nanoTime();
                    insertBinarySort(array);
                    time += System.nanoTime() - t0;
                }
                else if (algor == 3){
                    double t0 = System.nanoTime();
                    quickSort(array, 0, length-1);
                    time += System.nanoTime() - t0;
                }
                else {
                    double t0 = System.nanoTime();
                    heapSort(array);
                    time += System.nanoTime() - t0;
                }
            }
            return time/3;
        } 
    }
}
