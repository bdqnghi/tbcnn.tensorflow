

import java.util.Random;

public class Sort
{
    private static final int DEFAULT_SIZE = 30;
    
    public static void main(String[] args)
    {
        
        long startTime;
        double elapsedQuickSort;
        double elapsedHeapSort;
        int[] quick;
        
        
        if (args.length != 0)
        {
            try
            {
                quick = generateIntArray(Integer.parseInt(args[0]));
            } catch (NumberFormatException n)
            {
                System.out.println("'array size' argument must be greater than 0 and be an Integer.");
                System.out.printf("You entered as an argument: %s\n", args[0]);
                System.out.println("Continuing with default size of 30...");
                quick = generateIntArray(DEFAULT_SIZE);
            }
        }
        else
        {
            quick = generateIntArray(DEFAULT_SIZE);
        }
        
         
        int[] heap = quick; 

        int n = quick.length;

        printArray(quick, "original", 0);

        
        startTime = System.nanoTime();
        QuickSort.sort(quick, 0, n - 1); 
        elapsedQuickSort = (System.nanoTime() - startTime) * 1e-6; 

        printArray(quick, "quickSort", elapsedQuickSort);

        
        startTime = System.nanoTime();
        HeapSort.sort(heap); 
        elapsedHeapSort = (System.nanoTime() - startTime) * 1e-6; 

        printArray(heap, "heapSort", elapsedHeapSort);
    }

    
    private static int[] generateIntArray(int size)
    {
        Random rand = new Random(System.currentTimeMillis());
        int[] arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand.nextInt(size);
        }
        return arr;
    }

    
    private static void printArray(int a[], String sortMethod, double executionTime)
    {
        int n = a.length;

        switch (sortMethod)
        {
            case "quickSort":
            {
                System.out.printf("QuickSort took %.3f ms: ", executionTime);
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            case "heapSort":
            {
                System.out.printf("HeapSort took %.3f ms: ", executionTime);
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            case "original":
            {
                System.out.print("Original (Unsorted): ");
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            default:
            {
                System.out.println("Something went wrong...");
                break;
            }
        }
    }
}
