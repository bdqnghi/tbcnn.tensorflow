package njupt.ch1.EX;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Arrays;

public class Quick {
	public static void sort(Comparable[] a){
		sort(a, 0, a.length-1);
	}
	
	private static void sort(Comparable[] a, int lo, int hi){
		if(hi <= lo){
			return;
		}
		int j = partition(a, lo, hi);
		sort(a, lo, j-1);  
		sort(a, j+1, hi);  
	}
	
	private static int partition(Comparable[] a, int lo, int hi){
		
		int i = lo, j = hi+1;    
		Comparable v = a[lo];    
		while(true){
			
			while(less(a[++i], v)){
				if(i == hi)
					break;
			}
			while(less(v, a[--j])){
				if(j == lo)
					break;
			}
			if (i >= j)
				break;
			exch(a, i, j);
		}
		exch(a, lo, j);   
		return j;         
	}
	
	private static boolean less(Comparable v, Comparable w){
		return v.compareTo(w) < 0 ;
		
	}
	
	private static void exch(Comparable[] a, int i, int j)
	{
		Comparable t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	
	private static void show(Comparable[] a){
		
		for(int i = 0; i < a.length; i++){
			System.out.print(a[i] + " ");
		}
		System.out.println();
	}
	
	public static void main(String[] args) {
		File file = new File("H:\\java_test_data\\test_data\\test_data.txt");
		String[] myArray = new String[20000];  
		
		int i = 0;
		try {
			FileReader fr = new FileReader(file);
			BufferedReader buf = new BufferedReader(fr);
            String readLine = "";
            while((readLine = buf.readLine()) != null){
                myArray[i] = readLine;
                i++;
            }
            buf.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		System.out.println(i);
		System.out.println(myArray.length);
		String[] a = new String[i];
        for(int j=0; j < i; j++){
        	a[j] = myArray[j];
        }
        
		
		long start = System.currentTimeMillis();
		sort(a);
		long end = System.currentTimeMillis();
		show(a);
		System.out.println(end-start);	
	}
}
