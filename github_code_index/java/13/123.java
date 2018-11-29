
public class Suchen {
	
	static int findMax(int[] arr)
	{
		int max = 0;
		for (int i = 1; i < arr.length; i++)
		{
			if (arr[i] > arr[max])
				max = i;
		}
		return max;
	}
	
	static int findElement(int[] arr, int element)
	{
		int pos = 0;
		boolean isFound = false;
		while (!isFound && (pos < arr.length))
		{
			if (arr[pos] == element)
				isFound = true;
			else
				pos++;
		}
		if (isFound)		// if (isFound == true)
			return pos;
		else
			return -1;
	}
	
	static int findElementbinary(int[] arr, int element)
	{
		boolean isFound = false;
		int left = 0, right = arr.length - 1, middle = 0;
		int z = 0;
		while (!isFound && (left <= right))
		{
			middle = (left + right) / 2;
			z++;
			if (arr[middle] == element)
				isFound = true;
			else
			{
				if (arr[middle] > element)
					right = middle - 1;
				else
					left = middle + 1;
			}
		}
		System.out.println("Es wurde beim BinarySearch " + z +
				". Mal zugegriffen");
		if (isFound)		// if (isFound == true)
			return middle;
		else
			return -1;
	}
	
	static void bubbleSort(int[] arr)
	{
		int temp = 0;
		for (int i = arr.length - 1; i >= 0; i--)
			for (int j = 0; j <= i-1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
	}
	
	static void insertionSort(int[] arr)
	{
		int temp = 0, j = 0;
		for (int i = 1; i < arr.length; i++)
		{
			temp = arr[i];
			j = i;
			while ((j > 0) && (arr[j-1] > temp))
			{
				arr[j] = arr[j-1];
				j--;
			}
			arr[j] = temp;
		}
	}
	
	static void shellSort(int[] arr)
	{
		int temp = 0, h = 1, j = 0;
		do
			h = 3 * h + 1;
		while (h < arr.length);
		do {
			h = h / 3;
			for (int i = h; i < arr.length; i++)
			{
				temp = arr[i];
				j = i;
				while ((j >= h) && (arr[j-h] > temp))
				{
					arr[j] = arr[j-h];
					j = j - h;
				}
				arr[j] = temp;
			}
		} while ( h != 1);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] arg = {3, 6, 2, 12, 1, 15, 13, 9};
		int erg, find = 13;
		erg = findMax(arg);
		System.out.println("Index mit groesstem Wert: " + erg + 
				" Wert im Array: " + arg[erg]);
		erg = findElement(arg, find);
		if (erg == -1)
			System.out.println("Die Zahl " + find + 
					" wurde nicht im Array gefunden!");
		else
			System.out.println("Index mit gefundenem Wert: " + erg + 
					" Wert im Array: " + arg[erg]);
		
		shellSort(arg);
		System.out.println("Nach Shell-Sort:");
		for (int i=0; i < arg.length; i++)
			System.out.print(arg[i] + " ");
		System.out.println();
		
		insertionSort(arg);
		System.out.println("Nach Insertion-Sort:");
		for (int i=0; i < arg.length; i++)
			System.out.print(arg[i] + " ");
		System.out.println();
		
		bubbleSort(arg);
		System.out.println("Nach Bubble-Sort:");
		for (int i=0; i < arg.length; i++)
			System.out.print(arg[i] + " ");
		System.out.println();
		
		erg = findElementbinary(arg, find);
		if (erg == -1)
			System.out.println("Die Zahl " + find + 
					" wurde nicht im Array gefunden!");
		else
			System.out.println("Index mit gefundenem Wert: " + erg + 
					" Wert im Array: " + arg[erg]);
	}
}
