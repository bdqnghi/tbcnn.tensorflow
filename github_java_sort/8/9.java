

public class QuickSort {   
  
      
    
    public void sort(Integer[] array, int from, int end) {   
        quickSort(array, from, end);   
    }   
  
      
    private void quickSort(Integer[] array, int low, int high) {   
          
        if (low < high) {   
            
            
            
            int pivot = partition2(array, low, high);   
            
            
              
            quickSort(array, low, pivot - 1);   
            quickSort(array, pivot + 1, high);   
        }   
  
    }   
  
      
    private int partition1(Integer[] array, int low, int high) {   
        Integer pivotElem = array[low];
        
        int border = low;   
  
          
        for (int i = low + 1; i <= high; i++) {   
            
            if ((array[i].compareTo(pivotElem)) < 0) {   
                swap(array, ++border, i);
            }   
        }   
          
        swap(array, border, low);   
        return border;   
    }   
  
      
    private int partition2(Integer[] array, int low, int high) {   
        int pivot = low;
        
        while (true) {   
            if (pivot != high) {
                
                if ((array[high].compareTo(array[pivot])) < 0) {   
                    swap(array, high, pivot);   
                    
                    pivot = high;   
                } else {
                    high--;   
                }   
            } else {
                
                if ((array[low].compareTo(array[pivot])) > 0) {   
                    swap(array, low, pivot);   
                    
                    pivot = low;   
                } else {
                    low++;   
                }   
            }   
            if (low == high) {   
                break;   
            }   
        }   
        
        return pivot;   
    }   
  
      
    private int partition3(Integer[] array, int low, int high) {   
        int pivot = low;
        low++;   
        
        
  
        while (true) {   
            
            while (low < high) {   
                
                if ((array[low].compareTo(array[pivot])) >= 0) {   
                    break;   
                } else {
                    low++;   
                }   
            }   
  
            while (high > low) {   
                
                if ((array[high].compareTo(array[pivot])) < 0) {   
                    break;   
                } else {
                    high--;   
                }   
            }   
            
            if (low == high) {   
                break;   
            }   
  
            swap(array, low, high);   
        }   
  
        
        if ((array[pivot].compareTo(array[low])) > 0) {   
            
            swap(array, low, pivot);   
            pivot = low;   
        } else if ((array[pivot].compareTo(array[low])) <= 0) {   
            swap(array, low - 1, pivot);   
            pivot = low - 1;   
        }   
  
        
        return pivot;   
    }   
  
		  
    public void swap(Integer[] array, int i, int j) {   
        if (i != j) {
            Integer tmp = array[i];   
            array[i] = array[j];   
            array[j] = tmp;   
        }   
    } 
	
      
    public static void main(String[] args) {   
        Integer[] intgArr = { 5, 9, 1, 4, 2, 6, 3, 8, 0, 7 };  
        QuickSort quicksort = new QuickSort();   
        quicksort.sort(intgArr,0,intgArr.length-1);
        for(Integer intObj:intgArr){
			System.out.print(intObj + " ");
        }
    }   
}   
