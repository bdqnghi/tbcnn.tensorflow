package aeminium.shellsort;
import java.util.Random;
public class SeqShellSort {
	
	public static Integer[] data;
	
	public static int DEFAULT_SIZE  = 10000;
	
	SeqShellSort(){
		
		data = new Integer[DEFAULT_SIZE];
	}
	
	
    public static Integer[] InitializeColl(Integer[] data) {
	        
    	Random randGen = new Random();
	        
	        for (Integer i = 0; i < data.length; i++) {
	            data[i] = (randGen.nextInt());
	        }
	        return data;
	}
	public static void displayArray(Integer[] data) {
		for (int i = 0; i < data.length; i++) {
			System.out.println(""+ data[i]);
		}
	}
	public static void Sort(Integer[] data, Integer[] gaps)
    {
        for (Integer gap : gaps){
            
        	for (Integer i = gap; i < data.length; i++){
                Integer temp = data[i];
                Integer j = i;
                for (; j >= gap && data[j - gap] > temp; j -= gap)
                {
                    data[j] = data[j - gap];
                }
                data[j] = temp;
            }
        }
    }
	public static boolean isSorted(Integer[] data) {
        for (Integer i = 1; i < data.length; i++) {
            if (data[i-1] > data[i])
                return false;
        }
        return true;
    }
}
class Client{
	
	public static Integer[] gaps = new Integer[] {701,301,132,57,23,10,4,1};
	
	
	public static void main(String[] args) throws Exception{
		
		long start = System.nanoTime();
		
		SeqShellSort.InitializeColl(SeqShellSort.data); 
		SeqShellSort.displayArray(SeqShellSort.data); 
		if(!SeqShellSort.isSorted(SeqShellSort.data)){
			SeqShellSort.Sort(SeqShellSort.data,Client.gaps);
		}
		System.out.println("Sorted Array");
		long end = System.nanoTime();
    	long elapsedTime = end - start;
    	double ms = (double)elapsedTime / 1000000.0;
    	System.out.println(" Milli Seconds Time = "+ms);
	}
}


