

public class ShellSort {
	
	public static int[] array;
	private static int n;
	long time = 0;
	
	
	public ShellSort(int[] array) {
		
		ShellSort.array = array;
		n = array.length;
		
	}

	
	public void shellSort_1() {
		
		long begin = System.nanoTime();
        int step = 0;
        
        while(step <= n) {
        	step = 3 * step + 1;
        }

        if (step == 1 || step == 4) {
        	step = 1;
        }
        else {
        	for (int i = 0; i < 2; i++) {
        		step = (step - 1) / 3;
        	}
        }
        
        
        for (int shell = step; shell > 0; shell = (shell - 1) / 3) {
        	
            for (int i = shell; i < n; i += 1) {

                int temp = array[i];
                int j;
                
                for (j = i; j >= shell && array[j - shell] > temp; j -= shell) {
                	array[j] = array[j - shell];
                }

                array[j] = temp;
            }
        }
        
        long end = System.nanoTime();
        time = end - begin;
		
	} 
	
	
	public void shellSort_2() {
		
		long begin = System.nanoTime();
		int[] stepSet = {1, 5, 17, 53, 149, 373, 1123, 3371, 10111, 30341};
		int step = 0;
		int incr = 0;
		
        while(stepSet[incr] <= n) {
        	incr++;
        }
        
        if (stepSet[incr] == 1 || stepSet[incr] == 5) {
        	step = stepSet[0];
        }
        else {
        	for (int i = 0; i < 1; i++) {
        		step = stepSet[incr-2];
        	}
        }
        
        int shell = step;
        int stop = 0;
        
        while (shell >= 1 && stop != 2) {
        	
        	for (int i = shell; i < n; i += 1) {

        		int temp = array[i];
        		int j;
        		
        		for (j = i; j >= shell && array[j - shell] > temp; j -= shell) {
        			array[j] = array[j - shell];
        		}

        		array[j] = temp;
        		
        	}

        	if (incr < 1) {
        		incr = 0;
        		stop++;
        	}
          
        	shell = stepSet[incr--];
        	
        }
        
        long end = System.nanoTime();
        time = end - begin;
		
	} 

	
	public void shellSort_3() {
		
		long begin = System.nanoTime();
		int[] stepSet = {1, 10, 30, 60, 120, 360, 1080, 3240, 9720, 29160};
		int step = 0;
		int incr = 0;
		
        while(stepSet[incr] <= n) {
        	incr++;
        }
        
        if (stepSet[incr] == 1 || stepSet[incr] == 10) {
        	step = stepSet[0];
        }
        else {
        	for (int i = 0; i < 1; i++) {
        		step = stepSet[incr-2];
        	}
        }
        
        int shell = step;
        int stop = 0;
        
        while (shell >= 1 && stop != 2) {
        	
        	for (int i = shell; i < n; i += 1) {

        		int temp = array[i];
        		int j;
        		
        		for (j = i; j >= shell && array[j - shell] > temp; j -= shell) {
        			array[j] = array[j - shell];
        		}

        		array[j] = temp;
        		
        	}

        	if (incr < 1) {
        		incr = 0;
        		stop++;
        	}
        	
        	shell = stepSet[incr--];
          
        }
        
        long end = System.nanoTime();
        time = end - begin;
	
	} 
	
	
	public void shellSort_4() {
		
		long begin = System.nanoTime();
		int[] stepSet = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};
		int step = 0;
		int incr = 0;
		
        while(stepSet[incr] <= n) {
        	incr++;
        }
        
        if (stepSet[incr] == 1 || stepSet[incr] == 6) {
        	step = stepSet[0];
        }
        else {
        	for (int i = 0; i < 1; i++) {
        		step = stepSet[incr-2];
        	}
        }
        
        int shell = step;
        int stop = 0;
        
        while (shell >= 1 && stop != 2) {
        	
        	for (int i = shell; i < n; i += 1) {

        		int temp = array[i];
        		int j;
        		
        		for (j = i; j >= shell && array[j - shell] > temp; j -= shell) {
        			array[j] = array[j - shell];
        		}

        		array[j] = temp;
        		
        	}

        	if (incr < 1) {
        		incr = 0;
        		stop++;
        	}
        	
        	shell = stepSet[incr--];
          
        }
        
        long end = System.nanoTime();
        time = end - begin;
	
	} 
	
	
	public long getTime() {
		
		return time;
		
	} 
	
	
	public void displayArray() {
		
		for (int i = 0; i < n; i++) {
			System.out.print(array[i] + " ");
		}
		
	} 

} 
