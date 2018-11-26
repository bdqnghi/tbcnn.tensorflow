/**
 * Laura Davis CIS 260 903
 * This program demonstrates the selection sort algorithm for an array.
 *
 */
public class JavaSelectionSort 
{
	public static void main(String[] args)
	{
		int[] values = {5, 7, 2, 8, 9, 1};
		
		//print the unsorted array
		System.out.println("The unsorted values: ");
		for (int i = 0; i < values.length; i++)
		{
			System.out.print(values[i] + " ");
		}
		System.out.println();
		
		//sort the array
		selectionSort(values);
		
		//print the sorted array
		System.out.println("The sorted values: ");
		for (int i = 0; i < values.length; i++)
		{
			System.out.print(values[i] + " ");
		}
		System.out.println();
		
		lowest(values);
		
	}//end of main
	
	/**
	 * The selectionSort method finds the lowest value in the nested for loop 
	 * and then sorts them with each iteration or the main for loop. 
	 * @param array
	 */
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
					}//end if
					
				}//end nested for
	
				//reset minIndex to startScan (0) and sets minValue to the first box in the array
				array[minIndex] = array[startScan];
				array[startScan] = minValue;
				
			}//end main for
		
	}//end of selectionSort
	
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

}//end of class

