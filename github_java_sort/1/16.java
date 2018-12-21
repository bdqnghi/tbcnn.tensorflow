




import java.util.*;
public class homework1{
	
	 public static final int N = 200000; 
     public static final int K = 400;
     public static void main(String[ ] args){
     int i;                      
     int[ ] merge = new int[N];   
     int[ ] ins = new int[N];  
     int[ ] melez = new int[N];  
     Random r = new Random();	 
     
     for (i=0;i<N;i++) {
    	 merge[i]=r.nextInt(N);
    	 ins[i]=merge[i]; 
    	 melez[i]=merge[i]; 
    	 }
    System.out.println("Values Before the sort:");
	System.out.print("---------------------"+"  	 ");
	System.out.print("---------------------"+"   ");
	System.out.println("---------------------"+"");
     for(i = 0; i <merge.length; i++){ 
    	if (i==0){
    		System.out.print("PURE-MERGE-SORT ARRAY 	 ");
    		System.out.print("INSERTION-SORT ARRAY 	 ");
    		System.out.println("MELEZ-MERGE-SORT ARRAY 	 ");
    		System.out.print("---------------------"+"  	 ");
    		System.out.print("---------------------"+"   ");
    		System.out.println("---------------------"+"");
    	}
        System.out.print(merge[i]+"				");
        System.out.print(ins[i]+"				");
        System.out.println(melez[i]+"	");
          }
         System.out.println();  
         
     Calendar pure1 = Calendar.getInstance();	
     long s1=pure1.getTimeInMillis();			
     mergeSortPure(merge,0, N-1); 
     Calendar pure2 = Calendar.getInstance();
     long s2=pure2.getTimeInMillis();			
     long s3=s2-s1;  
         
     Calendar inst1 = Calendar.getInstance();	
     long s4=inst1.getTimeInMillis();			
     insertionSort(ins,N-1);
     Calendar inst2 = Calendar.getInstance();	
     long s5=inst2.getTimeInMillis();			
     long s6=s5-s4;
         
     Calendar melez1 = Calendar.getInstance();	
     long s7=melez1.getTimeInMillis();			
     mergeSortMelez(melez,0, N-1); 
     Calendar melez2 = Calendar.getInstance();
     long s8=melez2.getTimeInMillis();			
     long s9=s8-s7;   
     System.out.print("Values after PURE-MERGE-SORT:\n");
       for(i = 0; i <merge.length; i++){ 
    	if ((i%30)==0)System.out.println();
    	System.out.print(merge[i]+"  ");
      	}
     	System.out.println(" ");
     System.out.print("Values after INSERTION-SORT:\n");
     for(i = 0; i <ins.length; i++){ 
        if ((i%30)==0)System.out.println();
       	System.out.print(ins[i]+"  ");
      	}
        System.out.println();
     System.out.print("Values after MELEZ MERGE-SORT:\n");
     for(i = 0; i <melez.length; i++){ 
        if ((i%30)==0)System.out.println();
       	System.out.print(melez[i]+"  ");
      	}
        System.out.println();    
        System.out.println ("RUNNING TIME for MERGE-SORT : " + s3 + " msec");
        System.out.println ("RUNNING TIME for INSERTION-SORT : " + s6 + " msec");
        System.out.println ("RUNNING TIME for MELEZ MERGE-SORT : " + s9 + " msec");     
}

public static void mergeSortPure(int array[],int lo, int n){
     int low = lo;
	 int high = n;   
	 if (low>=high) {
	    return;
	 }
	 int middle = (low + high) / 2;
	 
	 mergeSortPure(array, low, middle);  
	 
	 mergeSortPure(array, middle + 1, high); 
	 
     int end_low = middle;
	 int start_high = middle + 1;
	 while ((low <= end_low) && (start_high <= high)) {
		 if (array[low] < array[start_high]) {
	        low++;
	        } else {
	               int Temp = array[start_high];
	               for (int k = start_high- 1; k >= low; k--) {
	               array[k+1] = array[k];
	               }
	               array[low] = Temp;
	               low++;
	               end_low++;
	               start_high++;
	     }
     }
   } 
   
public static void mergeSortMelez(int array[],int lo, int n){
     int A; 
	 int low = lo;
	 int high = n;  
	 int middle = (low + high) / 2;
	 A=high-low; 
	 
	 if (A<=K) {
		 insertionSort(array,high);
		 return;
	 }
  	 
	 mergeSortMelez(array, low, middle);  
	 
	 mergeSortMelez(array, middle + 1, high);
  	 
	 int end_low = middle;
	 int start_high = middle + 1;
	 while ((low <= end_low) && (start_high <= high)) {
		 if (array[low] < array[start_high]) {
			 low++;
		 } else {
			    int Temp = array[start_high];
			    for (int k = start_high- 1; k >= low; k--) {
				  array[k+1] = array[k];
			    }
			    array[low] = Temp;
			  	low++;
			  	end_low++;
			  	start_high++;
         }
    }
} 
    	
    
static void insertionSort(int[] arr,int lo) {
     int i, j, newValue;
     for (i = 1; i <= lo; i++) {
          newValue = arr[i];
          j = i;
          while (j > 0 && arr[j - 1] > newValue) {
                  arr[j] = arr[j - 1];
                  j--;
           }
           arr[j] = newValue;
     }
  }
}

