
public class ShellSort 
{
	private Comparable[] data;
	private static int counter = 0;
	
	public ShellSort(Comparable[] x)
	{
		data = new Comparable[x.length];
		for(int i = 0; i < x.length; i++)
		{
			this.data[i] = x[i];
		}
	}
	
	public void sortUsing(int[] h)
	{
		sort(this.data, h);
	}
	
	static boolean less(Comparable v, Comparable w)
	{
		return(v.compareTo(w) < 0);
	}
   
	public static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.println(a[i]);
        }
    }
	private static void exch(Comparable[] data, int i, int j)
	{
		Comparable t = data[i];
		data[i] = data[j];
		data[j] = t;
	}
	public static int getCount()
	{
		return counter;
	}
	public static void sort(Comparable[] a, int[] b)
	{
		int N = a.length;
		int[] incs = b;
		
		for(int k = 0; k < incs.length; k++)
		{
			int h = incs[k];
			counter++;
			for(int i = h; i < N; i++)
			{
				
				for(int j = i; j >= h; j-=h)
				{
					if(less(a[j], a[j-h]))
					{
						exch(a, j, j-h);
					}
					else
						break;
						
				}
			}
		}
	}
	
}
