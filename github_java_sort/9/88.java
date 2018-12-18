
public class JavaSelectionSort 
{
	public static void main(String[] args)
	{
		int[] values = {5, 7, 2, 8, 9, 1};
		
		
		System.out.println("The unsorted values: ");
		for (int i = 0; i < values.length; i++)
		{
			System.out.print(values[i] + " ");
		}
		System.out.println();
		
		
		selectionSort(values);
		
		
		System.out.println("The sorted values: ");
		for (int i = 0; i < values.length; i++)
		{
			System.out.print(values[i] + " ");
		}
		System.out.println();
		
		lowest(values);
		
	}
	
	
	public static void selectionSort(int[] array)
	{
		int startScan, index, minIndex, minValue;
		
		for (startScan = 0; startScan < (array.length-1); startScan++)
			{
				minIndex = startScan;
				minValue = array[startScan];
				
				for (index = startScan + 1; index < array.length; index++)
				{			
					if (array[index] < minValue)
					{
						minValue = array[index];
						minIndex = index;
					}
					
				}
	
				
				array[minIndex] = array[startScan];
				array[startScan] = minValue;
				
			}
		
	}
	
	public static void lowest(int[] values)
	{
		int lowest = values[0];

		for (int i = 1; i < values.length; i++)
		{
			if (values[i] < lowest)
			{
				lowest = values[i];
			}
		}
		System.out.println("The lowest value is: " + lowest);
	}

}

