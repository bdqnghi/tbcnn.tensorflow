package javaPractice.algo.sort;

/**
 *
 Java Program to Sort an Array of 10 Elements Using Heap Sort Algorithm
 This is a java program to perform Heap Sort. There are two types of heaps.
 First one is Max heap and second one is Min heap. Heap (Max/Min) is a special type of binary tree.
 The roots of the max heap is greater than its child roots.
 Other heap is Min heap it is also a special type of heap which has minimum root than his child.
 We can sort the array values using heap sorting algorithm. In this algorithm the heap build is used to rebuild the heap.
 In this example we sorting all elements of an array. The complexity of the heap sort is O(n.log(n))
 since the method build heap takes time O(n) and each of the (n-1) calls to maxheap takes time O(lg n).

 Here is the source code of the Java Program to Sort an Array of 10 Elements Using Heap Sort Algorithm.
 The Java program is successfully compiled and run on a Windows system. The program output is also shown below.
 */
import java.util.Random;



public class Heapsort

{

    private static int[] a;

    private static int   n;

    private static int   left;

    private static int   right;

    private static int   largest;



    public static void buildheap(int[] a)

    {

        n = a.length - 1;

        for (int i = n / 2; i >= 0; i--)

        {

            maxheap(a, i);

        }

    }



    public static void maxheap(int[] a, int i)

    {

        left = 2 * i;

        right = 2 * i + 1;

        if (left <= n && a[left] > a[i])

        {

            largest = left;

        } else

        {

            largest = i;

        }



        if (right <= n && a[right] > a[largest])

        {

            largest = right;

        }

        if (largest != i)

        {

            exchange(i, largest);

            maxheap(a, largest);

        }

    }



    public static void exchange(int i, int j)

    {

        int t = a[i];

        a[i] = a[j];

        a[j] = t;

    }



    public static void sort(int[] a0)

    {

        a = a0;

        buildheap(a);



        for (int i = n; i > 0; i--)

        {

            exchange(0, i);

            n = n - 1;

            maxheap(a, 0);

        }

    }



    public static void main(String[] args)

    {

        int N = 20;

        int[] sequence = new int[N];

        Random random = new Random();



        System.out.println("Heap Sort Test");



        for (int i = 0; i < N; i++)

            sequence[i] = Math.abs(random.nextInt(100));



        System.out.println("The original sequence is: ");

        for (int i = 0; i < sequence.length; i++)

            System.out.print(sequence[i] + " ");



        sort(sequence);



        System.out.println("\nThe sorted sequence is: ");

        for (int i = 0; i < sequence.length; i++)

            System.out.print(sequence[i] + " ");

    }

}

/*
$ javac Heapsort.java
$ java Heapsort

Heap Sort Test
The original sequence is:
3 72 19 49 3 20 91 47 6 25 71 94 15 81 86 66 29 20 21 82
The sorted sequence is:
3 3 6 15 19 20 20 21 25 29 47 49 66 71 72 81 82 86 91 94
 */
