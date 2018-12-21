import java.util.Random;

public class Insertion
    
{
    public static InsertionSortNode[] arr;

    

    public static void main(String[] args)
    {
	Random generator = new Random();
	
	int size = generator.nextInt(50);

	arr = new InsertionSortNode[size];

	int i = 0;
	
	while(i < arr.length)
	{
	    arr[i] = new InsertionSortNode();
	    arr[i].key = generator.nextInt(100);
	    i = i + 1;
	}

	printArray();
	
	insertionSort();

	printArray();
    }
    
    
    public static void insertionSort()
    
    {
	int i = 1;

	while 
	    
	    (i < arr.length)
	{
	    int j = i;
	    while
		
		(j > 0)
	    {
		if (arr[j].key < arr[j-1].key)
		{
		    InsertionSortNode tmp = arr[j];
		    arr[j] = arr[j-1];
		    arr[j-1] = tmp;
		}
		j = j - 1;
	    }
	    i = i + 1;
	}
    }

    public static void printArray()
    {
	int i = 0;

	while(i < arr.length)
	{
	    System.out.print(arr[i].key + " ");
	    i = i + 1;
	}

	System.out.println("");
    }
}
