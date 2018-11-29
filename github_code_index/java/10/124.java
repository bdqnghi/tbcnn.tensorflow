package algorithms.sort;

public class SortBubbleSort {
	
	public static void main(String args[]){
		
		int arr[] = {30,6,2,3,4,6,7,8,10,20,11,5,5,30};
		
	    int n = arr.length;
	    
	    
	    for(int i=0; i< n; i++){
	    	
	    	for(int j=1; j<(n-i); j++){    // largest value should come to the end each time
	    		
	    		if( arr[j-1] > arr[j]){            
	    			
	    			int temp = arr[j-1];
	    			
	    			arr[j-1]= arr[j];
	    			
	    			arr[j]= temp;
	    		}
	    		   		
	    	}
	    }
	    
	  System.out.println(" Sorted Array: " );  
	  
	  for(int m=0; m <n; m++){
		  
		  System.out.print(" "+ arr[m]);
	  }
	  			
	}

}
