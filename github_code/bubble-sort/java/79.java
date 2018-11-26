import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;


public class bubble {
	public void bubbleSort(int[] unsorted) 
	{
		boolean swap = false;
		int tempSwap;
		do
		{
			swap = false;
			
			for(int i=0; i< unsorted.length-1; i++)
			{
				if(unsorted[i] > unsorted[i+1]) {
					tempSwap = unsorted[i];
					unsorted[i] = unsorted[i+1];
					unsorted[i+1]=tempSwap;
					swap = true;	
				}
			}
		}
		while(swap);
	}
	public void printArray(int[] array) throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		
		for(int i = 0; i < array.length; i++)
			bw.write(array[i] + " "); 
		
		bw.write(" ");
		bw.flush();
	}
	public static void main(String[] args) throws IOException 
	{
		BufferedReader br = new BufferedReader (new InputStreamReader(System.in));
		int[] a = {2,12,4,65,3,8,4};
		String line = br.readLine();
		String[] numbers = line.split(",");
		int[] array = new int[numbers.length];
		for(int i = 0; i < numbers.length; i++)
			array[i] = Integer.parseInt(numbers[i]);
		
		
		bubble sort = new bubble();
		sort.printArray(array);
		sort.bubbleSort(array);
		sort.printArray(array);   

	}
}
