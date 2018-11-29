/**
 * 
 */
package sorting;

/**
 * @author Mursil
 *
 */
public class InsertionSort {
	
	/**
	 * Insertion sort using Marker based approach. 
	 * <br>Although this is simple algo, but make sure to map the concept of marker 
	 * in a piece of paper before writing this code 
	 * @see <a href="https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort"></a>
	 * @param data
	 */
	public static void sortAscending(int[] data){
	
		int marker, markerValue, inner;
		if(data == null)
			throw new NullPointerException();
		
		for(marker = 1; marker<data.length;marker ++)
		{
			markerValue = data[marker];// Saving the marker value in a tmp variable
			
			for(inner = marker;inner>0 ; inner--)
			{
				if(markerValue < data[inner-1])
					data[inner]=data[inner-1];
				else
					break;
					
					
			}
			data[inner] = markerValue;//Copying the markerValue into the new position. 

			
			
		}
		
		
	}

	public static void sortDescending(int[] data){

		
		int marker, markerValue, inner;
		if(data == null)
			throw new NullPointerException();
		
		for(marker = 1; marker<data.length;marker ++)
		{
			markerValue = data[marker];// Saving the marker value in a tmp variable
			
			for(inner = marker;inner>0 ; inner--)
			{
				if(markerValue > data[inner-1])
					data[inner]=data[inner-1];
				else
					break;
					
					
			}
			data[inner] = markerValue;
			
			
		}
		
	}

}

