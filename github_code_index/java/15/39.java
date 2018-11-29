
public class RodCuttingProblem 
{
	public int count;
		
	public int findMaximum(int i, int j)
	{
		return i >= j? i: j;
	
	}
	
	public int cutRod(int[] array, int[] p, int n)
	{
		count++;
		
		if(n < 0 || n == 0)
			return 0;
				
		int max = -1;
		int i;

//normal recursion
/*		for (int i = 1; i <= n; i++) 
		{
			max = findMaximum(max, p[i-1] + cutRod(p, n-i));
		}
*/
		
//dynamic programming
		for (i = 1; i <= n; i++) 
		{
			if(array[n-i] == -1)
			{
				array[n-i] = cutRod(array, p, n-i);
				max = findMaximum(max, p[i-1] + array[n-i]);
			}	
			else
			{
				max = findMaximum(max, p[i-1] + array[n-i]);
			}
		}
		
		return max;
	}
	
	
	public static void main(String[] args) 
	{
		RodCuttingProblem cuttingProblem = new RodCuttingProblem();
		int[] p  = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
		int[] array = new int[11];
		
		for (int i = 0; i < 11; i++) 
		{
			array[i] = -1;
		}
				
		array[10] = cuttingProblem.cutRod(array, p, 10);
		System.out.println(array[10]);
		
		for (int i = 0; i < 11; i++) 
 		{
			System.out.print(i + "| ");
		}	
		System.out.println();
		for (int i = 0; i < array.length; i++) 
 		{
			System.out.print(array[i] + "| ");
		}
		
		System.out.println("\nnumber of iterations: " + cuttingProblem.count);
	}

}
