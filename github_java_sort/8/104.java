public class Quicksort{
	
	public static void main(String[] args) throws Exception {
		if (args.length == 0){														
			throw new Exception("Bitte einen Parameter zur Feldgröße eingeben");	
		}
		if (args.length > 1){
			throw new Exception("Zu viele Parameter eingegeben!");
		}
		int n ;
		try{
			n = Integer.parseInt(args[0]);											
		}
		catch(Exception e){ System.out.println("Bitte einen Integer Wert eingeben"); return;}
		if (n < 1){
			throw new Exception("Bitte einen positiven Integer Wert eingeben");		
		}
		int[] a = new int[n];									
		a = zufallBefüll(a);									
		long tStart = System.currentTimeMillis();				
		quicksort(a,0,a.length-1);								
		long tEnd = System.currentTimeMillis();
		long msecs = tEnd- tStart;
		if(isSorted(a)){										
			System.out.println("Array ist Sortiert");
		}
		System.out.println("Quicksort hat " + msecs +" Millisekunden gebraucht" );	

	}

	public static int[] zufallBefüll(int[] array){					
		java.util.Random numberGenerator = new java.util.Random();
		int zaehler = 0;
		while(zaehler < array.length){
			array[zaehler] = numberGenerator.nextInt();
			zaehler++;
		}
		return array;
	}
	public static void quicksort(int[] array, int l, int r){		
		int i = 0;
		int j = 0;
		int pivot = 0;
		int tmp = 0;
		if (l < r){
			i = l;
			j = r;
			pivot = array[(l + r) / 2];
			while (i <= j){
				assert isSorted(array,i);
				while(array[i] < pivot){					
					i++;
				}
				while(array[j] > pivot){					
					j--;
				}
				if (i <= j) {								
					tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;
					i++;
					j--;
				}
			}
			quicksort(array,l,j);
			quicksort(array,i,r);
		}
	}
	public static boolean isSorted(int[] array){			
		int counter = 0;
		while (counter < array.length - 1){
			if (array[counter] > array[counter+1]){
				return false;
			}
			counter++;
		}
		return true;
	}
	public static boolean isSorted(int[] array, int grenze){	
		int counter = 0;
		while (counter < grenze){
			if (array[counter] > array[counter+1]){
				return false;
			}
			counter++;
		}
		return true;
	}
}