public class QuickSortJava
{
	public static void main(String[] args)
	{
		int n=5;
		int[] numbers = new int[n];

		for(int i=0; i<numbers.length; i++)
			numbers[i]=(int)(Math.random()*n);
		
		System.out.println("Random numbers before sorting");

		for(int i=0; i<numbers.length; i++)
			System.out.println(numbers[i]);

		System.out.println();

		sort(numbers,0,n-1);

		System.out.println("Random numbers after sorting");

		for(int i=0; i<numbers.length; i++)
			System.out.println(numbers[i]);

	}

	public static void sort(int[] v, int left, int right)
	{
		int i, last;
		if(left>=right)
			return;
		//move pivot to the v[left]
		swap(v, left, rand(left, right));
		last=left;
		//partition 
		for(i=left+1; i<= right; i++)
			if(v[i]<v[left])
				swap(v, ++last, i);
		//restore pivot element
		swap(v, left, last);
		//recursively sort each part
		sort(v, left, last-1);
		sort(v, last+1, right);
	} 

	public static void swap(int[] v, int i, int j)
	{
		int temp;

		temp=v[i];
		v[i]=v[j];
		v[j]=temp;
	}
	
	public static int rand(int left, int right)
	{
		return left+(int)(Math.random()*(right-left+1));
	}
}
