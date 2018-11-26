package mergesort.sequential_recursive;

public class MergeSortParallelRec implements Sort {

	static int MAX_THREAD_NUMBER = 2; 
	static Integer used_thread_number = 0; 
	
	synchronized static int incUsedThreadNumber()
	{
		return used_thread_number++; 
	}
	
	int[] array; 
	
	public long sort(int[] array) {
		this.array = array; 
		long time=System.currentTimeMillis();
		
		MergeSortThread mergeSortThread = new MergeSortThread(0, array.length -1);
		
		incUsedThreadNumber(); 
		Thread th = new Thread(mergeSortThread); 
		th.start(); 
		
		try {
			th.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} 
		return (System.currentTimeMillis()-time);
	}
	
	public long sortWithThreads(int[] array, int c) {
		MAX_THREAD_NUMBER=c;
		this.array = array; 
		long time=System.currentTimeMillis();
		
		MergeSortThread mergeSortThread = new MergeSortThread(0, array.length -1);
		
		incUsedThreadNumber(); 
		Thread th = new Thread(mergeSortThread); 
		th.start(); 
		
		try {
			th.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} 
		return (System.currentTimeMillis()-time);
	}
	
	private class MergeSortThread implements Runnable
	{
		
		int lower, upper; 
		
		public MergeSortThread(int lower, int upper) {
			this.lower = lower; 
			this.upper = upper; 
		}
		

		public void run() {
//			System.out.println("RUN THREAD: " + this.hashCode());
			this.mergeSort(this.lower, this.upper); 
		}
		
		
		
		private void mergeSort(int lower, int upper)
		{
			int middle = (lower + upper) / 2; 
			
			if(lower < upper)
			{
				Thread thLeft = null;  

				if(incUsedThreadNumber() < MAX_THREAD_NUMBER)
				{
					MergeSortThread mergeSortThreadLeft = new MergeSortThread(lower, middle);
					thLeft = new Thread(mergeSortThreadLeft); 
					thLeft.start(); 
				}
				else
				{
					this.mergeSort(lower, middle); 
				}
				
				
				
				Thread thRight = null;  
				if(incUsedThreadNumber() < MAX_THREAD_NUMBER)
				{
					MergeSortThread mergeSortThreadRight = new MergeSortThread(middle+1, upper);
					thRight = new Thread(mergeSortThreadRight); 
					thRight.start(); 
				}
				else
				{
					this.mergeSort(middle+1, upper); 
				}

				try {
					if(thLeft != null)
						thLeft.join();
					
					if(thRight != null)
						thRight.join(); 
					
					merge(lower, middle, upper); 

				} catch (InterruptedException e) {
					e.printStackTrace();
				} 
				
			}
		}
		
		private void merge(int lower, int middle, int upper)
		{
			// the tmpArray is created separately with every new call of merge
			int[] tmpArray = new int[array.length]; 
			// also, all of the following variables are independent 
			int left = lower; 
			int right = middle+1;
			int i = lower; 

			
			while(true)
			{
				
				if(left <= middle && ((right <= upper && array[left] < array[right]) || right > upper ))
				{
					tmpArray[i] = array[left];
					i++;
					left++; 
				}
				
				else if(right <= upper && ((left <= middle && array[right] <= array[left]) || left > middle))
				{
					tmpArray[i] = array[right]; 
					i++; 
					right++; 
				}
				
				else
				{
					break; 
				}
			}
			
			for(int j = lower; j <= upper; j++)
			{
				array[j] = tmpArray[j]; 
			}
			
		}

	}


	
	

}
