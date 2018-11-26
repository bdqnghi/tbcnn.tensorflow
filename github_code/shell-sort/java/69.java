package com.cl.dataStructures.advancedsord;

/**
 * Created by cl on 2017/9/18.
 * 希尔排序
 * <p>
 * 在插入排序的基础上修改而来
 */
public class ShellSort {
    private long[] theArray;
    private int nElems;

    public ShellSort(int nElems) {
        theArray = new long[nElems];
        this.nElems = 0;
    }

    void insert(long value) {
        theArray[nElems++] = value;
    }

    void display() {
        for (int i = 0; i < nElems; i++) {
            System.out.print(theArray[i] + " ");
        }
        System.out.println();
    }

    void shellSort() {
        int inner, outer;
        long temp;
        int h = 1;
        while (h <= nElems / 3)
            h = h * 3 + 1;
        while (h > 0) {
            for (outer = h; outer < nElems; outer++) {
                temp = theArray[outer];
                inner = outer;
                while (inner > h - 1 && theArray[inner - 1] >= temp) {
                    theArray[inner] = theArray[inner - h];
                    inner -= h;
                }
                theArray[inner] = temp;
            }
            h = (h - 1) / 3;
        }
    }

    public static void main(String[] args) {
        int max = 10;
        ShellSort shellSort = new ShellSort(max);
        for (int i = 0; i < max; i++) {
            shellSort.insert((long) (Math.random()*99));
        }
        shellSort.display();
        shellSort.shellSort();
        shellSort.display();
    }
}

