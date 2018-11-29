package com.wayne.algo.sort;

/**
 * Created by wayne on 2017/4/12.
 */
public class BubbleSort {

    private int[] array;
    private int size;
    private final int MAX = 10;

    public BubbleSort() {
        array = new int[MAX];
        size = 0;
    }

    public int[] getArray() {
        return this.array;
    }

    public void insert(int n) {
        if (size < MAX) {
            array[size++] = n;
        }
        else {
            return;
        }
    }

    public void sort() {
        for(int outter = size -1 ; outter > 1; outter--) {
            for (int inner = 0; inner < outter; inner++) {
                if ( array[inner] > array[inner+1]) {
                    swap( inner, inner+1);
                }
            }
        }
    }

    private void swap(int a, int b) {
        int temp = array[a];
        array[a] = array[b];
        array[b] = temp;

    }

    public String toString() {

        StringBuilder sbu = new StringBuilder();

        for (int i = 0; i < size; i++) {
            sbu.append(array[i] + "-");
        }

        return sbu.toString();
    }


    public static void main(String[] args) {

        BubbleSort bubbleSort = new BubbleSort();
        bubbleSort.insert(13 );
        bubbleSort.insert(10);
        bubbleSort.insert(35);
        bubbleSort.insert(15);
        bubbleSort.insert(25);
        bubbleSort.sort();
        System.out.println(bubbleSort);
    }
}
